#include "parseClass.h"


string parse::schemeData() {
  stringstream out;
  for (int i = 0; i < schemes.size(); i++) {
    out << schemes[i]->toString() << "\n";
  }

  return out.str();
}

string parse::factData() {
  stringstream out;
  for (int i = 0; i < facts.size(); i++) {
    out << facts[i]->toString() << "\n";
  }

  return out.str();
}

string parse::ruleData() {
  stringstream out;
  //cout << "Finding rules; rulesSize: " << rules.size() << "\n";
  for (int i = 0; i < rules.size(); i++) {
    //cout << "Still working\n";
    out << rules[i]->toString() << "\n";
  }

  return out.str();
}

string parse::queryData() {
  stringstream out;
  for (int i = 0; i < queries.size(); i++) {
    out << queries[i]->toString() << "\n";
  }

  return out.str();
}


string parse::toString(token t) {
//    token t = tokens.front();
    switch (t) {
	case COMMA: return "COMMA";
        case PERIOD: return "PERIOD";
	case Q_MARK: return "Q_MARK";
	case LEFT_PAREN: return "LEFT_PAREN";
	case RIGHT_PAREN: return "RIGHT_PAREN";
	case COLON: return "COLON";
	case COLON_DASH: return "COLON_DASH";
	case MULTIPLY: return "MULTIPLY";
	case ADD: return "ADD";
	case SCHEMES: return "SCHEMES";
	case FACTS: return "FACTS";
	case RULES: return "RULES";
	case QUERIES: return "QUERIES";
	case ID: return "ID";
	case STRING: return "STRING";
	case UNDEFINED: return "UNDEFINED";
	case WHITESPACE: return "WHITESPACE";
	case COMMENT: return "COMMENT";
	case MEOF: return "MEOF";
	default: break;
	}
//    //cout << t << endl;
	return "Trouble";
}


token parse::toToken(string s) {
    if (s == "COMMA") {
        return COMMA;
    }else if (s == "COLON_DASH") {
        return COLON_DASH;
    }else if (s == "RIGHT_PAREN") {
        return RIGHT_PAREN;
    }else if (s == "Q_MARK") {
        return Q_MARK;
    }else if (s == "STRING") {
        return STRING;
    }switch (s[0]) {
        case 'P': return PERIOD;
        case 'L': return LEFT_PAREN;
        case 'C': return COLON;
        case 'M': return MULTIPLY;
        case 'A': return ADD;
        case 'S': return SCHEMES;
        case 'F': return FACTS;
        case 'R': return RULES;
        case 'Q': return QUERIES;
        case 'I': return ID;
        default: break;
    }
    return MEOF;
}

string parse::offenderOut() {
    return toString(offender);
}

int parse::datalogParser(queue<token> &tokens, queue<string> &ts){
	tokenIndex = 0;
	tokenStrings = ts;
    token t = tokens.front();
    if (t == SCHEMES) {
        return (checkSCHEMES(tokens) && checkCOLON(tokens) && scheme(tokens) && schemelist(tokens) && a(tokens));
    }
    offender = t;
    return tokenIndex;
}

bool parse::a(queue<token> &tokens) {
	token t = tokens.front();
	if (t == FACTS) {
		return (checkFACTS(tokens) && checkCOLON(tokens) && factlist(tokens) && b(tokens));
	}
	offender = t;
	return false;
}

bool parse::b(queue<token> &tokens) {
	token t = tokens.front();
	if (t == RULES) {
		return (checkRULES(tokens) && checkCOLON(tokens) && rulelist(tokens) && c(tokens));
	}
    offender = t;
    return false;
}

bool parse::c(queue<token> &tokens) {
	token t = tokens.front();
	if (t == QUERIES) {
		return (checkQUERIES(tokens) && checkCOLON(tokens) && query(tokens) && querylist(tokens));
	}
    offender = t;
    return false;
}

bool parse::schemelist(queue<token> &tokens) {
    token t = tokens.front();
    if (t == FACTS || t == MEOF) {
        return true;
    }else if (t == ID) {
        return (scheme(tokens) && schemelist(tokens));
    }
    offender = t;
    return false;
}

void parse::addToPred(class PredicateClass* &p, int size, bool fact) {
	  //cout << "starting addToPred: ";
  for (int i = 0; i < size; i++) {
		string s = tokenStrings.front();
		tokenStrings.pop();
                class ParameterClass* param = new class ParameterClass(s);
		p->add(param);
                if (fact == true) {
			domain.push_back(s);
		}
		//cout << s << ", ";
	}
	//cout << endl;
}


bool parse::parse::scheme(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ID) {
    	int head = 0;
    	int size = 0;
        bool check = (checkID(tokens, head) && checkLEFT_P(tokens) && checkID(tokens, size)
                && idlist(tokens, size) && checkRIGHT_P(tokens));
        class PredicateClass* p = new class PredicateClass(tokenStrings.front());
        tokenStrings.pop();
	//cout << "schemeSize: " << size << endl;
        addToPred(p, size, false);
        schemes.push_back(p);
        return check;
    }
    offender = t;
    return false;
}

bool parse::idlist(queue<token> &tokens, int &num) {
    token t = tokens.front();
    if (t == RIGHT_PAREN) {
        return true;
    }else if (t == COMMA) {
        return (checkCOMMA(tokens) && checkID(tokens, num) && idlist(tokens, num));
    }
    offender = t;
    return false;
}

bool parse::factlist(queue<token> &tokens) {
    token t = tokens.front();
    if (t == RULES || t == MEOF) {
        return true;
    }else if (t == ID) {
        return (fact(tokens) && factlist(tokens));
    }
    offender = t;
    return false;
}

bool parse::fact(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ID) {
    	int head = 0;
    	int size = 0;
        bool check = (checkID(tokens, head) && checkLEFT_P(tokens) && checkSTRING(tokens, size)
                && stringlist(tokens, size) && checkRIGHT_P(tokens) && checkPERIOD(tokens));
        class PredicateClass* p = new class PredicateClass(tokenStrings.front());
        tokenStrings.pop();
	//cout << "factSize: " << size << endl;
        addToPred(p, size, true);
        facts.push_back(p);
        return check;
    }
    offender = t;
    return false;
}

bool parse::stringlist(queue<token> &tokens, int &num) {
    token t = tokens.front();
    if (t == RIGHT_PAREN) {
    	return true;
    }else if (t == COMMA) {
        return (checkCOMMA(tokens) && checkSTRING(tokens, num) && stringlist(tokens, num));
    }
    offender = t;
    return false;
}

bool parse::rulelist(queue<token> &tokens) {
    token t = tokens.front();
    if (t == QUERIES || t == MEOF) {offender = t;
        return true;
    }else if (t == ID) {
        return (rule(tokens) && rulelist(tokens));
    }
    offender = t;
    return false;
}

bool parse::rule(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ID) {
        class PredicateClass* p = headPredicate(tokens);
	bool check = checkCOLON_DASH(tokens);
	if (p == NULL || !check) {
	  return false;
	}
	//cout << "found head\n";
	class RuleClass* r = new class RuleClass(p);
	
	vector<class PredicateClass*> ps;
	p = predicate(tokens);
        ps = predicatelist(tokens);
	if (p == NULL ) {
	  return false;
	}if ( ps.size() == 1 && ps[0] == NULL ) {
	  return false;
	}
        
        r->addPred(p);
	for (int i = 0; i < ps.size(); i++) {
	  r->addPred(ps[i]);
	}
	
	rules.push_back(r);
        check = checkPERIOD(tokens);   
        return check;
    }
    offender = t;
    return false;
}

bool parse::querylist(queue<token> &tokens) {
    token t = tokens.front();
    if (t == MEOF) {
        return true;
    }else if (t == ID) {
        return (query(tokens) && querylist(tokens));
    }
    offender = t;
    return false;
}

bool parse::query(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ID) {
      
	class PredicateClass* p = predicate(tokens);
        bool check = checkQ_MARK(tokens);
	if (!check || p == NULL) {
	  return false;
	}
	queries.push_back(p);
	return true;
	
    }
    offender = t;
    return false;
}

void parse::addToPred(class PredicateClass* &p, vector<class ParameterClass*> &ps) {
	  //cout << "starting addToPred: ";
	for (int i = 0; i < ps.size(); i++) {
		p->add(ps[i]);
		//cout << s << ", ";
	}
	//cout << endl;
}

class PredicateClass* parse::headPredicate(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ID) {
      
      int num = 0;
      int size = 0;
      bool check = (checkID(tokens, num) && checkLEFT_P(tokens) && checkID(tokens, size)
                && idlist(tokens, size) && checkRIGHT_P(tokens));
      if (!check) {
	return NULL;
      }
      class PredicateClass* p = new class PredicateClass(tokenStrings.front());
      tokenStrings.pop();
      addToPred(p, size, false);
      //cout << "worked\n";
      return p;
      
    }
    offender = t;
    return NULL;
}

class PredicateClass* parse::predicate(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ID) {
            
      int num = 0;
      int size = 0;
      bool check = (checkID(tokens, num) && checkLEFT_P(tokens));
      class PredicateClass* pred = new class PredicateClass(tokenStrings.front());
      tokenStrings.pop();
      
      class ParameterClass* param = parameter(tokens, size);
      vector<class ParameterClass*> params = parameterlist(tokens, size);
      
      check = (check && checkRIGHT_P(tokens));
      if (!check || param == NULL || (params.size() == 1 && params[0] == NULL)) {
	return NULL;
      }
      vector<class ParameterClass*> pr;
      pr.push_back(param);
      makeOneVector(pr, params);
      addToPred(pred, pr);
      //cout << "worked\n";
      return pred;
      
    }
    offender = t;
    return NULL;
}

void parse::makeOneVector(vector<class PredicateClass*> &a, vector<class PredicateClass*> &b) {
	  //cout << "failure in makeOneVector\n";
  for (int i = 0; i < b.size(); i++) {
		a.push_back(b[i]);
	}
}

vector <class PredicateClass*> parse::predicatelist(queue<token> &tokens) {
    token t = tokens.front();
    vector<class PredicateClass*> a;
    vector<class PredicateClass*> ps;
    a.push_back(NULL);
    if (t == PERIOD) {
      //cout << "ps.size: " << ps.size() << endl;
      return ps;
    }else if (t == COMMA) {
	//cout << "problem?\n";
        checkCOMMA(tokens);
	class PredicateClass* p = predicate(tokens);
	vector<class PredicateClass*> b = predicatelist(tokens);
	if ( p == NULL || (b.size() == 1 && b[0] == NULL) ) {
	  return a;
	}
	ps.push_back(p);
	makeOneVector(ps, b);
	//cout << "ps.size: " << ps.size() << endl;
	return ps;
    }
    offender = t;
    return a;
}

class ParameterClass* parse::parameter(queue<token> &tokens, int &num) {
	token t = tokens.front();
	if (t == ID) {
		bool check = checkID(tokens, num);
		if (!check) {
		  return NULL;
		}
		class ParameterClass* p = new class ParameterClass(tokenStrings.front());
		tokenStrings.pop();
		return p;
		
	}else if (t == STRING) {
		bool check = checkSTRING(tokens, num);
		if (!check) {
		  return NULL;
		}
		class ParameterClass* p = new class ParameterClass(tokenStrings.front());
		tokenStrings.pop();
		return p;
		
	}else if (t == LEFT_PAREN) {
		return expression(tokens);
	}
	offender = t;
    return NULL;
}

void parse::makeOneVector(vector<class ParameterClass*> &a, vector<class ParameterClass*> &b) {
	for (int i = 0; i < b.size(); i++) {
		a.push_back(b[i]);
	}
}

vector<class ParameterClass*> parse::parameterlist(queue<token> &tokens, int &num) {
    token t = tokens.front();
    vector<class ParameterClass*> a;
    a.push_back(NULL);
    vector<class ParameterClass*> ps;
    if (t == RIGHT_PAREN) {
        return ps;
    }else if (t == COMMA) {
        checkCOMMA(tokens);
	class ParameterClass* p = parameter(tokens, num);
	vector<class ParameterClass*> b = parameterlist(tokens, num);
	if ( p == NULL || (ps.size() == 1 && ps[0] == NULL) ) {
	  return a;
	}
	ps.push_back(p);
	makeOneVector(ps, b);
	return ps;
    }
    offender = t;
    return a;
}

class ParameterClass* parse::expression(queue<token> &tokens) {
    token t = tokens.front();
    if (t == LEFT_PAREN) {
      
	int num = 0;
	bool check = checkLEFT_P(tokens);
	class ParameterClass* p = parameter(tokens, num);
	check = (check && operators(tokens));
	string s = tokenStrings.front();
	tokenStrings.pop();
	class ParameterClass* p2 = parameter(tokens, num);
	check = (check && checkRIGHT_P(tokens));
	if (p == NULL || p2 == NULL || !check) {
	  return NULL;
	}
	stringstream ss;
	ss << "( " << p->toString() << " " << s << " " << p2->toString() << " )";
	return new class ParameterClass(ss.str());
    }
    offender = t;
    return NULL;
}

bool parse::operators(queue<token> &tokens) {
    return (checkADD(tokens) || checkMULTIPLY(tokens));
}

//
// Check functions
//

bool parse::checkID(queue<token> &tokens, int &num) {
    token t = tokens.front();
    if (t == ID) {
        //cout << "sees ID\n";
    	tokenIndex++;
        tokens.pop();
	num++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkSTRING(queue<token> &tokens, int &num) {
    token t = tokens.front();
    if (t == STRING) {
        //cout << "sees string\n";
        tokens.pop();
        tokenIndex++;
	num++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkADD(queue<token> &tokens) {
    token t = tokens.front();
    if (t == ADD) {
        //cout << "sees add\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkMULTIPLY(queue<token> &tokens) {
    token t = tokens.front();
    if (t == MULTIPLY) {
        //cout << "sees multiply\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkFACTS(queue<token> &tokens) {
    token t = tokens.front();
    if (t == FACTS) {
        //cout << "sees FACT\n";
    	tokenIndex++;
        tokens.pop();
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkRULES(queue<token> &tokens) {
    token t = tokens.front();
    if (t == RULES) {
        //cout << "sees RULE\n";
    	tokenIndex++;
        tokens.pop();
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkQUERIES(queue<token> &tokens) {
    token t = tokens.front();
    if (t == QUERIES) {
        //cout << "sees query\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkRIGHT_P(queue<token> &tokens) {
    token t = tokens.front();
    if (t == RIGHT_PAREN) {
        //cout << "sees r_paren\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkLEFT_P(queue<token> &tokens) {
    token t = tokens.front();
    if (t == LEFT_PAREN) {
        //cout << "sees l_paren\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkCOMMA(queue<token> &tokens) {
    token t = tokens.front();
    if (t == COMMA) {
        //cout << "sees comma\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkPERIOD(queue<token> &tokens) {
    token t = tokens.front();
    if (t == PERIOD) {
        //cout << "sees period\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkCOLON(queue<token> &tokens) {
    token t = tokens.front();
    if (t == COLON) {
        //cout << "sees colon\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkCOLON_DASH(queue<token> &tokens) {
    token t = tokens.front();
    if (t == COLON_DASH) {
        //cout << "sees colon_dash\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}


bool parse::checkSCHEMES(queue<token> &tokens) {
    token t = tokens.front();
    if (t == SCHEMES) {
        //cout << "sees SCHEME\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkQ_MARK(queue<token> &tokens) {
    token t = tokens.front();
    if (t == Q_MARK) {
        //cout << "sees q_mark\n";
        tokens.pop();
        tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}

bool parse::checkMEOF(queue<token> &tokens) {
    token t = tokens.front();
    if (t == MEOF) {
    	tokenIndex++;
        return true;
    }
    offender = t;
    return false;
}


void parse::eraseSchemes() {
	int i = 0;
	while (!schemes.empty()) {
		delete schemes[i];
		schemes[i++] = NULL;
	}
}
void parse::eraseFacts() {
	int i = 0;
	while (!facts.empty()) {
		delete facts[i];
		facts[i++] = NULL;
	}
}
void parse::eraseRules() {
	int i = 0;
	while (!rules.empty()) {
		delete rules[i];
		rules[i++] = NULL;
	}
}
void parse::eraseQueries() {
	int i = 0;
	while (!queries.empty()) {
	  delete queries[i];
	  queries[i++] = NULL;
	}
}

class datalogClass* parse::datalogOut() {
    class datalogClass* d = new class datalogClass();
    d->addSchemes(schemes);
    d->addFacts(facts);
    d->addDomain(domain);
    //cout << "Problem?\n";
    d->addRules(rules);
    d->addQueries(queries);
    
    return d;
}



