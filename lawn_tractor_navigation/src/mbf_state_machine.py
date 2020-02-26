#!/usr/bin/env python

#from http://wiki.ros.org/move_base_flex/Tutorials/SimpleSmachForMoveBaseFlex
import rospy
import smach
import smach_ros

from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path

from mbf_msgs.msg import ExePathAction
from mbf_msgs.msg import GetPathAction
from mbf_msgs.msg import RecoveryAction


def main():
    rospy.init_node('mbf_state_machine')

    # Create SMACH state machine
    sm = smach.StateMachine(outcomes=['succeeded', 'aborted', 'preempted'])

    # Define userdata
    sm.userdata.goal = None
    sm.userdata.path = None
    sm.userdata.error = None
    sm.userdata.clear_costmap_flag = False
    sm.userdata.error_status = None

    with sm:
        # Goal callback for state WAIT_FOR_GOAL
        def goal_cb(userdata, msg):
            userdata.goal = msg
            return False

        # Monitor topic to get MeshGoal from RViz plugin
        smach.StateMachine.add(
            'WAIT_FOR_GOAL',
            smach_ros.MonitorState(
                '/move_base_simple/goal',
                PoseStamped,
                goal_cb,
                output_keys=['goal']
            ),
            transitions={
                'invalid': 'GET_PATH',
                'valid': 'WAIT_FOR_GOAL',
                'preempted': 'preempted'
            }
        )

        # Get path
        smach.StateMachine.add(
            'GET_PATH',
            smach_ros.SimpleActionState(
                '/move_base_flex/get_path',
                GetPathAction,
                goal_slots=['target_pose'],
                result_slots=['path']
            ),
            transitions={
                'succeeded': 'EXE_PATH',
                'aborted': 'WAIT_FOR_GOAL',
                'preempted': 'preempted'
            },
            remapping={
                'target_pose': 'goal'
            }
        )

        # Execute path
        smach.StateMachine.add(
            'EXE_PATH',
            smach_ros.SimpleActionState(
                '/move_base_flex/exe_path',
                ExePathAction,
                goal_slots=['path']
            ),
            transitions={
                'succeeded': 'WAIT_FOR_GOAL',
                'aborted': 'RECOVERY',
                'preempted': 'preempted'
            }
        )

        # Goal callback for state RECOVERY
        def recovery_path_goal_cb(userdata, goal):
            if userdata.clear_costmap_flag == False:
                goal.behavior = 'clear_costmap'
                userdata.clear_costmap_flag = True
            else:
                goal.behavior = 'straf_recovery'
                userdata.clear_costmap_flag = False

        # Recovery
        smach.StateMachine.add(
            'RECOVERY',
             smach_ros.SimpleActionState(
                'move_base_flex/recovery',
                RecoveryAction,
                goal_cb=recovery_path_goal_cb,
                input_keys=["error", "clear_costmap_flag"],
                output_keys = ["error_status", 'clear_costmap_flag']
            ),
            transitions={
                'succeeded': 'GET_PATH',
                'aborted': 'aborted',
                'preempted': 'preempted'
            }
        )

    # Create and start introspection server
    sis = smach_ros.IntrospectionServer('smach_server', sm, '/SM_ROOT')
    sis.start()

    # Execute SMACH plan
    sm.execute()

    # Wait for interrupt and stop introspection server
    rospy.spin()
    sis.stop()

if __name__=="__main__":
    main()