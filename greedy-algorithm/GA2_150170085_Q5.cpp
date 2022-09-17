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
    this->numberOfVertex = numberOfVertex; // the number of nodes
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
    neighborLists[currentPoint].second++; //Increasing degree when added an adjacent node
    adjMatrix[currentPoint][neighborPoint] = true; //Changing state true on adjancent matrix when added an adjancent node
}
//Sorting degree by descending order
void Graph::sortByDegrees()
{
    sort(this->neighborLists.begin(), this->neighborLists.end(), sortDeg);//Sorting neighborList by descending order function
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
            neighborLists.erase(neighborLists.begin() + dropList[i]);//Drop vertex

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
    Graph ga2(35);//Creating graph
    //Adding adjancent nodes
    ga2.addEdge(0, 1);
    ga2.addEdge(0, 6);
    
    ga2.addEdge(1, 0);
    ga2.addEdge(1, 2);
    ga2.addEdge(1, 5);

    ga2.addEdge(2, 1);
    ga2.addEdge(2, 3);

    ga2.addEdge(3, 2);
    ga2.addEdge(3, 4);
    ga2.addEdge(3, 10);
    ga2.addEdge(3, 11);

    ga2.addEdge(4, 3);
    ga2.addEdge(4, 5);

    ga2.addEdge(5, 1);
    ga2.addEdge(5, 4);
    ga2.addEdge(5, 6);
    ga2.addEdge(5, 9);

    ga2.addEdge(6, 0);
    ga2.addEdge(6, 5);
    ga2.addEdge(6, 7);
    ga2.addEdge(6, 8);

    ga2.addEdge(7, 6);
    ga2.addEdge(7, 8);
    ga2.addEdge(7, 20);

    ga2.addEdge(8, 6);
    ga2.addEdge(8, 7);
    ga2.addEdge(8, 9);
    ga2.addEdge(8, 19);

    ga2.addEdge(9, 5);
    ga2.addEdge(9, 8);
    ga2.addEdge(9, 10);
    ga2.addEdge(9, 17);
    ga2.addEdge(9, 19);

    ga2.addEdge(10, 3);
    ga2.addEdge(10, 9);
    ga2.addEdge(10, 11);
    ga2.addEdge(10, 16);

    ga2.addEdge(11, 3);
    ga2.addEdge(11, 10);
    ga2.addEdge(11, 12);

    ga2.addEdge(12, 11);
    ga2.addEdge(12, 13);
    ga2.addEdge(12, 15);

    ga2.addEdge(13, 12);
    ga2.addEdge(13, 14);

    ga2.addEdge(14, 13);
    ga2.addEdge(14, 15);
    ga2.addEdge(14, 26);

    ga2.addEdge(15, 12);
    ga2.addEdge(15, 14);
    ga2.addEdge(15, 16);
    ga2.addEdge(15, 26);

    ga2.addEdge(16, 10);
    ga2.addEdge(16, 15);
    ga2.addEdge(16, 17);
    ga2.addEdge(16, 24);
    ga2.addEdge(16, 25);

    ga2.addEdge(17, 9);
    ga2.addEdge(17, 16);
    ga2.addEdge(17, 18);
    ga2.addEdge(17, 31);

    ga2.addEdge(18, 17);
    ga2.addEdge(18, 22);
    ga2.addEdge(18, 23);

    ga2.addEdge(19, 8);
    ga2.addEdge(19, 9);
    ga2.addEdge(19, 20);
    ga2.addEdge(19, 21);

    ga2.addEdge(20, 7);
    ga2.addEdge(20, 19);
    ga2.addEdge(20, 21);

    ga2.addEdge(21, 19);
    ga2.addEdge(21, 20);
    ga2.addEdge(21, 22);
    ga2.addEdge(21, 33);
    ga2.addEdge(21, 34);

    ga2.addEdge(22, 18);
    ga2.addEdge(22, 21);
    ga2.addEdge(22, 23);
    ga2.addEdge(22, 32);

    ga2.addEdge(23, 18);
    ga2.addEdge(23, 22);
    ga2.addEdge(23, 31);
    ga2.addEdge(23, 32);

    ga2.addEdge(24, 16);
    ga2.addEdge(24, 25);
    ga2.addEdge(24, 29);

    ga2.addEdge(25, 16);
    ga2.addEdge(25, 24);
    ga2.addEdge(25, 26);
    ga2.addEdge(25, 29);

    ga2.addEdge(26, 14);
    ga2.addEdge(26, 15);
    ga2.addEdge(26, 25);
    ga2.addEdge(26, 27);
    ga2.addEdge(26, 29);

    ga2.addEdge(27, 26);
    ga2.addEdge(27, 28);

    ga2.addEdge(28, 27);
    ga2.addEdge(28, 29);
    ga2.addEdge(28, 30);

    ga2.addEdge(29, 24);
    ga2.addEdge(29, 25);
    ga2.addEdge(29, 26);
    ga2.addEdge(29, 28);
    ga2.addEdge(29, 30);
    ga2.addEdge(29, 31);

    ga2.addEdge(30, 28);
    ga2.addEdge(30, 29);
    ga2.addEdge(30, 31);

    ga2.addEdge(31, 17);
    ga2.addEdge(31, 24);
    ga2.addEdge(31, 29);
    ga2.addEdge(31, 30);
    ga2.addEdge(31, 32);

    ga2.addEdge(32, 22);
    ga2.addEdge(32, 23);
    ga2.addEdge(32, 31);
    ga2.addEdge(32, 33);

    ga2.addEdge(33, 21);
    ga2.addEdge(33, 32);
    ga2.addEdge(33, 34);

    ga2.addEdge(34, 21);
    ga2.addEdge(34, 33);


    auto startTime = chrono::high_resolution_clock::now(); //Time to start greedyAlgorithm2.
    ga2.greedyAlgorithm2();
    auto endTime = chrono::high_resolution_clock::now(); //Time to stop greedyAlgorithm2.
    auto runningTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);//Calculating greedyAlgorithm2 running time.
    cout << "Time in " << runningTime.count() / 1000000.0 << " ms." << endl;

    return 0;
}