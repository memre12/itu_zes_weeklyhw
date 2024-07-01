# Turtle Avoidance Path Planner

This project implements a path planner for a TurtleSim simulator, designed to navigate a turtle from an initial position to a randomly generated goal position while avoiding randomly placed static obstacles.

## Path Planning for Random Target with A* Algorithm
<div align="center">
    <img src="https://github.com/memre12/itu_zes_weeklyhw/assets/114512711/be2385d4-1647-4dc1-83fa-081d20918485" alt="TurtleSim Region with Path" width="600" />
</div>

## Following Path with Pure Pursuit Control Algorithm
<div align="center">
    <img src="https://github.com/memre12/itu_zes_weeklyhw/assets/114512711/c4ede772-63c5-4c3b-aa9c-a98e92267910" alt="Screenshot from 2024-06-28 14-43-36" width="600" />
</div>

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Configuration](#configuration)
- [Path Planning Algorithms](##path-planning-and-control-algorithms)
  - [A* Algorithm](#A*-Algorithm)
  - [Pure Pursuit](###pure-pursuit-control-algorithm)
- [Contact](#contact)

## Introduction

The Turtle Avoidance Path Planner is a ROS2-based application designed to enable a turtle in the TurtleSim simulator to navigate towards a target location while avoiding obstacles. This project leverages the A* algorithm for efficient pathfinding and employs the Pure Pursuit control algorithm for smooth path following. OpenCV is utilized to capture and process the simulator window for obstacle detection, including filtering out the main turtle to avoid self-detection, while Xlib is employed for screen capturing.



## Features

- **Path Planning:** Utilizes the A* algorithm to find the optimal path from the initial position to the goal position.
- **Obstacle Detection:** Uses OpenCV to capture the TurtleSim window and identify obstacles.
- **Dynamic Target Generation:** Generates random target positions within the simulator window.
- **Path Following:** Implements the Pure Pursuit algorithm for smooth path following.
- **ROS2 Integration:** Leverages ROS2 for communication between nodes and services.

## Configuration

The project uses a YAML configuration file to specify parameters such as grid size, obstacle thresholds, and PID parameters. The configuration file is located in the `config` directory.

Example configuration (`config/config.yaml`):

```yaml
avoidance_turtle:
  ros__parameters:
    turtle_name: "turtle1"
    grid_width: 200
    grid_height: 200
    offset_x: 0.0
    offset_y: 0.0
    num_turtles: 12
    dilation_size: 8
    lookahead_distance_base: 0.4
    remove_width: 15
    remove_height: 12
```

This section explains how to configure the project using a YAML file, providing an example of the configuration parameters. Here are the key parameters:

- `turtle_name`: Name of the turtle in the simulation.
- `grid_width`: Width of the occupancy grid.
- `grid_height`: Height of the occupancy grid.
- `offset_x`: X-axis offset for the grid.
- `offset_y`: Y-axis offset for the grid.
- `num_turtles`: Number of turtles (obstacles) in the simulation.
- `dilation_size`: Size of the dilation used in obstacle detection.
- `lookahead_distance_base`: Base distance for the lookahead algorithm.
- `remove_width`: Width of the area to remove obstacles.
- `remove_height`: Height of the area to remove obstacles.


## lPath Planning and Control Algorithms

### A* Algorithm

The A* (A-star) algorithm is a popular pathfinding algorithm used to find the shortest path between a start node and a goal node. It combines the benefits of Dijkstra's algorithm and Greedy Best-First Search by using a heuristic to guide its search.

**How it works:**
- The algorithm maintains a priority queue of nodes to be explored, prioritizing nodes with the lowest cost, calculated as the sum of the cost to reach the node (G) and the estimated cost to the goal (H).
- It expands nodes by evaluating their neighbors, updating the cost if a cheaper path is found.
- The heuristic function used in this project is the Euclidean distance between the current node and the goal node.

**Advantages:**
- Guarantees the shortest path if the heuristic is admissible (i.e., it never overestimates the actual cost).
- Efficiently explores the most promising paths first.

### Pure Pursuit Control Algorithm

The Pure Pursuit algorithm is a control algorithm used for path tracking to follow a precomputed path smoothly. It calculates the curvature needed to steer the vehicle (turtle) towards a lookahead point on the path.

**How it works:**
- The algorithm selects a point on the path ahead of the vehicle's current position, called the lookahead point.
- It calculates the steering angle needed to reach this point based on the curvature, which is the inverse of the radius of the circle connecting the vehicle and the lookahead point.
- The vehicle's linear and angular velocities are adjusted to follow this trajectory smoothly.

**Advantages:**
- Provides smooth and stable path following.
- Simple to implement and computationally efficient.


## Contact

For any questions or suggestions, please feel free to contact:

- Name: Mehmet Emre Demir
- Email: fe-mehmetemre@hotmail.com

