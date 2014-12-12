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

unsigned int
Pmr::getPath(std::queue<ArPose>& path) {
	std::stack<unsigned int> idx;
	std::cout << "Looking for path between ";
	std::cout << points_[0].getX() << "; " << points_[0].getY() << " and ";
	std::cout << points_[n_ - 1].getX() << "; " << points_[n_ - 1].getY() << std::endl;

	unsigned int dist = dijkstra(graph_, 0, n_ - 1, idx);
	
	std::cout << "Dijkstra gave us a " << idx.size() << " nodes long path for a distance of " << dist << std::endl;
	if (dist == 0)
		std::cout << "It failed; so we fallback on our basic approach" << std::endl;

	while (!idx.empty()) {
		path.push(points_[idx.top()]);
		idx.pop();
	}
	
	return dist;
}

void
Pmr::generate_graph()
{
	std::cout << "Generating graph" << std::endl;

	std::vector<ArLineSegment>* lines;
	ArPose point;

	points_.push_back(start_);
	lines = map_->getLines();

	std::cout << "  - " << n_ << " points" << std::endl;
	std::cout << "  - " << lines->size() << " obstacles" << std::endl;
	std::cout << "  - " << n_ << " points" << std::endl;

	for (int i = 0; i < n_ - 2; ++i)
	{
		point = random_point(lines);
		points_.push_back(point);
	}
	points_.push_back(finish_);

	std::cout << "Showing some points" << std::endl;
	for (unsigned int i = 0; i < n_ && i < 10; ++i)
		std::cout << "  - " << "points[" << i << "] = " << points_[i].getX() << "; " << points_[i].getY() << std::endl;
	std::cout << "  - " << "points[" << (n_ - 1) << "] = " << points_[n_ - 1].getX() << "; " << points_[n_ - 1].getY() << std::endl;

	std::cout << "Computing distances" << std::endl;

	compute_distance(lines);

	std::cout << "Showing some distances" << std::endl;
	for (unsigned int i = 0; i < n_ && i < 10; ++i)
		std::cout << "  - " << "dist(" << 0 << ", " << i << ") = " << graph_[0][i] << std::endl;
	std::cout << "  - " << "dist(" << 0 << ", " << (n_ - 1) << ") = " << graph_[0][n_ - 1] << std::endl;
}

void
Pmr::compute_distance(std::vector<ArLineSegment>* obs)
{
	ArPose			useless;
	bool			colliding = false;
	double			dist;
	unsigned int	nb_links = 0;

	for (int i = 0; i < n_; ++i) {
		if ((i + 1) % 100 == 0)
			std::cout << "  * Computed distances for the " << (i + 1) << " first nodes sons" << std::endl;
		for (int j = i + 1; j < n_; ++j) {
			dist = points_[i].squaredFindDistanceTo(points_[j]);
			if (dist > 360000 && dist < 3000000) { // This is a threshold
				colliding = false;
				for (auto& o : *obs) {
					if (ArLineSegment(points_[i], points_[j]).intersects(&o, &useless)) {
						colliding = true;
						break;
					}
				}
				if (!colliding) {
					graph_[i][j] = graph_[j][i] = dist;
					nb_links++;
				}
			}
		}
	}
	std::cout << "A total of " << nb_links << " aretes were created" << std::endl;
}

ArPose
Pmr::random_point(std::vector<ArLineSegment>* lines)
{
	bool ko = true;
	ArPose min = map_->getMinPose();
	ArPose max = map_->getMaxPose();
	ArPose point;

	if (min == NULL || max == NULL)
	{
		min = map_->getLineMinPose();
		max = map_->getLineMaxPose();
	}

	while (ko)
	{
		point = ArPose(fmod(std::rand() + min.getX(), max.getX()), fmod(std::rand() + min.getY(), max.getY()));
		ko = false;

		if (min < point && point < max) {
			for (auto line : *lines) {
				if (line.getDistToLine(point) < 400) {
					ko = true;
					break;
				}
			}
		}
	}

	return point;
}