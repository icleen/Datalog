//
//  relationClass.cpp
//  database
//
//  Created by Iain Lee on 10/24/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#include "relationClass.h"

string relation::attribute_at(int index) {
	return attributes[index];
}

string relation::tuple_at(int index1, int index2) {

	if ( index1 >= tuples.size() || index2 >= tuples[index1].size() ) {
		cout << "Bound error; that tuple does not exist ( relation::tuple_at() )\n";
		cout << index1 << " " << index2 << " " << tuples.size() << " " << tuples[index1].size() << endl;
		return "";
	}
	return tuples[index1][index2];
}

vector<string> relation::tuples_at(int index) {
	return tuples[index];
}

void relation::addAttribute(string attr) {
    attributes.push_back(attr);
}

void relation::addTuple(vector<string> tple) {
	if ( setFunction(tuples, tple) ) {
		tuples.push_back(tple);
	}
}

void relation::addTuples(vector< vector<string> > tples) {

	for (int i = 0; i < tples.size(); i++) {
		tuples.push_back(tples[i]);
	}

}

//
// Sorting Functions
//

void relation::sortTuples() {
//	cout << "Sort start\n";
	vector<string> tempTuples;
	for (int i = 0; i < tuples.size(); i++) {
		 string tup = stringTuple( tuples[i] );
		 tempTuples.push_back(tup);
		 int t = i;
		 int j = tempTuples.size() - 2;
		 while ( j >= 0 && tup < tempTuples[j] ) { // while true, swap up
			 // swaps the temporary variables
			 string temp = tempTuples[j];
			 tempTuples[j] = tempTuples[t];
			 tempTuples[t] = temp;
			 // swaps the actual tuples
			 vector<string> vtemp = tuples[j];
			 tuples[j] = tuples[t];
			 tuples[t] = vtemp;
			 t = j;
			 j--;
		 }
	}
}

//// swaps the temporary variables
//string temp = tempTuples[j];
//tempTuples[j] = tempTuples[t];
//tempTuples[t] = temp;
//
//// swaps the actual tuples
//vector<string> vtemp = tuples[j];
//tuples[j] = tuples[t];
//tuples[t] = temp;



string relation::stringTuple( vector<string> t) {
	stringstream ss;
	for (int i = 0; i < t.size(); i++) {
		ss << t[i];
	}
	return ss.str();
}
//
// Functions
//

vector< vector<string> > relation::select(int attr, string value) {
    
    vector< vector<string> > new_tuples;
    for (int i = 0; i < tuples.size(); i++) {
        if (tuples[i][attr] == value) {
            new_tuples.push_back(tuples[i]);
        }
    }
    
    return new_tuples;
}

vector< vector<string> > relation::select(int attr, int atr2) {
    
    vector< vector<string> > new_tuples;
    for (int i = 0; i < tuples.size(); i++) {
        if (tuples[i][attr] == tuples[i][atr2]) {
            new_tuples.push_back(tuples[i]);
        }
    }
    
    return new_tuples;
}

int relation::projectIndex(string attr) {
    for (int i = 0; i < attributes.size(); i++) {
        if (attr == attributes[i]) {
            return i;
        }
    }
    return -1;
}

vector< vector<string> > relation::project(vector<int> indexi) {
    vector< vector<string> > temp;

    for (int i = 0; i < tuples.size(); i++) {
    	vector<string> tple;
    	for (int j = 0; j < indexi.size(); j++) {
    		int num = indexi[j];
    		tple.push_back( tuples[i][num] );
    	}
    	if ( setFunction( temp, tple ) ) {
    		temp.push_back( tple );
    	}
    }
    
    return temp;
}

bool relation::setFunction( vector< vector<string> > a, vector<string> b) {

	for (int i = 0; i < a.size(); i++) {
		if ( a[i] == b ) {
			return false;
		}
	}

	return true;
}

void relation::rename( int attrIndex, string attrName) {
    attributes[attrIndex] = attrName;
}
