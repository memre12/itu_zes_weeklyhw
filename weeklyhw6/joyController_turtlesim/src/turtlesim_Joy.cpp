#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_srvs/srv/empty.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/msg/pose.hpp"
#include <sstream>
#include <chrono>
#include <iomanip>

class JoystickTurtleSubscriber : public rclcpp::Node {
public:
    JoystickTurtleSubscriber() : Node("joystick_turtle_subscriber") {
        // Initialize parameters
        this->declare_parameter<int>("axis_linear", 5);
        this->declare_parameter<int>("axis_angular", 0);
        this->declare_parameter<double>("scale_linear", 1.0);
        this->declare_parameter<double>("scale_angular", 1.0);
        this->declare_parameter<int>("button_clear", 0); // A
        this->declare_parameter<int>("button_reset", 1); // B
        this->declare_parameter<int>("button_spawn", 2); // Y
        this->declare_parameter<int>("button_toggle_pen", 3); // X

        // Retrieve parameters
        linear_ = this->get_parameter("axis_linear").as_int();
        angular_ = this->get_parameter("axis_angular").as_int();
        l_scale_ = this->get_parameter("scale_linear").as_double();
        a_scale_ = this->get_parameter("scale_angular").as_double();
        button_clear_ = this->get_parameter("button_clear").as_int(); // Get the clear button index
        button_reset_ = this->get_parameter("button_reset").as_int(); // Get the reset button index
        button_spawn_ = this->get_parameter("button_spawn").as_int(); // Get the spawn button index
        button_toggle_pen_ = this->get_parameter("button_toggle_pen").as_int(); // Get the toggle pen button index

        // Create subscription to joystick topic
        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&JoystickTurtleSubscriber::joystick_callback, this, std::placeholders::_1));

        // Create subscription to pose topic
        pose_subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "turtle1/pose", 10, std::bind(&JoystickTurtleSubscriber::pose_callback, this, std::placeholders::_1));

        // Create publisher to cmd_vel topic
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

        // Create a client for the clear service
        client_clear_ = this->create_client<std_srvs::srv::Empty>("clear");
        client_reset_ = this->create_client<std_srvs::srv::Empty>("reset");
        client_toggle_pen_ = this->create_client<turtlesim::srv::SetPen>("turtle1/set_pen");

        // Create a timer to periodically send the current pose
        timer = this->create_wall_timer(std::chrono::milliseconds(300), std::bind(&JoystickTurtleSubscriber::timerCallback, this));
        timer->cancel();

        RCLCPP_INFO(this->get_logger(), "Key Bindings:");
        RCLCPP_INFO(this->get_logger(), "- Right Back Trigger: Control linear velocity of the turtle.");
        RCLCPP_INFO(this->get_logger(), "- Left Horizontal Stick: Control angular velocity of the turtle.");
        RCLCPP_INFO(this->get_logger(), "- Button A: Clears turtlesim background and sets color.");
        RCLCPP_INFO(this->get_logger(), "- Button B: Resets turtlesim to start configuration and sets background color.");
        RCLCPP_INFO(this->get_logger(), "- Button X: Spawns a turtle at current position and orientation.");
        RCLCPP_INFO(this->get_logger(), "- Button Y: Sets pen color, width, and turns pen on/off.");

    }

private:
    void joystick_callback(const sensor_msgs::msg::Joy::SharedPtr msg) {
        if (msg->buttons[button_clear_] == 1 && last_button != 0) { // If the clear button is pressed
            auto request = std::make_shared<std_srvs::srv::Empty::Request>();
            auto result = client_clear_->async_send_request(request);
            // You might want to check the result or handle it asynchronously
            RCLCPP_INFO(this->get_logger(), "Clear screen request sent.");
            timer->cancel();
            timer->reset();
            last_button = 0;
        } else if (msg->buttons[button_reset_] == 1 && last_button != 1) { // If the reset button is pressed
            auto request = std::make_shared<std_srvs::srv::Empty::Request>();
            auto result = client_reset_->async_send_request(request);
            // You might want to check the result or handle it asynchronously
            RCLCPP_INFO(this->get_logger(), "Reset request sent.");
            timer->cancel();
            timer->reset();
            last_button = 1;
        } else if (msg->buttons[button_spawn_] == 1 && last_button != 2) {
            auto client = rclcpp::Node::create_client<turtlesim::srv::Spawn>("spawn");
            auto request = std::make_shared<turtlesim::srv::Spawn::Request>();

            // Set the spawn location and orientation
            request->x = current_x_;
            request->y = current_y_;
            request->theta = current_theta_;
            // Send the service request
            auto result = client->async_send_request(request);
            RCLCPP_INFO(this->get_logger(), "Spawn request sent.");
            timer->cancel();
            timer->reset();
            last_button = 2;
        } else if (msg->buttons[button_toggle_pen_] == 1 && last_button != 3) {
            auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
            request->r = 0xb3;
            request->g = 0xb8;
            request->b = 0xff;
            request->width = 3;
            request->off = !DENEME2;
            DENEME2 = !DENEME2;
            auto result = client_toggle_pen_->async_send_request(request);
            // You might want to check the result or handle it asynchronously

            RCLCPP_INFO(this->get_logger(), "Toggle pen request sent.");
            timer->cancel();
            timer->reset();
            last_button = 3;
        }else {
            geometry_msgs::msg::Twist msg_ = geometry_msgs::msg::Twist();
            msg_.linear.x = (msg->axes[5] + -1) * -10;
            msg_.angular.z = msg->axes[0] * 5;
            publisher_->publish(msg_);

        }
    }
    void timerCallback() {
       last_button = -1;
       timer->cancel();
    }

    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg) {
        current_x_ = msg->x;
        current_y_ = msg->y;
        current_theta_ = msg->theta;
    }

    int linear_, angular_, button_clear_, button_reset_, button_spawn_, button_toggle_pen_;
    int last_button = -1;
    double l_scale_, a_scale_;
    float current_x_, current_y_, current_theta_;
    bool DENEME2 = false;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_clear_; // Client for the clear service
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_reset_; // Client for the reset service
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr client_toggle_pen_; // Client for the toggle pen service
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscription_;


};

int main(int argc, char** argv) {
    // Initialize ROS
    rclcpp::init(argc, argv);

    // Create and spin the node
    rclcpp::spin(std::make_shared<JoystickTurtleSubscriber>());

    // Shutdown ROS
    rclcpp::shutdown();

    return 0;
}
