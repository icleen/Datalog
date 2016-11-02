//
//  basicAutomata.hpp
//  Lexicograph
//
//  Created by Iain Lee on 9/13/16.
//  Copyright © 2016 Iain. All rights reserved.
//

#ifndef basicAutomata_h
#define basicAutomata_h

#include <stdio.h>
#include "AutomataBaseClass.h"

class comma : public BaseAutomata {

public:
    comma() { };
    ~comma() { };
    int read(reader &r);
    token tokenOut();
    
};

class period : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class Q_mark : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class left_paren : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class right_paren : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class colon : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class multiplyClass : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class addClass : public BaseAutomata {
public:
    int read(reader &r);
    token tokenOut();
    
};

class colon_dash : public BaseAutomata {
private:
    const string keyword = ":-";
    
public:
    int read(reader &r);
    token tokenOut();

};

class schemes : public BaseAutomata {
private:
    const string keyword = "Schemes";

public:
    int read(reader &r);
    token tokenOut();
    
};

class facts : public BaseAutomata {
private:
    const string keyword = "Facts";
    
public:
    int read(reader &r);
    token tokenOut();
    
};

class rules : public BaseAutomata {
private:
    const string keyword = "Rules";
    
public:
    int read(reader &r);
    token tokenOut();
    
};

class queries : public BaseAutomata {
private:
    const string keyword = "Queries";
    
public:
    int read(reader &r);
    token tokenOut();
    
};

class WhiteSpace : public BaseAutomata {
    
public:
    int read(reader &r);
    token tokenOut();
    
};



#endif /* basicAutomata_h */
