//
//  database.h
//  parser
//
//  Created by Iain Lee on 10/23/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "datalogProgram.h"
#include "relationClass.h"


using namespace std;

#ifndef database_h
#define database_h

struct myNode {
    string name;
    int index;
};

class Database {

private:
	class datalogClass* datalog;
    vector<class relation*> relations;
    string renameOutput;
    
    void makeRelations();
    void makeTuples();
    vector<string> makeTuple(vector<class ParameterClass*> params);
    
    // interpretation functions:
    
    relation* queryFind(relation* relat, PredicateClass* query);
    relation* selector(relation* r, int a, int b);
    relation* selector(relation* r, int a, string b);
    relation* projector(relation* r);
    void renamer(relation* rel);
    vector<myNode*> projectList;
    
    int relationIndex(string name);
    relation* copyRelation(relation* a);
    int repeatVar(string var);
    
    // Lab 4 functions:
    void convertRules( vector<RuleClass*> rules );
    relation* ruler( RuleClass* rule );
    relation* ruler2( RuleClass* rule );

    relation* naturalJoin( relation* a, relation* b );

public:
    Database(datalogClass* data) : datalog(data) {
        makeRelations();
    };
    
    string interpretStart();




};


#endif /* database_h */
