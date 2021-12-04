#include "ros/ros.h"
#include "std_msgs/String.h"
#include "open_manipulator_msgs/KinematicsPose.h"
#include <tf2_ros/transform_broadcaster.h>

void poseCallback(const open_manipulator_msgs::KinematicsPose::ConstPtr& msg){
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;

  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "base";
  transformStamped.child_frame_id = "gripper_link";
  transformStamped.transform.translation.x = msg->pose.position.x;
  transformStamped.transform.translation.y = msg->pose.position.y;
  transformStamped.transform.translation.z = msg->pose.position.z;
  transformStamped.transform.rotation.x = msg->pose.orientation.x;
  transformStamped.transform.rotation.y = msg->pose.orientation.y;
  transformStamped.transform.rotation.z = msg->pose.orientation.z;
  transformStamped.transform.rotation.w = msg->pose.orientation.w;

  br.sendTransform(transformStamped);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "base_to_gripper_tf_broadcaster_node");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/gripper/kinematics_pose", 10, &poseCallback);

  ros::Rate loop_rate(200);
  while (ros::ok())
  {
    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
