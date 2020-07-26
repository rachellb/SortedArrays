#include<iostream>
#include<list>
#include<cstdlib>
using namespace std;

// The Exceptions ---------------------------------------------------------
class Exception {};
class SortedArrayException : public Exception {};
class SortedArrayMemoryException : public SortedArrayException {};
class SortedArrayBoundaryException : public SortedArrayException {};
class SortedArrayRedundantException : public SortedArrayException {};


//template<class DT>
//int binarySearch(SortedArray<DT>& sa, DT& x, int first, int last);

template <class DT>
class SortedArray {
	
	template<class DT>
	friend ostream& operator<< (ostream& s, SortedArray<DT>& sa);

protected:
	DT* elements; //The elements that will be inside the array
	int _size;    // The size of the array
	int capacity; // The initial capacity of the array
	void copy(const SortedArray<DT>& sa);

public:
	SortedArray(); //default constructor
	SortedArray(int n); //The non-default constructor
	SortedArray(const SortedArray<DT>& sa);
	virtual ~SortedArray();
	virtual DT& operator[] (int k);
	virtual int size() ; 
	void increaseSize(); //Increase the size of the objects in the array
	//void operator= (const SortedArray<DT>& sa);
	int find(const DT& lookfor);
	void insert(const DT& newElement); // For inserting new elements in the array
};

//The constructors ---------------------------------------------------------

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

//default constructor
template <class DT>
SortedArray<DT>::SortedArray() {
	_size = 0; // default in case allocation fails
	capcity = 0;
	elements = new DT[ARRAY_CLASS_DEFAULT_SIZE];
	if (elements == NULL) throw SortedArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
}

//non-default constructor
template <class DT>
SortedArray<DT>::SortedArray(int n) {
	_size = 0; // default in case allocation fails
	capacity = n;
	elements = new DT[n];
	if (elements == NULL) throw SortedArrayMemoryException();
	_size = n;
}

template <class DT>
SortedArray<DT>::SortedArray(const SortedArray<DT>& sa) {
	if (&sa != this)
		copy(sa);
}

//For implementing copy constructor
template <class DT>
void SortedArray<DT>::copy(const SortedArray<DT>& sa) {
	_size = 0;
	elements = new DT[sa.size()];
	if (elements == NULL) throw SortedArrayMemoryException();
	_size = sa.size();
	for (int i = 0; i < _size; i++) {
		elements[i] = sa.elements[i];
	}
}

//destructor
template <class DT>
SortedArray<DT>::~SortedArray (){
	if (elements != NULL) delete []elements;
	elements = NULL;
	_size = 0;
}

template <class DT>
int SortedArray<DT>::size () {
	return _size;
}

template <class DT>
void SortedArray<DT>::increaseSize() {
	_size = _size + 1;
}

template <class DT>
DT& SortedArray<DT>::operator[] (int k) {
	if ((k < 0) || (k >= size())) throw SortedArrayBoundaryException();
	return elements[k];
}

//The overloaded ostream operator ------------------------------------------------------------------------------
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

//The find function, returns the position of the element if in the array -----------------------------------------------------------------
template <class DT>
int SortedArray<DT>::find(const DT& lookfor) {

	int left = 0; //Start from the first spot in the array
	int right = (this->size() - 1); //Going all the way to the end of the array
	if (this->elements == NULL) throw SortedArrayException();
	while (left <= right) //While there is no overlap
	{
		int mid = (left + right) / 2; //The midpoint is calculated
		DT& midVal = this->elements[mid]; //What is the value at this point?
		bool found = (midVal == lookfor); //
		if (found)
		{
			return mid;
		}
		else if (midVal < lookfor) left = mid + 1;
		else if (midVal > lookfor) right = mid - 1;
	}
	

	return left; //If the value is not found, return -1
}


//Insertion ---------------------------------------------------------------------------------------------------------------------
template <class DT>
void SortedArray<DT>::insert(const DT& newElement) {
	//if ((this->find(newElement)) != 0) throw SortedArrayRedundantException(); // TODO: fix this If the element is already in the array, throw exception
	//if ((this->size() == this.capacity)) throw SortedArrayBoundaryException(); // If the array has already hit max capacity, throw exception

	int pos;
	pos = this->find(newElement); //Search in this array for the position of the element
	
	
	this->increaseSize(); //Increase  the size of the array by one

	
	int n = this->size();
	
	
	for (int i = n-1; i > pos; i--) { //Starting from the end of the array and going until right before position
		this->elements[i] = this->elements[i - 1];  //Move everything over by one, this way I don't overwrite elements
	}
	
	this->elements[pos] = newElement; //Insert the new element into the appropriate position
	
}





int main() {

	SortedArray<int> ai(5);

	for (int i = 0; i < (ai.size ()-1); i++) {
		ai[i] = i*2;
	}

	cout << ai << endl;
	
	//cout << ai[ai.size()-1] <<endl;

	//cout << ai.find(-1) << endl;

	//ai.insert(3);

	cout << ai;
	//cout << ai[5];
	
	return 0;

}