//
//  Tuple.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Tuple.h"

<<<<<<< HEAD

Tuple::Tuple(vector<Token*> columns){
    int i = 1;
    while (i < columns.size()){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
=======
Tuple::Tuple(Facts* fact){
    //vector<Token*> fact_tokens;
    for (int i = 1; i < fact->getTokens().size(); i++){//start at index one to skip the title of the fact, associated with the relation
        Token * temp = fact->getTokens()[i];
        if (temp->getTokenType() == ID)
            tokens.push_back(temp);
        //by pushing back only the ID tokens, the index values will correspond to the indices of the schema.
>>>>>>> d85868f90912b1507496ff4271e804e8dd5ecc92
    }
}

Tuple::~Tuple(){
<<<<<<< HEAD
    for (int i = 0; i < headings.size(); i++)
    	delete headings[i];
=======
    Token * temp = NULL;
    for (int i = tokens.size() - 1; i >= 0; i--){
        temp = tokens[i];
        tokens.pop_back();
        delete temp;
    }
}

Token * Tuple::getToken(int index){
    return tokens[index];
>>>>>>> d85868f90912b1507496ff4271e804e8dd5ecc92
}
