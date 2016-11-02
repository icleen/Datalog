#include "database.h"


void Database::makeRelations() {
    
    vector<class PredicateClass*> schemes = datalog->schemesOut();
    for (int i = 0; i < schemes.size(); i++) {
        relation* rel = new relation(schemes[i]->nameOut());
        vector<class ParameterClass*> params = schemes[i]->paramsOut();
        for (int j = 0; j < params.size(); j++) {
            rel->addAttribute(params[j]->toString());
        }
        relations.push_back(rel);
    }
    makeTuples();
}

void Database::makeTuples() {
    
    vector<class PredicateClass*> facts = datalog->factsOut();
    for (int i = 0; i < facts.size(); i++) {
        int index = relationIndex(facts[i]->nameOut());
        if (index == -1) {
            cout << "Fact matches no known relations\n";
            return;
        }
        relations[index]->addTuple(makeTuple(facts[i]->paramsOut()));
    }
    
}

vector<string> Database::makeTuple(vector<class ParameterClass*> params) {
    
    vector<string> tple;
    for (int k = 0; k < params.size(); k++) {
        tple.push_back(params[k]->toString());
    }
    return tple;
    
}

// finds the index of a given relation based off of name
int Database::relationIndex(string name) {
    for (int i = 0; i < relations.size(); i++) {
        if (relations[i]->nameOut() == name) {
            return i;
        }
    }
    return -1;
}

// makes a copy of a given relation
relation* Database::copyRelation(relation* a) {
    
    relation* b = new relation(a->nameOut());
    vector< vector<string> > tempTuple = a->tuplesOut();
    vector<string> attrs = a->attributesOut();
    for (int i = 0; i < tempTuple.size(); i++) {
        b->addTuple(tempTuple[i]);
    }
    for (int j = 0; j < attrs.size(); j++) {
        b->addAttribute(attrs[j]);
    }
    
    return b;
}

// returns the index of any already existing vars in the project list
int Database::repeatVar(string var) {

    for (int i = 0; i < projectList.size(); i++) {
        if (projectList[i]->name == var) {
            return i;
        }
    }
    return -1;
}

//
// Interpreting the data
//

string Database::interpretStart() {
	stringstream out;

    vector<class PredicateClass*> queries = datalog->queriesOut();
    vector<relation*> tempRelations;
    relation* tempRel;
    for (int i = 0; i < queries.size(); i++) {
    	out << queries[i]->toString() << "?";
//    	cout << "(" << i + 1 << ") Working...\n";
    	projectList.clear();
    	int index = relationIndex( queries[i]->nameOut() );
    	if ( index < 0 ) {
    		out << " No";
    	}else {
        	tempRel = queryFind( relations[index], queries[i] );
    //    	cout << "QueryFind?\n";
        	if ( tempRel->size() == 0 ) {
        		out << " No";
        	}else {
        		out << " Yes("<< tempRel->size() << ")";
        		out << renames(tempRel);
    //    		cout << "rename?\n";
        	}
    	}
    	out << "\n";
    }

    return out.str();
}

// returns a string with the relation info in it
string Database::renames(relation* rel) {
	if ( projectList.size() == 0) {
		return "";
	}
	stringstream out;
	out <<"\n";
	for (int i = 0; i < rel->size(); i++) {
		out << "  ";
		for ( int j = 0; j < projectList.size(); j++ ) {
			out << projectList[j]->name << "=" << rel->tuple_at( i, j);
			if ( j < projectList.size() - 1 ) {
				out << ", ";
			}
		}
		if ( i < rel->size() - 1 ) {
			out << "\n";
		}
	}

	return out.str();
}


// return a new relation based on the given relation and the data in the given query
relation* Database::queryFind(relation *relat, PredicateClass *query) {
    relation* tempRel = copyRelation(relat);
//    cout << "Here?\n";
    vector<ParameterClass*> params = query->paramsOut();
    for (int i = 0; i < params.size(); i++) {
//    	cout << "(" << i + 1 << ") Working...\n";
        if (params[i]->typeOut() == "DOM") {
        	// select on the value
        	tempRel = selector( tempRel, i, params[i]->toString() );
        }else {
        	// decide whether the VAR is already in the project list
            int  repeatIndex = repeatVar( params[i]->toString() );
            if (repeatIndex != -1) {
            	//deal with a repeated variable
                tempRel = selector( tempRel, i, projectList[repeatIndex]->index );
            }else {
            	// add to the project list for later projection and renaming
            	myNode* data = new myNode();
            	data->name = params[i]->toString();
            	data->index = i;
            	projectList.push_back(data);
            }
        }
    }
    tempRel = projector(tempRel);
    
    return tempRel;
}

// returns the new relation based off of the select function
relation* Database::selector(relation* r, int a, int b) {
	 relation* tempRel = new relation( r->nameOut() );
	tempRel->addTuples( r->select( a, b ) );
	return tempRel;
}

// returns the new relation based off of the select function
relation* Database::selector(relation* r, int a, string b) {
	relation* tempRel = new relation( r->nameOut() );
	tempRel->addTuples( r->select( a, b ) );
	return tempRel;
}

// returns the new relation based on the projections listed in the projectList
relation* Database::projector(relation* rel) {
	rel->sortTuples();
	if ( projectList.empty() ) {
		return rel;
	}
	relation* tempRel = new relation( rel->nameOut() );
	vector<int> indexi;
	for (int i = 0; i < projectList.size(); i++) {
		indexi.push_back( projectList[i]->index );
	}
	tempRel->addTuples( rel->project( indexi ) );
	return tempRel;
}








