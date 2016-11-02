//
//  otherAutomata.hpp
//  Lexicograph
//
//  Created by Iain Lee on 9/17/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#ifndef otherAutomata_h
#define otherAutomata_h

#include <stdio.h>
#include "AutomataBaseClass.h"

class stringClass : public BaseAutomata {
    
public:
    int read(reader &r);
    token tokenOut();
//    int findEnd(reader &r, string s1, string s2);
    
};

class BlockComment : public BaseAutomata {
    
public:
    int read(reader &r);
    token tokenOut();
//    int findEnd(reader &r, string s1, string s2);
    
};

class Comment : public BaseAutomata {
    
public:
    int read(reader &r);
    token tokenOut();
    
};

class IDautomata : public BaseAutomata {
    
public:
    int read(reader &r);
    token tokenOut();
    
};

class Undefined : public BaseAutomata {
private:
    bool notOtherToken(char c);
    string tokens;
    int findEndBC(reader &r);
    int findEndS(reader &r);
    
public:
    Undefined() {
        tokens = ",.?():+*#'";
    };
    int read(reader &r);
    token tokenOut();

};

class FileEnd : public BaseAutomata {
    
public:
    int read(reader &r);
    token tokenOut();
    
};


#endif /* otherAutomata_h */
