#include "Aria.h"

#include <stack>

class FollowPath
{
public:
	FollowPath(ArRobot* robot, ArActionGroup* wander, std::stack<ArPose> path, ArActionGoto* action, ArPose end);
	~FollowPath();

	void change_goal();
private:
	ArRobot* robot_;
	ArActionGroup* wander_;
	std::stack<ArPose> path_;
	ArActionGoto* action_;
	ArPose end_;
	
	ArFunctorC<FollowPath> myTaskCB_;
};