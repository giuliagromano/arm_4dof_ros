#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

// Callback function for 'joint_states' topic
void joint_statesCallback(const sensor_msgs::JointState::ConstPtr& msg){
  
  ROS_INFO("Received joint_state message:");
  // Print joint positions
  for (size_t i = 0; i < msg->position.size(); i++)  {
  	ROS_INFO("Position of Joint %s: %f",msg->name[i].c_str() , msg->position[i]);
  }
}

int main(int argc, char** argv)
{
  // Initialize ROS node
  ros::init(argc, argv, "arm_controller_node");
  ros::NodeHandle node;

  // Create a subscriber 
  ros::Subscriber jointstates_Sub = node.subscribe("arm/joint_states", 10, joint_statesCallback);
 
  // Create publishers 
  ros::Publisher joint0_Pub = node.advertise<std_msgs::Float64>("arm/joint0_position_controller/command", 1);
  ros::Publisher joint1_Pub = node.advertise<std_msgs::Float64>("arm/joint1_position_controller/command", 1);
  ros::Publisher joint2_Pub = node.advertise<std_msgs::Float64>("arm/joint2_position_controller/command", 1);
  ros::Publisher joint3_Pub = node.advertise<std_msgs::Float64>("arm/joint3_position_controller/command", 1);
  ros::Rate loopRate(10); 
    
  if(argc != 5){
 	ROS_INFO("Repeat the command with the right number of the desired joint positions...");
 	return 0;
  }
  
  double position_j0 = std::stod(argv[1]);
  double position_j1 = std::stod(argv[2]);
  double position_j2 = std::stod(argv[3]);
  double position_j3 = std::stod(argv[4]);
  
  std_msgs::Float64 joint0_command, joint1_command, joint2_command, joint3_command;

  joint0_command.data = position_j0;  
  joint1_command.data = position_j1; 
  joint2_command.data = position_j2; 
  joint3_command.data = position_j3;  
  
  while (ros::ok()) {

	ROS_INFO("Position command to joint0: %.2f", joint0_command.data);
	joint0_Pub.publish(joint0_command);
	
	ROS_INFO("Position command to joint1: %.2f", joint1_command.data);
	joint1_Pub.publish(joint1_command);
	
	ROS_INFO("Position command to joint2: %.2f", joint2_command.data);
	joint2_Pub.publish(joint2_command);

	ROS_INFO("Position command to joint3: %.2f", joint3_command.data);
	joint3_Pub.publish(joint3_command);
	
	ros::spinOnce();
	loopRate.sleep();
  }
	 
  return 0;
}
