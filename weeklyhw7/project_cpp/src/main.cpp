#include "rclcpp/rclcpp.hpp"
#include "AStar.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <cmath>
#include <random>
#include <vector>
#include <memory>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include <thread>
#include <random>


class Turtle_avoid : public rclcpp::Node
{
public:
    Turtle_avoid() 
        : Node("avoidance_turtle"),
          gen(rd()),
          dis(-0.1, 0.1),
          target_reached(false),
          grid_initialized_(false),
          main_turtle_spawned_(false),
          turtlesim_up_(false)
    {
        // Declare parameters
        this->declare_parameter<std::string>("turtle_name", "turtle1");
        this->declare_parameter<int>("grid_width", 500);  // Grid size
        this->declare_parameter<int>("grid_height", 500); // Grid size
        this->declare_parameter<double>("occupied_threshold", 0.2);


        // Get parameters
        name_ = this->get_parameter("turtle_name").as_string();
        grid_width_ = this->get_parameter("grid_width").as_int();
        grid_height_ = this->get_parameter("grid_height").as_int();
        occupied_threshold_ = this->get_parameter("occupied_threshold").as_double();

        // Initialize the occupancy grid
        occupancy_grid_.resize(grid_height_, std::vector<int>(grid_width_, 0));

        // Initialize publishers
        pub_ = this->create_publisher<geometry_msgs::msg::Twist>(name_ + "/cmd_vel", 10);

        // Initialize subscribers
        sub_ = this->create_subscription<turtlesim::msg::Pose>(
            name_ + "/pose", 10, std::bind(&Turtle_avoid::callbackPose, this, std::placeholders::_1));
        
        // Initialize service clients
        spawn_client_ = this->create_client<turtlesim::srv::Spawn>("spawn");

        // Create turtles
        create_homogeneous_turtles(24);

        // Create timers to call updateOccupancyGrid and captureScreen every 500 milliseconds
        timer_ = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&Turtle_avoid::updateOccupancyGrid, this));
        timer_1 = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&Turtle_avoid::captureScreen, this));
        controlLoop_timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&Turtle_avoid::controlLoop, this));

    }

private:
    void callbackPose(const turtlesim::msg::Pose::SharedPtr pose) {
        pose_ = *pose;
        turtlesim_up_ = true;
        // RCLCPP_INFO(this->get_logger(), "Turtle pose: x=%f, y=%f, theta=%f", pose_.x, pose_.y, pose_.theta);
    }

    void updateOccupancyGrid() {
        if (!flag_update_occupancy) {

            if (!turtlesim_up_) {
                RCLCPP_INFO(this->get_logger(), "Waiting for TurtleSim to start...");
                return;
            }

            // Capture the screen
            cv::Mat screen = captureScreen();
            if (screen.empty()) {
                RCLCPP_ERROR(this->get_logger(), "Failed to capture the screen.");
                return;
            }

            // Ensure the correct region is within bounds
            cv::Rect turtlesim_window(243, 235, 500, 500);
            if (turtlesim_window.x + turtlesim_window.width > screen.cols || turtlesim_window.y + turtlesim_window.height > screen.rows) {
                RCLCPP_ERROR(this->get_logger(), "TurtleSim window region is out of screen bounds.");
                return;
            }
            cv::Mat turtlesim_region = screen(turtlesim_window);

            // Convert the image to HSV color space
            cv::Mat hsv;
            cv::cvtColor(turtlesim_region, hsv, cv::COLOR_BGR2HSV);

            std::vector<cv::Scalar> lower_bounds = {
                cv::Scalar(35, 100, 100),   // Example HSV range for turtle1
                cv::Scalar(25, 50, 70),     // Example HSV range for turtle2
                cv::Scalar(100, 100, 100),  // Example HSV range for turtle3
                cv::Scalar(45, 50, 100),    // Example HSV range for turtle4
                cv::Scalar(85, 100, 100),   // Example HSV range for turtle5
                cv::Scalar(0, 100, 100),    // Example HSV range for turtle6
                cv::Scalar(75, 100, 100),   // Example HSV range for turtle7
                cv::Scalar(95, 50, 70),     // Example HSV range for turtle8
                cv::Scalar(50, 50, 70),     // Example HSV range for turtle9
                cv::Scalar(0, 100, 100),    // Example HSV range for background
                cv::Scalar(0, 0, 43),       // Example HSV range for background
                cv::Scalar(0, 0, 43),       // Lower bound for the yellow turtle with pink details
                cv::Scalar(0, 0, 79),       // Lower bound for the green turtle with red details
                cv::Scalar(0, 0, 0),        // Lower bound for the black turtle
            };
            std::vector<cv::Scalar> upper_bounds = {
                cv::Scalar(85, 255, 255),   // Example HSV range for turtle1
                cv::Scalar(35, 255, 255),   // Example HSV range for turtle2
                cv::Scalar(140, 255, 255),  // Example HSV range for turtle3
                cv::Scalar(85, 255, 255),   // Example HSV range for turtle4
                cv::Scalar(120, 255, 255),  // Example HSV range for turtle5
                cv::Scalar(15, 255, 255),   // Example HSV range for turtle6
                cv::Scalar(135, 255, 255),  // Example HSV range for turtle7
                cv::Scalar(135, 255, 255),  // Example HSV range for turtle8
                cv::Scalar(100, 255, 255),  // Example HSV range for turtle9
                cv::Scalar(10, 255, 255),
                cv::Scalar(162, 204, 255),
                cv::Scalar(162, 204, 255),  // Upper bound for the yellow turtle with pink details
                cv::Scalar(65, 228, 255),   // Upper bound for the green turtle with red details
                cv::Scalar(180, 255, 30),   // Upper bound for the black turtle
            };

            // Create a mask for the background color
            cv::Scalar lower_background = cv::Scalar(110, 70, 50);
            cv::Scalar upper_background = cv::Scalar(130, 255, 255);
            cv::Mat background_mask;
            cv::inRange(hsv, lower_background, upper_background, background_mask);

            // Clear the grid
            for (auto &row : occupancy_grid_) {
                std::fill(row.begin(), row.end(), 0);
            }

            // Detect turtles and update the occupancy grid
            for (size_t i = 0; i < lower_bounds.size(); ++i) {
                cv::Mat mask;
                cv::inRange(hsv, lower_bounds[i], upper_bounds[i], mask);

                // Remove the background from the mask
                cv::bitwise_and(mask, ~background_mask, mask);

                // Apply morphological operations to close gaps and then dilate
                cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1, -1), 2);
                int dilation_size = 1;  // Slightly larger size
                cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                cv::Point(dilation_size, dilation_size));
                cv::dilate(mask, mask, element);

                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

                // Create an image to draw filled contours
                cv::Mat filled_contours = cv::Mat::zeros(mask.size(), CV_8UC1);
                for (const auto &contour : contours) {
                    cv::drawContours(filled_contours, std::vector<std::vector<cv::Point>>{contour}, -1, cv::Scalar(255), cv::FILLED);
                }

                // Resize the filled_contours image to match the occupancy grid size
                cv::resize(filled_contours, filled_contours, cv::Size(grid_width_, grid_height_));

                for (int y = 0; y < grid_height_; ++y) {
                    for (int x = 0; x < grid_width_; ++x) {
                        if (filled_contours.at<uchar>(y, x) > 0) {
                            occupancy_grid_[y][x] = 1;
                        }
                    }
                }
            }

            double offset_x = 0.0;  // Adjust this value as needed
            double offset_y = 0.0;  // Adjust this value as needed


            // Convert turtle world position to grid position
            auto [turtle_x, turtle_y] = worldToGrid(pose_.x - offset_x, pose_.y - offset_y, grid_width_, grid_height_);

            // Define the dimensions of the removal area
            int remove_width = 15;  // Adjust as needed
            int remove_height = 12;  // Adjust as needed

            // Remove the turtle from the occupancy grid
            for (int y = std::max(0, turtle_y - remove_height); y <= std::min(grid_height_ - 1, turtle_y + remove_height); ++y) {
                for (int x = std::max(0, turtle_x - remove_width); x <= std::min(grid_width_ - 1, turtle_x + remove_width); ++x) {
                    occupancy_grid_[y][x] = 0;
                }
            }

            // Save the occupancy grid as an image for debugging
            cv::Mat occupancy_image(grid_height_, grid_width_, CV_8UC1);
            for (int y = 0; y < grid_height_; ++y) {
                for (int x = 0; x < grid_width_; ++x) {
                    occupancy_image.at<uchar>(y, x) = occupancy_grid_[y][x] ? 255 : 0;
                }
            }
            cv::imwrite("occupancy_grid.png", occupancy_image);
            cv::imwrite("turtlesim_region.png", turtlesim_region);

            // Apply additional dilation
            int dilation_size = 10;  // Increased dilation size
            cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                cv::Point(dilation_size, dilation_size));
            cv::dilate(occupancy_image, occupancy_image, element);

            // Update the occupancy grid based on the dilated image
            for (int y = 0; y < grid_height_; ++y) {
                for (int x = 0; x < grid_width_; ++x) {
                    occupancy_grid_[y][x] = occupancy_image.at<uchar>(y, x) > 0 ? 1 : 0;
                }
            }

            // Save the dilated occupancy grid as an image for debugging
            cv::imwrite("dilated_occupancy_grid.png", occupancy_image);

            grid_initialized_ = true;
            flag_update_occupancy = true;
        }
        else {
            return;
        }
    }

    void create_homogeneous_turtles(int num_turtles) {
        std::vector<std::pair<double, double>> positions;
        double central_x = 5.5;
        double central_y = 5.5;
        double exclusion_radius = 1.0;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.0, 10.0);

        while (positions.size() < static_cast<std::vector<std::pair<double, double>>::size_type>(num_turtles)) {
            double x = dis(gen);
            double y = dis(gen);

            // Skip the origin and central region
            if ((x == 0 && y == 0) || 
                (std::sqrt(std::pow(x - central_x, 2) + std::pow(y - central_y, 2)) <= exclusion_radius)) {
                continue;
            }

            // Check if position is already taken
            bool position_taken = false;
            for (const auto& pos : positions) {
                if (std::abs(pos.first - x) < 1e-6 && std::abs(pos.second - y) < 1e-6) {
                    position_taken = true;
                    break;
                }
            }

            if (!position_taken) {
                positions.emplace_back(x, y);
            }
        }

        for (size_t i = 0; i < positions.size(); ++i) {
            auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
            request->x = positions[i].first;
            request->y = positions[i].second;
            request->theta = 0.0;
            request->name = "turtle" + std::to_string(i + 2);

            while (!spawn_client_->wait_for_service(std::chrono::seconds(1))) {
                if (!rclcpp::ok()) {
                    RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                    return;
                }
                RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
            }

            auto result = spawn_client_->async_send_request(request);
            if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS) {
                RCLCPP_INFO(this->get_logger(), "Spawned turtle %s at (%f, %f)", request->name.c_str(), request->x, request->y);
                // Save the position of the spawned turtle
                turtle_positions_.emplace_back(request->x, request->y);
            } else {
                RCLCPP_ERROR(this->get_logger(), "Failed to spawn turtle");
            }
        }
    }





    cv::Mat captureScreen() {
        if(!flag_capture){
            // Open display
            Display* display = XOpenDisplay(nullptr);
            if (display == nullptr) {
                RCLCPP_ERROR(this->get_logger(), "Cannot open display.");
                return cv::Mat();
            }

            // Get the root window
            Window root = DefaultRootWindow(display);

            // Get screen dimensions
            XWindowAttributes gwa;
            XGetWindowAttributes(display, root, &gwa);
            int width = gwa.width;
            int height = gwa.height;

            // Capture the screen
            XImage* image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
            if (image == nullptr) {
                RCLCPP_ERROR(this->get_logger(), "Failed to capture the screen area.");
                XCloseDisplay(display);
                return cv::Mat();
            }

            // Convert the XImage to a cv::Mat
            cv::Mat screen(height, width, CV_8UC4, image->data);

            // Convert to BGR format (OpenCV default)
            cv::Mat screen_bgr;
            cv::cvtColor(screen, screen_bgr, cv::COLOR_BGRA2BGR);

            // Free the XImage and close the display
            XDestroyImage(image);
            XCloseDisplay(display);
            flag_capture = true;

            return screen_bgr;
        }
        else{
            return cv::Mat();
        }
    }

        void controlLoop() {
        // Check if the occupancy grid is initialized and the turtle is spawned
        if (!turtlesim_up_ || !grid_initialized_) return;

        // Check if the target is reached
        double dist_to_target = getDistance(pose_.x, pose_.y, target_x_, target_y_);
        if (dist_to_target < 0.6) {
            generateRandomTarget();
            RCLCPP_INFO(this->get_logger(), "New target: (%f, %f)", target_x_, target_y_);
            initial_orientation_adjustment_ = true;
            path_generated_ = false;
            flag_path = false;
            target_reached = true;
            path.clear();
            return;
        }

        // Stop the turtle if the target is reached
        if (target_reached) {
            geometry_msgs::msg::Twist stop_msg;
            stop_msg.linear.x = 0.0;
            stop_msg.angular.z = 0.0;
            pub_->publish(stop_msg);

            target_reached = false;
            return;
        }

        if (!path_generated_) {
            // Generate the path using A*
            AStar::Generator generator_;
            generator_.setWorldSize({500, 500});
            generator_.setHeuristic(AStar::Heuristic::euclidean);
            generator_.setDiagonalMovement(true);
            auto [start_x, start_y] = worldToGrid(pose_.x, pose_.y, grid_width_, grid_height_);
            auto [goal_x, goal_y] = worldToGrid(target_x_, target_y_, grid_width_, grid_height_);

            generator_.clearCollisions();
            for (size_t y = 0; y < occupancy_grid_.size(); ++y) {
                for (size_t x = 0; x < occupancy_grid_[0].size(); ++x) {
                    if (occupancy_grid_[y][x] == 1) {
                        generator_.addCollision({static_cast<int>(x), static_cast<int>(y)});
                    }
                }
            }
            RCLCPP_INFO(this->get_logger(), "Finding path from (%d, %d) to (%d, %d)", start_x, start_y, goal_x, goal_y);
            path = generator_.findPath({start_x, start_y}, {goal_x, goal_y});

            if (path.empty()) {
                RCLCPP_WARN(this->get_logger(), "No path found!");
                return;
            }

            // Calculate the distance between the first and last points in the path
            double path_start_to_end_distance = getDistance(path.front().x, path.front().y, path.back().x, path.back().y);
            double actual_start_to_goal_distance = getDistance(start_x, start_y, goal_x, goal_y);

            // Check if the distances are similar
            if (std::abs(path_start_to_end_distance - actual_start_to_goal_distance) > 1.0) {
                RCLCPP_WARN(this->get_logger(), "Invalid path found!");
                path_generated_ = false;
                path.clear();
                generateRandomTarget();
                return;
            }

            RCLCPP_INFO(this->get_logger(), "Path found with %ld points", path.size());

            // Path was found
            drawAndSavePath(path);
            path_generated_ = true;  // Set the flag to indicate the path is generated
        }

        // Pure Pursuit parameters
        double lookahead_distance_base = 0.4;  // Base value for lookahead distance
        double lookahead_distance = lookahead_distance_base * (1.0 + 0.5 * dist_to_target);  // Dynamic lookahead distance
        double min_distance = std::numeric_limits<double>::max();
        size_t lookahead_index = 0;

        // Find the lookahead point on the path
        for (size_t i = 0; i < path.size(); ++i) {
            auto [path_x, path_y] = gridToWorld(path[i].x, path[i].y, grid_width_, grid_height_);
            double distance = getDistance(pose_.x, pose_.y, path_x, path_y);
            if (distance >= lookahead_distance && distance < min_distance) {
                min_distance = distance;
                lookahead_index = i;
            }
        }

        if (lookahead_index >= path.size()) {
            lookahead_index = path.size() - 1;  // Ensure index is within bounds
        }

        // Get the lookahead point
        auto [lookahead_x, lookahead_y] = gridToWorld(path[lookahead_index].x, path[lookahead_index].y, grid_width_, grid_height_);

        double dx = lookahead_x - pose_.x;
        double dy = lookahead_y - pose_.y;

        double lookahead_angle = std::atan2(dy, dx);
        double alpha = lookahead_angle - pose_.theta;

        // Normalize alpha to the range [-pi, pi]
        if (alpha > M_PI) {
            alpha -= 2 * M_PI;
        } else if (alpha < -M_PI) {
            alpha += 2 * M_PI;
        }

        // Rotate first if angle difference is greater than 90 degrees and it's the initial orientation adjustment
        if (initial_orientation_adjustment_ && std::abs(alpha) > M_PI / 18) { // Angle difference threshold reduced for more accurate rotation
            geometry_msgs::msg::Twist rotate_msg;
            rotate_msg.linear.x = 0.0;
            rotate_msg.angular.z = std::max(-1.0, std::min(1.0, 2.0 * alpha)); // Increase angular velocity for faster rotation
            pub_->publish(rotate_msg);
            return;
        } else {
            initial_orientation_adjustment_ = false; // Finished initial orientation adjustment
        }

        double Ld = std::sqrt(dx * dx + dy * dy);
        double curvature = 2.0 * std::sin(alpha) / Ld;

        geometry_msgs::msg::Twist msg;
        msg.linear.x = std::max(0.1, 1.0 * dist_to_target / 10.0)*5.5;  // Reduce speed as it gets closer to the target
        msg.angular.z = curvature * msg.linear.x;

        // Apply a low-pass filter to the angular velocity to smooth out sudden changes
        static double prev_angular_z = 0.0;
        double alpha_filter = 0.5; // Adjust this value for more or less smoothing
        msg.angular.z = alpha_filter * msg.angular.z + (1.0 - alpha_filter) * prev_angular_z;
        prev_angular_z = msg.angular.z;

        pub_->publish(msg);
    }






    void drawAndSavePath(const std::vector<AStar::Vec2i>& path) {
        if (!flag_path) {
            cv::Mat path_image(grid_height_, grid_width_, CV_8UC3, cv::Scalar(255, 255, 255));

            // Engelleri çiz
            for (size_t y = 0; y < occupancy_grid_.size(); ++y) {
                for (size_t x = 0; x < occupancy_grid_[0].size(); ++x) {
                    if (occupancy_grid_[y][x] == 1) {
                        cv::rectangle(path_image, cv::Point(x, y), cv::Point(x + 1, y + 1), cv::Scalar(0, 0, 0), cv::FILLED);
                    }
                }
            }

            // Path'i çiz
            for (size_t i = 1; i < path.size(); ++i) {
                auto [prev_x, prev_y] = path[i - 1];
                auto [next_x, next_y] = path[i];
                cv::line(path_image, cv::Point(prev_x, prev_y), cv::Point(next_x, next_y), cv::Scalar(0, 0, 255), 2);
            }

            // Turtle'ın konumunu ve hedefi çiz
            auto [turtle_x, turtle_y] = worldToGrid(pose_.x, pose_.y, grid_width_, grid_height_);
            auto [target_grid_x, target_grid_y] = worldToGrid(target_x_, target_y_, grid_width_, grid_height_);
            cv::circle(path_image, cv::Point(turtle_x, turtle_y), 3, cv::Scalar(0, 255, 0), cv::FILLED);
            cv::circle(path_image, cv::Point(target_grid_x, target_grid_y), 3, cv::Scalar(255, 0, 0), cv::FILLED);

            // Path görüntüsünü kaydet
            cv::imwrite("path_image.png", path_image);

            // turtlesim_region üzerine path'i çiz
            cv::Mat turtlesim_region = cv::imread("turtlesim_region.png");
            if (turtlesim_region.empty()) {
                RCLCPP_ERROR(this->get_logger(), "Failed to read turtlesim_region.png");
                return;
            }

            // Path'i turtlesim_region üzerine çiz
            for (size_t i = 1; i < path.size(); ++i) {
                auto [prev_x, prev_y] = path[i - 1];
                auto [next_x, next_y] = path[i];
                // Koordinatları turtlesim_region boyutuna göre ayarla
                int prev_x_scaled = static_cast<int>(prev_x * turtlesim_region.cols / grid_width_);
                int prev_y_scaled = static_cast<int>(prev_y * turtlesim_region.rows / grid_height_);
                int next_x_scaled = static_cast<int>(next_x * turtlesim_region.cols / grid_width_);
                int next_y_scaled = static_cast<int>(next_y * turtlesim_region.rows / grid_height_);
                cv::line(turtlesim_region, cv::Point(prev_x_scaled, prev_y_scaled), cv::Point(next_x_scaled, next_y_scaled), cv::Scalar(0, 0, 255), 2);
            }

            // Turtle'ın konumunu ve hedefi turtlesim_region üzerine çiz
            int turtle_x_scaled = static_cast<int>(turtle_x * turtlesim_region.cols / grid_width_);
            int turtle_y_scaled = static_cast<int>(turtle_y * turtlesim_region.rows / grid_height_);
            int target_grid_x_scaled = static_cast<int>(target_grid_x * turtlesim_region.cols / grid_width_);
            int target_grid_y_scaled = static_cast<int>(target_grid_y * turtlesim_region.rows / grid_height_);
            cv::circle(turtlesim_region, cv::Point(turtle_x_scaled, turtle_y_scaled), 3, cv::Scalar(0, 255, 0), cv::FILLED);
            cv::circle(turtlesim_region, cv::Point(target_grid_x_scaled, target_grid_y_scaled), 3, cv::Scalar(255, 0, 0), cv::FILLED);

            // turtlesim_region görüntüsünü kaydet
            cv::imwrite("turtlesim_region_with_path.png", turtlesim_region);

            flag_path = true;
        } else {
            return;
        }
    }



    void generateRandomTarget() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis_x(1, 10);
        std::uniform_real_distribution<> dis_y(1, 10);

        double target_x, target_y;
        bool valid_target = false;

        while (!valid_target) {
            target_x = dis_x(gen);
            target_y = dis_y(gen);
            valid_target = true;

            // Ensure the target is not within 3 units of the current turtle's pose
            if (getDistance(target_x, target_y, pose_.x, pose_.y) < 3) {
                valid_target = false;
            } else {
                for (const auto& pos : turtle_positions_) {
                    double distance = getDistance(target_x, target_y, pos.first, pos.second);
                    if (distance < 1.0) {
                        valid_target = false;
                        break;
                    }
                }
            }
        }

        target_x_ = target_x;
        target_y_ = target_y;


        path_generated_ = false;
        RCLCPP_INFO(this->get_logger(), "New target: (%f, %f)", target_x_, target_y_);
    }





    double getDistance(double x1, double y1, double x2, double y2) {
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }

    std::pair<double, double> gridToWorld(int grid_x, int grid_y, int grid_width, int grid_height) {
        double world_x = (static_cast<double>(grid_x) / grid_width) * 11.0;
        double world_y = 11.0 - (static_cast<double>(grid_y) / grid_height) * 11.0;
        return {world_x, world_y};
    }

    std::pair<int, int> worldToGrid(double world_x, double world_y, int grid_width, int grid_height) {
        int grid_x = static_cast<int>(world_x / 11.0 * grid_width);
        int grid_y = grid_height - static_cast<int>(world_y / 11.0 * grid_height);
        return {grid_x, grid_y};
    }
    

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    bool target_reached = false;
    bool grid_initialized_;
    bool main_turtle_spawned_;
    bool turtlesim_up_;
    std::vector<AStar::Vec2i> path;
    bool path_generated_;
    bool flag_capture = false;
    bool flag_update_occupancy = false;
    bool flag_path = false;
    bool initial_orientation_adjustment_ = true;
    std::vector<std::vector<int>> occupancy_grid_;
    std::string name_;
    turtlesim::msg::Pose pose_;
    int grid_width_, grid_height_;
    double occupied_threshold_;
    double target_x_ = 5.5 , target_y_ = 5.5;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timer_1;
    rclcpp::TimerBase::SharedPtr cancel_timer_;
    rclcpp::TimerBase::SharedPtr controlLoop_timer_;
    std::vector<std::pair<double, double>> turtle_positions_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Turtle_avoid>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
