# ROS2 OpenCV Image Processing

* This project demonstrates an image processing pipeline using ROS2 and OpenCV, focusing on applying Gaussian blur, converting images to grayscale, and detecting edges with the Canny algorithm. The pipeline consists of an image publisher and subscriber, which communicate over a ROS2 topic. The publisher reads video frames, applies optional image processing algorithms, and publishes the frames. The subscriber receives these frames and can optionally apply further processing.

## Prerequisites

Before running this project, ensure you have the following installed on your system:
- ROS2
- OpenCV
- cv_bridge package
- yaml-cpp for YAML file parsing

## Installation

1. Clone this repository into your ROS2 workspace's `src` directory:
    ```bash
    git clone <repository-url> <your-workspace>/src/cpp_gae
    ```
2. Navigate back to your workspace and build the project:
    ```bash
    cd <your-workspace>
    colcon build --packages-select cpp_gae
    ```
3. Source your workspace to make the packages available:
    ```bash
    . install/setup.bash
    ```

## Configuration

* Parameters for the image processing pipeline are specified in the `param.yaml` file located in the `config` directory. Edit this file to adjust parameters such as Gaussian blur sigma, Canny edge detection thresholds, and the path to the video file.

## Running the Application

* To run the image publisher and subscriber, open two terminal windows and source your ROS2 workspace in each. Then, in the first terminal, launch the publisher:
```bash
ros2 run cpp_gae image_publisher
```
In the second terminal, launch the subscriber:
```bash
ros2 run cpp_gae image_subscriber
```

* After executing these commands, the publisher will start reading frames from the specified video file, processing them according to the settings defined in the `param.yaml` file, and then publishing the frames to a topic. The subscriber listens to this topic, receives the frames, and can apply additional processing or simply display them.

# Code Overview
## ImagePublisher
* Handles the loading of video frames, applying configured image processing techniques, and publishing the processed frames. It uses OpenCV for video handling and image processing operations, and ROS2 for communication.

Configuration Parameters:
* video_file_path: Path to the video file.
* publish_frequency: Frequency at which frames are published.
* filters: Specifies which image processing filters to apply, such as Gaussian * blur and Canny edge detection, including their parameters.
## ImageSubscriber
* Subscribes to the "image_topic" to receive image frames published by the ImagePublisher. It demonstrates how to use cv_bridge to convert ROS2 image messages into OpenCV images for display or further processing.

## Applying Image Processing
The application demonstrates:

* Gaussian Blur: To reduce image noise and detail.
* Grayscale Conversion: Converts the image to a grayscale image.
* Canny Edge Detection: Detects a wide range of edges in images.
## Additional Notes
The param.yaml file allows easy adjustment of the image processing pipeline's parameters without modifying the code.
The project structure facilitates easy extension with more image processing techniques or different ROS2 message types.
