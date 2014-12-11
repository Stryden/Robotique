#include "Aria.h"

ArActionGroup *wander;

void wanderMode(void)
{
	wander->activateExclusive();
}

int main(int argc, char** argv)
{
	// the connection
	ArSimpleConnector con(&argc, argv);
	if (!con.parseArgs())
	{
		con.logOptions();
		return 1;
	}

	ArRobot robot;
	ArSonarDevice sonar;
	// add the sonar object to the robot
	robot.addRangeDevice(&sonar);

	// open the connection to the robot; if this fails exit
	if (!con.connectRobot(&robot))
	{
		printf("Could not connect to the robot.\n");
		return 2;
	}
	printf("Connected to the robot. (Press Ctrl-C to exit)\n");

	Aria::init();
	ArPose end = ArPose(-2000, -2000);

	/* - the action group for wander actions: */
	wander = new ArActionGroup(&robot);
	// if we're stalled we want to back up and recover
	wander->addAction(new ArActionStallRecover, 100);
	// react to bumpers
	wander->addAction(new ArActionBumpers, 75);
	// turn to avoid things closer to us
	wander->addAction(new ArActionAvoidFront("Avoid Front Near", 225, 0), 50);
	// turn avoid things further away
	wander->addAction(new ArActionAvoidFront, 45);
	// keep moving
	wander->addAction(new ArActionGoto("Goto", end, 20, 400), 25);

	robot.enableMotors();
	wanderMode();
	robot.run(true);
	Aria::exit(0);
}
