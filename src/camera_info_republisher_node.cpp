#include <ros/ros.h>
#include "camera_info_republisher/camera_info_republisher.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "camera_info_republisher");

  CameraInfoRepublisher camera_info_republisher;

  return 0;
}