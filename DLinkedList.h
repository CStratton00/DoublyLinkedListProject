//
// Collin Stratton
// 10/3/2020
// This is my work
//

#pragma once

#ifndef DLINKLIST_H
#define DLINKLIST_H

#include <iostream>

using namespace std;

template <class T>
class DLinkedList {

	//PROVIDED
	friend ostream & operator<<(ostream & out, const DLinkedList<T> & rhs) {
		DNode * curr = rhs.header->next;
		while (curr != rhs.header) {
			out << curr->data << " ";
			curr = curr->next;
		}
		return out;
	}

public:

	//inner class DNode PROVIDED
	class DNode {
	public:
		DNode * next;
		DNode * prev;
		T data;

		DNode(T val = T()) {
			data = val;
			next = prev = this;
		}
		
	};

	//create an empty list:  PROVIDED
	DLinkedList() {
		//create the header
		header = new DNode();		
	}

	//add method  PROVIDED
	DNode * add(T item) {
		//add a new node and return a 
		//pointer to this node
		DNode * newNode = new DNode(item);
		newNode->prev = header;
		newNode->next = header->next;
		header->next->prev = newNode;
		header->next = newNode;
		return newNode;
	}

	/**
	* ASSIGNED
	* remove val from the list
	*
	* @param val
	* @return true if successful, false otherwise
	*/
	bool remove(T val) {
        DNode* temp = header;

        while(temp->data != val && temp->next != NULL) { temp = temp->next; }   // while loop to find the position to delete
        if(temp->data == val) {                                         // checks the position to delete
            temp->prev->next = temp->next;                              // removes references to the position to delete
            temp->next->prev = temp->prev;
            delete(temp);                                               // deletes temp from memory
            return true;
        }
		return false;
	}
	

	/**
	* ASSIGNED
	*
	* @param item
	*/
	void insertOrder(T item) {
	    DNode* newDNode = new DNode(item);                              // new node containing the new data
        DNode* temp = header->next;                                     // temp header node

        while(temp->data <= newDNode->data && temp != header) { temp = temp->next; }    // loop to know where to insert the new data

        if(temp->next == header && temp->data <= newDNode->data) {      // checks if the data is less than the final node
            newDNode->next = temp->next;                                // inserts node before the last value
            newDNode->prev = temp;

            temp->next->prev = newDNode;
            temp->next = newDNode;
        } else if(temp == header && temp->data >= newDNode->data) {     // checks if the data is greater than the final node
            newDNode->next = temp;                                      // inserts node after the last value
            newDNode->prev = temp->prev;

            temp->prev->next = newDNode;
            temp->prev = newDNode;
            header = newDNode;                                          // reassign header node
        } else {                                                        // inserts node for all other cases
            newDNode->next = temp;
            newDNode->prev = temp->prev;

            temp->prev->next = newDNode;
            temp->prev = newDNode;
        }
	}

	/**
	* ASSIGNED
	*
	* @param item
	*/
	bool insertOrderUnique(T item) {
        DNode* newDNode = new DNode(item);
        DNode* temp = header;

        while(newDNode->data != temp->data && temp->next != header) { temp = temp->next; }  // checks to make sure data is unique
        if(temp->next == header && newDNode->data != temp->data) {      // if the data is unique, add call insert order
            insertOrder(item);
            return true;
        }
		return false;
	}

	/**
	* ASSIGNED
	* PRE:  this and rhs are sorted lists
	* @param rhs
	* @return list that contains this and rhs merged into a sorted list
	* POST:  returned list will not contain duplicates, both rhs and this
	* will have no elements
	*/
	DLinkedList merge(DLinkedList rhs) {
		DLinkedList result;                                             // new Doubly Linked List
		DNode* head = result.header;                                    // head containing the header for the DList
		DNode* temp1 = header->next;                                    // temp for the lhs head
		DNode* temp2 = rhs.header->next;                                // temp for the rhs head

		while(temp1 != header && temp2 != rhs.header) {                 // loops through both lists
		    DNode* store;                                               // node to store other nodes

            if(temp1->data < temp2->data) {                             // checks for if list one < list two
                store = temp1;                                          // stores the temp1 value

                temp1->prev->next = temp1->next;                        // dereferences the temp node
                temp1->next->prev = temp1->prev;
                temp1 = temp1->next;
            } else {
                store = temp2;                                          // stores the temp2 value

                temp2->prev->next = temp2->next;                        // dereferences the temp node
                temp2->next->prev = temp2->prev;
                temp2 = temp2->next;
            }

            store->next = head->next;                                   // puts all the store list into the result list
            store->prev = head;

            head->next->prev = store;
            head->next = store;

            head = head->next;
		}

        if (temp1 == header) {                                          // checks if the temp1 list finished
            head->next = temp2;                                         // references the last set of nodes from the rhs to result
            head->next->prev = head;

            result.header->prev = rhs.header->prev;
            rhs.header->next = rhs.header->prev = rhs.header;
        } else {
            head->next = temp1;                                         // references the last set of nodes from the lhs to result
            head->next->prev = head;

            result.header->prev = header->prev;
            header->next = header->prev = header;
        }

        result.header->prev->next = result.header;                      // reassigns header

		return result;
	}

	
private:
	//DLinkedList fields:  PROVIDED
	DNode * header;	

};


#endif