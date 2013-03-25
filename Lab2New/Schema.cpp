//
//  Schema.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Schema.h"

Schema::Schema(Scheme* scheme){
    for (int i = 1; i < scheme->getTokens().size(); i++){
        if (scheme->getTokens()[i]->getTokenType() == ID) 
            headings.push_back(new Token(scheme->getTokens()[i]->getTokensValue(),scheme->getTokens()[i]->getTokenType()));
    }
}

Schema::Schema(Schema* old_schema){
    for (list<Token*>::iterator old_it = old_schema->headings.begin(); old_it != old_schema->headings.end(); old_it++)
        this->headings.push_back(new Token((*old_it)->getTokensValue(),(*old_it)->getTokenType()));
}

Schema::~Schema(){
    headings.erase(headings.begin(),headings.end());
}

void Schema::listRename(list<Token*> query_params){
    list<Token*>::iterator query_it = query_params.begin();
    list<Token*>::iterator schema_it = headings.begin();

    while (query_it != query_params.end() && schema_it != headings.end()){
        if ((*query_it)->getTokenType() == ID)
            (*schema_it)->setTokenValue((*query_it)->getTokensValue());
        query_it++;
        schema_it++;
    }
}