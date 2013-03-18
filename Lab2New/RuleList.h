//
//  RuleList.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__RuleList__
#define __Lab2New__RuleList__

#include <iostream>
#include "Rule.h"

class RuleList{
public:
    RuleList();
    ~RuleList();
    void Parse(Lex*);
    string toString();
    int size();
    
    vector<Rule*> getRules();
private:
    vector<Rule*> rule_list;
};

#endif /* defined(__Lab2New__RuleList__) */
