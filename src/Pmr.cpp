#include "Pmr.h"

Pmr::Pmr(ArMap* map, ArPose& start, ArPose& finish)
: map_(map), start_(start), finish_(finish)
{
	generate_graph();
}

Pmr::~Pmr()
{
}

void
Pmr::generate_graph()
{
	std::vector<ArLineSegment>* lines;
	ArPose point;

	points_.push_back(start_);

	lines = map_->getLines();

	for (int i = 0; i < 5000; ++i)
	{
		point = random_point(lines);
		points_.push_back(point);
	}
	points_.push_back(finish_);

	graph_ = Node(start_, points_);
}

ArPose
Pmr::random_point(std::vector<ArLineSegment>* lines)
{
	bool ok = true;
	ArPose min = map_->getMinPose();
	ArPose max = map_->getMaxPose();
	ArPose point;

	if (min == NULL || max == NULL)
	{
		min = map_->getLineMinPose();
		max = map_->getLineMaxPose();
	}

	while (ok)
	{
		point = ArPose(rand(), rand());
		ok = false;

		if (min < point && point < max)
		{
			for (auto line : *lines)
			{
				if (line.getDistToLine(point) < 50)
					ok = true;
			}
		}
	}

	return point;
}

Node&
Pmr::get_graph()
{
	return graph_;
}