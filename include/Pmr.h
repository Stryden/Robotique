#ifndef PMR_H_
# define PMR_H_

# include "Aria.h"
# include "dijkstra.h"
# include "arry.h"

# include <cstdlib>
# include <stack>
# include <queue>

class Pmr {
public:
	Pmr();
	Pmr(ArMap* map, ArPose start, ArPose finish, int n);
	~Pmr();

	unsigned int getPath(std::queue<ArPose>& path);

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

#endif // PMR_H_