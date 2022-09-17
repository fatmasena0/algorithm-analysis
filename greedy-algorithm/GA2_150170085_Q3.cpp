// Fatma Sena Akçağlayan 150170085
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;
//Sorting degree by descending order
bool sortDeg(const pair<int,int> &a,const pair<int,int> &b)
{
    return (a.second > b.second);
}

class Graph
{
public:
    int numberOfVertex;
    vector<pair<int, int>> neighborLists; //<vertex number, degree>
    vector<vector<bool>> adjMatrix;       //Adjacent node matrix, if nodes are adjacent then this point will be true
    Graph(int);
    void addEdge(int, int);
    void sortByDegrees();
    void greedyAlgorithm2();
};

Graph::Graph(int numberOfVertex)
{
    this->numberOfVertex = numberOfVertex; //The number of nodes
    neighborLists.resize(numberOfVertex);  //The number of nodes is sizing on neighborLists
    adjMatrix.resize(numberOfVertex);      //The number of nodes is sizing on adjancentMatrix raw
    for (int i = 0; i < numberOfVertex; i++)
    {
        neighborLists[i].first = i; //Adding index number
        neighborLists[i].second = 0; //Adding degree to 0 at start
        adjMatrix[i].resize(numberOfVertex); //The number of nodes is sizing on adjMatrix column
    }
}

void Graph::addEdge(int currentPoint, int neighborPoint)
{
    neighborLists[currentPoint].second++;//Increasing degree when added an adjacent node
    adjMatrix[currentPoint][neighborPoint] = true;//Changing state true on adjancent matrix when added an adjancent node
}

void Graph::sortByDegrees()
{
    sort(this->neighborLists.begin(), this->neighborLists.end(), sortDeg);//Sorting neighborList by sortDeg function
}

void Graph::greedyAlgorithm2()
{
    this->sortByDegrees();//Calling sort function by degrees to sort nodes
    int colorNumber = 0;//Color starting with 0 index number, it means color 1
    while (neighborLists.size() != 0)//Checking vertex nodes.
    {
        vector<int> dropList;//This list for add which vertex is colored and for which vertex will dropping
        vector<int> color;//This list keeping colored vertex
        color.push_back(neighborLists[0].first);//Adding first vertex to colored
        dropList.push_back(0);//Adding index 0 for drop it after colored.

        cout << "Vertex " << neighborLists[0].first + 1 << "---> Color " << colorNumber + 1 << endl;

        for (int i = 1; i < neighborLists.size(); i++)//Checking neighbor nodes.
        {
            bool isNeighbor = false;//Is neighbor
            for (int k = 0; k < color.size(); k++)//Checking colored vertex.
            {
                if (adjMatrix[neighborLists[i].first][color[k]])//If urrent vertex and colored vertex are neghbor then...
                {
                    isNeighbor = true;//Change state to true.
                    if (k == 0)//If first colored vertex then...
                    {
                        cout << "Checking " << neighborLists[i].first + 1 << " ---> false" << endl;
                        break;
                    }
                    else//If other colored vertex then...
                        cout << "Checking " << neighborLists[i].first + 1 << " ---> false  (since it is connected to " << color[k] + 1 << ")" << endl;
                }
            }
            if (!isNeighbor)//If not neighbor then..
            {
                color.push_back(neighborLists[i].first);//Color it.
                dropList.push_back(i);//add olored vertex index to drop
                cout << "Checking " << neighborLists[i].first + 1 << " ---> true" << endl;
                cout << "Vertex " << neighborLists[i].first + 1 << " ---> Color " << colorNumber + 1 << endl;
            }
        }

        for (int i = dropList.size() - 1; i >= 0; i--)//Check which vertex must to be drop
        {
            neighborLists.erase(neighborLists.begin() + dropList[i]); //Drop vertex

        }
        cout << "Vertices ";
        for (int i = 0; i < color.size()-1; i++)//Check which vertex dropped
        {
            cout << color[i] + 1 << ",";
        }
        cout << color.back() + 1  << " are dropped!!" << endl;
        cout << endl;
        colorNumber++;//Increase color number for new color.
    }
    cout << "Well done!! All the vertices are colored." << endl;
    cout << "Min color num:" << colorNumber << endl; 
}

int main()
{
    Graph ga2(7);//Creating graph
    //Adding adjancent nodes
    ga2.addEdge(0, 1);
    ga2.addEdge(0, 3);
    ga2.addEdge(0, 4);
    ga2.addEdge(1, 0);
    ga2.addEdge(1, 2);
    ga2.addEdge(1, 3);
    ga2.addEdge(2, 1);
    ga2.addEdge(2, 3);
    ga2.addEdge(2, 5);
    ga2.addEdge(2, 6);
    ga2.addEdge(3, 0);
    ga2.addEdge(3, 1);
    ga2.addEdge(3, 2);
    ga2.addEdge(3, 4);
    ga2.addEdge(3, 5);
    ga2.addEdge(4, 0);
    ga2.addEdge(4, 3);
    ga2.addEdge(4, 5);
    ga2.addEdge(5, 2);
    ga2.addEdge(5, 3);
    ga2.addEdge(5, 4);
    ga2.addEdge(5, 6);
    ga2.addEdge(6, 2);
    ga2.addEdge(6, 5);

    auto startTime = chrono::high_resolution_clock::now(); //time to start greedyAlgorithm2.
    ga2.greedyAlgorithm2();
    auto endTime = chrono::high_resolution_clock::now(); //Time to stop greedyAlgorithm2.
    auto runningTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);//Calculating greedyAlgorithm2 running time.
    cout << "Time in " << runningTime.count() / 1000000.0 << " ms." << endl;

    return 0;
}