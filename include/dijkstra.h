#ifndef DIJKSTRA_H_
# define DIJKSTRA_H_

# include <iostream>
# include <stack>
# include <ctime>
# include <vector>
# include <cstdlib>
# include <algorithm>
# include "arry.h"

double dijkstra(arry g, unsigned int start, unsigned int end, std::stack<unsigned int>& path);

#endif // DIJKSTRA_H_