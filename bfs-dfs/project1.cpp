// Fatma Sena Akçağlayan 150170085
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>

using namespace std;

class Player                                                        // class to keep the all data of each player is read
{
public:
    string algorithm;                                               // bfs or dfs
    bool *game_board;                                               // keeps the game board as a list
    int start_point, size_of_board, number_of_ship, ship_counter;   // start_point: first hit, size_of_board: matrix size, ship_counter: how many indexes are marked for ships in game_board
                                                                    
    Player(string, int, int, int, int);                             // constructor
    void generate_gameboard(int, int, int, int);                    // ships are marked on the gamboard
    ~Player();                                                      // deconstructer
};

class Graph                                                         // class to keep the all data of each player`s graph
{
public:
    int number_of_nodes, visited_counter, memory_counter;
    list<int> *neighbor_lists;                                      // To keep all neighbors of all nodes

    Graph(int);                                                     // constructor
    void add_edge(int, int);                                        // add edge between two neighbors
    void depth_first_search(int, bool *, int);                      // dfs algorithm
    void breadth_first_search(int, bool *, int);                    // bfs algorithm
    ~Graph();                                                       // deconstructer
};

Player::Player(string algorithm, int start_x, int start_y, int size_of_board, int number_of_ship)
{
    this->ship_counter = 0;                                         // initially no ship on gameboard
    this->algorithm = algorithm;
    this->size_of_board = size_of_board;
    this->number_of_ship = number_of_ship;
    this->start_point = size_of_board * start_x + start_y;          // the starting coordinate is converted to the corresponding index.
    this->game_board = new bool[size_of_board * size_of_board];     // a list with the length of the number of elements of the matrix was created for the gameboard
}

void Player::generate_gameboard(int x1, int y1, int x2, int y2)
{
    if (x1 == x2)                                                   // if the x coordinates are equal the ship will be placed vertically
    {
        for (int y = y1; y < y2 + 1; y++)                           // marked ships from top to bottom
        {
            int index = this->size_of_board * x1 + y;               // the relevant index in the list is calculated according to the incoming coordinates
            this->game_board[index] = true;                         // marked as there is a ship in the relevant index
            this->ship_counter++;                                   // increase the number of indexes with ships to find how many nodes have ships
        }
    }
    else if (y1 == y2)                                              // if the y coordinates are equal the ship will be placed horizontally
    {
        for (int x = x1; x < x2 + 1; x++)                           // marked ships from left to right
        {
            int index = this->size_of_board * x + y1;               // the relevant index in the list is calculated according to the incoming coordinates
            this->game_board[index] = true;                         // marked as there is a ship in the relevant index
            this->ship_counter++;                                   // increase the number of indexes with ships to find how many nodes have ships
        }
    }
}

Player::~Player()
{
    delete[] game_board;                                            // free space reserved for gameboard from memory
}

Graph::Graph(int number_of_nodes)
{
    this->memory_counter = 0;                                       // counts the number of nodes pushed to the stack or queue
    this->visited_counter = 0;                                      // counts the number of nodes marked as visited
    this->number_of_nodes = number_of_nodes;                        // the number of nodes on game board
    neighbor_lists = new list<int>[number_of_nodes];                // space reserved for list of node's neighbors
}

void Graph::add_edge(int current_point, int neighbor_point)
{
    this->neighbor_lists[current_point].push_back(neighbor_point);  // neighbor is added to the list holding current_point's neighbors
}

void Graph::depth_first_search(int start_point, bool *rival_board, int ship_counter)
{
    stack<int> dfs_stack;                                           // each node and its neighbors will be pushed in the stack in order
    vector<bool> visited(number_of_nodes, false);                   // list that keeps track of whether each node has been visited

    dfs_stack.push(start_point);                                    // push the first visited point to the stack.
    this->memory_counter++;                                         // memory_counter increases each time when a point is pushed to the stack

    while (!dfs_stack.empty())                                      // continues until the stack is empty
    {
        int current_point = dfs_stack.top();                        // the node at the top of the stack is assigned the current_point
        dfs_stack.pop();                                            // the node at the top of the stakc is popped

        if (!visited[current_point])                                // if the current_point is not visited before
        {
            visited[current_point] = true;                          // current_point is marked as visited
            visited_counter++;                                      // visited_counter is increased by 1
            if (rival_board[current_point] == true)                 // check there is any ship on current visited point on the rival board 
            {
                ship_counter--;                                     // sinked the ship and ship_counter is decreased by 1
                if (ship_counter == 0)                              // if all ships are sinked
                    break;                                          // game over
            }
            // loops to add the neighbors of the current visited node 
            for (auto i = neighbor_lists[current_point].rbegin(); i != neighbor_lists[current_point].rend(); ++i) 
            {
                if (!visited[*i])                                   // if the neighbor is not visited before
                {
                    dfs_stack.push(*i);                             // push the neighbor to the stack
                    this->memory_counter++;                         // memory_counter increases each time when a point is pushed to the stack
                }
            }        
        }
    }
}

void Graph::breadth_first_search(int start_point, bool *rival_board, int ship_counter)
{
    queue<int> bfs_queue;                                           // each node and its neighbors will be pushed in the stack in order
    vector<bool> visited(number_of_nodes, false);                   // list that keeps track of whether each node has been visited
 
    bfs_queue.push(start_point);                                    // push the first visited point to the queue
    this->memory_counter++;                                         // memory_counter increases each time when a point is pushed to the queue

    while (!bfs_queue.empty())                                      // continues until the queue is empty
    {
        int current_point = bfs_queue.front();                      // the node at the top of the queue is assigned the current_point
        bfs_queue.pop();                                            // the node at the top of the queue is popped
        if (!visited[current_point])    
        {
            visited[current_point] = true;                          // current neighbor is marked as visited
            this->visited_counter++;                                // visited_counter is increased by 1
            if (rival_board[current_point] == true)                 // check there is any ship on first visited point on the rival board 
            {
                ship_counter--;                                     // sinked the ship and ship_counter is decreased by 1
                if (ship_counter == 0)                              // if all ships are sinked
                    return;                                         // game over
            }
            // loops to add and visit the neighbors of the current node 
            for (auto i = neighbor_lists[current_point].begin(); i != neighbor_lists[current_point].end(); ++i) 
            {
                if (!visited[*i])                                   // if the neighbor is not visited before
                {                            
                    bfs_queue.push(*i);                             // push the current visited neighbor to the queue
                    this->memory_counter++;                         // memory_counter increases each time when a point is pushed to the queue
                }
            }
        }
    }
}

Graph::~Graph()
{
    delete[] neighbor_lists;                                        // free space reserved for neighbors from memory
}

int main(int argc, char **argv)
{    
    if (argc != 3)                                                  // check the arguments are taken from command line.
        return 1;

    int size_of_board;                                              // variables to hold data from the file given as arguments
    int number_of_ship;
    int x1, y1, x2, y2;
    int start_x, start_y;
    string algorithm;

    fstream file_player1, file_player2;                             // variables for player1 and player2 files

    
    file_player1.open(argv[1]);                                     // files are opened
    file_player2.open(argv[2]);

    // all data up to ship coordinates are assigned to the relevant variables
    file_player1 >> algorithm >> start_x >> start_y >> size_of_board >> number_of_ship;
    Player player1(algorithm, start_x, start_y, size_of_board, number_of_ship);
    file_player2 >> algorithm >> start_x >> start_y >> size_of_board >> number_of_ship;
    Player player2(algorithm, start_x, start_y, size_of_board, number_of_ship);

    // All ship coordinates are read.
    for (int i = 0; i < number_of_ship; i++)
    {
        file_player1 >> x1 >> y1 >> x2 >> y2;                       // the ship's start and end coordinates are assigned to x1, y1, x2 and y2
        player1.generate_gameboard(x1, y1, x2, y2);                 // in this function, it is marked that there are ships in the relevant places on the game board according to the given coordinates
        file_player2 >> x1 >> y1 >> x2 >> y2;                       // same operations for player2
        player2.generate_gameboard(x1, y1, x2, y2);                 // same operations for player2
    }

    file_player1.close();                                           // files are closed
    file_player2.close();

    // Generating graph nodes as many as the parameter
    Graph player1_graph(size_of_board * size_of_board);
    Graph player2_graph(size_of_board * size_of_board);

    // Neighbors of all nodes are added to the graph.
    // Nodes are kept in adjList instead of adjMatrix. 
    // For this, the coordinates of a node's neighbors are calculated 
    // to which index they correspond to in the list.
    for (int i = 0; i < size_of_board * size_of_board; i++)
    {
        int top, left, bottom, right;
        top = i - size_of_board;    
        left = i - 1;               
        bottom = i + size_of_board;
        right = i + 1;   

        // The node can be at the top, leftmost, bottom or rightmost of the matrix. 
        // These situations are checked not to leave the game board.     

        if (top >= 0)
        {
            // The neighbor on the up is added.
            player1_graph.add_edge(i, top);
            player2_graph.add_edge(i, top);
        }
        if (left >= 0 && (left % size_of_board != size_of_board - 1))
        {
            // The neighbor on the left is added.
            player1_graph.add_edge(i, left);
            player2_graph.add_edge(i, left);
        }
        if (bottom < size_of_board * size_of_board)
        {
            // The neighbor on the bottom is added.
            player1_graph.add_edge(i, bottom);
            player2_graph.add_edge(i, bottom);
        }
        if (right < size_of_board * size_of_board && (right % size_of_board != 0))
        {
            // The neighbor on the right is added.
            player1_graph.add_edge(i, right);
            player2_graph.add_edge(i, right);
        }
    }

    // The relevant algorithm is run according to the value read from the file.
    auto time1 = chrono::high_resolution_clock::now();         // time to start running player 1 

    if (player1.algorithm == "DFS")
        player1_graph.depth_first_search(player1.start_point, player2.game_board, player2.ship_counter);
    else
        player1_graph.breadth_first_search(player1.start_point, player2.game_board, player2.ship_counter);

    auto time2 = chrono::high_resolution_clock::now();         // time to start running player 2

    if (player2.algorithm == "DFS")
        player2_graph.depth_first_search(player2.start_point, player1.game_board, player1.ship_counter);
    else
        player2_graph.breadth_first_search(player2.start_point, player1.game_board, player1.ship_counter);

    auto time3 = chrono::high_resolution_clock::now();                              
    auto duration1 = chrono::duration_cast<chrono::nanoseconds>(time2 - time1); 
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(time3 - time2); 

    // Game result is printed
    cout << "The algorithm: Player1: " << player1.algorithm << ", Player2: " << player2.algorithm << endl;

    if (player1_graph.visited_counter <= player2_graph.visited_counter)    
    {
        cout << "The number of visited nodes: Player1: " << player1_graph.visited_counter << ", Player2: " << player1_graph.visited_counter - 1 << endl;
        cout << "The number of nodes kept in the memory: Player1: " << player1_graph.memory_counter << ", Player2: " << player1_graph.memory_counter << endl;
        cout << "The running time: " << duration1.count() / 1000000.0 << "ms" << endl;
        cout << "The result: Player1 won!" << endl;
    }
    else
    {
        cout << "The number of visited nodes: Player1: " << player2_graph.visited_counter << ", Player2: " << player2_graph.visited_counter << endl;        
        cout << "The number of nodes kept in the memory: Player1: " << player2_graph.memory_counter << ", Player2: " << player2_graph.memory_counter << endl;
        cout << "The result: Player2 won!" << endl;
        cout << "The running time: " << duration2.count() / 1000000.0 << "ms" << endl;
    }
    return 0;
}
