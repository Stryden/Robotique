#include "Pmr.h"

Pmr::Pmr()
: map_(NULL), start_(), finish_(), n_(0), graph_(NULL)
{
}

Pmr::Pmr(ArMap* map, ArPose start, ArPose finish, int n)
: map_(map), start_(start), finish_(finish), n_(n)
{	
	std::vector<double> tmp(n, 0);
	graph_ = arry(n, tmp);
	
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

	for (int i = 0; i < n_ - 2; ++i)
	{
		point = random_point(lines);
		points_.push_back(point);
	}
	points_.push_back(finish_);

	compute_distance(lines);
}

void
Pmr::compute_distance(std::vector<ArLineSegment>* obs)
{
	ArLineSegment segment;
	ArPose useless;
	int l = points_.size();

	for (int i = 0; i < l; ++i)
		for (int j = 0; j < l; ++j)
			for (auto o : *obs)
			{
				if (i != j)
				{
					segment = ArLineSegment(points_[i], points_[j]);
					if (segment.intersects(&o, &useless))
						graph_[i][j] = points_[i].findDistanceTo(points_[j]);
				}
			}
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
			for (auto line : *lines)
				if (line.getDistToLine(point) < 50)
					ok = true;
	}

	return point;
}

std::stack<double>
Pmr::get_path()
{
	return path_;
}

std::vector<ArPose>
Pmr::get_points()
{
	return points_;
}