// Fatma Sena Akçağlayan 150170085
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

//struct to keep the all data of each tweet is read
struct Tweet
{
    int tweet_id;          //Enumeration of the Tweet
    string tweet_datetime; //Tweet time in a structured format
    int tweet_unixtime;    //Tweet time in Unix format
    string artist_name;    //Artist name of the song
    string track_title;    //Name of the song
    string country;        //Tweet location
};

int partition(Tweet arr[], int low, int high)
{
    string pivot_country = arr[high].country;                                                            //country value of last element is taken as pivot
    transform(pivot_country.begin(), pivot_country.end(), pivot_country.begin(), ::tolower);             //for case-insensetive alphabetic order
                                                                                                         //all letters change to lower case
    string pivot_artist_name = arr[high].artist_name;                                                    //artist_name pivot is used if countries are same
    transform(pivot_artist_name.begin(), pivot_artist_name.end(), pivot_artist_name.begin(), ::tolower); //all letters change to lower case
    int pivot_unixtime = arr[high].tweet_unixtime;                                                       //unix_time pivot is used if countries and also artist_name are same

    int i = (low - 1); //keep index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        string temp_country = arr[j].country; //current country value taken into temp to change lowercase
        transform(temp_country.begin(), temp_country.end(), temp_country.begin(), ::tolower);
        string temp_artist_name = arr[j].artist_name; //current artist name value taken into temp to change lowercase
        transform(temp_artist_name.begin(), temp_artist_name.end(), temp_artist_name.begin(), ::tolower);
        int temp_unixtime = arr[j].tweet_unixtime; //current unix time

        if (temp_country < pivot_country)
        {                         //if current country value is before alphabetically than the pivot
            i++;                  //index of smaller element is increased
            swap(arr[i], arr[j]); //swapped two elements
        }
        else if (temp_country == pivot_country && temp_artist_name < pivot_artist_name)
        {                         //if current country value is same with pivot, artist_names are compared
            i++;                  //index of smaller element is increased
            swap(arr[i], arr[j]); //swapped two elements
        }
        else if (temp_country == pivot_country && temp_artist_name == pivot_artist_name && temp_unixtime <= pivot_unixtime)
        {
            i++;                  //index of smaller element is increased
            swap(arr[i], arr[j]); //swapped two elements
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int partition_randomized(Tweet arr[], int low, int high)
{
    //random element is selected as pivot
    srand(time(NULL));
    int random = low + rand() % (high - low);

    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

void deterministic_quickSort(Tweet arr[], int low, int high)
{
    if (low < high) //if starting index is smaller than ending index
    {
        int pi = partition(arr, low, high); //partitioning index

        deterministic_quickSort(arr, low, pi - 1);  //elements before partition are sorted
        deterministic_quickSort(arr, pi + 1, high); //elements after partition are sorted
    }
}

void randomized_quickSort(Tweet arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition_randomized(arr, low, high);

        randomized_quickSort(arr, low, pi - 1);
        randomized_quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char **argv)
{
    if (argc != 5) //check the arguments are taken from command line
        return 1;
    //taken arguments from command line
    int N = stoi(argv[1]); //number of the tweets to be sorted
    string A = argv[2];    //randomized or deterministic pivot selection
    string I = argv[3];    //input file path
    string O = argv[4];    //output file path

    fstream input_file;
    input_file.open(I); //input file opened

    string line;
    string temp;
    getline(input_file, line); //header line is read

    Tweet *t_list = new Tweet[N]; //an array to keep all tweet

    for (int i = 0; i < N; i++) //all lines are read and kept in t_list
    {
        getline(input_file, temp, '\t');
        t_list[i].tweet_id = stoi(temp);
        getline(input_file, t_list[i].tweet_datetime, '\t');
        getline(input_file, temp, '\t');
        t_list[i].tweet_unixtime = stoi(temp);
        getline(input_file, t_list[i].artist_name, '\t');
        getline(input_file, t_list[i].track_title, '\t');
        getline(input_file, t_list[i].country, '\n');
    }
    input_file.close();

    clock_t t;
    //deterministic or randomized sort algorithm run according to A value is taken from command line
    if (A == "deterministic")
    {
        t = clock();
        deterministic_quickSort(t_list, 0, N - 1);
        t = clock() - t;
    }
    else
    {
        t = clock();
        randomized_quickSort(t_list, 0, N - 1);
        t = clock() - t;
    }

    cout << "Sorted in " << (float)t/CLOCKS_PER_SEC * 1000 << " milliseconds by using " << A << " pivot selection." << endl; 

    ofstream output_file(O);
    if (output_file.is_open())
    {
        output_file << line;        //header line is written
        for (int i = 0; i < N; i++) //all tweets are kept in t_list are written to output_file
        {
            output_file << "\n"
                        << t_list[i].tweet_id << "\t";
            output_file << t_list[i].tweet_datetime << "\t";
            output_file << t_list[i].tweet_unixtime << "\t";
            output_file << t_list[i].artist_name << "\t";
            output_file << t_list[i].track_title << "\t";
            output_file << t_list[i].country;
        }
        output_file.close();
    }
    return 0;
}
