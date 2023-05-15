// C++ implementation of
// the Quadratic Probing
#include <bits/stdc++.h>
using namespace std;

// Function to print an array
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

// Function to implement the
// quadratic probing
void hashing(int table[], int tsize, int arr[], int N)
{
    int probe_table[N];
    // Iterating through the array
    for (int i = 0; i < N; i++)
    {
        // Computing the hash value
        int hv = arr[i] % tsize;

        // Insert in the table if there
        // is no collision
        int k = 1;
        if (table[hv] == -1)
            table[hv] = arr[i];
        else
        {
            // If there is a collision
            // iterating through all
            // possible quadratic values
            for (int j = 0; j < tsize; j++, k++)
            {
                // Computing the new hash value
                int t = (hv + j * j) % tsize;
                if (table[t] == -1)
                {
                    // Break the loop after
                    // inserting the value
                    // in the table
                    table[t] = arr[i];
                    break;
                }
            }
        }
        probe_table[i] = k;
    }
    printArray(probe_table, N);
    cout << "--------------------" << endl;
    printArray(table, tsize);
}

// Driver code
int main()
{
    int arr[] = {25, 88, 3, 38, 20, 71, 55, 56, 50, 105};
    int N = 10;

    // Size of the hash table
    int L = 17;
    int hash_table[17];

    // Initializing the hash table
    for (int i = 0; i < L; i++)
    {
        hash_table[i] = -1;
    }

    // Function call
    hashing(hash_table, L, arr, N);
    return 0;
}

// This code is contributed by gauravrajput1
