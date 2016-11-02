//
//  basicAutomata.cpp
//  Lexicograph
//
//  Created by Iain Lee on 9/13/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#include "basicAutomata.h"

//
int comma::read(reader &r) {
    if ( r.curCharOut() == ',' ) {
        return 1;
    }
    return 0;
}
//
 token comma::tokenOut() {
    return COMMA;
     
}

//
int period::read(reader &r) {
    if ( r.curCharOut() == '.' ) {
        return 1;
    }
    return 0;
}
//
 token period::tokenOut() {
  return PERIOD;
}

//
int Q_mark::read(reader &r) {
    if ( r.curCharOut() == '?' ) {
        return 1;
    }
    return 0;
}
//
 token Q_mark::tokenOut() {
  return Q_MARK;
}

//
int left_paren::read(reader &r) {
    if ( r.curCharOut() == '(' ) {
        return 1;
    }
    return 0;
}
//
 token left_paren::tokenOut() {
  return LEFT_PAREN;
}

//
int right_paren::read(reader &r) {
    if ( r.curCharOut() == ')' ) {
        return 1;
    }
    return 0;
}
//
 token right_paren::tokenOut() {
  return RIGHT_PAREN;
}

//
int colon::read(reader &r) {
    if ( r.curCharOut() == ':' ) {
        return 1;
    }
    return 0;
}
//
token colon::tokenOut() {
    return COLON;
}

//
int multiplyClass::read(reader &r) {
    if ( r.curCharOut() == '*' ) {
        return 1;
    }
    return 0;
}
//
token multiplyClass::tokenOut() {
    return MULTIPLY;
}

//
int addClass::read(reader &r) {
    if ( r.curCharOut() == '+' ) {
        return 1;
    }
    return 0;
}
//
token addClass::tokenOut() {
    return ADD;
}


//
int WhiteSpace::read(reader &r) {
    if ( isspace(r.curCharOut()) ) {
        return 1;
    }
    return 0;
}
//
token WhiteSpace::tokenOut() {
    return WHITESPACE;
}


//
int colon_dash::read(reader &r) {
    r.resetNext();
    int index = 0;
    if ( r.curCharOut() == keyword[index++] ) {
        bool go = true;
        while ( go ) {
            stringstream ss;
            ss << keyword[index];
            if ( r.nextCharOut() == ss.str() ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    if (index != keyword.size()) {
        index = 0;
    }
    
    return index;
}
//
token colon_dash::tokenOut() {
    return COLON_DASH;
}

//
int schemes::read(reader &r) {
    r.resetNext();
    int index = 0;
    if ( r.curCharOut() == keyword[index++] ) {
        bool go = true;
        while ( go ) {
            stringstream ss;
            ss << keyword[index];
            if ( r.nextCharOut() == ss.str() ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    if (index != keyword.size()) {
        index = 0;
    }
    r.resetNext();
    return index;
}
//
token schemes::tokenOut() {
    return SCHEMES;
}

//
int facts::read(reader &r) {
    r.resetNext();
    int index = 0;
    if ( r.curCharOut() == keyword[index++] ) {
        bool go = true;
        while ( go ) {
            stringstream ss;
            ss << keyword[index];
            if ( r.nextCharOut() == ss.str() ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    if (index != keyword.size()) {
        index = 0;
    }
    r.resetNext();
    return index;
}
//
token facts::tokenOut() {
    return FACTS;
}

//
int rules::read(reader &r) {
    r.resetNext();
    int index = 0;
    if ( r.curCharOut() == keyword[index++] ) {
        bool go = true;
        while ( go ) {
            stringstream ss;
            ss << keyword[index];
            if ( r.nextCharOut() == ss.str() ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    if (index != keyword.size()) {
        index = 0;
    }
    r.resetNext();
    return index;
}
//
token rules::tokenOut() {
    return RULES;
}

//
int queries::read(reader &r) {
    r.resetNext();
    int index = 0;
    if ( r.curCharOut() == keyword[index++] ) {
        bool go = true;
        while ( go ) {
            stringstream ss;
            ss << keyword[index];
            if ( r.nextCharOut() == ss.str() ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    if (index != keyword.size()) {
        index = 0;
    }
    r.resetNext();
    return index;
}
//
token queries::tokenOut() {
    return QUERIES;
}




