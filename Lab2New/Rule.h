//
//  Rule.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Rule__
#define __Lab2New__Rule__

#include <iostream>
#include "Predicate.h"

class Rule {
public:
    Rule(Lex*);
    ~Rule();
    void Parse(Lex*);
    string toString();
    void addPred(Lex*);
    void HeadPred(Lex*);
    void IdentifierList(Lex*);
    void IDTail(Lex*);
    string printHead();
    string printList(int);
private:
    vector<Predicate*> preds;
    vector<Token*> tokens;
};

#endif /* defined(__Lab2New__Rule__) */
