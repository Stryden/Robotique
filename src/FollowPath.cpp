#include "FollowPath.h"

FollowPath::FollowPath(ArRobot* robot, ArActionGroup* wander, std::stack<ArPose> path, ArActionGoto* action, ArPose end)
: robot_(robot),wander_(wander), path_(path), action_(action), end_(end), myTaskCB_(this, &FollowPath::change_goal)
{
	robot->addSensorInterpTask("FollowPath", 30, &myTaskCB_);
}

FollowPath::~FollowPath()
{

}

void
FollowPath::change_goal()
{
	ArPose curPose = robot_->getPose();

	while (Aria::getRunning && curPose != end_)
	{

		curPose = robot_->getPose();
		if (curPose == path_.top())
		{
			printf("chatte\n");
			path_.pop();
			action_->setGoal(path_.top());
		}

	}
}