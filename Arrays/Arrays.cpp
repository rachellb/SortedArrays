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

public:
	SortedArray(); //default constructor
	SortedArray(int n); //The non-default constructor
	virtual ~SortedArray();
	virtual DT& operator[] (int k);
	virtual int size() ;  //Getter for size
	void setSize(int n);
	int getCapacity();
	void increaseSize(); //Increase the size of the objects in the array
	int find(const DT& lookfor);
	void insert(const DT& newElement); // For inserting new elements in the array
	void remove(const DT& oldElement); // Removes elements from the array
	SortedArray<DT>& split(int pos); //Splits the array at position pos, making two arrays
	void join(SortedArray<DT>& P); // Joins two arrays, destroying array P afterword

};

//The constructors ---------------------------------------------------------

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

//default constructor
template <class DT>
SortedArray<DT>::SortedArray() {
	_size = 0; // default in case allocation fails
	capacity = 0;
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
	_size = 0; //Starts out with no elements 
}

//destructor method ---------------------------------------------------------------------------
template <class DT>
SortedArray<DT>::~SortedArray (){
	if (elements != NULL) delete []elements;
	elements = NULL;
	_size = 0;
}

//Getter methods --------------------------------------------------------------------------
template <class DT>
int SortedArray<DT>::size () {
	return _size;
}

template <class DT>
void SortedArray<DT>::setSize(int n) {
	_size = n;
}

template <class DT>
int SortedArray<DT>::getCapacity() {
	return capacity;
}

//A fuction for increasing size, not sure if necessary ------------------------------------------------------------
template <class DT>
void SortedArray<DT>::increaseSize() {
	_size = _size + 1;
}

//The overloaded indexing operator ------------------------------------------------------------------------------
template <class DT>
DT& SortedArray<DT>::operator[] (int k) {
	if ((k < 0) || (k >= getCapacity())) throw SortedArrayBoundaryException(); //If indexing outside of bounds of array, throw error
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
	
	if ((this->size() == this->getCapacity())) throw SortedArrayBoundaryException(); // If the array has already hit max capacity, throw exception

	int pos;
	pos = this->find(newElement); //Search in this array for the position of the element
	
	if (this->elements[pos] == newElement) throw SortedArrayRedundantException(); //Should throw an error if the item is already in the array

	int n = this->size();

	this->increaseSize(); //Increase  the size of the array by one

	
for (int i = n; i > pos; i--) { //Starting from the end of the array and going until right before position
	this->elements[i] = this->elements[i - 1];  //Move everything over by one, this way I don't overwrite elements
}

this->elements[pos] = newElement; //Insert the new element into the appropriate position

}

//The remove function ------------------------------------------------------------------------------------
template<class DT>
void SortedArray<DT>::remove(const DT& oldElement) {

	int pos;
	pos = this->find(oldElement); //Search in this array for the position of the element
	if (this->elements[pos] != oldElement) throw SortedArrayMemoryException(); //If the element is not in the array, throw exception

	int n = this->size();

	for (int i = pos; i < n - 1; i++) { //Starting from the desired element and going until the next to last spot
		this->elements[i] = this->elements[i + 1]; //Should overwrite from the desired position to the end
	}

	this->_size = this->_size - 1; //Decrease the size of the array
}



//Returns a sorted array containing elements i through end of array being split, erases these elements from old array-------------------------
template<class DT>
SortedArray<DT>& SortedArray<DT>::split(int pos) {

	SortedArray<DT>* newArray = new SortedArray<DT>(this->getCapacity()); // Initiate an array to hold elements from position to end

	int x = this->size() - pos;

	for (int i = 0; i < x; i++) {
		newArray->elements[i] = this->elements[pos + i]; //Copy the elements from old  array to new array
		this->remove(this->elements[pos + i]); //Remove this element from the old array
	}

	newArray->setSize(x); //The size of the new array will be the old arrays size minus the cut point

	return *newArray; // If you star a star, does that make it just the value?
}

template<class DT>
void SortedArray<DT>::join(SortedArray<DT>& P) {

	if ((this->size() + P.size()) > this->getCapacity()) throw SortedArrayBoundaryException(); //If adding this array overruns array capacity, throw error

	for (int i = 0; i < P.size(); i++) {
		this->insert(P[i]); //Insert into the array 
	}

	//This works just like the destructor, fairly sure this is correct.
	if (P.elements != NULL) delete[] P.elements;
	P.elements = NULL;
	P._size = 0;

}

//Linked List Exceptions -------------------------------------------------------------------------------------

class LinkedListException : public Exception {};
class LinkedListMemory : public LinkedListException {};
class LinkedListBounds : public LinkedListException {};
class LinkedListNotFound : public LinkedListException {};
class LinkedListAttachToEmpty : public LinkedListException {};

template <class DT>
class LinkedSortedArrays
{

	template<class DT>
	friend ostream& operator<< (ostream& s, LinkedSortedArrays<DT>& la);

private:
	list<SortedArray<DT>> nameIT; //If it's a list of arrays, are we only making one list?
	int ArraySizeFactor;

public:
	LinkedSortedArrays(); //Default Constructor
	LinkedSortedArrays(int as); // Non-default Constructor
	~LinkedSortedArrays();
	DT& getList(LinkedSortedArrays<DT>& lsa);
	DT& find(const DT& key);
};

//The constructors ---------------------------------------------------------------------------------------------------
//Default
template <class DT>
LinkedSortedArrays<DT>::LinkedSortedArrays() {
	ArraySizeFactor = 0;
}

//Non-default constructor
template <class DT>
LinkedSortedArrays<DT>::LinkedSortedArrays(int asf) {
	ArraySizeFactor = asf;
}


//Destructor ----------------------------------------------------------------------------------------------------
template<class DT>
LinkedSortedArrays<DT>::~LinkedSortedArrays() {
	nameIT.clear();
	ArraySizeFactor = 0;
}

//Getters --------------------------------------------------------------------------------------------------------
template <class DT>
DT& LinkedSortedArrays<DT>::getList(LinkedSortedArrays<DT>& lsa) {
	return nameIT;
}



template <class DT>
ostream& operator << (ostream& s, LinkedSortedArrays<DT>& la) {
	for (int val : la.nameIT) {
		cout << val << endl; //Should iterate through all items in the list, then calls the ostream operator for each array
	}
}


/*
template<class DT>
DT& LinkedSortedArrays<DT>::find(const DT& key) {

}
*/

int main() {

	SortedArray<int>* ai = new SortedArray<int>(10); 
	SortedArray<int>* ai2 = new SortedArray<int>(10);

	LinkedSortedArrays<SortedArray<int>>* ls = new LinkedSortedArrays<SortedArray<int>>(10); //The star means pointer, list made in heap
	



	/*
	for (int i = 0; i < 5; i++) {
		(*ai)[i] = i*2;
		(*ai).increaseSize();
	}

	for (int i = 0; i < 5; i++) {
		(*ai2)[i] = (i*2)+1;
		(*ai2).increaseSize();
	}

	cout << *ai << endl;
	cout << (*ai2) << endl;

	(*ai).join(*ai2);

	cout << (*ai) << endl;
	*/
	//SortedArray<int> ai2 = ai.split(3); //Split at position 3

	//cout << ai;
	//cout << ai2;
	
	return 0;

}