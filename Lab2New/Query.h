//
//  Query.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Query__
#define __Lab2New__Query__

#include <iostream>
#include "Predicate.h"

class Query {
public:
    Query(Lex*);
    ~Query();
    void Parse(Lex*);
    //void ConstantList(Lex*);
    //void ConstantTail(Lex*);
    string toString();
    
    Predicate * getPred();
private:
    Token * token;
    Predicate * pred;
};

#endif /* defined(__Lab2New__Query__) */
