//
//  Tuple.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Tuple.h"

Tuple::Tuple(Facts* fact){
    //vector<Token*> fact_tokens;
    for (int i = 1; i < fact->getTokens().size(); i++){//start at index one to skip the title of the fact, associated with the relation
        Token * temp = fact->getTokens()[i];
        if (temp->getTokenType() == ID || temp->getTokenType() == STRING)
            tokens.push_back(temp);
    }
}

Tuple::~Tuple(){
    Token * temp = NULL;
    for (int i = tokens.size() - 1; i >= 0; i--){
        temp = tokens[i];
        tokens.pop_back();
        delete temp;
        temp = NULL;
    }
}

vector<Token*> Tuple::getTokens(){
    return tokens;
}
