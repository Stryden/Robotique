#include "Pmr.h"

Pmr::Pmr()
: map_(NULL), start_(), finish_(), n_(0)
{
}

Pmr::Pmr(ArMap* map, ArPose start, ArPose finish, int n)
: map_(map), start_(start), finish_(finish), n_(n)
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
	std::vector<ArPose> points;
	ArPose point;

	*graph_ = new double[n_];
	for (int i = 0; i < n_; ++i)
		graph_[i] = new double[n_]();


	points.push_back(start_);
	lines = map_->getLines();

	for (int i = 0; i < 5000; ++i)
	{
		point = random_point(lines);
		points.push_back(point);
	}
	points.push_back(finish_);

	compute_distance(points, lines);
}

void
Pmr::compute_distance(std::vector<ArPose> points, std::vector<ArLineSegment>* obs)
{
	ArLineSegment segment;
	int l = points.size();

	for (int i = 0; i < l; ++i)
		for (int j = 0; j < l; ++i)
			for (auto o : *obs)
			{
				segment = ArLineSegment(points[i], points[i]);

				if (segment.intersects(&o, NULL))
					graph_[i][j] = ArPose::distanceBetween(points[i], points[j]);
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

double **
Pmr::get_graph()
{
	return graph_;
}