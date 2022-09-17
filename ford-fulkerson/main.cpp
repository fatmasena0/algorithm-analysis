// Fatma Sena Akçağlayan 150170085
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#define MAX_WEIGHT 1000

using namespace std;

class Graph
{
public:
    int V, src, des;
    int **adjMatrix;
    int **pathMatrix;
    float **probMatrix;
    vector<pair<int, int>> probIndex;
    vector<pair<int, float>> flowProb;
    Graph(int V);                               // Constructor
    bool isPathReachable(int, int, int, int *); // to find shortest path from source to destination
    void combination(Graph, vector<pair<int, int>>, int, int, int, vector<pair<int, int>>, int);
};

Graph::Graph(int V)
{
    this->V = V;
    adjMatrix = new int *[V];
    probMatrix = new float *[V];
    pathMatrix = new int *[V];
    for (int i = 0; i < V; i++)
    {
        adjMatrix[i] = new int[V];
        probMatrix[i] = new float[V];
        pathMatrix[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            adjMatrix[i][j] = 0;
            probMatrix[i][j] = 0.0;
            pathMatrix[i][j] = 0;
        }
    }
}

bool Graph::isPathReachable(int src, int dest, int v, int pathIndex[]) // find the shortest path by using breadth first search algorithm
{
    list<int> queue;
    bool visited[v];

    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
        pathIndex[i] = -1;
    }

    visited[src] = true;
    queue.push_back(src);

    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < V; i++)
        {
            if (adjMatrix[u][i] != 0)
            {
                if (visited[i] == false)
                {
                    visited[i] = true;
                    pathIndex[i] = u;
                    queue.push_back(i);

                    if (i == dest)
                        return true;
                }
            }
        }
    }

    return false;
}

int increaseFlow(int **P, int f, int size)
{
    int min = MAX_WEIGHT;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (P[i][j] > 0 && P[i][j] < min)
            {
                min = P[i][j];
            }
        }
    }
    return min;
}
int fordFulkerson(Graph G, int s, int t)
{
    int flow = 0;     // all zero flow
    Graph GFlow(G.V); // Gf <- G
    for (int i = 0; i < GFlow.V; i++)
    {
        for (int j = 0; j < GFlow.V; j++)
        {
            GFlow.adjMatrix[i][j] = G.adjMatrix[i][j];
            GFlow.pathMatrix[i][j] = G.pathMatrix[i][j];
        }
    }
    while (true) // while t is reachable from s in 𝐺flow
    {
        int pathIndex[GFlow.V];
        if (GFlow.isPathReachable(s - 1, t - 1, GFlow.V, pathIndex))
        {
            vector<int> path;
            int point = t - 1;
            path.push_back(point);
            while (pathIndex[point] != -1) // Find a path P from s to t in 𝐺flow
            {
                path.push_back(pathIndex[point]);
                point = pathIndex[point];
            }
            for (int i = path.size() - 1; i >= 1; i--)
            {
                GFlow.pathMatrix[path[i]][path[i - 1]] = GFlow.adjMatrix[path[i]][path[i - 1]];
            }

            //𝑓 ← increaseFlow(P,f)
            int min = increaseFlow(GFlow.pathMatrix, flow, GFlow.V);
            flow = flow + min;

            // update 𝐺flow
            for (int i = 0; i < GFlow.V; i++)
            {
                for (int j = 0; j < GFlow.V; j++)
                {
                    if (GFlow.pathMatrix[i][j] != 0)
                    {
                        GFlow.adjMatrix[i][j] = GFlow.adjMatrix[i][j] - min;
                        GFlow.pathMatrix[i][j] = 0;
                    }
                }
            }
        }
        else
            return flow;
    }
    return flow;
}

void Graph::combination(Graph g, vector<pair<int, int>> arr, int n, int r, int index, vector<pair<int, int>> combinedArr, int i)
{
    if (index == r)
    {
        Graph tempG(V);
        float **copyProbMatrix = new float *[V];
        for (int i = 0; i < V; i++)
        {
            copyProbMatrix[i] = new float[V];
            for (int j = 0; j < V; j++)
            {
                tempG.adjMatrix[i][j] = g.adjMatrix[i][j];
                tempG.probMatrix[i][j] = g.probMatrix[i][j];
                copyProbMatrix[i][j] = g.probMatrix[i][j];
            }
        }

        float probability = 1;
        for (int j = 0; j < r; j++) // probability of disconnected edges are calculated
        {
            tempG.adjMatrix[combinedArr[j].first][combinedArr[j].second] = 0; // edges are removed from the graph
            probability *= (tempG.probMatrix[combinedArr[j].first][combinedArr[j].second]);
            copyProbMatrix[combinedArr[j].first][combinedArr[j].second] = 0; // calculated probability are removed from the copyProbMatrix
        }
        for (int i = 0; i < V; i++) // probability of connected edges are calculated
        { 
            for (int j = 0; j < V; j++)
            {
                if (copyProbMatrix[i][j] > 0)
                {
                    probability *= (1 - copyProbMatrix[i][j]);
                }
            }
        }

        int flow = fordFulkerson(tempG, src, des);
        for (long unsigned int i = 0; i < flowProb.size(); i++) 
        {
            if (flowProb[i].first == flow) // is there current flow in flowProb 
            {
                flowProb[i].second += probability; // increase the probability of current flow value
                return;
            }
        }
        flowProb.push_back(make_pair(flow, probability)); // add current flow and probability to flowProb
        return;
    }

    if (i >= n)
        return;

    combinedArr[index] = arr[i];
    // recursive calling is used to find all combination
    combination(g, arr, n, r, index + 1, combinedArr, i + 1);
    combination(g, arr, n, r, index, combinedArr, i + 1);
}

int main(int argc, char **argv)
{
    if (argc != 4) // check the arguments are taken from command line.
        return 1;

    int n;
    fstream inputFile;

    inputFile.open(argv[1]); // file is opened

    inputFile >> n; // n = size of matrix 
    if (n < 2 || n > 100000) // 2 ≤ |V| ≤ 100000
        return 1;

    Graph G(n); // Graph G is created
    G.src = stoi(argv[2]);
    G.des = stoi(argv[3]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            inputFile >> x;
            G.adjMatrix[i][j] = x; // adjMatrix
            if (x < 0 || x > 1000)
                return 1; // W(e) constraint
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            float x;
            inputFile >> x;
            G.probMatrix[i][j] = x; // probMatrix
            if (x > 0)
                G.probIndex.push_back(make_pair(i, j));
        }
    }

    inputFile.close(); // file is closed

    for (long unsigned int i = 0; i <= G.probIndex.size(); i++) // to calculate flow and probability for all combinations
    {
        vector<pair<int, int>> array;
        array.resize(i);
        G.combination(G, G.probIndex, G.probIndex.size(), i, 0, array, 0);
    }

    float maxFlow = 0;
    for (long unsigned int i = 0; i < G.flowProb.size(); i++)
    {
        cout << "Probability of occurence : " << G.flowProb[i].second << ", Maximum Flow : " << G.flowProb[i].first << endl;
        maxFlow += G.flowProb[i].first * G.flowProb[i].second;
    }
    cout << endl;
    cout << "Expected Maximum Flow from node " << argv[2] << " to node " << argv[3] << ": " << maxFlow << endl;
    return 0;
}
