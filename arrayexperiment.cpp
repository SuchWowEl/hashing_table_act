#include <iostream>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;

void printArray(int arr[], int n)
{
    int k = 0;
    // Iterating and printing the array
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
        k += arr[i];
    }
    if (n == 10)
    {
        cout << endl
             << "Total probe: " << k << endl;
    }
}

void hashing_quadratic(int table[], int tsize, int arr[], int N)
{
    int probe_table[N];
    // Iterating through the array
    for (int i = 0; i < N; i++)
    {
        /* Computing the hash value
        int hash_one = hash_one_num(arr[i]);
        int hash_two = hash_two_num(arr[i]);
        int hv = hash_one % tsize;*/
        int hv = arr[i] % tsize;

        // Insert in the table if there
        // is no collision
        int k = 1;
        for (int j = 0; j < tsize; j++, k++)
        {
            // Computing the new hash value
            int t = (hv + (j * j)) % tsize;
            // cout << "hash_val recursion: " << t << endl;
            //  int t = (hv + j * j) % tsize;
            if (table[t] == -1)
            {
                // Break the loop after
                // inserting the value
                // in the table
                table[t] = arr[i];
                break;
            }
        }
        probe_table[i] = k;
    }
    cout << "Quadratic: " << endl;
    printArray(probe_table, N);
    cout << "--------------------" << endl;
    printArray(table, tsize);
}

void hashing_linear(int table[], int tsize, int arr[], int N)
{
    int probe_table[N];
    // Iterating through the array
    for (int i = 0; i < N; i++)
    {
        /* Computing the hash value
        int hash_one = hash_one_num(arr[i]);
        int hash_two = hash_two_num(arr[i]);
        int hv = hash_one % tsize;*/
        int hv = arr[i] % tsize;

        // Insert in the table if there
        // is no collision
        int k = 1;
        for (int j = 0; true; j++, k++)
        {
            // Computing the new hash value
            int t = (hv + j) % tsize;
            // cout << "hash_val recursion: " << t << endl;
            //  int t = (hv + j * j) % tsize;
            if (table[t] == -1)
            {
                // Break the loop after
                // inserting the value
                // in the table
                table[t] = arr[i];
                break;
            }
        }
        probe_table[i] = k;
    }
    cout << "Linear: " << endl;
    printArray(probe_table, N);
    cout << "--------------------" << endl;
    printArray(table, tsize);
}

int hash_one_num(int value, int tsize)
{
    return value % tsize;
}

int hash_two_num(int value)
{
    return (13 - (value % 13));
}

void hashing_double(int table[], int tsize, int arr[], int N)
{
    int probe_table[N];
    // Iterating through the array
    for (int i = 0; i < N; i++)
    {
        // Computing the hash value
        int hash_one = hash_one_num(arr[i], tsize);
        int hash_two = hash_two_num(arr[i]);
        int hv = hash_one % tsize;

        // Insert in the table if there
        // is no collision
        int k = 1;
        for (int j = 0; true; j++, k++)
        {
            // Computing the new hash value
            int t = (hash_one + (j * hash_two)) % tsize;
            // cout << "hash_val recursion: " << t << endl;
            //  int t = (hv + j * j) % tsize;
            if (table[t] == -1)
            {
                // Break the loop after
                // inserting the value
                // in the table
                table[t] = arr[i];
                break;
            }
        }
        probe_table[i] = k;
    }
    cout << "Double: " << endl;
    printArray(probe_table, N);
    cout << "--------------------" << endl;
    printArray(table, tsize);
}

bool isPrime(int num)
{
    if (num < 2)
        return false;

    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

int hashsize_getter(float x)
{
    int lower = static_cast<int>(x);
    int upper = static_cast<int>(x);

    // Find the nearest prime number greater than x
    int prime = 0;
    while (true)
    {
        if (!isPrime(upper))
            upper++;
        else
        {
            prime = upper;
            break;
        }
        if (!isPrime(lower))
            lower++;
        else
        {
            prime = lower;
            break;
        }
    }
    return prime;

    // Find the nearest prime number smaller than x
    /*while (!isPrime(lower)) {
        lower--;
    }*/

    // Determine which prime number is closer to x
    /*if (abs(upper - x) <= abs(lower - x)) {
        return upper;
    } else {
        return lower;
    }*/
}

int main()
{
    // int copy[] = {25, 88, 3, 38, 20, 71, 55, 56, 50, 105};
    int N = 30;
    int *arr = new int[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = (rand() % N) + 1;
        // cout << i + 1 << ". " << arr[i] << endl;
    }

    // Size of the hash table
    int L = hashsize_getter((float)N * 1.3);
    cout << "Size of hash_table is: " << L << endl;
    int *hash_table = new int[L];

    // Initializing the hash table
    for (int i = 0; i < L; i++)
    {
        hash_table[i] = -1;
    }
    // Function call
    auto start1 = chrono::high_resolution_clock::now();
    hashing_linear(hash_table, L, arr, N);
    auto stop1 = chrono::high_resolution_clock::now();

    auto duration1 = chrono::duration_cast<std::chrono::microseconds>(stop1-start1);
    cout << endl
         << endl;

    // Quadratic ------------------------------------------------------------------------------

    for (int i = 0; i < L; i++)
    {
        hash_table[i] = -1;
    }
    auto start2 = chrono::high_resolution_clock::now();
    hashing_quadratic(hash_table, L, arr, N);
    auto stop2 = chrono::high_resolution_clock::now();

    auto duration2 = chrono::duration_cast<std::chrono::microseconds>(stop2-start2);
    cout << endl
         << endl;

    // Double ------------------------------------------------------------------------------

    for (int i = 0; i < L; i++)
    {
        hash_table[i] = -1;
    }
    auto start3 = chrono::high_resolution_clock::now();
    hashing_double(hash_table, L, arr, N);
    auto stop3 = chrono::high_resolution_clock::now();

    auto duration3 = chrono::duration_cast<std::chrono::microseconds>(stop3-start3);
    cout << endl
         << endl;


    cout << "Execution time of Linear Probing in microseconds: " << (double)duration1.count() << " microseconds" << endl;

    cout << "Execution time of Quadratic Probing in microseconds: " << (double)duration2.count() << " microseconds" << endl;

    cout << "Execution time of Double Hashing in microseconds: " << (double)duration3.count() << " microseconds" << endl;



    delete[] arr, hash_table;
}
