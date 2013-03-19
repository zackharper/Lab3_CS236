//
//  Schema.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Schema.h"

Schema::Schema(vector<Token*> columns){
    //skip the id at index 0 because it is the title of the relation
    for (int i = 1; i < columns.size(); i++){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
    }
}

Schema::~Schema(){
    Token * temp = NULL;
    for (int i = headings.size() - 1; i >= 0; i--){
        temp = headings[i];
        headings.pop_back();
        delete temp;
        temp = NULL;
    }
}

string Schema::toString(){
    string str = "(";
    for (int i = 0; i < headings.size(); i++){
        str += headings[i]->getTokensValue();
        if (i != headings.size() - 1)
            str += ",";
    }
    str += ")";
    return str;
}

vector<Token*> Schema::getHeadings(){
	return headings;
}