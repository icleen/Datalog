//
//  readingClass.hpp
//  Lexicograph
//
//  Created by Iain Lee on 9/13/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#ifndef readingClass_h
#define readingClass_h

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class reader {
private:
    vector<string> lines;
    int curLine;
    int nextLine;
    int curChar;
    int nextChar;
    void switchLines();
    void getnextline();
    
public:
    reader() {
        curLine = 0;
        nextLine = 0;
        curChar = 0;
        nextChar = 1;
    };
    
    bool readIn(string file_name);
    const char curCharOut();
    const string nextCharOut();
    string deleteChar(int num_of_chars);
    bool isEmpty();
    int curLineOut();
    void resetNext();
    
};

#endif /* readingClass_h */
