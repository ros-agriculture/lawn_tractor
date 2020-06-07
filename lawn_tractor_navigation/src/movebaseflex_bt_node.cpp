#include <movebaseflex_bt_node.h> 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
//-------------------------------------------------------------
// Simple Action to print a Goal Pose (PURE BT implementation)
//-------------------------------------------------------------

BT::NodeStatus WaitForGoal::tick() {
    geometry_msgs::PoseStamped goalpose;
    geometry_msgs::PoseStampedConstPtr msg = 
      ros::topic::waitForMessage<geometry_msgs::PoseStamped>(goal_topic_,ros::Duration(10));
      if (msg == NULL){
        ROS_INFO("No Goal PoseStamped Recieved");
        return NodeStatus::FAILURE;
      }
      else {
        ROS_INFO("SUCCESS");
        setOutput<geometry_msgs::PoseStamped>("goal",*msg); //TODO: Pass around ConstPtr 
        return NodeStatus::SUCCESS; 
      }
}

BT::PortsList WaitForGoal::providedPorts(){
  return {BT::OutputPort<geometry_msgs::PoseStamped>("goal")};
}

BT::NodeStatus GetPathActionClient::tick() {
    ROS_INFO("GetPathActionTick");
    actionlib::SimpleActionClient<mbf_msgs::GetPathAction> ac(getInput<std::string>("server_name").value(), true);
    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer(); //will wait for infinite time
    ROS_INFO("Action server started, sending goal.");
    // send a goal to the action
    mbf_msgs::GetPathGoal goal;

    goal.target_pose = getInput<geometry_msgs::PoseStamped>("goalpose").value();
    ac.sendGoal(goal);
    std::cout << "after goal" << std::endl;
    //wait for the action to return
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0)); //TODO: Probably shorten the timout

    if (finished_before_timeout)
    {
      actionlib::SimpleClientGoalState state = ac.getState();
      switch(state.state_)
      {
        case actionlib::SimpleClientGoalState::SUCCEEDED:{
          mbf_msgs::GetPathResultConstPtr outPathPtr = ac.getResult();
          setOutput<mbf_msgs::GetPathResultConstPtr>("result",outPathPtr);
          return NodeStatus::SUCCESS;
          break;
        }
        default:
          return NodeStatus::FAILURE;
          break;
      }
    }
    else
      ROS_INFO("Action did not finish before the time out.");
      return NodeStatus::FAILURE;
  }

BT::PortsList GetPathActionClient::providedPorts(){
  return{ 
  BT::InputPort<geometry_msgs::PoseStamped>("goalpose"),
  BT::InputPort<std::string>("server_name"),
  BT::OutputPort<mbf_msgs::GetPathResultConstPtr>("result") 
  };
}

BT::NodeStatus ExePathActionClient::tick(){
  actionlib::SimpleActionClient<mbf_msgs::ExePathAction> ac(getInput<std::string>("server_name").value(), true);
  ac.waitForServer();
  mbf_msgs::ExePathGoal goal;
  mbf_msgs::GetPathResultConstPtr pathPtr = getInput<mbf_msgs::GetPathResultConstPtr>("pathPtr").value();
  nav_msgs::Path path = pathPtr->path;
  goal.path = path;
  ac.sendGoal(goal);
  return NodeStatus::SUCCESS;
}

BT::PortsList ExePathActionClient::providedPorts(){
  return{
    BT::InputPort<std::string>("server_name"),
    BT::InputPort<mbf_msgs::GetPathResultConstPtr>("pathPtr") 
  };
}
//----------------------------------------------------------
  // Simple tree, used to execute once each action.
  static const char* xml_text = R"(
 <root >
     <BehaviorTree>
        <Sequence>
            <Timeout msec="10000">
                <WaitForGoal goal="{goal_pose}" />
            </Timeout>
            <GetPath server_name="move_base_flex/get_path" goalpose="{goal_pose}" result="{pathResultPtr}"/>
            <ExePath server_name="move_base_flex/exe_path" pathPtr="{pathResultPtr}" />
        </Sequence>
     </BehaviorTree>
 </root>
 )";

int main(int argc, char **argv)
{
  ros::init(argc, argv, "movebaseflex_bt_node");
  ros::NodeHandle nh;

  BehaviorTreeFactory factory;

  NodeBuilder getPathActionClient_withNH = [&nh](const std::string& name,const NodeConfiguration& config){
    return std::make_unique<GetPathActionClient>(name,config,nh);
  };

  std::cout << "Here: post builder" << std::endl;

  factory.registerNodeType<WaitForGoal>("WaitForGoal");
  factory.registerBuilder<GetPathActionClient>("GetPath",getPathActionClient_withNH);
  factory.registerNodeType<ExePathActionClient>("ExePath");
  auto tree = factory.createTreeFromText(xml_text);
  NodeStatus status = NodeStatus::IDLE;

  // TODO: Not sure why this logger is not working
  // RosoutLogger logger(tree.rootNode(),ros::console::Level::Info); 
  PublisherZMQ publisher_zmq(tree);
  printTreeRecursively(tree.rootNode());

  while( ros::ok() && (status == NodeStatus::IDLE || status == NodeStatus::RUNNING))
  {
    std::cout << "Here: MAIN" << std::endl;
    ros::spinOnce();
    status = tree.tickRoot();
    std::cout << status << std::endl;
    ros::Duration sleep_time(0.01);
    sleep_time.sleep();
  }

  return 0;
}

