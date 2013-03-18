//
//  FactList.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__FactList__
#define __Lab2New__FactList__
#include "Facts.h"

class FactList{
public:
    FactList();
    ~FactList();
    void Parse(Lex*);
    string toString();
    int size();
    
    vector<Facts*> getFacts();
private:
    vector<Facts*> fact_list;
};

#endif /* defined(__Lab_2__SchemeList__) */