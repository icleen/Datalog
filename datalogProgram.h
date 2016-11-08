//
//  datalogProgram.hpp
//  parser
//
//  Created by Iain Lee on 10/4/16.
//  Copyright © 2016 Iain. All rights reserved.
//

//#include "parseClass.h"
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>


using namespace std;

#ifndef datalogProgram_h
#define datalogProgram_h


enum paramType { DOM, VAR };

class ParameterClass {
private:
//	token theToken;
	string name;
    paramType type;
        
    void findType();
        
public:
	ParameterClass() { };
	ParameterClass(string input) : name (input) {
            findType();
        };
	void defineParam(string input) { name = input; };
	string toString() { return name; };
    string typeOut() {
        if (type == DOM) {
            return "DOM";
        }else {
            return "VAR";
        }
    };

};


class PredicateClass {
private:
	string name;
	vector<ParameterClass*> params;

public:
	PredicateClass(string nme) : name(nme) { };
	void changeName(string newName) { name = newName; };
	void add(ParameterClass* p) { params.push_back(p); };
    
    string nameOut() {
        return name;
    };
    vector<ParameterClass*> paramsOut() {
        return params;
    };
	string toString();

};



class RuleClass {
private:
//	string name;
	class PredicateClass* headPredicate;
	vector<class PredicateClass*> preds;

public:
	RuleClass(class PredicateClass* head = NULL) : headPredicate(head) { };
//	bool changeName(string nme) { name = nme; };
	bool addHeadPred(class PredicateClass* head);
	bool addPred(class PredicateClass* ps);
	string toString();

};



class datalogClass {
private:

	vector<class PredicateClass*> schemes;
	vector<class PredicateClass*> facts;
	vector<string> domain;
	vector<class RuleClass*> rules;
	vector<class PredicateClass*> queries;
    
    string schemeData();
    string factData();
    string ruleData();
    string queryData();
    string domainData();
	
public:

	void addSchemes(vector<class PredicateClass*> &s);
	void addFacts(vector<class PredicateClass*> &f);
	void addDomain(vector<string> &d);
	void addRules(vector<class RuleClass*> &r);
	void addQueries(vector<class PredicateClass*> &q);
	
    vector<class PredicateClass*> factsOut() {
        return facts;
    };
    vector<class PredicateClass*> schemesOut() {
        return schemes;
    };
    vector<class RuleClass*> rulesOut() {
            return rules;
        };
    vector<class PredicateClass*> queriesOut() {
        return queries;
    };
    
    vector<string> schemeNames();
    
    string queryToString(int index);
	string toString();

};



#endif /* datalogProgram_h */
