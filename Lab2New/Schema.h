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
    Schema(Scheme*);
    Schema(Schema*);
    ~Schema();
    void listRename(list<Token*>);

    list<Token*> headings;
private:
};

#endif /* defined(__Lab2New__Schema__) */
