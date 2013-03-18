//
//  Facts.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Facts__
#define __Lab2New__Facts__

#include <iostream>
#include "Lex.h"

class Facts {
public:
    Facts(Lex*);
    ~Facts();
    void Parse(Lex*);
    void ConstantList(Lex*);
    void ConstantTail(Lex*);
    string toString();
    
    vector<Token*> getTokens();
private:
    vector<Token*> tokens;
};

#endif /* defined(__Lab2New__Facts__) */
