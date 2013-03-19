//
//  Schema.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Schema.h"

Schema::Schema(vector<Token*> columns){
    int i = 1;
    while (i < columns.size()){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
    }
}

Schema::~Schema(){
    for (int i = 0; i < headings.size(); i++)
    	delete headings[i];
}

vector<Token*> Schema::getHeadings(){
	return headings;
}