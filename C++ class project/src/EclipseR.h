/*
 * EclipseR.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Junaid
 */

#ifndef ECLIPSER_H_
#define ECLIPSER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "AVLtree.h"
#include "Eclipse.h"
#include "HashTable.h"
#include "ResizableArray.h"
#include "LinkedList.h"

using namespace std;

class EclipseR {
public:
	EclipseR();
	virtual ~EclipseR();

	int monthToValue(Eclipse e);
	int PartitionMonth(ResizableArray<Eclipse> &dataArray, int i, int k);
	void QuicksortMonth(ResizableArray<Eclipse> &dataArray, int i, int k);

	int Partition(ResizableArray<Eclipse> &dataArray, int i, int k, const int column);
	void Quicksort(ResizableArray<Eclipse> &dataArray, int i, int k, const int column);

	void parse(string &line, int &startingIndex, int &endingIndex);
	void parseFile(ifstream &inFS, ResizableArray<Eclipse> &dataArray);
	void fileInput(ResizableArray<Eclipse> &resizableArray);

	void userPrompt(ResizableArray<Eclipse> &dataArray);
	void find(ResizableArray<Eclipse> &dataArray, ResizableArray<Eclipse> &foundEclipses, const int sortedColumn);
	void output(ResizableArray<Eclipse> &foundEclipses);
	void sort(ResizableArray<Eclipse> &dataArray, int &sortedColumn);
};


#endif /* ECLIPSER_H_ */
