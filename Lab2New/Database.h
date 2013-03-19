//YO THIS IS TO CHECK IF GITHUB/BITBUCKETZ IS WERKIN
//  Database.h
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab2New__Database__
#define __Lab2New__Database__

#include <iostream>
#include <vector>
#include "Relation.h"
using namespace std;

class Database {
public:
    Database(DataLog*);
    ~Database();
    void MakeTuples(FactList*);
    
    string toString();
private:
    vector<Relation*> relations;
    
};
#endif /* defined(__Lab2New__Database__) */
