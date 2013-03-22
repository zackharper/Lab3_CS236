//
//  Schema.h
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Schema__
#define __Lab2New__Schema__

#include <iostream>
#include "DataLog.h"
#include "Tuple.h"
using namespace std;

class Schema {
public:
    Schema(list<Token*>);
    Schema(Schema*);
    ~Schema();
    void rename(Token *, int);
    void listRename(list<Token*>);
    void project(list<Token*>);

    string toString();
    list<Token*> headings;
private:
    void destroy(int);
};

#endif /* defined(__Lab2New__Schema__) */
