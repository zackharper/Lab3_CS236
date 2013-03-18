//
//  QueryList.h
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__QueryList__
#define __Lab2New__QueryList__

#include <iostream>
#include "Query.h"

class QueryList{
public:
    QueryList();
    ~QueryList();
    void Parse(Lex*);
    string toString();
    int size();
    
    vector<Query*> getQueries();
private:
    vector<Query*> query_list;
};


#endif /* defined(__Lab2New__QueryList__) */
