/**
 * Simple ROS Node
 **/
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int count = 0;
char message[20];

void MasterMsgCallback(const std_msgs::String::ConstPtr& msg)
{
    msg->data.copy(message,10,0);
    count++;
    ROS_INFO("I heard: %s", msg->data.c_str());
}

int main(int argc, char* argv[])
{
    //this must be called before anything else ROS-related
    ros::init(argc, argv, "TcpProcess_node");

    // Create a ROS node handle
    ros::NodeHandle nh_TcpProcess;

    ROS_INFO("Hello World TcpProcess!!");

    //subscribe to MasterMsg topic
    ros::Subscriber sub = nh_TcpProcess.subscribe("MasterMsg", 1000, MasterMsgCallback);

    while(ros::ok)
    {
        if(count >= 1)
        {
            //if M command(move)
            ROS_INFO("%s", message);
            ROS_INFO("%c", message[0]);
            ROS_INFO("%c", message[1]);
            switch(message[0])
            {
                case 'M':
                    ROS_INFO("I got a move command");
                    switch(message[1])
                    {
                        case '1':
                            ROS_INFO("Move to M1");
                            break;
                        case '2':
                            ROS_INFO("Move to M2");
                            break;
                        case '3':
                            ROS_INFO("Move to M3");
                            break;
                        default:
                            ROS_INFO("Unknown move command");
                            break;
                    }                    
                    break;
                case 'R':
                    ROS_INFO("I got a Report command");
                    break;
                default:
                    ROS_INFO("???????"); 
                    break;
            }    
            count--;
        }
        ros::spinOnce();
    }
    
    //Dont exit the program
    ros::spin();
}