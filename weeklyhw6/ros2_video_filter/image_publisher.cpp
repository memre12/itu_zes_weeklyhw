#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp> 
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <yaml-cpp/yaml.h>
#include <chrono>
#include <fstream> // Add for reading YAML file
// add config directory to yaml and add param.yaml file , 3video
class ImagePublisher : public rclcpp::Node
{
public:
    ImagePublisher() : Node("image_publisher")
    {
        // Load parameters from a YAML file
        load_parameters_from_yaml();

        // Open the video file
        cap.open(video_file_path_);

        // Check if the video opened successfully
        if (!cap.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Could not open the video");
            rclcpp::shutdown();
        }

        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image_topic", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000 / publish_frequency_), // Adjust according to the video FPS (e.g., 30 FPS)
            std::bind(&ImagePublisher::timer_callback, this));

        // Initialize apply_edge_detection_ to false by default
        apply_edge_detection_ = false;
    }

private:
    void load_parameters_from_yaml()
    {
        try {
            // Open the YAML file
            std::ifstream fin("/home/emre/ros2_pck/src/cpp_gae/config/param.yaml"); // Change the path to your YAML file
            if (!fin.is_open()) {
                RCLCPP_ERROR(this->get_logger(), "Could not open the YAML file");
                rclcpp::shutdown();
            }
            // Parse the YAML file
            YAML::Node yaml_node = YAML::Load(fin);
            video_file_path_ = yaml_node["image_processing_pipeline"]["video_file_path"].as<std::string>();
            publish_frequency_ = yaml_node["image_processing_pipeline"]["publish_frequency"].as<int>();
            blur_kernel_size_ = yaml_node["image_processing_pipeline"]["filters"]["gaussian_blur"]["kernel_size"].as<int>();
            canny_low_threshold_ = yaml_node["image_processing_pipeline"]["filters"]["canny_edge_detection"]["low_threshold"].as<double>();
            canny_high_threshold_ = yaml_node["image_processing_pipeline"]["filters"]["canny_edge_detection"]["high_threshold"].as<double>();
            apply_edge_detection_ = yaml_node["image_processing_pipeline"]["filters"]["canny_edge_detection"]["enabled"].as<bool>();
            apply_grayscale_conversion_ = yaml_node["image_processing_pipeline"]["filters"]["grayscale_conversion"]["enabled"].as<bool>();
        } catch (const YAML::BadFile& bf) {
            RCLCPP_FATAL(this->get_logger(), "Could not open the YAML file: %s", bf.what());
            rclcpp::shutdown();
        } catch (const YAML::TypedBadConversion<std::string>& tbc) {
            RCLCPP_FATAL(this->get_logger(), "Bad conversion: %s", tbc.what());
            rclcpp::shutdown();
        } catch (const YAML::Exception& e) {
            RCLCPP_FATAL(this->get_logger(), "General YAML exception: %s", e.what());
            rclcpp::shutdown();
        }
    }

    void timer_callback()
    {
        cv::Mat frame;
        if (cap.read(frame)) // Read a new frame
        {
            // Apply image processing filters
            if (apply_edge_detection_) {
                // Apply Gaussian Blur
                cv::Mat blurred_frame;
                cv::GaussianBlur(frame, blurred_frame, cv::Size(blur_kernel_size_, blur_kernel_size_), 0);

                // Apply Canny Edge Detection
                cv::Mat canny_frame;
                cv::Canny(blurred_frame, canny_frame, canny_low_threshold_, canny_high_threshold_);

                // Convert processed frame to a ROS2 message
                sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(std_msgs::msg::Header(), "mono8", canny_frame).toImageMsg();
                publisher_->publish(*msg);
            } else if (apply_grayscale_conversion_) {
                // Apply Grayscale conversion
                cv::Mat grayscale_frame;
                cv::cvtColor(frame, grayscale_frame, cv::COLOR_BGR2GRAY);

                // Convert processed frame to a ROS2 message
                sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(std_msgs::msg::Header(), "mono8", grayscale_frame).toImageMsg();
                publisher_->publish(*msg);
            } else {
                // Convert the frame to a ROS2 message without processing
                sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
                publisher_->publish(*msg);
            }

            RCLCPP_INFO(this->get_logger(), "Publishing video frame");
        }
        else {
            RCLCPP_INFO(this->get_logger(), "Video ended or error reading frame");
            rclcpp::shutdown();
        }
    }

    cv::VideoCapture cap;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

    // Parameters
    std::string video_file_path_;
    int publish_frequency_;
    int blur_kernel_size_;
    double canny_low_threshold_;
    double canny_high_threshold_;
    bool apply_edge_detection_;
    bool apply_grayscale_conversion_;
};

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber() : Node("image_subscriber")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "image_topic", 10,
            std::bind(&ImageSubscriber::image_callback, this, std::placeholders::_1));

        // Initialize apply_edge_detection_ to false by default
        apply_edge_detection_ = false;
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            // Convert ROS message to OpenCV image
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);

            // Show the Grayscale image
            cv::imshow("Grayscale Image", cv_ptr->image);
            cv::waitKey(1);

            // If edge detection is applied, show it too
            if (apply_edge_detection_) {
                // Apply Canny Edge Detection
                cv::Mat canny_frame;
                cv::Canny(cv_ptr->image, canny_frame, canny_low_threshold_, canny_high_threshold_);

                // Show the Edge detected image
                cv::imshow("Edge Detected Image", canny_frame);
                cv::waitKey(1);
            }
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    bool apply_edge_detection_;
    double canny_low_threshold_;
    double canny_high_threshold_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto image_publisher = std::make_shared<ImagePublisher>();
    auto image_subscriber = std::make_shared<ImageSubscriber>();
    rclcpp::spin(image_publisher);
    rclcpp::shutdown();
    return 0;
}
