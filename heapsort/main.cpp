// Fatma Sena Akçağlayan 150170085
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class Vehicle
{
public:
    int vehicle_id;  // Unique ID for vehicles
    string location; // Location code where the vehicle is placed initially
    double distance; // Distance to Hotel Bee from the current location in kilometers
    int speed;       // Average speed of the vehicle in km/h
    double key;      // estimated time for the vehicles to reach to the Hotel Bee
};

class Request
{
public:
    string location;  // Destination location
    double distance;  // Distance of the destination location to the hotel
    int lucky_number; // Lucky number of the customer if any
};

int heap_size = 0;      // Initial value for heap size
const int MAX = 100000; // MAX value is used to check key values

void swap(Vehicle *a, Vehicle *b) // swap two Vehicle information using pointers
{
    Vehicle t;
    t = *a;
    *a = *b;
    *b = t;
}

int index_right_child(int index) // returns the right child index
{
    // 1 indexed heap is used for easy understanding, so 1643 is entered
    if ((((2 * index) + 1) < 1643) && (index >= 1))
        return (2 * index) + 1; // for example 13th index is right child of the 6th index
    return -1;
}

int index_left_child(int index) // returns the right child index
{
    if (((2 * index) < 1643) && (index >= 1))
        return 2 * index; // for example 12th index is right child of the 6th index
    return -1;
}

int index_parent(int index) // returns the parent index
{
    if ((index > 1) && (index < 1643))
        return index / 2; // for example 6th index is parent of 12th and 13th index
    return -1;
}

void min_heapify(Vehicle V_arr[], int index) // checking for the smallest element
{
    int left = index_left_child(index);   // get index of left child
    int right = index_right_child(index); // get index of right child

    int smallest = index;

    if ((left <= heap_size) && (left > 0))
    {
        if (V_arr[left].key < V_arr[smallest].key) // check the left child is small or not
            smallest = left;
    }

    if ((right <= heap_size) && (right > 0))
    {
        if (V_arr[right].key < V_arr[smallest].key) // check the right child is small or not
            smallest = right;
    }

    // if there is smallest key value, updating the min-heap tree
    if (smallest != index)
    {
        swap(&V_arr[index], &V_arr[smallest]); // the smaller element is moved to root
        min_heapify(V_arr, smallest);          // recursively called
    }
}

Vehicle extract(Vehicle V_arr[]) // return and delete the root of a heap
{
    Vehicle root = V_arr[1];     // root is the node has minimum key value
    V_arr[1] = V_arr[heap_size]; // last element of tree is assigned to root
    heap_size--;                 // heap size is decreased by one
    min_heapify(V_arr, 1);       // min_heapify function call to minimum key value moved to root again
    return root;                 // returns root which kept the V_arr[1]
}

void decrease_key(Vehicle V_arr[], int index, Vehicle key) // change its position to go according to the new key
{
    V_arr[index] = key; // can be the last index of a particular index or heap
    while ((index > 1) && (V_arr[index_parent(index)].key > V_arr[index].key)) // check the key values
    {
        swap(&V_arr[index], &V_arr[index_parent(index)]); // its priority increases and moves up.
        index = index_parent(index);
    }
}

void insert(Vehicle V_arr[], Vehicle key) // inserts a new element in the correct order according to its key
{
    heap_size++;                         // heap size inreases by one
    V_arr[heap_size].key = MAX;          // making last element very large
    decrease_key(V_arr, heap_size, key); // the move up will take place in the min_heapify function
}

int main(int argc, char **argv)
{
    if (argc != 2) // check the arguments are taken from command line
        return 1;

    int N = stoi(argv[1]); // N is the total number of extract, decrease and insert operations that program should execute, convert string to integer with stoi()

    //------------------------------------------ TASK 1 ------------------------------------------------------
    //-------------------------------------- BUILD MIN-HEAP --------------------------------------------------
    fstream vehilce_file;
    vehilce_file.open("vehicles.txt"); // input file opened, information of vehicles of Take Me There

    string s, header_line;
    getline(vehilce_file, header_line); // header line is read

    Vehicle *vehicles = new Vehicle[1643]; // the array to keep all vehicles as heap structure

    for (int i = 0; i < 1642; i++)
    {
        Vehicle temp; // temp is a variable Vehicle type kept the information read from the file
        vehilce_file >> temp.vehicle_id;
        vehilce_file >> temp.location;
        vehilce_file >> temp.distance;
        vehilce_file >> temp.speed;
        temp.key = temp.distance / temp.speed; // estimated time that is key value is calculated
        insert(vehicles, temp);                // new vehicle inserts to vehicles min-heap
    }
    vehilce_file.close(); // file closed
    //-------------------------------------- BUILD MIN-HEAP --------------------------------------------------
    //------------------------------------------ TASK 1 ------------------------------------------------------

    clock_t t;
    t = clock();

    //------------------------------------------ TASK 2 and 3 -------------------------------------------------
    fstream request_file;
    request_file.open("requests.txt"); // the file included transportation requests coming from the customers is opened

    getline(request_file, header_line); // header line is read

    ofstream output_file("call_history.txt"); // the file will contain the called vehicle IDs in order

    int count = 0; // counter for total number of extract, decrease and insert operations
    while (count < N)
    {
        Request req; // req variable kept the request read from the file
        Vehicle updated_vehicle;
        request_file >> req.location;
        request_file >> req.distance;
        request_file >> req.lucky_number;
        if (req.lucky_number == 0) // Task 2 Case I
        {
            Vehicle fastest_vehicle = extract(vehicles);
            count++; // count increased as extract function is called
            updated_vehicle.vehicle_id = fastest_vehicle.vehicle_id;
            updated_vehicle.speed = fastest_vehicle.speed;
            output_file << fastest_vehicle.vehicle_id << "\n"; // vehicle_id written into the output file
        }
        else // Task Case II
        {
            vehicles[req.lucky_number + 1].key = 0;                                       // key value set to 0 for highest priority
            decrease_key(vehicles, req.lucky_number + 1, vehicles[req.lucky_number + 1]); // the vehicle whose key is changed will become root
            Vehicle lucky_vehicle = extract(vehicles);                                    // extract the root of heap
            count += 2;                                                                   // count increased by 2 as decrease and extract functions are called
            updated_vehicle.vehicle_id = lucky_vehicle.vehicle_id;
            updated_vehicle.speed = lucky_vehicle.speed;
            output_file << lucky_vehicle.vehicle_id << "\n"; // vehicle_id written into the output file
        }
        updated_vehicle.location = req.location;
        updated_vehicle.distance = req.distance;
        updated_vehicle.key = updated_vehicle.distance / updated_vehicle.speed; // new key value is updated, TASK 3
        insert(vehicles, updated_vehicle);                                      // updated vehicle is inserted to heap, TASK 3
        count++;                                                                // count increased as insert function is called
    }
    request_file.close(); // request_file closed
    output_file.close();  // output_file closed
    //------------------------------------------ TASK 2 and 3 -------------------------------------------------

    t = clock() - t;
    cout << "Task 2 and 3 executed in " << (float)t / CLOCKS_PER_SEC * 1000 << " milliseconds. " << endl;

    return 0;
}
