#include <iostream>
#include "ExtensibleHashTable.h"
#include "Bucket.h"
#include <cmath>
#include <exception>

using namespace std;

int main(){
    //provide some test cases for users
    ExtensibleHashTable ht(3);
    /*case 1
    ht.insert(64);
    ht.insert(66);
    ht.insert(200);
    ht.insert(13);
    ht.insert(67);
    ht.insert(218);
    //ht.print();
    cout<<endl;
    ht.insert(253);
    //ht.print();
    cout<<endl;
    ht.insert(153);
    //ht.print();
    cout<<endl;
    ht.insert(109);
    //invalid input
    ht.insert(-11);
    ht.print();
    */
    /* case 2
    ht.insert(233);
    //ht.print();
    cout<<endl;
    ht.remove(233);
    //ht.print();
    cout<<endl;
    cout<<ht.find(153)<<endl;
    */
    /* case 3
    ht.insert(1);
    ht.insert(1);
    ht.insert(1);
    ht.insert(1);
    ht.print();
    */
    /* case 4
    int f = 1;
    for(int i = 1; i <= 16; i++){
        f = 32 * i;
        ht.insert(f);
    }
    ht.print();
    */
    /* case 5
    for(int i = 1; i <= 12; i++)
        ht.insert(i);
    ht.print();
    cout<<".."<<endl;
    */
    /* case 6
    for(int i = 1; i <= 12; i++)
        ht.insert(i);
    cout<<"ht:"<<endl;
    ht.print();
    ExtensibleHashTable c;
    c = ht;
    cout<<"c:"<<endl;
    c.print();
    c.insert(20);
    cout<<"ht:"<<endl;
    ht.print();
    cout<<"c:"<<endl;
    c.print();
    */
    /* case 7
    for(int i = 1; i <= 4; i++){
        ht.insert(i);
        ht.insert(i);
        ht.insert(i);
    }
    ht.print();
    cout<<endl;
    ht.remove(1);
    ht.print();
    cout<<endl;
    */

    
    return 0;
}
