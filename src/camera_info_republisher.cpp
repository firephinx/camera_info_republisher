#include "camera_info_republisher/camera_info_republisher.h"

CameraInfoRepublisher::CameraInfoRepublisher() : nh_(), rate_(10), camera_info_received_(false)
{
    nh_.param("static_camera_info", static_camera_info_, true);
    nh_.param("camera_info_input_topic_name", camera_info_input_topic_name_, std::string("/camera/camera_info"));
    nh_.param("camera_info_output_topic_name", camera_info_output_topic_name_, std::string("/camera_info_republisher/camera/camera_info"));

    camera_info_subscriber_ = nh_.subscribe(camera_info_input_topic_name_, 1, &CameraInfoRepublisher::setCameraInfo, this);

    ROS_INFO("Waiting for camera info.");
    while (!camera_info_received_  && ros::ok())
    {
        ros::spinOnce();
        rate_.sleep();
    }

    if(static_camera_info_)
    {
        ROS_INFO("Received camera info. Shutting down camera info subscriber.");
        camera_info_subscriber_.shutdown();
    }
    else
    {
        ROS_INFO("Received camera info.");
    }

    ROS_INFO("Starting camera info publisher.");

    camera_info_publisher_ = nh_.advertise<sensor_msgs::CameraInfo>(camera_info_output_topic_name_, 1);

    while (ros::ok())
    {
        camera_info_publisher_.publish(camera_info_);

        ros::spinOnce();

        rate_.sleep();
    }
}

void CameraInfoRepublisher::setCameraInfo(const sensor_msgs::CameraInfoConstPtr& camera_info)
{
    camera_info_ = *camera_info;
    camera_info_received_ = true;
}