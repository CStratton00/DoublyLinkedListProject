//
// Collin Stratton
// 10/3/2020
// This is my work
//

#include "DLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string cleanUp(string str);

int main() {

	DLinkedList<string> lst1;
	DLinkedList<string> lst2;

	ifstream fin("Text1.in");

	string str;

	while (fin>>str) {		
		str = cleanUp(str);
		lst1.insertOrderUnique(str);
	}
	fin.close();

	fin.open("Text2.in");
	while (fin>>str) {
		str = cleanUp(str);
		lst2.insertOrderUnique(str);
	}

	cout << "List 1: " << lst1 << endl;
	cout << "List 2: " << lst2 << endl;
	

	DLinkedList<string> combined = lst1.merge(lst2);

	cout << "\nAFTER MERGE" << endl;
	cout << "List 1: " << lst1 << endl;
	cout << "List 2: " << lst2 << endl;
	cout << "\nCombined: " << combined << endl;


	return 0;
}

/**
* ASSIGNED
* @param str
* @return str in all lower case with LEADING and TRAILING non-alpha
* chars removed
*/
string cleanUp(string str) {
    for (int i = 0; i < str.length(); i++) {                    // loops through the full string
        int characters = (unsigned char) str[i];                // sets characters to the value at str[i]

        if (characters > 64 && characters < 91) { str[i] = char(characters + 32); } // makes sure characters is lowercase
        else if (!(characters == 39 || (characters > 96 && characters < 123))) {    // removes all non alphabetical characters in a range
            str.erase(i, i + 1);
            i--;
        }
    }

    return str;
}