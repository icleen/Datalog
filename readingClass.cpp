//
//  readingClass.cpp
//  Lexicograph
//
//  Created by Iain Lee on 9/13/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#include "readingClass.h"

bool reader::readIn(string file_name) {
    ifstream in_file;
    in_file.open( file_name.c_str() );
    
    if (in_file.fail()) {
        cout << "No file found!" << endl;
        return false;
    }else {
        string input;
        //    reads in each line from the input file and puts into lines
        while ( !in_file.eof() ) {
            getline(in_file, input);
            lines.push_back(input);
        }
    }
    in_file.close();
    return true;
}


const char reader::curCharOut() {
    if (isEmpty()) {
        return ' ';
    }if (lines[curLine].size() == 0) {
        return '\n';
    }
    return lines[curLine].at(curChar);
}


const string reader::nextCharOut() {
    if (nextLine >= lines.size()) {
        return "EOF";
    }
    if (nextChar >= lines[nextLine].length()) {
        nextChar = 0;
        nextLine++;
        return "\n";
    }
    
    stringstream ss;
    ss << lines[nextLine][nextChar++];
    return ss.str();
}

string reader::deleteChar(int char_nums) {
    string result;
//    cout << "charNums: " << char_nums << " lines[curLine].size: " << lines[curLine].size() << endl;
    if (char_nums == 1 && lines[curLine].size() == 0) {
        curLine++;
        return result;
    }
    while ( char_nums > lines[curLine].size() ) {
        char_nums -= (lines[curLine].size() + 1);
//        cout << "charNums: " << char_nums << " lines[curLine].size: " << lines[curLine].size() << endl;
        if (char_nums == 0) {
            result += lines[curLine++];
            return result;
        }else {
            result += lines[curLine++] + "\n";
        }
    }
    if (lines[curLine].length() == char_nums) {
        result += lines[curLine];
        curLine++;
        getnextline();
        curChar = 0;
        nextChar = 1;
        
    }else if (lines[curLine].size() == 0) {
        getnextline();
        curChar = 0;
        nextChar = 1;
    }else {
        stringstream ss;
        ss << lines[curLine].substr(curChar, char_nums);
        result += ss.str();
        unsigned long length = lines[curLine].length() - (curChar + char_nums); // new length
        string temp = lines[curLine].substr((curChar + char_nums), length);
        lines[curLine] = temp;
        nextChar = curChar + 1;
        
    }
    return result;
}

bool reader::isEmpty() {
    if (curLine >= lines.size()) {
        curLine = lines.size();
        return true;
    } else {
        return false;
    }
}

int reader::curLineOut() {
    return curLine + 1;
}

void reader::resetNext() {
    nextLine = curLine;
    nextChar = curChar + 1;
}

void reader::getnextline() {
    while ( curLine < lines.size() && lines[curLine].size() == 0 ) {
        curLine++;
    }
}

