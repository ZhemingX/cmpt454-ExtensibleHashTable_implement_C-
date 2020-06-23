#include "Bucket.h"
#include <cmath>
#include <iostream>

using namespace std;

//constructor for no parameters
Bucket::Bucket(){
    //dynamic allocation for the array
    this->size = 4;
    this->B = new int[4];
    this->occupy = 0;
    this->local_depth = 1;
    this->pr = 0;
}

//constructor with one parameter indicating bucket size
Bucket::Bucket(int N){
    //dynamic allocation for the array
    this->size = N;
    this->B = new int[N];
    this->occupy = 0;
    this->local_depth = 1;
    this->pr = 0;
}

//deep copy constructor, overloaded operator
Bucket& Bucket::operator=(const Bucket& b){
    if(this->B != NULL)
        delete[] this->B;
    this->size = b.get_size();
    this->occupy = b.get_occupy();
    this->local_depth = b.get_local_depth();
    this->pr = b.get_pr();
    this->B = new int[this->size];
    for(int i = 0; i < this->occupy; i++){
        this->B[i] = b.get_ith_key(i);
        //cout<< b.get_ith_key(i)<<endl;
    }
    return *this;
}

//destructor
Bucket::~Bucket(){
        delete[] this->B;
        //cout<<"delete"<<endl;
}

//method for getting the size of each bucket
int Bucket::get_size() const{
    return this->size;
}

//method for getting the number od positions that are occupied
int Bucket::get_occupy() const{
    return this->occupy;
}

//method for setting the number od positions that are occupied
void Bucket::set_occupy(int n){
    this->occupy = n;
}

//method for getting the local depth
int Bucket::get_local_depth() const{
    return this->local_depth;
}

//method for setting the local depth
void Bucket::set_local_depth(int n){
    this->local_depth = n;
}

//method for pushing a key to the end of bucket
void Bucket::push_key(int n){
    if(this->occupy == this->size){
        cout<<"Bucket is Full!"<<endl;
        return;
    }
    this->B[occupy] = n;
    this->occupy ++;
}

//method for getting the key at ith position
int Bucket::get_ith_key(int i) const{
    return this->B[i];
}

//method for getting the pr
int Bucket::get_pr() const{
    return this->pr;
}

//mwthod for setting the pr
void Bucket::set_pr(int n){
    this->pr = n;
}

//found current depth of the bucket
int Bucket::found_depth(){
    if(occupy == 0)
        return 0;
    int f = 1;
    int flag = 1;
    int d = 0;
    while(flag){
        int mode = pow(2, f);
        int term = B[0] % mode;
        for(int i = 1; i < occupy; i++){
            if(B[i] % mode != term)
                flag = 0;
        }
        if(flag){
            f++;
            d++;
        }
    }
    return d;
}

