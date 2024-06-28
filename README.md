# ITU SCT Autonomous Group Projects and Assignments

<h1 align="center">
  <img src="https://github.com/memre12/itu_zes_weeklyhw/assets/114512711/a67b6b5c-b0ba-46dd-8ee0-92d1709f0a0f" alt="itu-gae">
</h1>

In this GitHub repository, I demonstrate solutions of assignments and projects. These topics include OOP (Object Oriented Programming) concepts, basic and advanced uses of the C++ language, basic and advanced uses of the ROS2 framework used in robotics, localization, path planning, mapping, SLAM, low-level and high-level controller designs, perception, etc. that make up autonomous software, and finally the proper Github usage.

## Contents
Brief descriptions and content for the weekly projects and assignments are listed below:

- Week1: This project aims to teach advanced C++ programming through the implementation of `structs` and `classes`, focusing on mathematical operations, object-oriented principles, error handling, and user interaction. Explorers will learn to `encapsulate` data and methods within classes, manage errors using `try-catch` blocks, and interact with users via the `terminal`. The project also covers the use of `STL containers`, `template classes`, and best practices for code organization, including the use of `namespaces` and modular code structure. Additionally, learners will enhance their skills in algorithm development for tasks like matrix operations and explore advanced improvements such as using `CMake` for building the project and sharing work on GitHub with proper documentation.

- Week2: This project aims to explore the various variable types in C++ and their properties. It focuses on creating combinations of `int`, `float`, and `double` with modifiers like `long`, `short`, and `unsigned`, understanding their sizes, and their limits. Additionally, the project covers the use of `auto`, `const`, and `constexpr` keywords, as well as fixed-width integer and float types (e.g., `int32_t`, `float64_t`), `size_t`, and `wchar_t`. The goal is to provide a deep understanding of variable types, memory usage, and best practices in C++ programming.

- Week3: This project focuses on exploring pointers in C++, including their fundamentals and smart pointer variants (`auto_ptr`, `unique_ptr`, `shared_ptr`, `weak_ptr`). Learners will investigate the limitations of raw pointers, such as memory leaks and dangling pointers, and learn the appropriate use cases for each smart pointer type based on ownership models. Practical implementation involves creating a `SmartPointer` class and utilizing standard smart pointers to demonstrate memory management operations. The project culminates in a report summarizing research findings and includes source code showcasing pointer functionalities.

- Week4: This assignment tasks learners with creating a restaurant bot in C++ using OOP principles. The bot interacts with users through a terminal interface, offering menu selections from a provided menu.json file, focusing on modularization, error handling, and clear documentation. Key classes include `MenuItem`, `Starter`, `Salad`, `MainCourse`, `Drink`, `Appetizer`, `Dessert`, `Menu`, and `User`, encapsulated within the proper namespaces. Each food type class inherits from `MenuItem` and includes specific attributes like temperature for Starter and toppings for Salad. The bot also includes functionality to suggest random menus or menus tailored to user-defined taste balances. A report on class relationships(`UML Diagram`) using OOP concepts and `Doxygen-style` documentation are also part of the assignment requirements.

- Week5: This assignment involves designing a graphical user interface (`GUI`) in C++ using `Qt` for a restaurant bot previously implemented in a terminal interface. Students will utilize `Qt Designer` and `Qt Creator` to create a front-end interface that connects seamlessly with the existing back-end code handling menu functionalities from a menu.json file. The GUI should maintain all functionalities of the previous assignment while enhancing the user experience with a visually appealing design. Learners are encouraged to adhere to general coding practices such as consistent style, descriptive variable names, modularization, and error handling as well as documentation using `Doxygen` format.

- Week6: This project focuses on leveraging ROS2 for two distinct tasks: First, developing ROS2 nodes to publish and subscribe to image data using `sensor_msgs::msg::Image`, integrating basic `OpenCV` filters like `Gaussian Blur` and `Canny Edge` Detection, and configuring parameters via YAML files. Second, implementing a joystick controller for manipulating turtles in `turtlesim`, mapping joystick inputs to `adjust turtle velocities`, and incorporating functionalities for `clearing`/`resetting` the environment, `spawning` new turtles, and `managing pen` settings. This assignment aims to provide a comprehensive experience in ROS2 development, encompassing `image processing`, `simulation control`, and adherence to C++ coding standards.

- Week7: In this project, the Turtle Avoidance Path Planner is a ROS2-based application that enables a turtle in the TurtleSim simulator to navigate towards a target location while avoiding obstacles. The project leverages the A* algorithm for efficient pathfinding and employs the Pure Pursuit control algorithm for smooth path following. The application uses OpenCV to capture and process the simulator window for obstacle detection. This includes filtering out the main turtle to avoid self-detection. Additionally, Xlib is employed for screen capturing. The system dynamically generates random target positions within the simulator window, ensuring a versatile and adaptive navigation experience. Through the integration of ROS2, the application facilitates communication between nodes and services, enabling seamless interaction and data exchange. The project is configured using a YAML file, where parameters such as grid size, number of obstacles and PID parameters can be specified, allowing for easy customization and optimization of the path planning and control algorithms.

For further details of a project, you may refer to the corresponding README.md under that project folder.

## Installation
Necessary instructions to build and use the specific project are explained in the corresponding README.md files in each weekly project. Feel free to explore the repository and access the solutions for different research assignments. You can download the files directly or clone the entire repository to your local machine.

## Disclaimer 
The solutions provided in this repository are for educational and reference purposes only. Users are encouraged to understand and learn from the solutions rather than presenting them as their own work. If you are already a member of the ITU SCT Autonomous Group, you are encouraged to use this repository only for ideas where you are stuck, other users are welcome to use this repository for educational purposes.

## Contact

For any questions or suggestions, please feel free to contact:

- Name: Mehmet Emre Demir
- Email: fe-mehmetemre@hotmail.com
