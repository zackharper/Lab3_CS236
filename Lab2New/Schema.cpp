//
//  Schema.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Schema.h"

Schema::Schema(vector<Token*> columns){
    int i = 1;//skip the id at index 0 because it is the title of the relation
    while (i < columns.size()){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
    }
}

Schema::~Schema(){
    for (int i = 0; i < headings.size(); i++)
    	delete headings[i];
}

Token * Schema::getHeading(int index){
	return headings[index];
}