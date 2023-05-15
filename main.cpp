#include <bits/stdc++.h>
using namespace std;

// template for generic type
template <typename K, typename V>

// Hashnode class
class HashNode
{
public:
	V value;
	K key;

	// Constructor of hashnode
	HashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
	}
};

// template for generic type
template <typename K, typename V>

// Our own Hashmap class
class HashMap
{
	// hash element array
	HashNode<K, V> **arr;
	int capacity;
	// current size
	int size;
	// dummy node
	HashNode<K, V> *dummy;

public:
	HashMap()
	{
		// Initial capacity of hash array
		capacity = 17;
		size = 0;
		arr = new HashNode<K, V> *[capacity];

		// Initialise all elements of array as NULL
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

		// dummy node with value and key -1
		dummy = new HashNode<K, V>(-1, -1);
	}
	// This implements hash function to find index
	// for a key
	int hashCode(K key)
	{
		return key % capacity;
	}

	// Function to add key value pair
	int insertNode(K key, V value)
	{
		HashNode<K, V> *temp = new HashNode<K, V>(key, value);
		int probeCount = 1;

		// Apply hash function to find index for given key
		int hashIndex = hashCode(key);

		// find next free space
		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1)
		{
			hashIndex++;
			hashIndex %= capacity;
			probeCount++;
		}

		cout << probeCount << " ";

		// if new node to be inserted
		// increase the current size
		if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
			size++;

		arr[hashIndex] = temp;

		return probeCount;
	}

	// Function to delete a key value pair
	V deleteNode(int key)
	{
		// Apply hash function
		// to find index for given key
		int hashIndex = hashCode(key);

		// finding the node with given key
		while (arr[hashIndex] != NULL)
		{
			// if node found
			if (arr[hashIndex]->key == key)
			{
				HashNode<K, V> *temp = arr[hashIndex];

				// Insert dummy node here for further use
				arr[hashIndex] = dummy;

				// Reduce size
				size--;
				return temp->value;
			}
			hashIndex++;
			hashIndex %= capacity;
		}

		// If not found return null
		return NULL;
	}

	// Function to search the value for a given key
	V get(int key)
	{
		// Apply hash function to find index for given key
		int hashIndex = hashCode(key);
		int counter = 0;

		// finding the node with given key
		while (arr[hashIndex] != NULL)
		{ // int counter =0; // BUG!

			if (counter++ > capacity) // to avoid infinite loop
				return NULL;

			// if node found return its value
			if (arr[hashIndex]->key == key)
				return arr[hashIndex]->value;
			hashIndex++;
			hashIndex %= capacity;
		}

		// If not found return null
		return NULL;
	}

	// Return current size
	int sizeofMap()
	{
		return size;
	}

	// Return true if size is 0
	bool isEmpty()
	{
		return size == 0;
	}

	// Function to display the stored key value pairs
	void display()
	{
		cout << endl;
		for (int i = 0; i < capacity; i++)
		{

			if (arr[i] != NULL && arr[i]->key != -1)
				cout << "key = " << arr[i]->key << " value = " << arr[i]->value << endl;
			else
				cout << -1 << endl;
		}
	}
};

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
void hashing_quadratic(int table[], int tsize, int arr[], int N)
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
	cout << "Quadratic: " << endl;
	printArray(probe_table, N);
	cout << "--------------------" << endl;
	printArray(table, tsize);
}

int hash_one_num(int value)
{
	return value % 17;
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
		int hash_one = hash_one_num(arr[i]);
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

// Driver method to test map class
int main()
{

	// Linear ---------------------------------------------------------------------------
	HashMap<int, int> *h = new HashMap<int, int>;
	int probeCountTotal = 0;

	cout << "Inserting and counting how many probes are done in each insert:" << endl;

	probeCountTotal += h->insertNode(25, 2021);
	probeCountTotal += h->insertNode(88, 2000);
	probeCountTotal += h->insertNode(3, 2011);
	probeCountTotal += h->insertNode(38, 2012);
	probeCountTotal += h->insertNode(20, 2009);
	probeCountTotal += h->insertNode(71, 2002);
	probeCountTotal += h->insertNode(55, 2003);
	// probeCountTotal += h->insertNode(55, 2017);
	probeCountTotal += h->insertNode(56, 2015);
	probeCountTotal += h->insertNode(50, 2007);
	probeCountTotal += h->insertNode(105, 2023);

	cout << endl;

	cout << "Total probes: " << probeCountTotal;

	h->display();
	cout << endl
		 << "----------------------------------------------------" << endl;

	// Quadratic ---------------------------------------------------------------------------

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
	hashing_quadratic(hash_table, L, arr, N);
	cout << endl
		 << endl;

	// Double ------------------------------------------------------------------------------

	// Set all values to -1
	for (int i = 0; i < L; i++)
	{
		hash_table[i] = -1;
	}
	hashing_double(hash_table, L, arr, N);

	return 0;
}
