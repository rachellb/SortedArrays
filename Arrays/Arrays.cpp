#include<iostream>
#include<list>
#include<cstdlib>
using namespace std;

// The Exceptions ---------------------------------------------------------
class Exception {};
class SArrayException : public Exception {};
class SArrayMemoryException : public SArrayException {};
class SArrayBoundaryException : public SArrayException {};


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

};

//The constructors ---------------------------------------------------------

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

//default constructor
template <class DT>
SortedArray<DT>::SortedArray() {
	_size = 0; // default in case allocation fails
	elements = new DT[ARRAY_CLASS_DEFAULT_SIZE];
	if (elements == NULL) throw SArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
}

//non-default constructor
template <class DT>
SortedArray<DT>::SortedArray(int n) {
	_size = 0; // default in case allocation fails
	elements = new DT[n];
	if (elements == NULL) throw SArrayMemoryException();
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
	if ((k < 0) || (k >= size())) throw SArrayBoundaryException();
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

int main() {

	SortedArray<int> ai(5);

	for (int i = 0; i < ai.size (); i++) {
		ai[i] = i;
	}

	cout << ai;

	return 0;

}