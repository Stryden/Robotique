#include "Aria.h"

#include <cstdlib>
#include <stack>


typedef std::vector<std::vector<int>> arry;
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
	std::vector<ArPose> points_;
	arry graph_;


	void generate_graph();
	void compute_distance(std::vector<ArLineSegment> *obs);
	ArPose random_point(std::vector<ArLineSegment>* lines);

	arry get_graph();
public:
};