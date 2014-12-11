#include "Aria.h"

#include <vector>

class Node;
typedef std::pair<Node*, int> Edge;

class Node {
public:
	Node();
	Node(ArPose point, std::vector<ArPose> points);
	~Node();

private:
	ArPose point_;
	std::vector<Edge> neighbors_;

	void compute_neighbors(std::vector<ArPose> points);
public:
	std::vector<Edge> get_neighbors_();
	ArPose get_point();

};