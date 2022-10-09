#include <cstdlib>
#include <qstring.h>

//tmp
#include <iostream>
using namespace std;
#include <limits.h>
#define V 9

//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
//TODO rewrite code to my task
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

QString dijkstra(short graph[V][V], int src)
{
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);

    return QString::number(13);
}

QString algorithm_search(short ** graph,size_t size_of_matrix,
                         size_t from, size_t to){
//    TODO
    return "";
}

/* test */
/*int main()
{

    short graph[V][V] = { { 0, 1, 0, 0, 0, 0, 0, 1, 0 },
                        { 1, 0, 1, 0, 0, 0, 0, 1, 0 },
                        { 0, 1, 0, 1, 0, 1, 0, 0, 1 },
                        { 0, 0, 1, 0, 1, 1, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                        { 0, 0, 1, 1, 1, 0, 1, 0, 0 },
                        { 0, 0, 0, 0, 0, 1, 0, 1, 1 },
                        { 1, 1, 0, 1, 0, 0, 1, 0, 1 },
                        { 0, 0, 1, 0, 0, 0, 1, 1, 0 } };

    dijkstra(graph, 0);

    return 0;
}*/
