//
//  otherAutomata.cpp
//  Lexicograph
//
//  Created by Iain Lee on 9/17/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#include "otherAutomata.h"

int stringClass::read(reader &r) {
    r.resetNext();
    int index = 0;
    bool ends = false;
    stringstream ss;
    ss << r.curCharOut();
    if ( ss.str() == "'") {
        index++;
        bool go = true;
        while ( go ) {
            string s = r.nextCharOut();
            if ( s == "'" ) {
                if (r.nextCharOut() != "'") {
                    go = false;
                    ends = true;
                    index++;
                }else {
                    index += 2;
                }
            }else if ( s == "EOF" ){
                go = false;
            }else {
                index++;
            }
        }
    }
    r.resetNext();
    if (!ends) {
        index = 0;
    }
    return index;
}

token stringClass::tokenOut() {
    return STRING;
}


int BlockComment::read(reader &r) {
    r.resetNext();
    int index = 0;
    bool ends = false;
    if (r.curCharOut() == '#' && r.nextCharOut() == "|") {
        index = 2;
        bool go = true;
        while ( go ) {
            string s = r.nextCharOut();
            if ( s == "|") {
                if (r.nextCharOut() == "#") {
                    go = false;
                    ends = true;
                    index += 2;
                }else {
                    index++;
                }
            }else if (s == "EOF"){
                go = false;
            }else {
                index++;
            }
        }
    }
    r.resetNext();
    if (!ends) {
        index = 0;
    }
    return index;
}

token BlockComment::tokenOut() {
    return COMMENT;
}



int Comment::read(reader &r) {
    r.resetNext();
    int index = 0;
    if (r.curCharOut() == '#' && r.nextCharOut() != "|") {
        r.resetNext();
        index++;
        bool go = true;
        while ( go ) {
            if ( r.nextCharOut() != "\n" ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    r.resetNext();
    return index;
}

token Comment::tokenOut() {
    return COMMENT;
}


int IDautomata::read(reader &r) {
    r.resetNext();
    int index = 0;
    
    if (isalpha(r.curCharOut())) {
        index++;
        bool go = true;
        while ( go ) {
            string s = r.nextCharOut();
            if ( isalnum(s[0]) ) {
                index++;
            }else {
                go = false;
            }
        }
    }
    r.resetNext();
    return index;
}

token IDautomata::tokenOut() {
    return ID;
}

//
bool Undefined::notOtherToken(char c) {
    if ( isalpha(c) ) {
        return false;
    }
    for (int i = 0; i < tokens.size(); i++) {
        if (c == tokens[i]) {
            return false;
        }
    }
    return true;
}

int Undefined::findEndS(reader &r) {
    int index = 1;
    bool ends = false;
    bool go = true;
    while ( go ) {
        string s = r.nextCharOut();
        if ( s == "'") {
            if (r.nextCharOut() != "'") {
                go = false;
                ends = true;
                index++;
            }else {
                index += 2;
            }
        }else if (s == "EOF"){
            go = false;
        }else {
            index++;
        }
    }
    if (ends) {
        index = 0;
    }
    return index;
}

int Undefined::findEndBC(reader &r) {
    int index = 2;
    bool ends = false;
    bool go = true;
    while ( go ) {
        string s = r.nextCharOut();
        if ( s == "|") {
            if (r.nextCharOut() == "#") {
                go = false;
                ends = true;
                index += 2;
            }else {
                index++;
            }
        }else if (s == "EOF"){
            go = false;
        }else {
            index++;
        }
    }
    if (ends) {
        index = 0;
    }
    return index;
}

int Undefined::read(reader &r) {
    r.resetNext();
    int index = 0;
    if ( notOtherToken(r.curCharOut()) && !isspace(r.curCharOut()) ) {
        index++;
    }else if (r.curCharOut() == '#' && r.nextCharOut() == "|") {
        index = findEndBC(r);
    }else if ( r.curCharOut() == '\'' ) {
        index = findEndS(r);
    }
    r.resetNext();
    return index;
}

token Undefined::tokenOut() {
    return UNDEFINED;
}


int FileEnd::read(reader &r) {
    r.resetNext();
    return 0;
}

token FileEnd::tokenOut() {
    return MEOF;
}




