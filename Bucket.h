#ifndef	__BUCKET__H__
#define	__BUCKET__H__

#include <cmath>
#include <iostream>

using namespace std;
class Bucket{
	private:
		//array of integers
		int* B;

		//size of each bucket
		int size;

		//number of positions that are occupied
		int occupy;

		//local depth of certain bucket
		int local_depth;

		//a flag indicating whether this bucket is print
		//1 for print, 0 for not print
		int pr;

	public:
		//constructor for no parameters
		Bucket();

		//constructor with one parameter indicating bucket size
		Bucket(int N);

		//deep copy constructor, overloaded operator
		Bucket& operator=(const Bucket& b);

		//destructor
		~Bucket();

		//method for getting the size of each bucket
		int get_size() const;

		//method for getting the number od positions that are occupied
		int get_occupy() const;

		//method for setting the number od positions that are occupied
		void set_occupy(int n);

		//method for getting the local depth
		int get_local_depth() const;

		//method for setting the local depth
		void set_local_depth(int n);

		//method for pushing a key to the end of bucket
		void push_key(int n);

		//method for getting the key at ith position
		int get_ith_key(int i) const;

		//method for getting the pr
		int get_pr() const;

		//mwthod for setting the pr
		void set_pr(int n);

		//found current depth of the bucket
		//like [1010, 0010, 1110], current depth is 2 regardless of the local depth
		int found_depth();


};

#endif /* __BUCKET__H__ */
