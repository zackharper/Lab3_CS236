//
//  DataLog.h
//  Lab 2
//
//  Created by Samuel Turner on 2/5/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab_2__DataLog__
#define __Lab_2__DataLog__

#include <iostream>
#include <algorithm>
#include "SchemeList.h"
#include "FactList.h"
#include "RuleList.h"
#include "QueryList.h"

class DataLog {
public:
    DataLog(Lex*);
    ~DataLog();
    string toString(Lex*);
    string itoa(int);
    void Parse(Lex*);
    string sortDomain(Lex*);
    void search(string);
    
    SchemeList * getSchemeList();
    FactList * getFactList();
    RuleList * getRuleList();
    QueryList * getQueryList();
private:
    vector<TokenType> types;
    vector<string> domain;
    SchemeList * schemes;
    FactList * facts;
    RuleList * rules;
    QueryList * queries;
};

#endif /* defined(__Lab_2__DataLog__) */
