#include <iostream>
#include <string>
#include <vector>
#include "nf.hpp"
using namespace std;

nf::NodeFrontEndWrapper NFWrap;
#define WRAPPER NFWrap

#define SIZE 9

struct StringWeightGraphNode : public nf::WeightedGraphNode<StringWeightGraphNode, std::string> {
    StringWeightGraphNode()
        : GraphNode<StringWeightGraphNode, std::string>(NFWrap.api())
        , WeightedGraphNode<StringWeightGraphNode, std::string>(NFWrap.api()) {}
};

static const int k_int_max = (unsigned int) ~0 >> 1;
// dijkstra algorithm
class Graph
{
    vector<StringWeightGraphNode*> amStr;
    // This is bad, only for example!
    int am[SIZE][SIZE] = {{0,  4, 0,  0,  0,  0, 0,  8, 0},
                          {4,  0, 8,  0,  0,  0, 0, 11, 0},
                          {0,  8, 0,  7,  0,  4, 0,  0, 2},
                          {0,  0, 7,  0,  9, 14, 0,  0, 0},
                          {0,  0, 0,  9,  0, 10, 0,  0, 0},
                          {0,  0, 4, 14, 10,  0, 2,  0, 0},
                          {0,  0, 0,  0,  0,  2, 0,  1, 6},
                          {8, 11, 0,  0,  0,  0, 1,  0, 7},
                          {0,  0, 2,  0,  0,  0, 6,  7, 0}},
                        /*= {
                            {0, 4, 2, 8},
                            {4, 0, 0, 0},
                            {2, 0, 0, 3},
                            {8, 0, 3, 0}
                        },*/
        distance[SIZE] = {k_int_max};
    int vertices[SIZE], visited[SIZE] = {-1}, path[SIZE] = {-1};
    int verticeCount, visitedCount;

    void resetDijkstra()
    {
        for (size_t i = 0; i < SIZE; ++i)
        {
            distance[i] = k_int_max;
            visited[i] = path[i] = -1;
        }
        visitedCount = 0;
    }

    bool isVisited(size_t idx)
    {
        for (size_t i = 0; i < visitedCount; ++i)
            if (visited[i] == idx) return true;
        return false;
    }

    bool isVisitedPath(size_t idx)
    {
        if (visited[idx] == -1) return false;
        return true;
    }

    int* neighbors(int v, int &size)
    {
        short i_v = -1;
        int _size = 0;
        int *n_arr;
        size = 0;
        for (size_t i = 0; i < verticeCount; ++i)
            if (vertices[i] == v) i_v = i;
        if (i_v == -1) return NULL;

        for (size_t i = 0; i < verticeCount; ++i)
            if (am[i_v][i]) ++_size;

        if (_size == 0)
            return NULL;

        n_arr = new int[_size];
        for (size_t i = 0; i < verticeCount; ++i)
            if (am[i_v][i])
                n_arr[size++] = vertices[i];
        return n_arr;
    }

public:
    Graph()
    {
        for (int i = 0; i < SIZE; i++) {
            vertices[i] = i;
            StringWeightGraphNode* node = new StringWeightGraphNode();
            if (i == 0)
                node->setPosition(250, 250);
            node->setData(i);
            amStr.push_back(node);
        }

        // Neighbor relations - copy from static 2D array
        for (int i = 0; i < SIZE; i++) {
            switch (i)
            {
            case 0:
                amStr[i]->addNeighbor(amStr[1], 4);
                amStr[i]->addNeighbor(amStr[7], 8);
                break;
            
            case 1:
                amStr[i]->addNeighbor(amStr[0], 4);
                amStr[i]->addNeighbor(amStr[2], 8);
                amStr[i]->addNeighbor(amStr[7], 11);
                break;
            case 2:
                amStr[i]->addNeighbor(amStr[1], 8);
                amStr[i]->addNeighbor(amStr[3], 7);
                amStr[i]->addNeighbor(amStr[5], 4);
                amStr[i]->addNeighbor(amStr[8], 2);
                break;
            case 3:
                amStr[i]->addNeighbor(amStr[2], 7);
                amStr[i]->addNeighbor(amStr[4], 9);
                amStr[i]->addNeighbor(amStr[6], 14);
                break;
            case 4:
                amStr[i]->addNeighbor(amStr[3], 9);
                amStr[i]->addNeighbor(amStr[5], 10);
                break;
            case 5:
                amStr[i]->addNeighbor(amStr[2], 4);
                amStr[i]->addNeighbor(amStr[3], 14);
                amStr[i]->addNeighbor(amStr[4], 10);
                amStr[i]->addNeighbor(amStr[6], 2);
                break;
            case 6:
                amStr[i]->addNeighbor(amStr[5], 2);
                amStr[i]->addNeighbor(amStr[7], 1);
                amStr[i]->addNeighbor(amStr[8], 6);
                break;
            case 7:
                amStr[i]->addNeighbor(amStr[1], 8);
                amStr[i]->addNeighbor(amStr[2], 11);
                amStr[i]->addNeighbor(amStr[6], 1);
                amStr[i]->addNeighbor(amStr[8], 7);
                break;
            case 8:
                amStr[i]->addNeighbor(amStr[2], 2);
                amStr[i]->addNeighbor(amStr[6], 6);
                amStr[i]->addNeighbor(amStr[7], 7);
                break;
            }
        }

        verticeCount = SIZE;
        visitedCount = 0;
    }

    void print()
    {
        cout << "   ";
        for (int i = 0; i < verticeCount; i++)
            cout << vertices[i] << "  ";
        cout << endl;

        for (int y = 0; y < verticeCount; y++)
        {
            cout << vertices[y] << "| ";
            for (int x = 0; x < verticeCount; x++)
                cout << am[x][y] << ((am[x][y] > 9) ? " " : "  ");
            cout << endl;
        }
        cout << endl;
    }

    void printDistances()
    {
        cout << "dist: ";
        for (size_t i = 0; i < SIZE; ++i)
            cout << " " << distance[i];
        cout << endl;
    }
    void printVisited()
    {
        cout << "sptS: ";
        for (size_t i = 0; i < SIZE; ++i)
            cout << " " << visited[i];
        cout << endl;
    }

    void printPath()
    {
        cout << "path: ";
        for (size_t i = 0; i < SIZE; ++i)
            cout << " " << path[i];
        cout << endl;
    }

    // Dijkstra's shortest path algorithm
    void dijkstra(size_t idx)
    {
        resetDijkstra();
        distance[idx] = 0;
        while (visited[SIZE-1] == -1)
        {
            int dist = k_int_max, i_idx = -1, size;
            for (size_t i = 0; i < SIZE; ++i)
            {
                if (distance[i] < dist && !isVisited(i))
                {
                    dist = distance[i];
                    i_idx = i;
                }
            }
            visited[visitedCount++] = i_idx;
            int *n_arr = neighbors(i_idx, size);
            for (size_t i = 0; i < size; ++i)
            {
                if (!isVisited(n_arr[i]) && am[i_idx][n_arr[i]] + distance[i_idx] < distance[n_arr[i]])
                    distance[n_arr[i]] = am[i_idx][n_arr[i]] + distance[i_idx];
            }
            if (n_arr != NULL) delete [] n_arr;
        }
    }
// root: 1
// dist: [\4, \0, \8, \15, \22, \12, \12, \11, \10]
// stpS: [1, 0, 2, 8, 7, 5, 6, 3, 4]
    void dijkstraPath(size_t idx)
    {
        size_t ms = 700;
        resetDijkstra();
        distance[idx] = 0;
        path[idx] = idx;
        while (visited[SIZE-1] == -1)
        {
            int dist = k_int_max, i_idx = -1, size;
            for (size_t i = 0; i < SIZE; ++i)
            {
                if (distance[i] < dist && !isVisited(i))
                {
                    dist = distance[i];
                    i_idx = i;
                }
            }
            visited[visitedCount++] = i_idx;
            int *n_arr = neighbors(i_idx, size);
            for (size_t i = 0; i < size; ++i)
            {
                if (!isVisited(n_arr[i]) && am[i_idx][n_arr[i]] + distance[i_idx] < distance[n_arr[i]])
                {
                    distance[n_arr[i]] = am[i_idx][n_arr[i]] + distance[i_idx];
                    path[n_arr[i]] = i_idx;
                    amStr[i_idx]->highlight();
                    nf::Utils::delay(ms);
                }
            }
            
            if (n_arr != NULL) delete [] n_arr;
        }
        printDistances();
        printVisited();
        printPath();
    }
};

int main()
{
    NFWrap.init("Oriendted graph");
    const size_t v = 1;
    Graph g;
    g.print();

    g.dijkstra(v);
    g.printDistances();
    g.printVisited();
    cout << endl;
    g.dijkstraPath(v);
    g.printDistances();
    g.printVisited();
    g.printPath();
    START_LOOP;
    return 0;
}