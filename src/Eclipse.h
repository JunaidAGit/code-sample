/*
 * Eclipse.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Junaid
 */

#ifndef SRC_ECLIPSE_H_
#define SRC_ECLIPSE_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

namespace std {

class Eclipse {
public:

	//Basics
	Eclipse();
	Eclipse(const Eclipse& e);
	virtual ~Eclipse();

	//Output overload
	friend ostream& operator<<(ostream& s, const Eclipse& e);

	//Assignment operator
	Eclipse& operator=(const Eclipse& e);

	//Month to value conversion
	int monthToValue(const Eclipse e);

	//Comparison operators
	bool operator==(const Eclipse e);
	bool operator<(const Eclipse e);
	bool operator>(const Eclipse e);
	bool operator<=(const Eclipse e);
	bool operator>=(const Eclipse e);
	bool operator!=(const Eclipse e);

	//Helper function
	string columnValueToVariable(const int columnValue);

	//Variables
	string catalogNumber;
	string plate;

	string year;
	string month;
	string day;

	string greatestEclipse;

	string DTs;

	string lunar;
	string saros;

	string type;

	string gamma;

	string mag;

	string latitude;

	string longitude;

	string alt;

	string azm;

	string width;

	string central;

};

}/* namespace std */

#endif /* SRC_ECLIPSE_H_ */
