//
//  Predicate.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Predicate__
#define __Lab2New__Predicate__

#include <iostream>
#include "Parameter.h"

class Predicate {
public:
    Predicate(Lex*);
    ~Predicate();
    void Parse(Lex*);
    void ParameterList(Lex*);
    void ParameterTail(Lex*);
    string toString();
private:
    vector<Token*> tokens;//tokens vector will have ID, left paren, commas, and right paren
    vector<Parameter*> params;//will contain the parameter list that will be separated by commas
};

#endif /* defined(__Lab2New__Predicate__) */
