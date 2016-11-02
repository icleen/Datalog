//
//  AutomataBaseClass.h
//  Lexicograph
//
//  Created by Iain Lee on 9/13/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "readingClass.h"
#include "parseClass.h"

using namespace std;

#ifndef AutomataBaseClass_h
#define AutomataBaseClass_h

class BaseAutomata {

public:
    BaseAutomata() { };
    virtual ~BaseAutomata() { };
    //reads the string and returns how many characters it can take
    virtual int read(reader &r) = 0;
    //outputs the token correlating with the base class
    virtual token tokenOut() = 0;

};



#endif /* AutomataBaseClass_h */
