
#include "datalogProgram.h"



void ParameterClass::findType() {
    if (name[0] != '\'') {
        type = VAR;
    }else {
        type = DOM;
    }
}


string PredicateClass::toString() {
    stringstream out;
    out << name << "(";
    for (int i = 0; i < params.size(); i++) {
        out << params[i]->toString();
        if (i < (params.size() - 1)) {
            out << ",";
        }
    }
    out << ")";
    return out.str();
}

bool RuleClass::addHeadPred(class PredicateClass* head) {
    if (head == NULL) {
        return false;
    }
    headPredicate = head;
    return true;
}


bool RuleClass::addPred(class PredicateClass* ps) {
    if (ps == NULL) {
        return false;
    }
    preds.push_back(ps);
    
    return true;
}


string RuleClass::toString() {
    stringstream out;
    //cout << "head: " << headPredicate->toString() << endl;
    out << headPredicate->toString() << " :- ";
    
    for (int i = 0; i < preds.size(); i++) {
        out << preds[i]->toString();
        if (i < (preds.size() - 1)) {
            out << ",";
        }
    }
    
    return out.str();
}

void datalogClass::addSchemes(vector<class PredicateClass*> &s) {
  schemes = s;
}

void datalogClass::addFacts(vector<class PredicateClass*> &f) {
  facts = f;
}

void datalogClass::addDomain(vector<string> &d) {
  if (d.empty()) {
    return;
  }
  sort(d.begin(), d.end());
  domain.push_back(d[0]);
//  cout << "Here?\n";
  for (int i = 1; i < d.size(); i++) {
    if (domain[domain.size() - 1] != d[i]) {
      domain.push_back(d[i]);
    }
  }
}

void datalogClass::addRules(vector<class RuleClass*> &r) {
  rules = r;
}

void datalogClass::addQueries(vector<class PredicateClass*> &q) {
  queries = q;
}

string datalogClass::toString() {
  stringstream out;
    out << "Schemes(" << schemes.size() << "):\n" << schemeData();
    out << "Facts(" << facts.size() << "):\n" << factData();
    out << "Rules(" << rules.size() << "):\n" << ruleData();
    out << "Queries(" << queries.size() << "):\n" << queryData();
    out << "Domain(" << domain.size() << "):\n" << domainData();
    
    return out.str();
}
  
string datalogClass::schemeData() {
  stringstream out;
  for (int i = 0; i < schemes.size(); i++) {
    out  << "  " << schemes[i]->toString() << "\n";
  }

  return out.str();
}

string datalogClass::factData() {
  stringstream out;
  for (int i = 0; i < facts.size(); i++) {
    out  << "  " << facts[i]->toString() << ".\n";
  }

  return out.str();
}

string datalogClass::ruleData() {
  stringstream out;
  //cout << "Finding rules; rulesSize: " << rules.size() << "\n";
  for (int i = 0; i < rules.size(); i++) {
    //cout << "Still working\n";
    out << "  " << rules[i]->toString() << ".\n";
  }

  return out.str();
}

string datalogClass::queryData() {
  stringstream out;
  for (int i = 0; i < queries.size(); i++) {
    out << "  " << queries[i]->toString() << "?\n";
  }

  return out.str();
}

string datalogClass::queryToString(int i) {
    stringstream out;
    out << queries[i]->toString() << "?";
    return out.str();
}

string datalogClass::domainData() {
  stringstream out;
  
  for (int i = 0; i < domain.size(); i++) {
    out << "  " << domain[i] << "\n";
  }
  
  return out.str();
}



vector<string> datalogClass::schemeNames() {
    vector<string> names;
    for (int i = 0; i < schemes.size(); i++) {
        names.push_back(schemes[i]->nameOut());
    }
    
    return names;
}

  
