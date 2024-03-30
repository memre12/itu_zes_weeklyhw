#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp> // Include for VideoCapture
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <yaml-cpp/yaml.h>
#include <chrono>
#include <fstream> // Add for reading YAML file

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber() : Node("image_subscriber")
    {
        // Load parameters from YAML file
        load_parameters_from_yaml();

        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "image_topic", 10,
            std::bind(&ImageSubscriber::image_callback, this, std::placeholders::_1));
    }

private:

    void load_parameters_from_yaml()
    {
        // Open YAML file
        std::ifstream fin("/home/emre/ros2_pck/src/cpp_gae/config/param.yaml"); // Change the path to your YAML file
        if (!fin)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open parameters.yaml file");
            return;
        }

        // Parse YAML file
        YAML::Node config = YAML::Load(fin);

        // Get parameters from YAML
        gaussian_blur_sigma_ = config["gaussian_blur_sigma"].as<double>(0.0);
        canny_threshold1_ = config["canny_threshold1"].as<int>(50);
        canny_threshold2_ = config["canny_threshold2"].as<int>(150);

        // Close YAML file
        fin.close();
    }

    void apply_gaussian_blur(const cv::Mat& input_image, cv::Mat& output_image)
    {
        cv::GaussianBlur(input_image, output_image, cv::Size(5, 5), gaussian_blur_sigma_);
    }

    void convert_to_grayscale(const cv::Mat& input_image, cv::Mat& output_image)
    {
        cv::cvtColor(input_image, output_image, cv::COLOR_BGR2GRAY);
    }

    void apply_canny_edge_detection(const cv::Mat& input_image, cv::Mat& output_image)
    {
        cv::Canny(input_image, output_image, canny_threshold1_, canny_threshold2_);
    }

    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            // Convert ROS message to OpenCV image
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            
            // Apply Gaussian Blur
            cv::Mat blurred_image;
            apply_gaussian_blur(cv_ptr->image, blurred_image);

            // Convert to Grayscale
            cv::Mat gray_image;
            convert_to_grayscale(blurred_image, gray_image);

            // Apply Canny Edge Detection
            cv::Mat canny_image;
            apply_canny_edge_detection(gray_image, canny_image);

            // Display the processed image
            cv::imshow("Original Image", cv_ptr->image);
            cv::imshow("Blurred Image", blurred_image);
            cv::imshow("Grayscale Image", gray_image);
            cv::imshow("Filtered Image", canny_image);
            cv::waitKey(1);
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    double gaussian_blur_sigma_;
    int canny_threshold1_;
    int canny_threshold2_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}
