/*
 * EclipseR.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Junaid Ahmed
 */

#include "EclipseR.h"

using namespace std;

//Initializing to check for valid eclipses
int invalidEclipses = 0;

//Header information
string headerInfo[10];

//Array of catalog numbers
ResizableArray<string> catalogNumbers;

//Linked list that contains all of the eclipse data
LinkedList<Eclipse> linkedList;

//AVLTree that contains all of the eclipse data
AVLtree<Eclipse> tree;

//Converts the month to an int value. The int is opposite of the month value because higher months have higher values for the purpose of sorting.
int monthToValue(Eclipse e) {

	if (e.month.find("Jan") != std::string::npos) {
		return 12;
	}

	else if (e.month.find("Feb") != std::string::npos) {
		return 11;
	}

	else if (e.month.find("Mar") != std::string::npos) {
		return 10;
	}

	else if (e.month.find("Apr") != std::string::npos) {
		return 9;

	} else if (e.month.find("May") != std::string::npos) {
		return 8;

	} else if (e.month.find("Jun") != std::string::npos) {
		return 7;

	} else if (e.month.find("Jul") != std::string::npos) {
		return 6;

	} else if (e.month.find("Aug") != std::string::npos) {
		return 5;

	} else if (e.month.find("Sep") != std::string::npos) {
		return 4;

	} else if (e.month.find("Oct") != std::string::npos) {
		return 3;

	} else if (e.month.find("Nov") != std::string::npos) {
		return 2;

	} else if (e.month.find("Dec") != std::string::npos) {
		return 1;
	}

	else {
		//cerr << "Conversion failed << endl; //This will create 4 error messages because of 4 empty eclipses.
		return -1;
	}
}

//Partition algorithm for MONTH for Quicksort from Zybooks. Edited for Eclipses. Pairs with Quicksort as the most efficient sorting algorithm for sorting eclipses.
int PartitionMonth(ResizableArray<Eclipse> &dataArray, int i, int k) {
	int l = 0;
	int h = 0;
	int midpoint = 0;
	int pivot = 0;
	Eclipse *temp = new Eclipse();
	bool done = false;

	/* Pick middle element as pivot */
	midpoint = i + (k - i) / 2;

	pivot = monthToValue(dataArray.at(i));

	l = i;
	h = k;

	while (!done) {

		/* Increment l while dataArray[l] < pivot */
		while (l < dataArray.length && pivot > monthToValue(dataArray.at(l))) {
			++l;
		}

		/* Decrement h while pivot < dataArray[h] */
		while (h >= 0 && pivot < monthToValue(dataArray.at(h))) {
			--h;
		}

		/* If there are zero or one elements remaining,
		 all numbers are partitioned. Return h */
		if (l >= h) {
			done = true;
		} else {
			/* Swap dataArray[l] and dataArray[h],
			 update l and h */
			*temp = dataArray.at(l);
			dataArray.at(l) = dataArray.at(h);
			dataArray.at(h) = *temp;

			++l;
			--h;
		}
	}

	return h;
}

//Quicksort algorithm for month quicksort from zybooks. Edited for Eclipses. Most efficient algorithm for sorting eclipses.
void QuicksortMonth(ResizableArray<Eclipse> &dataArray, int i, int k) {
	int j = 0;

	/* Base case: If there are 1 or zero elements to sort,
	 partition is already sorted */
	if (i >= k) {
		return;
	}

	/* Partition the data within the array. Value j returned
	 from partitioning is location of last element in low partition. */
	j = PartitionMonth(dataArray, i, k);

	/* Recursively sort low partition (i to j) and
	 high partition (j + 1 to k) */

	QuicksortMonth(dataArray, i, j);
	QuicksortMonth(dataArray, j + 1, k);

	return;
}

//Partition algorithm used for Quicksort from Zybooks. Edited for Eclipses. Pairs with QuickSort as the most efficient sorting algorithm for sorting eclipses.
int Partition(ResizableArray<Eclipse> &dataArray, int i, int k,
		const int column) {

	int l = 0;
	int h = 0;
	int midpoint = 0;
	string pivot = "";
	Eclipse *temp = new Eclipse();
	bool done = false;

	/* Pick middle element as pivot */
	midpoint = i + (k - i) / 2;

	pivot = dataArray.at(midpoint).columnValueToVariable(column);

	l = i;
	h = k;

	while (!done) {

		/* Increment l while dataArray[l] < pivot */
		while (dataArray.at(l).columnValueToVariable(column) < pivot
				&& l < dataArray.length) {
			++l;
		}

		/* Decrement h while pivot < dataArray[h] */
		while (pivot < dataArray.at(h).columnValueToVariable(column) && h >= 0) {
			--h;
		}

		/* If there are zero or one elements remaining,
		 all numbers are partitioned. Return h */
		if (l >= h) {
			done = true;
		} else {
			/* Swap dataArray[l] and dataArray[h],
			 update l and h */
			*temp = dataArray.at(l);
			dataArray.at(l) = dataArray.at(h);
			dataArray.at(h) = *temp;

			++l;
			--h;
		}
	}

	return h;
}

//Quicksort algorithm from zybooks. Edited for Eclipses. Most efficient algorithm for sorting eclipses.
void Quicksort(ResizableArray<Eclipse> &dataArray, int i, int k,
		const int column) {
	int j = 0;

	/* Base case: If there are 1 or zero elements to sort,
	 partition is already sorted */
	if (i >= k) {
		return;
	}

	/* Partition the data within the array. Value j returned
	 from partitioning is location of last element in low partition. */
	j = Partition(dataArray, i, k, column);

	/* Recursively sort low partition (i to j) and
	 high partition (j + 1 to k) */
	Quicksort(dataArray, i, j, column);

	Quicksort(dataArray, j + 1, k, column);

	return;
}

//Binary search algorithm modified from http://www.algolist.net/Algorithms/Binary_search
int binarySearch(ResizableArray<Eclipse> array, string valueToSearch,
		int columnValue, int left, int right) {
	while (left <= right) {
		int middle = (left + right) / 2;
		if (array.at(middle).columnValueToVariable(columnValue)
				== valueToSearch)
			return middle;
		else if (array.at(middle).columnValueToVariable(columnValue)
				> valueToSearch)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return -1;
}

//Parses the starting and ending indicies
void parse(string &line, int &startingIndex, int &endingIndex) {
	startingIndex = line.find_first_not_of(" ", endingIndex);
	endingIndex = line.find_first_of(" ", startingIndex);
}

//Parses the data from the given file
void parseFile(ifstream &inFS, ResizableArray<Eclipse> &dataArray) {

	//line string for parsing
	string line;

	//bool to check for duplicate catalogNumbers
	bool swapEclipse = false;

	//Initializing indices
	int startingIndex = 0;
	int endingIndex = 0;

	//This is to read in the first 10 lines of the file and skip it
	for (int i = 0; i < 10; ++i) {
		getline(inFS, line);
		headerInfo[i] = line;
		//inFS >> headerInfo[i];
	}

	//While the file has not reached its end
	while (getline(inFS, line)) {
		if (inFS.good()) {

			//Creates a new pointer to an eclipse object
			Eclipse *eclipse = new Eclipse;

			//Parses the catalogNumber: this does not use parse because it starts at index 0
			startingIndex = line.find_first_not_of(" ", 0);
			endingIndex = line.find_first_of(" ", startingIndex);
			eclipse->catalogNumber = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Adds the catalogNumber to the array of catalog numbers
			catalogNumbers.add(eclipse->catalogNumber);

			//Catalog number check
			swapEclipse = false;

			//Sets the swap eclipse to true in order to swap it later
			//Check if "-2" is correct
			for (int i = 0; i < catalogNumbers.length - 2; ++i) {
				if (catalogNumbers.at(i) == eclipse->catalogNumber) {
					swapEclipse = true;
				}
			}

			if ("" == eclipse->catalogNumber) {
				continue;
			}

			//Parses the plate
			parse(line, startingIndex, endingIndex);
			eclipse->plate = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the year
			parse(line, startingIndex, endingIndex);
			eclipse->year = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the month
			parse(line, startingIndex, endingIndex);
			eclipse->month = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the day
			parse(line, startingIndex, endingIndex);
			eclipse->day = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the greatestEclipse
			parse(line, startingIndex, endingIndex);
			eclipse->greatestEclipse = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the DTs
			parse(line, startingIndex, endingIndex);
			eclipse->DTs = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the lunar
			parse(line, startingIndex, endingIndex);
			eclipse->lunar = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the saros
			parse(line, startingIndex, endingIndex);
			eclipse->saros = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the type
			parse(line, startingIndex, endingIndex);
			eclipse->type = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the gamma
			parse(line, startingIndex, endingIndex);
			eclipse->gamma = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the magnitude
			parse(line, startingIndex, endingIndex);
			eclipse->mag = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the latitude
			parse(line, startingIndex, endingIndex);
			eclipse->latitude = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the longitude
			parse(line, startingIndex, endingIndex);
			eclipse->longitude = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the altitude
			parse(line, startingIndex, endingIndex);
			eclipse->alt = line.substr(startingIndex,
					endingIndex - startingIndex);

			//Parses the azm
			parse(line, startingIndex, endingIndex);
			eclipse->azm = line.substr(startingIndex,
					endingIndex - startingIndex);

			//If the eclipse is partial, there is no width or central duration
			if (eclipse->type.find("P") != std::string::npos) {
				eclipse->width = "";
				eclipse->central = "";
			}

			//Otherwise, there is a width and central duration
			else {

				//Parses the width
				parse(line, startingIndex, endingIndex);
				eclipse->width = line.substr(startingIndex,
						endingIndex - startingIndex);

				//Parses the central duration
				parse(line, startingIndex, endingIndex);
				eclipse->central = line.substr(startingIndex,
						line.length() - 1);
			}

//			bool invalidEclipse = false;
//
//			for (int i = 0; i < 15; ++i) {
//				if (eclipse->columnValueToVariable(i) == "") {
//					cerr << "Invalid number of columns";
//					invalidEclipse = true;
//					break;
//				}
//			}
//

			bool addedToTree = false;

			//If a duplicate catalogNumber is found, swap the eclipses
			if (swapEclipse) {

				//Error handling is encapsulated in the AVLtree
				addedToTree = tree.insert(*eclipse);

				//Increment the number of invalid eclipses
				++invalidEclipses;

				//To check whether the swap has been completed
				bool arraySwap = false;
				bool linkedListSwap = false;

				//Does a linear search for the eclipse with the duplicate catalogNumber
				//Check if its right to do "-2"
				for (int i = 0; i < dataArray.length - 2; ++i) {

					//If a duplicate catalogNumber is found, replace in the array
					if (dataArray.at(i).catalogNumber
							== eclipse->catalogNumber) {
						arraySwap = true;
						dataArray.replaceAt(*eclipse, i);
					}

					//Replaces the value in the linkedList as well
					if (linkedList.infoAt(i).catalogNumber
							== eclipse->catalogNumber) {
						linkedListSwap = true;
						linkedList.replaceAt(*eclipse, i);
					}

					if (tree.find(*eclipse) != NULL) {

					}

					//If the eclipses have been swapped in the dataArray and linked list, break the loop
					if (arraySwap && linkedListSwap) {
						arraySwap = false;
						linkedListSwap = false;
						break;
					}
				}
			}

			//Otherwise, add the eclipse to the lists
			else {
				dataArray.add(*eclipse);
				linkedList.add(*eclipse);
				addedToTree = tree.insert(*eclipse);
			}
		}
	}

	//Closes the file after it has been completely parsed
	inFS.close();

	return;
}

//Obtains file input
void fileInput(ResizableArray<Eclipse> &dataArray) {

	//File stream and fileName
	ifstream inFS;
	string fileName = "";

	//Loops until the user enters a valid fileName
	while (true) {

		//Prompts user
		cout
				<< "Please enter name of file to read or press enter to continue: ";

		//Inputs fileName
		getline(cin, fileName);

		//If fileName is not given, end file input
		if (fileName == "") {
			break;
		}

		//Opens the file
		inFS.open(fileName);

		//If the file doesn't exist, then loop until proper file name found
		if (!inFS.is_open()) {
			cout << "File is not available." << endl;
			continue;
		}

		//Parse the file to extract data
		parseFile(inFS, dataArray);
	}
}

//Finds the selected data that the user is looking for
void find(ResizableArray<Eclipse> &dataArray,
		ResizableArray<Eclipse> &foundEclipses, const int sortedColumn) {

	//Obtains the data field
	int dataField;

	do {
		cout << "Data field to find (1-18)?" << endl;
		cin >> dataField;
	} while (dataField < 1 || dataField > 18);

	//Obtains the value to search
	string valueToSearch;
	cout << "Value to search?" << endl;
	getline(cin, valueToSearch);
	getline(cin, valueToSearch);

	//This if statement uses the most efficient algorithm: Binary or Linear search

	//If the search value is sorted, it will use binary search
	if (sortedColumn == dataField) {
		int search = binarySearch(dataArray, valueToSearch, dataField, 0,
				dataArray.length - 1);

		//Decrements from the middle until the last found element and adds to the found eclipses
		for (int i = search - 1; i >= 0; --i) {
			if (dataArray.at(i).columnValueToVariable(dataField).find(
					valueToSearch) != std::string::npos) {
				foundEclipses.add(dataArray.at(i));
			} else {
				break;
			}
		}

		//Adds the middle array
		foundEclipses.add(dataArray.at(search));

		//Increments from the middle until the last found element and adds to the found eclipses
		for (int i = search + 1; i < dataArray.length; ++i) {
			if (dataArray.at(i).columnValueToVariable(dataField).find(
					valueToSearch) != std::string::npos) {
				foundEclipses.add(dataArray.at(i));
			} else {
				break;
			}
		}
	}

	//If the search value is not sorted, it will use linear search
	else {

		//Iterates through the entire data array
		for (int i = 0; i < dataArray.length; ++i) {

			//If the value to search matches what is being searched for in the column, it adds the eclipse to the foundEclipses
			if (dataArray.at(i).columnValueToVariable(dataField).find(
					valueToSearch) != std::string::npos) {
				foundEclipses.add(dataArray.at(i));
			}
		}
	}

	for (int i = 0; i < foundEclipses.length; ++i) {
		cout << foundEclipses.at(i) << endl;
	}

	cout << "Eclipses found: " << (foundEclipses.length - 1) << endl;
}

//Outputs the found eclipses to an external file
void output(ResizableArray<Eclipse> &dataArray,
		ResizableArray<Eclipse> &foundEclipses) {

	//Obtains the name of the file to save to
	string saveFile;
	cout << "File name to output to?" << endl;
	//cin >> saveFile;
	getline(cin, saveFile);

	//Writes output file
	ofstream outputFile(saveFile, ofstream::out);

	//Header information
	for (int i = 0; i < 10; ++i) {
		outputFile << headerInfo[i] << endl;
	}

	//Eclipse information
	outputFile << dataArray << endl;

	//Outputs the data lines read, the valid eclipses read, and the eclipses in memory
	outputFile << "Data lines read: " << (dataArray.length) << "; "

	<< "Valid eclipses read: " << (dataArray.length - 3)
			<< "; " "Eclipses in memory: "
			<< (dataArray.length - invalidEclipses) << endl; //should subtract duplicates as well

	//Closes file
	outputFile.close();

	return;
//AS you read through the data file, if you find an eclipse with the same catalog number as one that's already in there
//It should go in place of the one that is already there
//How many data lines you actually read
//6 lines, but line 3 had the wrong number of columns so that would not be valid
//5 might have been valid eclipses
//because the 6th one replaced the 2nd one, you only now have 4 eclipses in memory
}

//Uses a quicksort algorithm to sort the data array
void sort(ResizableArray<Eclipse> &dataArray, int &sortedColumn) {

	//Obtains the data field to sort from. Loops until valid input.
	do {
		cout << "Data field to sort (1-18)?" << endl;
		cin >> sortedColumn;
	} while (sortedColumn < 1 || sortedColumn > 18);

	if (4 == sortedColumn) {
		QuicksortMonth(dataArray, 0, dataArray.length - 1);
	}

	else {
		//Quicksorts starting from the first element in the data array to the last, keeping track of the sorted column
		Quicksort(dataArray, 0, dataArray.length - 1, sortedColumn);

	}

	//Prevents newline overflow due to cin >> sortedColumn
	string emptyString;
	getline(cin, emptyString);

	return;
}

//Allows you to add additional files
void merge(ResizableArray<Eclipse> &dataArray) {
	fileInput(dataArray);
}

//Removes the elements in the purgeFile from the data
void purge(ResizableArray<Eclipse> &dataArray) {

	//File stream and fileName
	ifstream inFS;
	string fileName = "";

	//Loops until the user enters a valid fileName
	while (true) {

		//Prompts user
		cout
				<< "Please enter name of file to purge or press enter to continue: "
				<< endl;

		//Inputs fileName
		getline(cin, fileName);

		//If fileName is not given, end file input
		if (fileName == "") {

			break;
		}

		//Opens the file
		inFS.open(fileName);

		//If the file doesn't exist, then loop until proper file name found
		if (!inFS.is_open()) {
			cout << "File is not available." << endl;
			continue;
		}

		//Array to keep track of catalogNumbers, and a line string for parsing
		ResizableArray<string> catalogRemoval;
		string line;

		//Initializing indices
		int startingIndex = 0;
		int endingIndex = 0;

		//This is to read in the first 10 lines of the file and skip it
		for (int i = 0; i < 10; ++i) {
			getline(inFS, line);
			headerInfo[i] = line;
			//inFS >> headerInfo[i];
		}

		//While the file has not reached its end
		while (getline(inFS, line)) {
			if (inFS.good()) {
				//Parses the catalogNumber and adds it to the array of catalogRemvals
				startingIndex = line.find_first_not_of(" ", 0);
				endingIndex = line.find_first_of(" ", startingIndex);
				catalogRemoval.add(
						line.substr(startingIndex,
								endingIndex - startingIndex));

			}
		}

		//Closes the file after using
		inFS.close();

		//Booleans to check for removals
		bool arrayRemoved = false;
		bool treeRemoved = false;
		bool linkedListRemoved = false;

		//Iterates through all of the catalogNumbers
		for (int i = 0; i < catalogRemoval.length - 1; ++i) {

			//Iterates through each eclipse's catalog number
			for (int j = 0; j < dataArray.length; ++j) {

				//Checks to remove from catalogNumbers
				if (catalogRemoval.at(i) == catalogNumbers.at(j)) {
					catalogNumbers.removeAt(j);
				}

				//Checks whether the given catalogRemoval numbers match the eclipse's catalog number
				if (catalogRemoval.at(i) == dataArray.at(j).catalogNumber) {

					//Sets removal to true
					arrayRemoved = true;

					//Removes the eclipse associated with the catalogNumber from the dataArray
					dataArray.removeAt(j);
				}

				//Checks to remove the Eclipse from the tree. If it hasn't been removed from the
				//tree but it has been removed from the array, it removes that Eclipse.
				if (!treeRemoved && arrayRemoved) {

					//Creates an eclipse with the same catalogNumber as the eclipse to be removed
					Eclipse removal;
					removal.catalogNumber = catalogRemoval.at(i);

					//Finds and removes the Eclipse with the same catalogNumber
					//as the one in the tree
					//Sets removal to true after removing from the tree
					treeRemoved = tree.remove(removal);

				}

				//Checks to remove from the linked list
				if (catalogRemoval.at(i)
						== linkedList.infoAt(j).catalogNumber) {
					//Sets removal to true
					linkedListRemoved = true;

					//Removes from the linked list
					linkedList.removeAt(j);
				}



				//Restarts the catalogNumber iteration
				if (arrayRemoved && linkedListRemoved && treeRemoved) {
					arrayRemoved = false;
					linkedListRemoved = false;
					treeRemoved = false;
					break;
				}
			}
		}
	}
}

//Catalog order function/linked display function. Prints linked list in catalog order.
void catalog() {

	//Creates a converted resizableArray from the linkedList
	ResizableArray<Eclipse> *convertedArray = linkedList.linkedListToArray();

	//void Quicksort(ResizableArray<Eclipse> &dataArray, int i, int k,
	//		const int column)

	//Removing any empty eclipses to prevent errors
	for (int i = 0; i < convertedArray->length; ++i) {
		if (convertedArray->at(i).catalogNumber == "") {
			convertedArray->removeAt(i);
		}
	}

	//Sorting by catalog number (used column 1, but note there is an error with sorting conducted by first digit)
	Quicksort(*convertedArray, 0, (convertedArray->length - 1), 1);

	//Iterates through the converted array to print the eclipses
	for (int i = 0; i < convertedArray->length; ++i) {
		cout << convertedArray->at(i) << endl;
	}
}

//Hashes the data and allows to display the hashed data
void hashDisplay(ResizableArray<Eclipse> &dataArray) {

	//Initialized the table to be the length of the dataArray
	HashTable *hashTable = initializeTable(dataArray.length);

	//Iterates through the data array to fill the hash table
	for (int i = 0; i < dataArray.length; ++i) {

		//If there is an empty eclipse, do not add it to the hash table
		if (dataArray.at(i).catalogNumber == "") {
			continue;
		}

		//Inserts the data array to the hash table
		Insert(dataArray.at(i), hashTable);
	}

	//Print function to print out the elements in the hash table
	Retrieve(hashTable);
}

//Converts the AVLtree to a resizableArray in preTraversal order and prints
void preTraversal() {
	ResizableArray<Eclipse> prePrint = tree.toResizableArray(
			AVLtree<std::Eclipse>::pre);

	//Prints out the resizableArray in the order of the preorder traversal tree
	for (int i = 0; i < prePrint.length; ++i) {
		cout << prePrint.at(i) << endl;
	}
}

//Converts the AVLtree to a resizableArray in postTraversal order and prints
void postTraversal() {
	ResizableArray<Eclipse> postPrint = tree.toResizableArray(
			AVLtree<std::Eclipse>::post);

	//Prints out the resizableArray in the order of the postorder traversal tree
	for (int i = 0; i < postPrint.length; ++i) {
		cout << postPrint.at(i) << endl;
	}
}

//Prompts the user for FOQS
void userPrompt(ResizableArray<Eclipse> &dataArray) {

	ResizableArray<Eclipse> *foundEclipses = new ResizableArray<Eclipse>;

	//Int checks which column is sorted
	int sortedColumn = 0;

	//Initializing user prompt character
	string userPrompt = "";

	//Continuous prompt until user hits Q
	while (true) {

		//Questions the user for F, O, Q, or S
		cout
				<< "Enter 'F' to find, 'O' to output, 'S' to sort, 'M' to merge, 'P' to purge, 'C' to catalog order, 'H' to hash display, 'L' to linked display, 'R' to pre-order traversal, 'T' to post-order traversal,  or 'Q' to quit "
				<< endl;
		getline(cin, userPrompt);

		//Error checking to prevent overflow
		if (userPrompt.length() > 1) {
			cout << "Invalid selection" << endl;
		}

		//F prompts a find
		else if (userPrompt.find("F") != std::string::npos
				|| userPrompt.find("f") != std::string::npos) {
			find(dataArray, *foundEclipses, sortedColumn);
		}

		//O prompts an output
		else if (userPrompt.find("O") != std::string::npos
				|| userPrompt.find("o") != std::string::npos) {
			output(dataArray, *foundEclipses);
		}

		//S prompts a sort
		else if (userPrompt.find("S") != std::string::npos
				|| userPrompt.find("s") != std::string::npos) {
			sort(dataArray, sortedColumn);
		}

		//M prompts a merge
		else if (userPrompt.find("M") != std::string::npos
				|| userPrompt.find("m") != std::string::npos) {
			merge(dataArray);
		}

		//P prompts a purge
		else if (userPrompt.find("P") != std::string::npos
				|| userPrompt.find("p") != std::string::npos) {
			purge(dataArray);
		}

		//C prompts a catalog order
		else if (userPrompt.find("C") != std::string::npos
				|| userPrompt.find("c") != std::string::npos) {
			catalog();
		}

		//H prompts a hash display
		else if (userPrompt.find("H") != std::string::npos
				|| userPrompt.find("h") != std::string::npos) {
			hashDisplay(dataArray);
		}

		//L prompts a linked display
		else if (userPrompt.find("L") != std::string::npos
				|| userPrompt.find("l") != std::string::npos) {
			catalog();
		}

		//R prompts a pre-order traversal
		else if (userPrompt.find("R") != std::string::npos
				|| userPrompt.find("r") != std::string::npos) {
			preTraversal();
		}

		//T prompts a post-order traversal
		else if (userPrompt.find("T") != std::string::npos
				|| userPrompt.find("t") != std::string::npos) {
			postTraversal();
		}

		//Quits with Q
		else if (userPrompt.find("Q") != std::string::npos
				|| userPrompt.find("q") != std::string::npos) {
			cout << "Thank you for using EclipseR!";
			break;
		}

		//Tells user that anything else is incorrect
		else {
			cout << "Invalid selection" << endl;
		}
	}
}

int main() {

	//Resizable array to store the data
	ResizableArray<Eclipse> *dataArray = new ResizableArray<Eclipse>;

	//Obtains file input
	fileInput(*dataArray);

	//Obtain user prompt
	userPrompt(*dataArray);

	return 0;
}
