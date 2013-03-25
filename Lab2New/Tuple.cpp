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
        if (temp->getTokenType() == ID || temp->getTokenType() == STRING){
            //token_vec.push_back(temp);
            token_list.push_back(new Token(temp->getTokensValue(),temp->getTokenType()));
        }
    }
}

Tuple::Tuple(Tuple* old_tuple){
    for (list<Token*>::iterator old_it = old_tuple->token_list.begin(); old_it != old_tuple->token_list.end(); old_it++)
        this->token_list.push_back(new Token((*old_it)->getTokensValue(),(*old_it)->getTokenType()));
}

Tuple::~Tuple(){
    token_list.erase(token_list.begin(),token_list.end());
}

bool Tuple::listSelect(list<Token*> query_params){
    list<Token*>::iterator query_it = query_params.begin();
    list<Token*>::iterator token_it = token_list.begin();
    while (query_it != query_params.end() && token_it != token_list.end()) {
        if ((*query_it)->getTokenType() == STRING){
            if ((*query_it)->getTokensValue() != (*token_it)->getTokensValue())
                return false;
        }
        query_it++;
        token_it++;
    }
    return true;
}

void Tuple::project(list<Token*> query_params){
    list<Token*>::iterator token_it = token_list.begin();    
    list<Token*>::iterator query_it = query_params.begin();
    while (query_it != query_params.end() && token_it != token_list.end()) {
        if ((*query_it)->getTokenType() == STRING)
            token_list.erase(token_it);
        token_it++;
        query_it++;
    }
}