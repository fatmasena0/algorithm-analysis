// Fatma Sena Akçağlayan 150170085
#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

class Graph
{
public:
    int numberOfVertex, colorCount;
    vector<int> colorsVertex;           //Colored vertex list.
    vector<bool> availableColor;        //Available color for neighbor nodes.
    vector<vector<int>> neighborLists;  //Adjacent node list.
    Graph(int);
    void addEdge(int, int);
    void greedyAlgorithm1();
};

Graph::Graph(int numberOfVertex)
{
    this->colorCount = 1;                  //Color counter.
    this->numberOfVertex = numberOfVertex; //The number of nodes.
    neighborLists.reserve(numberOfVertex); //The number of nodes memory allocating.
}

void Graph::addEdge(int currentPoint, int neighborPoint)
{
    this->neighborLists[currentPoint].push_back(neighborPoint); // Neighbor is added to the list holding current_point's neighbors.
}

void Graph::greedyAlgorithm1()
{
    this->colorsVertex.push_back(0); // vertex 0 -> color 0 (vertex+1), 0 index means color 1.
    this->colorsVertex.push_back(1); // vertex 1 -> color 1 (vertex+1), 1 index means color 2.
    availableColor.push_back(true);  // If true Index 0 means color 1 in available color.
    availableColor.push_back(true);  // If true Index 1 means color 2 in available color.

    for (int i = 2; i < numberOfVertex; i++)//Checking vertex nodes.
    {
        vector<bool> tempColor = availableColor;//This is keeping available color to manipulate per neighbor's available color.
        for (int j = 0; j < neighborLists[i].size(); j++)//Checking neighbor nodes.
        {
            if (neighborLists[i][j] < i)//If neighbor node lower than current vertex then...
            {
                tempColor[colorsVertex[neighborLists[i][j]]] = false;//Current neighbor's available color will false to current vertex.
            }
            else
                break;//If neighbor node bigger than current vertex will not check it.
        }

        bool isColored = false;//Is Colored current vertex.
        for (int j = 0; j < availableColor.size(); j++)//Checking available colors to color vertex.
        {
            if (tempColor[j])//If color available.
            {
                this->colorsVertex.push_back((j));//Color it.
                isColored = true;//Vertex colored then change state to true.
                break;
            }
        }
        if (!isColored)//If vertex not colored.
        {
            colorCount++;//Increase color counter to new color.
            this->colorsVertex.push_back(colorCount);//Color vertex with new color.
            availableColor.push_back(true);//Add new color to available color.
            continue;
        }
    }
}

int main()
{
    Graph ga1(7);//Creating graph
    //Adding adjancent nodes
    ga1.addEdge(0, 1);
    ga1.addEdge(0, 3);
    ga1.addEdge(0, 4);
    ga1.addEdge(1, 0);
    ga1.addEdge(1, 2);
    ga1.addEdge(1, 3);
    ga1.addEdge(2, 1);
    ga1.addEdge(2, 3);
    ga1.addEdge(2, 5);
    ga1.addEdge(2, 6);
    ga1.addEdge(3, 0);
    ga1.addEdge(3, 1);
    ga1.addEdge(3, 2);
    ga1.addEdge(3, 4);
    ga1.addEdge(3, 5);
    ga1.addEdge(4, 0);
    ga1.addEdge(4, 3);
    ga1.addEdge(4, 5);
    ga1.addEdge(5, 2);
    ga1.addEdge(5, 3);
    ga1.addEdge(5, 4);
    ga1.addEdge(5, 6);
    ga1.addEdge(6, 2);
    ga1.addEdge(6, 5);

    auto startTime = chrono::high_resolution_clock::now(); //Time to start greedyAlgorithm1.
    ga1.greedyAlgorithm1();
    auto endTime = chrono::high_resolution_clock::now(); //Time to stop greedyAlgorithm1.
    auto runningTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);//Calculating greedAlgorithm2 running time.
    
    for (int i = 0; i < 7; i++)
    {
        cout << "Vertex " << i + 1 << "--->Color " << ga1.colorsVertex[i] + 1 << endl;
    }
    cout << endl;
    cout << "Number of different colors:" << ga1.colorCount + 1 << endl;
    cout << "Time in " << runningTime.count() / 1000000.0 << " ms." << endl;

    return 0;
}