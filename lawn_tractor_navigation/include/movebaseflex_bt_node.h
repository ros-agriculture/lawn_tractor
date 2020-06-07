#include <actionlib/client/simple_action_client.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <behaviortree_cpp_v3/bt_factory.h>
#include <behaviortree_cpp_v3/loggers/bt_zmq_publisher.h>
#include <actionlib_tutorials/FibonacciAction.h>
#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include <mbf_msgs/ExePathAction.h>
#include <mbf_msgs/GetPathAction.h>
#include <mbf_msgs/RecoveryAction.h>

using namespace BT;

class WaitForGoal : public BT::SyncActionNode
{
public:
    WaitForGoal(const std::string& name, const BT::NodeConfiguration& config):
    BT::SyncActionNode(name,config) {}
    BT::NodeStatus tick() override;
    static BT::PortsList providedPorts();
private:
    const std::string goal_topic_= "/move_base_simple/goal";
};

class GetPathActionClient : public BT::SyncActionNode
{
public:
    GetPathActionClient(const std::string& name, const BT::NodeConfiguration& config,ros::NodeHandle& nh): 
    BT::SyncActionNode(name,config),node_(nh){}
    BT::NodeStatus tick() override;
    static BT::PortsList providedPorts();
    using GetPath =  actionlib::SimpleActionClient<mbf_msgs::GetPathAction>;
private:
    ros::NodeHandle& node_;
};

class ExePathActionClient : public BT::SyncActionNode
{
    public:
        ExePathActionClient(const std::string& name, const BT::NodeConfiguration& config):
        BT::SyncActionNode(name,config){}
        BT::NodeStatus tick() override;
        static BT::PortsList providedPorts();
};
