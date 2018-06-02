#ifndef _CAMERA_INFO_REPUBLISHER_H
#define _CAMERA_INFO_REPUBLISHER_H

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>

class CameraInfoRepublisher
{
    private:
        ros::NodeHandle nh_;
        std::string camera_info_input_topic_name_;
        std::string camera_info_output_topic_name_;
        sensor_msgs::CameraInfo camera_info_;
        bool static_camera_info_;
        bool camera_info_received_;

        ros::Subscriber camera_info_subscriber_;
        ros::Publisher camera_info_publisher_;

        void setCameraInfo(const sensor_msgs::CameraInfoConstPtr& camera_info);

    public:
        CameraInfoRepublisher();
        ~CameraInfoRepublisher(){}
};


#endif