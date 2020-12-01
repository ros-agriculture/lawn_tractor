#include <mbf_behaviorTree.h> 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
//-------------------------------------------------------------
// Simple Action to print a Goal Pose (PURE BT implementation)
//-------------------------------------------------------------

//Wait For Goal-------------------
BT::NodeStatus WaitForGoal::tick() {
    geometry_msgs::PoseStamped goalpose;
    geometry_msgs::PoseStampedConstPtr msg = 
      ros::topic::waitForMessage<geometry_msgs::PoseStamped>(goal_topic_,ros::Duration(600));
      if (msg == NULL){
         ROS_INFO("FAILED HERE");	
	 return NodeStatus::FAILURE;
      }
      else {
        setOutput<geometry_msgs::PoseStamped>("goal",*msg); //TODO: Pass around ConstPtr 
        return NodeStatus::SUCCESS; 
      }
}

BT::PortsList WaitForGoal::providedPorts(){
  return {BT::OutputPort<geometry_msgs::PoseStamped>("goal")};
}

//Get Path-------------------
BT::NodeStatus GetPathActionClient::tick() {
    actionlib::SimpleActionClient<mbf_msgs::GetPathAction> ac(getInput<std::string>("server_name").value(), true);
    ac.waitForServer(); //will wait for infinite time
    // send a goal to the action
    mbf_msgs::GetPathGoal goal;

    goal.target_pose = getInput<geometry_msgs::PoseStamped>("goalpose").value();
    ac.sendGoal(goal);
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
      return NodeStatus::FAILURE;
  }

BT::PortsList GetPathActionClient::providedPorts(){
  return{ 
  BT::InputPort<geometry_msgs::PoseStamped>("goalpose"),
  BT::InputPort<std::string>("server_name"),
  BT::OutputPort<mbf_msgs::GetPathResultConstPtr>("result") 
  };
}

//Execute Path-------------------
BT::NodeStatus ExePathActionClient::tick(){
  actionlib::SimpleActionClient<mbf_msgs::ExePathAction> ac(getInput<std::string>("server_name").value(), true);
  ac.waitForServer();
  mbf_msgs::ExePathGoal goal;
  mbf_msgs::GetPathResultConstPtr pathPtr = getInput<mbf_msgs::GetPathResultConstPtr>("pathPtr").value();
  nav_msgs::Path path = pathPtr->path;
  goal.path = path;
  ac.sendGoal(goal);

  bool finished_before_timeout = ac.waitForResult(ros::Duration(120.0)); //TODO: make this duration a rosparam / handle in the BT
  if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        switch(state.state_)
        {
          case actionlib::SimpleClientGoalState::SUCCEEDED:{
            mbf_msgs::ExePathResultConstPtr exePathPtr = ac.getResult();
            return NodeStatus::SUCCESS;
            break;
          }
          default:
            ROS_INFO("Failure to reach goal before timeout %s",state.toString().c_str());
            return NodeStatus::FAILURE;
            break;
        }
    }
  else
      return NodeStatus::FAILURE; 
}

BT::PortsList ExePathActionClient::providedPorts(){
  return{
    BT::InputPort<std::string>("server_name"),
    BT::InputPort<mbf_msgs::GetPathResultConstPtr>("pathPtr") 
  };
}

BT::NodeStatus RecoveryActionClient::tick(){
    actionlib::SimpleActionClient<mbf_msgs::RecoveryAction> ac(getInput<std::string>("server_name").value(), true);
    ac.waitForServer();
    mbf_msgs::RecoveryGoal goal;
    ac.sendGoal(goal); //do we have to populate the goal with anything?

    bool finished_before_timeout = ac.waitForResult(ros::Duration(120.0)); 
    if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        switch(state.state_)
        {
          case actionlib::SimpleClientGoalState::SUCCEEDED:{
            ROS_INFO("Correctly Recovered");
            return NodeStatus::SUCCESS;
            break;
          }
          default:
            ROS_INFO("Was Not correctly able to recover");
            return NodeStatus::FAILURE;
            break;
        }
    }
  else
      return NodeStatus::FAILURE; 
}

BT::PortsList RecoveryActionClient::providedPorts(){
  return{
   BT::InputPort<std::string>("server_name") 
  };
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mbf_behaviorTree");
  ros::NodeHandle nh("~");
  std::string xml_file;
  std::string pkgpath = ros::package::getPath("lawn_tractor_navigation"); // TODO: make this a param
  std::string filepathprefix = pkgpath + "/config/behavior_tree/";
  nh.param<std::string>("xml_file", xml_file, "movebaseflex_tree.xml");

  std::string completeFilepath = filepathprefix + xml_file;
  
  BehaviorTreeFactory factory;

  factory.registerNodeType<WaitForGoal>("WaitForGoal");
  factory.registerNodeType<GetPathActionClient>("GetPath");
  factory.registerNodeType<ExePathActionClient>("ExePath");
  factory.registerNodeType<RecoveryActionClient>("Recovery");
  auto tree = factory.createTreeFromFile(completeFilepath);

  NodeStatus status = NodeStatus::IDLE;

  PublisherZMQ publisher_zmq(tree);
  // printTreeRecursively(tree.rootNode());

  while( ros::ok() && (status == NodeStatus::IDLE || status == NodeStatus::RUNNING))
  {
    ros::spinOnce();
    status = tree.tickRoot();
    std::cout << status << std::endl;
    ros::Duration sleep_time(0.01);
    sleep_time.sleep();
  }

  return 0;
}
