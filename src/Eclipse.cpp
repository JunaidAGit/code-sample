/*
 * Eclipse.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Junaid
 */

#include "Eclipse.h"

namespace std {

Eclipse::Eclipse() {
}

Eclipse::~Eclipse() {
	// Auto-generated destructor stub
}

//Decodes the eclipse value from the catalog number
string Eclipse::columnValueToVariable(const int columnValue) {

	switch (columnValue) {

	case 1:
		return catalogNumber;
	case 2:
		return plate;
	case 3:
		return year;
	case 4:
		return month;
	case 5:
		return day;
	case 6:
		return greatestEclipse;
	case 7:
		return DTs;
	case 8:
		return lunar;
	case 9:
		return saros;
	case 10:
		return type;
	case 11:
		return gamma;
	case 12:
		return mag;
	case 13:
		return latitude;
	case 14:
		return longitude;
	case 15:
		return alt;
	case 16:
		return azm;
	case 17:
		return width;
	case 18:
		return central;
	default:
		throw range_error("Error: sorted column out of bounds");
	}
}

//Creating an eclipse from another sets it data equal to the other
Eclipse::Eclipse(const Eclipse& e) {
	catalogNumber = e.catalogNumber;
	plate = e.plate;

	year = e.year;
	month = e.month;
	day = e.day;

	greatestEclipse = e.greatestEclipse;

	DTs = e.DTs;

	lunar = e.lunar;
	saros = e.lunar;

	type = e.type;

	gamma = e.gamma;

	mag = e.mag;

	latitude = e.latitude;

	longitude = e.longitude;

	alt = e.alt;

	azm = e.azm;

	width = e.width;

	central = e.central;
}

//Equals operator
Eclipse& Eclipse::operator=(const Eclipse& e) {

	catalogNumber = e.catalogNumber;
	plate = e.plate;

	year = e.year;
	month = e.month;
	day = e.day;

	greatestEclipse = e.greatestEclipse;

	DTs = e.DTs;

	lunar = e.lunar;
	saros = e.lunar;

	type = e.type;

	gamma = e.gamma;

	mag = e.mag;

	latitude = e.latitude;

	longitude = e.longitude;

	alt = e.alt;

	azm = e.azm;

	width = e.width;

	central = e.central;

	return *this;
}

//Sends out the data
ostream& operator<<(ostream& os, const Eclipse& e) {
	os << setw(5) << e.catalogNumber << "  " << e.plate << "  " << setw(5)
			<< e.year << " " << e.month << " " << e.day << "  "
			<< e.greatestEclipse << "  " << setw(5) << e.DTs << " " << setw(6)
			<< e.lunar << "  " << setw(6) << e.saros << "   " << setw(2)
			<< e.type << "  " << setw(7) << e.gamma << "  " << e.mag << "  "
			<< setw(5) << e.latitude << " " << setw(6) << e.longitude << "  "
			<< setw(2) << e.alt << "  " << setw(3) << e.azm << "  " << setw(3)
			<< e.width << "  " << e.central;
	return os;
}

//Preliminary equality comparison method. Checking for catalogNumbers because everything else ought to be correct.
bool Eclipse::operator==(const Eclipse e) {

	//The integers to compare
	int first_comparate = stoi(e.catalogNumber);
	int second_comparate = stoi(this->catalogNumber);

	//The comparison of the integers
	if (first_comparate == second_comparate) {
		return true;
	}

	//Return false if they are not equal
	else {
		return false;
	}
}

bool Eclipse::operator<(const Eclipse e) {

	//The integers to compare
	int first_comparate = stoi(e.catalogNumber);
	int second_comparate = stoi(this->catalogNumber);

	//The comparison of the integers
	if (first_comparate < second_comparate) {
		return true;
	}

	//Return false if they are not equal
	else {
		return false;
	}
}

bool Eclipse::operator>(const Eclipse e) {

	//The integers to compare
	int first_comparate = stoi(e.catalogNumber);
	int second_comparate = stoi(this->catalogNumber);

	//The comparison of the integers
	if (first_comparate > second_comparate) {
		return true;
	}

	//Return false if they are not equal
	else {
		return false;
	}
}

bool Eclipse::operator<=(const Eclipse e) {
	//The integers to compare
	int first_comparate = stoi(e.catalogNumber);
	int second_comparate = stoi(this->catalogNumber);

	//The comparison of the integers
	if (first_comparate <= second_comparate) {
		return true;
	}

	//Return false if they are not equal
	else {
		return false;
	}
}

bool Eclipse::operator>=(const Eclipse e) {

	//The integers to compare
	int first_comparate = stoi(e.catalogNumber);
	int second_comparate = stoi(this->catalogNumber);

	//The comparison of the integers
	if (first_comparate >= second_comparate) {
		return true;
	}

	//Return false if they are not equal
	else {
		return false;
	}
}

bool Eclipse::operator!=(const Eclipse e) {

	//If the catalogNumbers aren't equal, return true
	if (this->catalogNumber != e.catalogNumber) {
		return true;
	} else {
		return false;
	}
}

//bool Eclipse::operator<=(const Eclipse e) {
//	//The integers to compare
//	int *first_comparate = new int();
//	int *second_comparate = new int();
//
//	//Using a boolean to error check the conversion
//	bool stringToIntConversion;
//
//	//Converting the first string to int
//	stringToIntConversion = String2Int(e.catalogNumber, *first_comparate);
//
//	//Error checking
//	if (!stringToIntConversion) {
//		cerr << "String to int first conversion failed" << endl;
//	}
//
//	//Converting the second string to int
//	stringToIntConversion = String2Int(this->catalogNumber, *second_comparate);
//
//	//Error checking
//	if (!stringToIntConversion) {
//		cerr << "String to int second conversion failed" << endl;
//	}
//
//	//The comparison of the integers
//	if (*first_comparate <= *second_comparate) {
//		return true;
//	}
//
//	//Return false if they are not equal
//	else {
//		return false;
//	}
//}

} /* namespace std */
