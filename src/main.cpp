#include "Aria.h"
#include "Pmr.h"

ArActionGroup *wander;

void wanderMode(void)
{
	wander->activateExclusive();
}

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		printf("Error\n");
		return 3;
	}

	ArMap map;

	if (!map.readFile(argv[1]))
	{
		printf("Error Map\n");
		return 4;
	}

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
	ArPose start = robot.getPose();
	ArPose end = ArPose(atoi(argv[2]), atoi(argv[3]));
	
	printf("Compute graph...\n");
	Pmr pmr = Pmr(&map, start, end, atoi(argv[4]));
	printf("end\n");
	
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
