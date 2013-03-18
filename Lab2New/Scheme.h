//
//  Scheme.h
//  Lab 2
//
//  Created by Samuel Turner on 2/5/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab_2__Scheme__
#define __Lab_2__Scheme__

#include <iostream>
#include "Lex.h"
//COMMENTZ
class Scheme {
public:
    Scheme(Lex*);
    ~Scheme();
    void Parse(Lex*);
    void IdentifierList(Lex*);
    void IDTail(Lex*);
    string toString();
    
    vector<Token*> getTokens();
private:
    vector<Token*> tokens;
};

#endif /* defined(__Lab_2__Scheme__) */
