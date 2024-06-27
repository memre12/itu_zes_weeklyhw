import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    
    config = os.path.join(
        get_package_share_directory('project_cpp'),
        'config',
        'config.yaml'
    )

    project_cpp_node = Node(
        package='project_cpp',
        executable='avoidance',
        name='avoidance_turtle',
        output='screen',
        parameters=[config]
    )

    turtlesim_node = Node(
        package='turtlesim',
        executable='turtlesim_node',
        name='turtlesim_node',
        output='screen'
    )

    ld.add_action(project_cpp_node)
    ld.add_action(turtlesim_node)

    return ld
