//
//  Parameter.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Parameter__
#define __Lab2New__Parameter__

#include <iostream>
#include "Lex.h"

class Parameter {
    
public:
    Parameter(Lex*);
    ~Parameter();
    void Parse(Lex*);
    void Expression(Lex*);
    string toString();
private:
    vector<Token*> tokens;
};

#endif /* defined(__Lab2New__Parameter__) */
