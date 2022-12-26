#include "search.h"
#include <algorithm>
#include <list>

//void write_results(size_t from, size_t to, short* parents, std::vector <size_t>* result);
//bool bfs(short* graph, short size, short to, short* visited, std::list<short>& buffer, short* parents) {
//    if (buffer.empty()) return false;

//    short from = buffer.front();
//    buffer.pop_front();

//    visited[from] = 1;
//    if (from == to) {
//        return true;
//    }

//    for (size_t i = 0; i < size; ++i) {
//        if (graph[from*size + i] == 0) continue;
//        if (visited[i] == 1) continue;
//        if (std::find(buffer.begin(), buffer.end(), i) != buffer.end()) continue;

//        parents[i] = from;
//        buffer.push_back(i);
//    }
//    return bfs(graph, size, to, visited, buffer, parents);
//}

//std::vector <size_t> search_graph(short* graph, size_t size, size_t from, size_t to) {
//    short* visited = new short[size];
//    short* parents = new short[size];
//    std::vector <size_t> results;

//    // don't visit
//    for (size_t i = 0; i < size; ++i) {
//        visited[i] = 0;
//    }

//    std::list<short> buffer;
//    buffer.push_back(from - 1);
//    bfs(graph, size, to, visited, buffer, parents);

//    write_results(from - 1, to - 1, parents, &results);

//    // free memory
//    delete[] visited;
//    delete[] parents;
//    return results;
//}

//void write_results(size_t from, size_t to, short* parents, std::vector <size_t> * result) {
//    if (to == from) {
//        result->push_back(to + 1);
//        return;
//    }
//    size_t prefrom = parents[to];
//    write_results(from, prefrom, parents, result);
//    result->push_back(to + 1);
//}


void write_results(size_t from, size_t to, short* parents, std::vector <size_t>* result);
bool bfs(short* graph, short size, short to, short* visited, std::list<short>& buffer, short* parents) {
    if (buffer.empty()) return false;

    short from = buffer.front();
    buffer.pop_front();

    visited[from] = 1;
    if (from == to) {
        return true;
    }

    for (size_t i = 0; i < size; ++i) {
        if (graph[from*size + i] == 0) continue;
        if (visited[i] == 1) continue;
        if (std::find(buffer.begin(), buffer.end(), i) != buffer.end()) continue;

        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(graph, size, to, visited, buffer, parents);
}

std::vector <size_t> search_graph(short* graph, size_t size, size_t from, size_t to) {
    short* visited = new short[size];
    short* parents = new short[size];
    std::vector <size_t> results;

    // don't visit
    for (size_t i = 0; i < size; ++i) {
        visited[i] = 0;
    }

    std::list<short> buffer;
    buffer.push_back(from - 1);
    bfs(graph, size, to, visited, buffer, parents);

    write_results(from - 1, to - 1, parents, &results);

    // free memory
    delete[] visited;
    delete[] parents;
    return results;
}

void write_results(size_t from, size_t to, short* parents, std::vector <size_t> * result) {
    if (to == from) {
        result->push_back(to + 1);
        return;
    }
    size_t prefrom = parents[to];
    write_results(from, prefrom, parents, result);
    result->push_back(to + 1);
}
