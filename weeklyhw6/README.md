# ROS2 Basics and Turtlesim Joystick Control

This repository contains two main ROS2 projects. The first project focuses on the basics of ROS2 publishers and subscribers, integrated with OpenCV for image processing. The second project is a Turtlesim joystick controller, allowing for intuitive control of the Turtlesim with a joystick.

## Part 1: ROS2 Publishers & Listeners with OpenCV
### Overview

Create a publisher node and a subscriber node that handle image data using the `sensor_msgs::msg::Image` message type. This part also introduces basic image processing with OpenCV, applying filters like Gaussian Blur, Grayscale, and Canny Edge Detection.
### Usage

- **Publisher Node**: Reads an MP4 file and publishes frames as ROS images at a defined frequency.
- **Subscriber Node**: Subscribes to the image topic, applies OpenCV filters, and either publishes the results or displays them based on the configuration.


### Configuration

Parameters for image processing and control flow are set in a YAML configuration file, allowing for dynamic adjustments without code changes.

## Part 2: Turtlesim Joystick Controller

### Overview

Control the ROS2 Turtlesim with a joystick (e.g., Logitech F710), mapping joystick inputs to Turtlesim movements and actions.

### Key Bindings

- **Linear Velocity**: Triggers control the turtle's speed.
- **Angular Velocity**: Sticks adjust the turtle's turning.
- **Button A**: Clears the Turtlesim background.
- **Button B**: Resets Turtlesim.
- **Button X**: Spawns a new turtle at the current location.
- **Button Y**: Toggles the turtle's pen on and off.



 These projects' details are in the related files. To understand projects properly, read descriptions.
