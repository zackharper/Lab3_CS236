//
//  SchemeList.h
//  Lab 2
//
//  Created by Samuel Turner on 2/5/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#ifndef __Lab_2__SchemeList__
#define __Lab_2__SchemeList__

#include <iostream>
#include "Scheme.h"

class SchemeList{
public:
    SchemeList();
    ~SchemeList();
    void Parse(Lex*);
    string toString();
    int size();
    
    vector<Scheme*> getSchemes();
private:
    vector<Scheme*> list;
};

#endif /* defined(__Lab_2__SchemeList__) */
