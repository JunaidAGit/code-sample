/*
 * sha256 part of EclipseR3.0
 *
 *  Created on: November 12th, 2017
 *      Author: Junaid Ahmed
 *      HashMap class from: http://www.sanfoundry.com/cpp-program-hash-tables-double-hashing/
 *      Modified by JA to accomodate for Eclipses
 */

#include <iostream>
#include "sha256.h"

/*
 * C++ Program to Implement Linked Hash Tables with Double Hashing
 */

#define MIN_TABLE_SIZE 10
using namespace std;
/*
 * Node Type Declaration
 */
enum EntryType {
	Legitimate, Empty, Deleted
};
/*
 * Node Declaration
 */
struct HashNode {
	Eclipse element;
	enum EntryType info;
};
/*
 * Table Declaration
 */
struct HashTable {
	int size;
	HashNode *table;
};

/*
 * Function to Genereate First Hash: Function by Junaid Ahmed
 */
int HashFunc1(Eclipse key, int size) {

	string value;

	//Error checking: If the catalog number is blank, it will set the value to -1
	if (key.catalogNumber.find_first_not_of(" ") == std::string::npos
			|| key.catalogNumber == "") {
		value = "-1";
	}

	//Error checking: If an empty catalogNumber is not found, the value is set equal to it.
	else {
		value = key.catalogNumber;
	}

	try {
		//Gets a hashed string using sha256
		string str = sha256(value);

		//Obtains the first 5 characters of the hash
		str = str.substr(0, 5);

		//Converts to an integer in base-16
		return (std::stoi(str, 0, 16) % size);

	} catch (exception *e) {
		try {
			//This is HashFunc2
			return (std::stoi(value) * size - 1) % size;
		} catch (exception *e)

		{	//This is the basic modulus hash
			return (std::stoi(value) % size);
		}
	}
}
/*
 * Function to Genereate Second Hash: Collision resolution strategy.
 * Modified method to convert catalogNumber to an integer before applying math.
 */
int HashFunc2(Eclipse key, int size) {
	return ((std::stoi(key.catalogNumber) * size - 1) % size);
}
/*
 * Function to Initialize Table
 */
HashTable *initializeTable(int size) {
	HashTable *htable;

	//Minimum table size
	if (size < MIN_TABLE_SIZE) {
		cout << "Table Size Too Small" << endl;
		return NULL;
	}
	htable = new HashTable;

	//Maximum table size
	if (htable == NULL) {
		cout << "Out of Space" << endl;
		return NULL;
	}
	htable->size = size;
	htable->table = new HashNode[htable->size];

	//Minimum table size
	if (htable->table == NULL) {
		cout << "Table Size Too Small" << endl;
		return NULL;
	}

	for (int i = 0; i < htable->size; i++) {
		htable->table[i].info = Empty;
		htable->table[i].element.catalogNumber = "-1";
	}
	return htable;
}
/*
 * Function to Find Element from the table
 */
int Find(Eclipse key, HashTable *htable) {
	int hashVal = HashFunc1(key, htable->size);
	int stepSize = HashFunc2(key, htable->size);

	//Traverses through the hash table looking for the item
	while (htable->table[hashVal].info != Empty
			&& htable->table[hashVal].element != key) {
		hashVal = hashVal + stepSize;
		hashVal = hashVal % htable->size;
	}
	return hashVal;
}
/*
 * Function to Insert Element into the table
 */
void Insert(Eclipse key, HashTable *htable) {
	int pos = Find(key, htable);
	if (htable->table[pos].info != Legitimate) {
		htable->table[pos].info = Legitimate;
		htable->table[pos].element = key;
	}
}
/*
 * Function to Rehash the table
 */
HashTable *Rehash(HashTable *htable) {
	int size = htable->size;
	HashNode *table = htable->table;
	htable = initializeTable(2 * size);
	for (int i = 0; i < size; i++) {
		if (table[i].info == Legitimate)
			Insert(table[i].element, htable);
	}
	delete(table); //Changed from free(table)
	return htable;
}
/*
 * Function to Retrieve the table
 */
void Retrieve(HashTable *htable) {
	for (int i = 0; i < htable->size; i++) {
		string value = htable->table[i].element.catalogNumber;
		if (value == "-1")
			cout << "Position: " << setw(5) << i + 1 << "  Element: NULL"
					<< endl << endl;
		else
			cout << "Position: " << setw(5) << i + 1 << "  Element: " << htable->table[i].element
					<< endl << endl;
	}
}
