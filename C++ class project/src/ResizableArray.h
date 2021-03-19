/*
 * ResizableArray.h
 *
 *  Created on: Sep 26, 2017
 *      Author: Wyatt Carpenter
 */

#ifndef RESIZABLEARRAY_H_
#define RESIZABLEARRAY_H_
#include <iostream>
#include <iomanip>
#include <string>

namespace std {

template<typename T>
class ResizableArray {
	friend ostream &operator<<(ostream& s, ResizableArray& ca) {
//		for (int i = ca.length - 1; i >= 0; i--) {
//			s << ca.entries[i] << endl;
//		}
//		return s;

		for (int i = 0; i < ca.length; ++i) {
			s << ca.at(i) << std::endl;
		}

		return s;
	}

private:
	T * entries;
	int actuallength;
public:
	int length;
	void add(T entry) {
		if (length >= actuallength) {
			actuallength *= 2;
			T* tmp = new T[actuallength];
			for (int i = 0; i < length; i++) {
				tmp[i] = entries[i];
			}
			delete[] entries;
			entries = tmp;
		}
		entries[length - 1] = entry;
		length++;
	}
	void addAt(T entry, int index) {
		this->at(index);
		if (length >= actuallength) {
			actuallength *= 2;
			T* tmp = new T[actuallength];
			for (int i = 0; i < length; i++) {
				tmp[i] = entries[i];
			}
			delete[] entries;
			entries = tmp;
		}
		T tmp[length - index];
		for (int i = index; i < length; i++) {
			tmp[i] = entries[i];
		}
		length++;
		entries[index] = entry;
		for (int i = index; i < length; i++) {
			entries[i] = tmp[i];
		}
	}
	void replaceAt(T entry, int index) {
		this->at(index) = entry;
	}
	T pop() {
		if (length < actuallength / 2) {
			actuallength /= 2;
			T* tmp = new T[actuallength];
			for (int i = 0; i < actuallength; i++) {
				tmp[i] = entries[i];
			}
			delete[] entries;
			entries = tmp;
		}
		length--;
		return entries[length];
	}

	//Junaid edit
	void removeAt(int index) {

		for (int i = index; i < length - 1; ++i) {
			entries[i] = entries[i + 1];
		}

		//Wyatt check
		length--;
		if (length < actuallength / 2) {
			actuallength /= 2;
			T* tmp = new T[actuallength];
			for (int i = 0; i < actuallength; i++) {
				tmp[i] = entries[i];
			}
			delete[] entries;
			entries = tmp;
		}
	}
	//return entries[length];

// Wyatt Carpenter
//		T tmp[length - index - 1];
//		for (int i = index + 1; i < length; i++) {
//			tmp[i] = entries[i];
//		}
//
//		length--;
//		for (int i = index; i < length; i++) {
//			entries[i] = tmp[i];
//		}
//		if (length < actuallength / 2) {
//			actuallength /= 2;
//			T* tmp = new T[actuallength];
//			for (int i = 0; i < actuallength; i++) {
//				tmp[i] = entries[i];
//			}
//			delete[] entries;
//			entries = tmp;
//		}
//		return entries[length];
//}
	T &at(int i) {
		//"safe version" of array access
		//that throws an
		if (i > length) {
			throw std::out_of_range("Wow, that's quite a pickle you're in");
		}
		return entries[i];
	}

	ResizableArray(int baselength = 16) {
		length = 1;
		actuallength = baselength;
		entries = new T[actuallength];
	}
	~ResizableArray() {
		delete[] entries;
	}

};

}/* namespace std */
#endif /* RESIZABLEARRAY_H_ */
