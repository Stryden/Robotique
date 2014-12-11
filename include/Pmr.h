#include "Aria.h"

#include <cstdlib>


class Pmr {
public:
	Pmr();
	Pmr(ArMap* map, ArPose start, ArPose finish, int n);
	~Pmr();

private:
	ArMap* map_;
	ArPose start_;
	ArPose finish_;
	
	int n_;
	double** graph_;


	void generate_graph();
	void compute_distance(std::vector<ArPose> points, std::vector<ArLineSegment> *obs);
	ArPose random_point(std::vector<ArLineSegment>* lines);

	double** get_graph();
public:
};