/*
 * LinkedList.h
 *
 *  Created on: Oct 24, 2017
 *      Author: Nathan Thomas
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

//#include <iomanip>
//#include <string>
#include "ResizableArray.h"

template<typename T>
class LinkedList {
	friend std::ostream& operator<<(std::ostream& output, LinkedList<T>& l) {

		LinkedList<T>* curr = &l;
		while (curr != nullptr) {
			if (curr->_info != nullptr) {
				output << curr->info() << "\n";
			}
			curr = curr->_next;
		}

		return output;
	}
public:
	//both variables are set to null
	LinkedList();
	//initializes info. next is set to null
	LinkedList(T& info);
	//initializes both variables to passed in variables
	LinkedList(T& info, LinkedList<T>* next);
	//copy constructor. initialize linked list variables to same values as passed in linked list's variables
	LinkedList(const LinkedList<T>& l);
	//destructor. if not null delete the pointer and set to null (done for both pointers)
	virtual ~LinkedList();

	//overloaded operator = method.
	LinkedList<T>& operator=(const LinkedList<T>& l);

	//returns the pointer that points to the next linked list
	LinkedList<T>* next() const;

	//returns the info for this linked list
	T& info() const;

	//returns the node matching the key. If no matches throws an exception
	T& find(T& key) const;

	//returns the info at said index
	T& infoAt(int index) const;

	//returns the size of the linked list
	int size() const;

	//returns true if the linked list is empty
	bool isEmpty() const;

	//adds the object to the beginning of the linked list
	void add(T& object);

	//add the object to the specified index
	void addAt(T& object, int index);

	//deletes the first node of the linked list
	T remove();

	//removes the node at the specified index
	T removeAt(int index);

	//replaces the current info with new info. if no info throws an error
	void replace(T& object);

	//replaces the info at the given index
	void replaceAt(T& object, int index);

	//stores the linked list elements into a resizable array. return a pointer
	ResizableArray<T>* linkedListToArray();

private:
	//put _ before name so methods could be titled next() and info()
	LinkedList<T>* _next; //points to the next node in the linked list
	T* _info; //holds the information for the current node

};

//default constructor. both variables are set to null
template<typename T>
LinkedList<T>::LinkedList() {
	_next = nullptr;
	_info = nullptr;
}

//initializes info. next is set to null
template<typename T>
LinkedList<T>::LinkedList(T& info) {
	_info = new T(info);
	if (_info == nullptr) {
		throw exception();
	}
	_next = nullptr;
}

//initializes both variables to passed in variables
template<typename T>
LinkedList<T>::LinkedList(T& info, LinkedList<T>* next) {
	_info = new T(info);
	if (_info == nullptr) {
		throw exception();
	}
	_next = next; //we set the values to be equal
}

//copy constructor. initialize linked list variables to same values as passed in linked list's variables
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& l) {
	if (l._info == nullptr) {
		_info = nullptr;
	} else {
		_info = new T(*l._info);
		if (_info == nullptr) {
			throw exception();
		}
	}
	if (l._next == nullptr) {
		_next = nullptr;
	} else {
		_next = new LinkedList<T>(*l._next);
		if (_next == nullptr) {
			throw exception();
		}
	}
}

//destructor. if not null delete the pointer and set to null (done for both pointers)
template<typename T>
LinkedList<T>::~LinkedList() {
	if (_info != nullptr) {
		delete _info;
		_info = nullptr;
	}
	if (_next != nullptr) {
		delete _next;
		_next = nullptr;
	}
}

//overloaded operator = method.
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& l) {
	if (this != &l) {
		if (_info != nullptr) {
			delete _info;
		}
		if (_next != nullptr) {
			delete _next;
		}
		LinkedList(l);
	}

}

//returns the pointer that points to the next linked list
template<typename T>
LinkedList<T>* LinkedList<T>::next() const {
	return _next;
}

//returns the info for this linked list
template<typename T>
T& LinkedList<T>::info() const {
	if (_info == nullptr) {
		throw exception();
	}
	return *_info;
}

//returns the node matching the key. If no matches throws an exception
template<typename T>
T& LinkedList<T>::find(T& key) const {

	if (_info == nullptr) {
		throw exception();
	} else if (*_info == key) {
		return *_info;
	} else if (_next == nullptr) {
		//item was not found. throw exception
		throw exception();
	}
	return (_next->find(key));
}

//returns the info at said index
template<typename T>
T& LinkedList<T>::infoAt(int index) const {
	if (index < 0) {
		throw exception(); //index is out of bounds. this statement saves us from traversing the whole list when index is negative.
	}
	if (_info == nullptr) {
		throw exception();
	} else if (index == 0) {
		return *_info;
	} else if (_next == nullptr) {
		throw exception(); //index was out of bounds
	}
	//when _info not null, index not 0, and _next is not null.
	return (_next->infoAt(index - 1));

}

//returns the size of the linked list
template<typename T>
int LinkedList<T>::size() const {
	if (_next == nullptr) {
		if (_info == nullptr) {
			return 0; //if both pointers are 0 then the size of the linked list is 0
		}
		return 1;
	}
	return (1 + _next->size());
}

//returns true if the linked list is empty
template<typename T>
bool LinkedList<T>::isEmpty() const {
	return (_info == nullptr); //if info is not set then the linked list is empty
}

//adds the object to the beginning of the linked list
template<typename T>
void LinkedList<T>::add(T& object) {
	if (_info == nullptr) {
		_info = new T(object);
	} else {
		LinkedList<T>* newLL = new LinkedList<T>(*_info, _next);
		if (newLL == nullptr) {
			throw exception();
		}
		*_info = object;
		_next = newLL;
	}
}

//add the object to the specified index
template<typename T>
void LinkedList<T>::addAt(T& object, int index) {
	if (index < 0) {
		throw exception(); //avoid traversing the list if the index is negetive.
	}
	if (index == 0) {
		add(object);
	} else {
		if (_next == nullptr) {
			_next = new LinkedList<T>(object);
			if (_next == nullptr) {
				throw exception();
			}
			//this statement stops addAt from adding the object to the end twice. if not would call function again and add at index 0.
			if (index == 1) {
				return;
			}
		}
		_next->addAt(object, index - 1);
	}
}

//deletes the first node of the linked list
template<typename T>
T LinkedList<T>::remove() {

	if (_info == nullptr) {
		throw exception();
	}
	T oldInfo = *_info;
	delete _info;
	if (_next == nullptr) {
		_info = nullptr;
	} else {
		//at this point we know that next has a value
		LinkedList<T>* oldNext = _next;
		_info = _next->_info;
		_next = _next->_next;
		oldNext->_info = nullptr;
		oldNext->_next = nullptr;
	}
	return oldInfo;

}

//removes the node at the specified index
template<typename T>
T LinkedList<T>::removeAt(int index) {
	if (index < 0) {
		throw exception();
	}
	if (_info == nullptr) {
		throw exception();
	} else if (index == 0) {
		return remove();
	} else if (_next == nullptr) {
		throw exception(); //index was too large;
	}

	return _next->removeAt(index - 1);

}
//replaces the current info with new info. if no info throws an error
template<typename T>
void LinkedList<T>::replace(T& object) {
	if (_info == nullptr) {
		throw exception();
	} else {
		*_info = object;
	}
}

//replaces the info at the given index
template<typename T>
void LinkedList<T>::replaceAt(T& object, int index) {
	if (index < 0) {
		throw exception();
	}
	if (_info == nullptr) {
		throw exception();
	} else if (index == 0) {
		replace(object);
		return;
	} else if (_next == nullptr) {
		throw exception();
	}
	_next->replaceAt(object, index - 1);
}

//stores the linked list elements into a resizable array. return a pointer
template<typename T>
ResizableArray<T>* LinkedList<T>::linkedListToArray() {
	ResizableArray<T>* newArray = new ResizableArray<T>(size());
	LinkedList<T>* curr = this;

	while (curr != nullptr) {
		if (curr->_info != nullptr) {
			newArray->add(curr->info());
		}
		curr = curr->_next;
	}
	return newArray;
}

#endif /* LINKEDLIST_H_ */
