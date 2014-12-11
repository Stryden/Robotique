#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define NB_NODES 10 // Cannot be 0 or 1

unsigned int dijkstra(unsigned int g[NB_NODES * NB_NODES], unsigned int start, unsigned int end, std::stack<unsigned int>& path) {
	unsigned int	dist[NB_NODES];
	int				pred[NB_NODES];
	std::vector<unsigned int> Q;
	unsigned int	min_dist;
	unsigned int	min;
	unsigned int	alt;
	unsigned int	n;

	for (unsigned int i = 0; i < NB_NODES; ++i) {
		dist[i] = INT_MAX;
		pred[i] = -1;
		Q.push_back(i);
	}
	dist[start] = 0;

	while (!Q.empty()) {
		min_dist = INT_MAX;
		min = -1;
		for (auto v : Q) {
			if (dist[v] <= min_dist) {
				min_dist = dist[v];
				min = v;
			}
		}

		Q.erase(std::remove(Q.begin(), Q.end(), min), Q.end());

		for (auto v : Q) {
			if (g[min * NB_NODES + v]) {
				alt = dist[min] + g[min * NB_NODES + v];
				if (alt < dist[v]) {
					dist[v] = alt;
					pred[v] = min;
				}
			}
		}
	}

	n = end;
	while (n != start && n != -1) {
		path.push(n);
		n = pred[n];
	}

	return dist[end];
}


int _tmain(int argc, _TCHAR* argv[])
{
	/* Initialization of g */
	unsigned int g[NB_NODES * NB_NODES] = { 0 };
	std::srand(std::time(0));
	for (unsigned int i = 0; i < 2 * NB_NODES; ++i) {
		unsigned int val = std::rand() % 150;
		g[std::rand() % (NB_NODES * NB_NODES)] = val;
	}

	std::stack<unsigned int> path;
	unsigned int length = dijkstra(g, 0, NB_NODES - 1, path);
	unsigned int node;
	std::cout << "Path found : " << std::endl;
	while (path.size()) {
		std::cout << "* " << path.top() << std::endl;
		path.pop();
	}
	return 0;
}