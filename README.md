# camera_info_republisher

This ros package is used for republishing a camera_info topic locally.

## Configuration Instructions
1. Modify the parameters in the launch/camera_info_republisher.launch file to your liking.
2. `static_camera_info` set to `true` subscribes to the `camera_info_input_topic_name` topic once and saves the sensor_msgs::CameraInfo message that is sent to the camera_info_republisher node. Afterwards, the camera_info_republisher node publishes the saved CameraInfo on the `camera_info_output_topic_name` at the `publish_frequency` rate.
2. `static_camera_info` set to `false` continually subscribes to the `camera_info_input_topic_name` topic. Then, the camera_info_republisher node publishes the most recently saved CameraInfo on the `camera_info_output_topic_name` at the `publish_frequency` rate.

## Usage Instructions
1. First build the ros package using `catkin_make` in your catkin workspace.
2. Source your `devel/setup.bash` in your catkin workspace.
3. Start the camera_info_republisher node with the command `roslaunch camera_info_republisher camera_info_republisher.launch`.