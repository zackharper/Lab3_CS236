//
//  Tuple.h
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Tuple__
#define __Lab2New__Tuple__

#include <iostream>
#include <vector>
#include "DataLog.h"
using namespace std;

class Tuple {
public:
    Tuple(Facts*);
    Tuple(Tuple*);
    ~Tuple();
    bool select(vector<Token*>);
    bool listSelect(list<Token*>);
    void project(list<Token*>);
    void printTokenList();
    void destroy();
    vector<Token*> getTokens();
    list<Token*> token_list;

private:
    //vector<Token*> tokens;
    //vector<Token*> token_vec;
};

#endif /* defined(__Lab2New__Tuple__) */
