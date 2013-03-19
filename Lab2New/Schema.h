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
using namespace std;

class Schema {
public:
    Schema(vector<Token*>);
    ~Schema();

    vector<Token*> getHeadings();
private:
    vector<Token*> headings;
};
#endif /* defined(__Lab2New__Schema__) */
