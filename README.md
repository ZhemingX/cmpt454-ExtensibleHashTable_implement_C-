# ExtensibleHashTable_implement_C-
Just provide tips for students who take database systems and struggle with ExtensibleHashTable.

type this command in command line (for windows or linux):
g++ main.cpp ExtensibleHashTable.cpp Bucket.cpp -o main.exe

The hash table is to store non-negative integers. This class is obviously (I hope) not incredibly useful 
but is intended for you to learn and demonstrate your knowledge of the index structure discussed in class.
In practice, if the structure was used as an index the table would store key-address pairs where the address 
would be the disk page that the record with the matching key was contained. Since we are not going to connect 
our hash table to data we will just store the key value (an integer). 

Six main functions for this container class:
ExtensibleHashTable() – this constructor creates an empty hash table
ExtensibleHashTable(int) – this constructor creates an empty hash table
void insert(int) – inserts the key into the hash table in the appropriate bucket
bool find(int) – searches the hash table for the key
bool remove(int) – searches the hash table for the key;if found, removes all matching values (as there may be duplicate keys) 
                   from the hash table; returns true if the key was found and removed, false otherwise
void print() – prints the contents of the directory and buckets
