/*****************************************
 * UW User ID:  20817404
 * Submitted for ECE 250
 * Semester of Submission:  Fall 2021
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
		Type *array;
		int ifront;
		int iback;
		int deque_size;
		int initial_array_capacity;
		int array_capacity;
		void resize();

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
// Your initalization list
{
	// Enter your implementation here
	if(n<16){
		n=16;
	}
	initial_array_capacity=n;
	array_capacity=n;
	array = new Type[array_capacity];
	ifront=0;
	iback=0;
	deque_size=0;
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	// Enter your implementation here
	initial_array_capacity= deque.initial_array_capacity;
	array_capacity=deque.array_capacity;
	array = new Type[array_capacity];
	ifront=deque.ifront;
	iback=deque.iback;
	deque_size=deque.deque_size;
	
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	// Enter your implementation here
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
	delete [] array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here
	return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	if(deque_size==0){
		return true;
	}
	return false;
}

//Returns the first element of the deque
template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
	if(deque_size==0){
		throw underflow();
	}
	return array[ifront];
}

//Returns the last element of the deque
template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
		if(deque_size==0){
		throw underflow();
	}
	return array[iback];
}

//swaps all the member variables of this deque with those of the argument
template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );

	// Enter your implementation here
	std::swap( ifront, deque.ifront );
	std::swap( iback, deque.iback );
	std::swap( deque_size, deque.deque_size );
	std::swap( initial_array_capacity, deque.initial_array_capacity );
	std::swap( array_capacity, deque.array_capacity );

}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

//Insert the new element at the front of the deque. The capacity of the array is doubled if the array is filled before inserting the element.
template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	resize();
	if(!empty()){
		if (ifront == 0){
			ifront = capacity()-1;
		}
		else {
			ifront--;
		}
	}
	array[ifront] = obj;
	deque_size++;

}

//Insert the new element at the back of the deque. The capacity of the array is doubled if the array is filled before inserting the element.

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	resize();
	if(!empty()){
		iback=(iback+1)%capacity();
	}
	array[iback] = obj;
	deque_size++;

}
//Removes the element at the front of the deque. If, after the element is removed, the array is 1/4 full or less and the array capacity is greater than the initial capacity, the capacity of the array is halved
template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here
	if(empty()) {
		throw underflow();
	}
  if(ifront != iback) {
		ifront = (ifront+1)%capacity();
	}
	deque_size--;
	resize();

}

//Removes the element at the back of the deque. If, after the element is removed, the array is 1/4 full or less and the array capacity is greater than the initial capacity, the capacity of the array is halved
template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
	if(empty()){
		throw underflow();
	}
	if(ifront!= iback){
			if(iback == 0) {
				iback = capacity()-1;
			}
			else {
				iback--;
				}

	}
	deque_size --;
	resize();
}

//Empties the deque by resetting the member variables
template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
	deque_size = initial_array_capacity;
	array_capacity = initial_array_capacity;
	ifront=0;
	iback=0;


}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functions (helper functions) here
//If, after removing an element from a deque the number of elements is 1/4 the capacity of the array or less, then the capacity of the array is halved. The capacity of the array may not be reduced below the initially specified capacity.
//If an element is being inserted into a deque where the array is already full, the capacity of the array is doubled.
template <typename Type>
void Resizable_deque<Type>::resize(){
	int old_capacity= capacity();
	if(size()==capacity()){
		array_capacity*=2;
	}else if(size()<=capacity()/4){
		array_capacity= std::max(initial_array_capacity,capacity()/2);
	}else{
	}
	if(old_capacity - array_capacity!=0){
		Type *old_array = array;
		array = new Type [array_capacity];
		for(int i=0; i< array_capacity; i++){
			array[i] = old_array [(i+ifront)%old_capacity];

		}
		ifront = 0;
		iback = size() - 1;
		delete [] old_array;

	}
	

}




/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
