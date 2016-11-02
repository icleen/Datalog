//
//  relationClass.hpp
//  database
//
//  Created by Iain Lee on 10/24/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#ifndef relationClass_h
#define relationClass_h

#include <stdio.h>
#include <vector>
#include <string>
#include <set>

#include "datalogProgram.h"

using namespace std;


class relation {
private:
    string name;
    vector<string> attributes;
    vector< vector<string> > tuples;
    
    int projectIndex(string attr);
    
    bool setFunction( vector< vector<string> > a, vector<string> b);
    string stringTuple( vector<string> t);

public:
    relation(string nme) : name(nme) {  };
    
    string nameOut() {
        return name;
    };
    int size() {
    	return tuples.size();
    };
    
    string attribute_at(int index);
    string tuple_at(int index1, int index2);
    vector<string> tuples_at(int index);

    void addAttribute(string attr);
    void addTuple(vector<string> tple);
    void addTuples(vector< vector<string> > tples);
    
    vector< vector<string> > tuplesOut() {
        return tuples;
    }
    
    vector< vector<string> > select(int attr, string value);
    vector< vector<string> > select(int attr, int attr2);
    vector< vector<string> > project(vector<int> indexi);
    void rename( int attrIndex, string attrName);
    void sortTuples();
};



#endif /* relationClass_h */
