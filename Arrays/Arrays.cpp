#include<iostream>
#include<list>
#include<cstdlib>
using namespace std;

// The Exceptions ---------------------------------------------------------
class Exception {};
class SortedArrayException : public Exception {};
class SortedArrayMemoryException : public SortedArrayException {};
class SortedArrayBoundaryException : public SortedArrayException {};

//testing

template <class DT>
class SortedArray {
	
	template<class DT>
	friend ostream& operator<< (ostream& s, SortedArray<DT>& sa);

protected:
	DT* elements; //The elements that will be inside the array
	int _size;    // The size of the array

public:
	SortedArray(); //default constructor
	SortedArray(int n); //The non-constructor
	virtual ~SortedArray();
	virtual DT& operator[] (int k);
	virtual int size() const; 
	//void operator= (const SortedArray<DT>& sa);
	int find(const DT& lookfor);
	void insert(DT& newElement); //
};

//The constructors ---------------------------------------------------------

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

//default constructor
template <class DT>
SortedArray<DT>::SortedArray() {
	_size = 0; // default in case allocation fails
	elements = new DT[ARRAY_CLASS_DEFAULT_SIZE];
	if (elements == NULL) throw SortedArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
}

//non-default constructor
template <class DT>
SortedArray<DT>::SortedArray(int n) {
	_size = 0; // default in case allocation fails
	elements = new DT[n];
	if (elements == NULL) throw SortedArrayMemoryException();
	_size = n;
}

//destructor
template <class DT>
SortedArray<DT>::~SortedArray (){
	if (elements != NULL) delete[] elements;
	elements = NULL;
	_size = 0;
}

template <class DT>
int SortedArray<DT>::size () const {
	return _size;
}

template <class DT>
DT& SortedArray<DT>::operator[] (int k) {
	if ((k < 0) || (k >= size())) throw SortedArrayBoundaryException();
	return elements[k];
}

//The overloaded ostream operator
template <class DT>
ostream& operator << (ostream& s,  SortedArray<DT>& sa) { //This line taken from pg 146 of book

	for (int i = 0; i < sa.size(); i++)
	{
		if (i > 0)
		{
			s << ' '; //Prints a space between all elements, but not before first
		}
		s << sa[i]; //Prints the given element
	}
	s << endl; //Ends with an endline

	return s;
}

template <class DT>
int SortedArray<DT>::find(const DT& lookfor) {

	int left = 0; //Start from the first spot in the array
	int right = (this->size() - 1); //Going all the way to the end of the array
	if (this->elements == NULL) throw SortedArrayException();
	while (left <= right) //While there is no overlap
	{
		int mid = (left + right) / 2; //The midpoint is calculated
		int midVal = this->elements[mid]; //What is the value at this point?
		bool found = (midVal == lookfor); //
		if (found)
		{
			return mid;
		}
		else if (midVal < lookfor) left = mid + 1;
		else if (midVal > lookfor) right = mid - 1;
	}
	

	return -1; //If the value is not found, return -1
}

/*
template<class DT>
int binarySearch(SortedArray<DT>& sa, DT& x, int first, int last) { //Takes an array, a value to search for, and a first and last positions, returns the position 
	int mid;
	int midVal;

	if (first < last) { //If the first position is less than the last position
		mid = (first + last) / 2; //The middle position is between the first and last position
		midVal = sa[mid]; //The value at that position in the array
		if (x == midval) return mid; //If that is the value we are looking for, return that position
		else if (midval < x) //If midval is less than the value we are looking for
			return binarySearch(sa, x, mid + 1, last); //Search the right half of the array
		else return binarySearch(sa, x, first, mid); //Otherwise search the lower half

	else {
		if ((first == last) && (sa[first] < x))
			result = first + 1;
	}
	}
}
*/


int main() {

	SortedArray<int> ai(5);

	for (int i = 0; i < (ai.size ()); i++) {
		ai[i] = i;
	}

	int pos = ai.find(-2);
	cout << pos;

	return 0;

}