#include "camera_info_republisher/camera_info_republisher.h"

CameraInfoRepublisher::CameraInfoRepublisher() : nh_(), camera_info_received_(false)
{
    double publish_frequency;
    nh_.param("/camera_info_republisher/publish_frequency", publish_frequency, (double) 10.0);
    nh_.param("/camera_info_republisher/static_camera_info", static_camera_info_, true);
    nh_.param("/camera_info_republisher/camera_info_input_topic_name", camera_info_input_topic_name_, std::string("/camera/camera_info"));
    nh_.param("/camera_info_republisher/camera_info_output_topic_name", camera_info_output_topic_name_, std::string("/camera_info_republisher/camera/camera_info"));

    ros::Rate rate(publish_frequency);

    camera_info_subscriber_ = nh_.subscribe(camera_info_input_topic_name_, 1, &CameraInfoRepublisher::setCameraInfo, this);

    ROS_INFO("Waiting for camera info.");
    while (!camera_info_received_  && ros::ok())
    {
        ROS_INFO("Still waiting for camera info.");
        ros::spinOnce();
        rate.sleep();
    }

    if(static_camera_info_)
    {
        ROS_INFO("Static_camera_info was set to True so shutting down camera info subscriber.");
        camera_info_subscriber_.shutdown();
    }

    ROS_INFO("Starting camera info publisher.");

    camera_info_publisher_ = nh_.advertise<sensor_msgs::CameraInfo>(camera_info_output_topic_name_, 1);

    while (ros::ok())
    {
        camera_info_.header.seq = camera_info_.header.seq + 1;
        camera_info_.header.stamp = ros::Time::now();
        camera_info_publisher_.publish(camera_info_);

        ros::spinOnce();

        rate.sleep();
    }
}

void CameraInfoRepublisher::setCameraInfo(const sensor_msgs::CameraInfoConstPtr& camera_info)
{
    camera_info_ = *camera_info;
    camera_info_received_ = true;
    ROS_INFO("Received camera info.");
}