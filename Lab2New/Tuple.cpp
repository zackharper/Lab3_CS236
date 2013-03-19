//
//  Tuple.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Tuple.h"


Tuple::Tuple(vector<Token*> columns){
    int i = 1;
    while (i < columns.size()){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
    }
}

Tuple::~Tuple(){
    for (int i = 0; i < headings.size(); i++)
    	delete headings[i];
}
