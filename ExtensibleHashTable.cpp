#include "ExtensibleHashTable.h"
#include "Bucket.h"
#include <cmath>
#include <exception>
#include <iostream>

using namespace std;

//return the size of directory
int ExtensibleHashTable::get_directory_size() const{
    return pow(2, this->global_depth);
}

//below are two necessary recursive functions for insertion
//insert the key when there is no need to double the directory
void ExtensibleHashTable::insert_nodouble(int entry, int key){
    //if there is empty space
    int occupy = directory[entry]->get_occupy();
    int size = directory[entry]->get_size();
    int base = this->get_directory_size();
    if(occupy < size){
        directory[entry]->push_key(key);
        return;
    }
    else{
        //create a new bucket for dual entry
        int dual_entry = (entry >= pow(2, global_depth - 1))?entry:entry + pow(2, global_depth - 1);
        int orig_entry = dual_entry - pow(2, global_depth - 1);
        directory[dual_entry] = new Bucket(size);
        directory[dual_entry]->set_local_depth(global_depth);
        //create a new bucket for the original entry for replacement
        Bucket* newb = new Bucket(size);
        newb->set_local_depth(global_depth);
        //redistribute original keys between two buckets
        for(int i = 0; i < size; i++){
            if(directory[orig_entry]->get_ith_key(i) % base == dual_entry)
                directory[dual_entry]->push_key(directory[orig_entry]->get_ith_key(i));
            else
                newb->push_key(directory[orig_entry]->get_ith_key(i));
        }
        Bucket *tmp = directory[orig_entry];
        directory[orig_entry] = newb;
        delete tmp;
        //assign the new key into the bucket, if not full insert it, else call insert_double()
        if(directory[entry]->get_occupy() < size){
            directory[entry]->push_key(key);
        }
        else{
            ExtensibleHashTable::insert_double(entry, key);
        }
    }
}

//insert the key when there is a need to double the directory
void ExtensibleHashTable::insert_double(int entry, int key){
    //if there is empty space
    int occupy = directory[entry]->get_occupy();
    int size = directory[entry]->get_size();
    int base = this->get_directory_size();
    if(occupy < size){
        directory[entry]->push_key(key);
        return;
    }
    else{
        //double the directory
        Bucket** directory_t = new Bucket*[base * 2];
        this->global_depth++;
        //make a pointer for each directory to the corresponding bucket
        for(int i = 0; i < 2 * base; i++){
            int index = (i >= base)? (i - base) : i;
            directory_t[i] = directory[index];
        }
        Bucket** tmp = directory;
        directory = directory_t;
        delete tmp;
        //create bucket for the new entry
        int new_entry = entry + pow(2, global_depth - 1);
        directory[new_entry] = new Bucket(size);
        directory[new_entry]->set_local_depth(global_depth);
        //create a new bucket for the original entry for replacement
        Bucket* newb = new Bucket(size);
        newb->set_local_depth(global_depth);
        //redistribution between two buckets
        for(int i = 0; i < size; i++){
            if(directory[entry]->get_ith_key(i) % (2 * base) == new_entry)
                directory[new_entry]->push_key(directory[entry]->get_ith_key(i));
            else
                newb->push_key(directory[entry]->get_ith_key(i));
        }
        //
        Bucket *tp = directory[entry];
        directory[entry] = newb;
        delete tp;
        
        if(directory[key % (2 * base)]->get_occupy() < size)
            directory[key % (2 * base)]->push_key(key);
        else
            ExtensibleHashTable::insert_double(key % (2 * base), key);
    }
}

//constructor with no parameters
ExtensibleHashTable::ExtensibleHashTable(){
    //the directory should initially consist of two entries 0 nad 1
    this->global_depth = 1;
    directory = new Bucket*[2];
    directory[0] = new Bucket;
    directory[1] = new Bucket;
}

//constructor with one parameter indicating the size of each bucket
ExtensibleHashTable::ExtensibleHashTable(int N){
    //the directory should initially consist of two entries 0 nad 1
    this->global_depth = 1;
    directory = new Bucket*[2];
    directory[0] = new Bucket(N);
    directory[1] = new Bucket(N);
}

//deep copy constructor, overloaded operator
ExtensibleHashTable& ExtensibleHashTable::operator=(const ExtensibleHashTable& e){
    if(this->directory != NULL){
        for(int i = 0; i < this->get_directory_size(); i++){
            if(i % int(pow(2, directory[i]->get_local_depth())) == i)
                delete this->directory[i];
        }
    }
    this->global_depth = e.get_global_depth();
    this->directory = new Bucket*[this->get_directory_size()];
    for(int i =0; i < this->get_directory_size(); i++){
        int ld = e.directory[i]->get_local_depth();
        if(i % int(pow(2, ld)) == i){
            Bucket* tmp = new Bucket;
            *tmp = *(e.directory[i]);

            //cout<<i<<":"<<endl;
            //cout<<tmp->get_local_depth()<<endl;
            //cout<<tmp->get_occupy()<<endl;

            this->directory[i] = tmp;

            //for(int j = 0; j <this->directory[i]->get_occupy(); j++)
            //    cout<<this->directory[i]->get_ith_key(j)<<endl;

        }
        else{
            this->directory[i] = this->directory[i % int(pow(2, ld))];
        }
    }
    return *this;
}

//destructor
ExtensibleHashTable::~ExtensibleHashTable(){
    for(int i = 0; i < this->get_directory_size(); i++){
        if(i % int(pow(2, directory[i]->get_local_depth())) == i)
            delete this->directory[i];
    }
}

//method for getting the global_depth
int ExtensibleHashTable::get_global_depth() const{
    return this->global_depth;
}

//searches the hash table for the key; if found returns true, 
//otherwise returns false
bool ExtensibleHashTable::find(int key){
    int base = this->get_directory_size();
    //find entry K
    int K = key % base;
    //traversal through allocated positions
    int s = directory[K]->get_occupy();
    for(int i = 0; i < s; i++){
        if(directory[K]->get_ith_key(i) == key)
            return true;
    }
    return false;
}

//inserts the key into the hash table in the appropriate bucket
void ExtensibleHashTable::insert(int key){
    int base = this->get_directory_size();
    int K = key % base;
    int size = directory[K]->get_size();
    int occupy_size = directory[K]->get_occupy();
    //deal with negative input values
    try{
        if(key < 0){
            throw invalid_argument("Invalid input!"); 
        }
    }
    catch(invalid_argument& s){
        cout<<s.what()<<endl;
        return;
    }
    //deal with runtime error for one particular case
    try{
        if(size == occupy_size){
            // whether all keys are identical to new key
            int flag = 1;
            for( int i = 0; i < size; i++){
                flag = flag & (directory[K]->get_ith_key(i) == key);
            }
            if(flag)
                throw runtime_error("Runtime Error!"); 
        }
    }
    catch(runtime_error& e){
        cout<<e.what()<<endl;
        return;
    }
    // two insert recursive processes
    if(global_depth > directory[K]->get_local_depth())
        ExtensibleHashTable::insert_nodouble(K, key);
    else if(global_depth == directory[K]->get_local_depth())
        ExtensibleHashTable::insert_double(K, key);
    return;
}

//searches the hash table for the key; 
//if found, removes all matching values (as there may be duplicate keys) from the hash table; 
//returns true if the key was found and removed, false otherwise
bool ExtensibleHashTable::remove(int key){
    int base = this->get_directory_size();
    //find entry K
    int K = key % base;
    int size = directory[K]->get_size();
    //determine whether the bucket contains key
    int flag = 0;
    Bucket* candidate = new Bucket(size);
    for(int i = 0; i < directory[K]->get_occupy(); i++){
        if(directory[K]->get_ith_key(i) != key){
            candidate->push_key(directory[K]->get_ith_key(i));
        }
        else
            flag = 1;
    }
    Bucket* tmp = directory[K];
    directory[K] = candidate;
    delete tmp;

    if(flag)
        return true;
    return false;
}

//prints the contents of the directory and buckets; 
//see below for exactly what should be printed
void ExtensibleHashTable::print(){
    //set all prs to 0 first
    for(int i = 0; i < this->get_directory_size(); i++){
        directory[i]->set_pr(0);
    }
    //print process
    for(int i = 0; i < this->get_directory_size(); i++){
        cout<<i<<": "<<directory[i]<<" --> ";
        if(directory[i]->get_pr() == 0){
            directory[i]->set_pr(1);
            cout<<"[";
            for(int j = 0; j < directory[i]->get_size(); j++){
                if(j >= directory[i]->get_occupy()){
                    if(j == 0)
                        cout<<"-";
                    else
                        cout<<",-";
                }
                else{
                    if(j == 0)
                        cout<<directory[i]->get_ith_key(j);
                    else   
                        cout<<","<<directory[i]->get_ith_key(j);
                    
                }
            }
            cout<<"] ("<<directory[i]->get_local_depth()<<")"<<endl;
        }
        else
            cout<<endl;
    }
}