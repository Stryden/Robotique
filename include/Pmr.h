#include "Aria.h"
#include "Node.h"

#include <cstdlib>


class Pmr {
public:
	Pmr(ArMap* map, ArPose& start, ArPose& finish);
	~Pmr();

private:
	ArMap* map_;
	ArPose& start_;
	ArPose& finish_;
	std::vector<ArPose> points_;
	Node graph_;

	void generate_graph();
	ArPose random_point(std::vector<ArLineSegment>* lines);

	Node& get_graph();
public:
};