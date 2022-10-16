#ifndef SEARCH_H
#define SEARCH_H

#include <vector>

//std::vector <uint32_t> search_function(size_t from, size_t to, size_t size_of_array, short ** matrix);

std::vector <size_t> search_graph(short* graph, size_t size, size_t from, size_t to);
#endif // SEARCH_H
