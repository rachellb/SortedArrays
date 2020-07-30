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
	SortedArray(int n, const DT& val); //Non-default with pre-initialized array of values
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
	DT& getMin(); //returns the min value of the array
	DT& getMax(); //returns the max value of the array
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

//non-default constructor 
template <class DT>
SortedArray<DT>::SortedArray(int n, const DT& val) {
	_size = 0; // default in case allocation fails
	capacity = n;
	elements = new DT[n];
	if (elements == NULL) throw SortedArrayMemoryException();
	_size = n; //Starts out with no elements 
	for (int i = 0; i < n; i++) {
		elements[i] = val; //Fill with value
	}
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


//Max and Min values in the array ---------------------------------------------------------------------------------------
template <class DT>
DT& SortedArray<DT>::getMin() {
	return this->elements[0]; //Returns the first value in the array
}

template <class DT>
DT& SortedArray<DT>::getMax() {
	return this->elements[this->size()-1]; //Returns the last value in the array
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
	

	return left; //If the value is not found, return left
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
	list<SortedArray<DT>> getList();
	int getArraySize();
	int find(const DT& key); //Finds elements in the arrays
	void insert(const DT& newOne); //Inserts new item into array if it fits and isn't already there
	void insertArray(const SortedArray<DT>& newA);
};

//The constructors ---------------------------------------------------------------------------------------------------
//Default
template <class DT>
LinkedSortedArrays<DT>::LinkedSortedArrays() {
	ArraySizeFactor = 0;
	list<SortedArray<DT>> nameIT;
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
list<SortedArray<DT>> LinkedSortedArrays<DT>::getList() {
	return nameIT;
}

//Getters --------------------------------------------------------------------------------------------------------
template <class DT>
int LinkedSortedArrays<DT>::getArraySize() {
	return ArraySizeFactor;
}


template <class DT>
ostream& operator << (ostream& s, LinkedSortedArrays<DT>& la) {

	typename list<SortedArray<DT>>::iterator iter;

	for (iter = la.nameIT.begin(); iter != la.nameIT.end(); iter++) {
		s << *iter << endl;
	}

	return s;
}



template<class DT>
int LinkedSortedArrays<DT>::find(const DT& key) {

	//Hopefully, this grabs the first item in the first array and last item of the last, and checks against the key
	if ((this->nameIT.front()[0] > key)) throw LinkedListBounds(); 

	SortedArray<DT> last = this->nameIT.back(); //Grabs the final array in list

	int s = ((this->nameIT.back()).size()) - 1; //Maybe will be position of final element?
	if (last[s] < key) throw LinkedListBounds();

	DT* findme = new DT(key);
	int nodeCount = 0;
	int indexInNode = -1;
	typename list <SortedArray<DT> > ::iterator it;

	for (it = nameIT.begin(); it != nameIT.end(); it++) {
		//getMin() and getMax() return the min and max value in the current SortedArray
		if (key >= (*it).getMin() && key <= (*it).getMax()) {
			indexInNode = (*it).find(*findme);
			break;
		}
		nodeCount++;
	}
	//delete findme;
	return (nodeCount * ArraySizeFactor) + indexInNode; // return an int which would represent the pos if all boxes in one array.

}


template<class DT>
void LinkedSortedArrays<DT>::insert(const DT& newOne) {


	DT& val = this->find(newOne); //Not sure what this should be attached to
	
	//Case 1: Item already in list:
	if (*val == newOne) throw SortedArrayException(); //If value at location is equal to the new value, throw error

	//Case 2: Item not in list and there's room for insertion
	this->getList().insert(val); //I don't think this makes sense, how is it inserting into the appropriate spot?

	//Case 3: Item not in list but no room to insert, so will need to split an array and add it to list


}

template <class DT>
void LinkedSortedArrays<DT>::insertArray(const SortedArray<DT>& newA) {
	this->nameIT.push_back(newA);
}


int main() {

	LinkedSortedArrays<int>* ls = new LinkedSortedArrays<int>(10);


	int findPos = (*ls).find(value); //insertPos will hold the value returned by the LSA find method
	int nodePosition = findPos / ls->getArraySize();  // int division floors the result to get correct node
	int elementsPosition = findPos % ls->getArraySize();  // modulo gives us the remainder which represents the array position


	//SortedArray<int>* ai = new SortedArray<int>(5); 
	//SortedArray<int>* ai2 = new SortedArray<int>(10, 7); // Makes an array of 10 number 7s.

	
	/*
	for (int i = 0; i < 5; i++) {
		(*ai)[i] = i * 2;
		(*ai).increaseSize();
	}
	cout << (*ai) << endl;
	cout << (*ai).getMax();
	*/
	

	//cout << *ai;

	//list<SortedArray<int>>  x = ls.getList();

	//list<SortedArray<int>> test;

	/*
	test.push_front(*ai);

	ls->nameIT.push_front(*ai);
	*/
	//(*ls).getList().push_front(*ai); //I thought this would add list

	//(*ls).insertArray(*ai);

	int pos = (*ls).find(8);

	cout << (*ls);


	//cout << ls;

	//ls->getList();
	
	

	/*
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