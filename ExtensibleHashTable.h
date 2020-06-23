#ifndef	__EXTENSIBLEHASHTABLE__H__
#define	__EXTENSIBLEHASHTABLE__H__

#include "Bucket.h"
#include <cmath>
#include <exception>

class ExtensibleHashTable{
	private:
		//global depth
		int global_depth;

		//a directory that is an array of pointers to Buckets
		Bucket** directory;

		//return the size of directory
		int get_directory_size() const;

		//insert the key when there is no need to double the directory 
		void insert_nodouble(int entry, int key);

		//insert the key when there is a need to double the directory
		void insert_double(int entry, int key);
	
	public:
		//constructor with no parameters
		ExtensibleHashTable();

		//constructor with one parameter indicating the size of each bucket
		ExtensibleHashTable(int N);

		//deep copy constructor, overloaded operator
		ExtensibleHashTable& operator=(const ExtensibleHashTable& e);

		//destructor
		~ExtensibleHashTable();

		//method for getting the global_depth
		int get_global_depth() const;

		//searches the hash table for the key; if found returns true, 
		//otherwise returns false
		bool find(int key);

		//inserts the key into the hash table in the appropriate bucket
		void insert(int key);

		//searches the hash table for the key; 
		//if found, removes all matching values (as there may be duplicate keys) from the hash table; 
		//returns true if the key was found and removed, false otherwise
		bool remove(int key);

		//prints the contents of the directory and buckets; 
		//see below for exactly what should be printed
		void print();
};

#endif /* __EXTENSIBLEHASHTABLE__H__ */
