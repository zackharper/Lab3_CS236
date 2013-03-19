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

string Schema::toString(){
    string str = "(";
    for (int i = 0; i < headings.size(); i++){
        str += headings[i]->getTokensValue();
        if (i != headings.size() - 1)
            str += ",";
    }
    return str;
}

Token * Schema::getHeading(int index){
	return headings[index];
}