#include <queue>
#include <string>
#include <iostream>
#include "datalogProgram.h"
//#include "AutomataBaseClass.h"

using namespace std;

#ifndef parseClass_h
#define parseClass_h

enum token { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, UNDEFINED, COMMENT, WHITESPACE, MEOF };

class parse {
private:
    token offender;
    int tokenIndex;
    
    queue<string> tokenStrings;
    
    int schemeIndex;
    vector<class PredicateClass*> schemes;
    
    int factIndex;
    vector<class PredicateClass*> facts;
    vector<string> domain;
    
    int ruleIndex;
    vector<class RuleClass*> rules;
    
    int queryIndex;
    vector<class PredicateClass*> queries;
    
    void addToPred(class PredicateClass* &p, int size, bool fact);
    void addToPred(class PredicateClass* &p, vector<class ParameterClass*> &ps);
    void makeOneVector(vector<class PredicateClass*> &a, vector<class PredicateClass*> &b);
    void makeOneVector(vector<class ParameterClass*> &a, vector<class ParameterClass*> &b);
    
    void eraseSchemes();
    void eraseFacts();
    void eraseRules();
    void eraseQueries();
    
public:
    
    ~parse() {
    	eraseSchemes();
    	eraseFacts();
    	eraseRules();
    	eraseQueries();
    }
    
    class datalogClass* datalogOut();
    
    string schemeData();
    string factData();
    string ruleData();
    string queryData();
    
    string toString(token t);
    token toToken(string s);
    string offenderOut();

    int datalogParser(queue<token> &tokens, queue<string> &ts);
    bool a(queue<token> &tokens);
    bool b(queue<token> &tokens);
    bool c(queue<token> &tokens);
    
    bool scheme(queue<token> &tokens);
    bool schemelist(queue<token> &tokens);
    bool idlist(queue<token> &tokens, int &num);
	
    bool factlist(queue<token> &tokens);
    bool fact(queue<token> &tokens);
    bool stringlist(queue<token> &tokens, int &num);
	
    bool rulelist(queue<token> &tokens);
    bool rule(queue<token> &tokens);
    
    bool querylist(queue<token> &tokens);
    bool query(queue<token> &tokens);

    class PredicateClass* headPredicate(queue<token> &tokens);
    class PredicateClass* predicate(queue<token> &tokens);
    vector <class PredicateClass*> predicatelist(queue<token> &tokens);
    
    class ParameterClass* parameter(queue<token> &tokens, int &num);
    vector<class ParameterClass*> parameterlist(queue<token> &tokens, int &num);
    class ParameterClass* expression(queue<token> &tokens);

    bool operators(queue<token> &tokens);
    
    bool checkID(queue<token> &tokens, int &num);
    bool checkSTRING(queue<token> &tokens, int &num);
    bool checkADD(queue<token> &tokens);
    bool checkMULTIPLY(queue<token> &tokens);

    bool checkFACTS(queue<token> &tokens);
    bool checkRULES(queue<token> &tokens);
    bool checkQUERIES(queue<token> &tokens);
    bool checkRIGHT_P(queue<token> &tokens);
    bool checkLEFT_P(queue<token> &tokens);
    bool checkCOMMA(queue<token> &tokens);
    bool checkPERIOD(queue<token> &tokens);
    bool checkMEOF(queue<token> &tokens);
    bool checkCOLON(queue<token> &tokens);
    bool checkCOLON_DASH(queue<token> &tokens);
    bool checkSCHEMES(queue<token> &tokens);
    bool checkQ_MARK(queue<token> &tokens);

};

#endif /* parseClass_h */
