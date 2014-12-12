#include "dijkstra.h"

#define NB_NODES 10 // Cannot be 0 or 1

double dijkstra(arry g, unsigned int start, unsigned int end, std::stack<unsigned int>& path) {
	unsigned int				nb_nodes = g.size();
	
	std::vector<double>			dist (nb_nodes, INT_MAX);
	std::vector<int>			pred (nb_nodes, -1);
	std::vector<unsigned int>	Q;

	unsigned int	min_dist;
	unsigned int	min;
	unsigned int	alt;
	unsigned int	n;

	for (unsigned int i = 0; i < nb_nodes; ++i)
		Q.push_back(i);
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
			if (g[min][v] > 360000) { // here is a threshold
				alt = dist[min] + g[min][v];
				if (alt < dist[v]) {
					dist[v] = alt;
					pred[v] = min;
				}
			}
		}
	}

	std::cout << "Path is like this (reverse order) :" << std::endl;
	n = end;
	while (n != start && n != -1) {
		if (pred[n] != -1)
			std::cout << "  - " << pred[n] << " to " << n << " : " << g[pred[n]][n] << std::endl;
		path.push(n);
		n = pred[n];
	}

	return (n == start) ? dist[end] : 0;
}

/*
int main(int argc, char* argv[])
{
	unsigned int nb_nodes = 10;

	// Initialization of g
	std::vector<double> tmp(nb_nodes, 0);
	arry g(nb_nodes, tmp);

	std::srand(std::time(0));
	for (unsigned int i = 0; i < 2 * nb_nodes; ++i) {
		double val = std::rand() % 150 / 7;
		g[std::rand() % nb_nodes][std::rand() % nb_nodes] = val;
	}

	std::stack<unsigned int> path;
	unsigned int length = dijkstra(g, 0, nb_nodes - 1, path);
	unsigned int node;
	std::cout << "Path found : " << std::endl;
	while (path.size()) {
		std::cout << "* " << path.top() << std::endl;
		path.pop();
	}
	return 0;
}*/