#include "Node.h"
#include <iostream>

Node::Node()
: point_(NULL)
{
}

Node::Node(ArPose point, std::vector<ArPose> points)
: point_(point)
{
	compute_neighbors(points);
}


Node::~Node()
{
}

void
Node::compute_neighbors(std::vector<ArPose> points)
{
	for (auto point : points)
	{

	}
}

std::vector<Edge>
Node::get_neighbors_()
{
	return neighbors_;
}

ArPose
Node::get_point()
{
	return point_;
}
