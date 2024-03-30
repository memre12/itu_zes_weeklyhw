# Joystick Controlled Turtlesim Node

This ROS 2 package allows users to control the Turtlesim node using joystick inputs. It offers interactive features such as dynamic velocity control, screen clearing, simulation resetting, turtle spawning, and pen toggling, all through a physical joystick interface.

## Overview

The `JoystickTurtleSubscriber` class, derived from `rclcpp::Node`, encapsulates the functionality for subscribing to joystick inputs and controlling the Turtlesim. It maps joystick axes and buttons to turtle movements and commands, providing an intuitive interface for interaction with the Turtlesim environment.

### Key Components

#### Subscriptions

- **Joystick Input**: Listens to `/joy` topic for joystick inputs, which control the turtle's motion and execute specific actions based on button presses.
- **Turtle Pose**: Monitors `/turtle1/pose` to maintain current knowledge of the turtle's position and orientation, crucial for spawning turtles accurately.

#### Publishers and Service Clients

- **Velocity Commands**: Publishes to `/turtle1/cmd_vel` to dictate the turtle's movement speed and direction.
- **Service Requests**: Sends requests to Turtlesim services (`clear`, `reset`, `set_pen`) to clear the background, reset the simulation, and adjust the pen's drawing state.

### Callback Functions

- **joystick_callback**: Handles joystick inputs, translating axis movements to velocity commands and button presses to service requests or specific actions.
- **pose_callback**: Updates internal state with the turtle's current position and orientation, necessary for operations like spawning.
- **timerCallback**: Ensures actions triggered by button presses are processed after a certain interval, preventing unintended repeated actions.


## Joystick Button Mappings

The package maps specific joystick buttons to particular actions within the Turtlesim environment. Here's a brief overview of what each mapped button does:

- **Right Back Trigger (Axis)**: Controls the linear velocity of the turtle. The position of the trigger adjusts the speed.
- **Left Horizontal Stick (Axis)**: Controls the angular velocity of the turtle. Moving the stick left or right rotates the turtle accordingly.
- **Button A**: Clears the Turtlesim background, effectively removing any traces made by the turtle's pen.
- **Button B**: Resets the Turtlesim simulation to its initial state, including the turtle's position.
- **Button X**: Spawns a new turtle at the current location and orientation of the turtle being controlled. This allows for multiple turtles to be controlled simultaneously.
- **Button Y**: Toggles the pen state (on/off), enabling or disabling the drawing of the turtle's path as it moves.


## Functional Flow

1. **Initialization**: On node startup, parameters for joystick control are declared and initialized. These include mappings for linear and angular control axes, scaling factors for velocities, and button mappings for various commands.
2. **Joystick Control**: As joystick messages are received, the `joystick_callback` interprets axis positions for movement control and button states for executing commands like clearing the screen or spawning new turtles.
3. **Pose Tracking**: The `pose_callback` keeps the application informed about the turtle's current location, enabling accurate spawning of new turtles at the correct position and orientation.
4. **Command Execution**: Based on button inputs, appropriate ROS 2 service clients are invoked to interact with the Turtlesim, performing actions like resetting the simulation or toggling the pen's drawing state.

### Running the Project

Ensure your ROS 2 environment is properly set up and that the joystick device is connected. Launch the package using the provided launch script to start controlling the Turtlesim with your joystick.

```bash
ros2 launch joystick_turtle_subscriber launch_node.py
