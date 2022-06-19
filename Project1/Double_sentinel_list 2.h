/*****************************************
 * UW User ID:  20817404
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2021
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head(nullptr ),
list_tail(nullptr ),
list_size( 0 )
{
	list_head = new Double_node();
	list_tail = new Double_node();
	list_head->previous_node = nullptr;
	list_head->next_node = end();
	list_tail->previous_node = rend();
	list_tail->next_node = nullptr;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// Enter your implementation here

	for(	Double_node *current_node = this->list_head; current_node!=nullptr; current_node=current_node->next()){

		Double_node *temp = current_node;
		delete temp;
		temp = nullptr;
		if(current_node==list_tail){
			delete current_node;
			current_node= nullptr;
		}
	}



}

// size() returns the number of items in the list.
template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}


//empty() returns true if there is no items in the list, false otherwise.
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	int num_node = size();
	if(num_node==0){
		return true;
	}
	return false;
}

//front() returns the value stored in the first non-sentinel node.
template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Enter your implementation here
	
	if(empty()){
		throw underflow();
	}
	return list_head->next()->value(); 
	

	// This returns a default value of Type
}

//back() returns the value stored in the last non-sentinel node.
template <typename Type>
Type Double_sentinel_list<Type>::back() const {

	if(empty()){
		throw underflow();
	}
	return list_tail->previous()->value();// This returns a default value of Type

}

//begin() returns the address of the first non-sentinel node.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Enter your implementation here

	return list_head->next();

}


//end() returns the address of the last sentinel node.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Enter your implementation here
	return list_tail;
}


//rbegin() returns the address of the last non-sentinel node.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Enter your implementation here
	Double_node* current_node = list_tail->previous();

	return current_node;
}


//begin() returns the address of the first sentinel node.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Enter your implementation here
	return list_head;
}

//find() returns the address of the node that contains the object.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	for(Double_node *current_node=list_head; current_node!=nullptr; current_node= current_node->next()){
		if((current_node->value())==obj){
			return current_node;
		}
	}
	return end();
}

//count() returns the number of nodes that contain the object.
template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here
	int num = 0; 
	for(Double_node *current_node= list_head->next(); current_node!=list_tail; current_node= (current_node->next())){

		if((current_node->value())==obj){
			 num++;
		}
	}



	return num;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

//push_front() inserts a new node at the front of the list, after the head sentinel.
template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {

		Double_node *temp = list_head->next();
		Double_node *new_node = new Double_node(obj,list_head, list_head->next());
		//updating the address of the first non sentinal node's previous_node to the new inserted node.
		temp->previous_node = new_node;
		//updating the address of the list head's next_node to new inserted node.
		list_head->next_node = new_node;
		list_size ++;
	
}

//push_back() inserts a new node at the end of the list, before the tail sentinel.
template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {

		Double_node *temp = list_tail->previous();
		Double_node *new_node = new Double_node(obj,list_tail->previous_node, list_tail);
		//updating the address of the last non sentinal node's next_node to the new inserted node.
		temp->next_node = new_node;
		//updating the address of the list tail's previous_node to new inserted node.
		list_tail->previous_node = new_node;
		list_size ++;
	
}


 //pop_front() deletes the first non sentinel node from the front of the list, after the head sentinel.
template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Enter your implementation here
	if(empty()){
		throw underflow();
	}
	else{
		// temp1 points to the first non-sentinel node
		Double_node *temp1= list_head->next();
		// temp2 points to the second non-sentinel node
		Double_node *temp2= temp1->next();
		//updating list_head next_node to second non-sentinel node
		list_head->next_node = temp2;
		//updating second non-sentinel node's previous node to list_head
		temp2->previous_node = list_head;
		//deleting first non-sentinel node
		delete temp1;
		temp1 = nullptr;
		
	}
	list_size --;
}

//pop_back() deletes the last non sentinel node from the end of the list, before the tail sentinel.
template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Enter your implementation here
if(empty()){
		throw underflow();
	}
	else{

		// temp1 points to the last non-sentinel node
		Double_node *temp1= list_tail->previous();
		// temp2 points to the second last non-sentinel node
		Double_node *temp2= temp1->previous();
		//updating list_tail's previous_node to second last non-sentinel node
		list_tail->previous_node = temp2;
		//updating second last non-sentinel node's next node to list_tail
		temp2->next_node = list_tail;
		//deleting last non-sentinel node
		delete temp1;
		temp1 = nullptr;
	}
	list_size --;


}


//Delete() deletes all the nodes in the linked list that have a value equal to the argument value 
// and returns the number of deleted node
template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// variable for counting deleted node.
	int count = 0;
	Double_node * current_node = list_head->next();	
	//loop will start from first non-sentinel node go till last non-sentinel node.
	while(current_node!=list_tail){
	//if the value of the current_node matches the object, set the temp pointer to current node
	//update the list head's next node to current node's next node.
	//update the previous node of current node's next node to list head.
	//then delete temp.
	// and increment the count value.
	if(current_node->value()==obj){
		Double_node *temp= current_node;
		list_head->next_node = current_node->next();
		current_node->next()->previous_node= list_head;
		current_node= current_node->next();
		delete temp;
		temp = nullptr;
		count++;
	}
	else{
		//if the object is not fount in current node. set current node to its next node.
			current_node = current_node->next();
		}
	}
		

	list_size = list_size - count;
	return count;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ), 
previous_node( pn ),
next_node( nn )
{
}

//value() returns value in the node.
template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return node_value; // This returns a default value of Type
}

//previous() returns address of the previous node.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return previous_node;
}

//next() returns address of the next node.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
