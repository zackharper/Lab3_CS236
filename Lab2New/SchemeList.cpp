//
//  SchemeList.cpp
//  Lab 2
//
//  Created by Samuel Turner on 2/5/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "SchemeList.h"
#include <assert.h>

SchemeList::SchemeList(){
    /*
     have a loop that analyzes each next token. this will provide a potentially infinite loop of schemes until the appropriate token is considered. the loop creates the "scheme list tail"*/
}

SchemeList::~SchemeList(){
    for (int i = 0; i < list.size(); i++)
        delete list[i];
}

void SchemeList::Parse(Lex * lexer){
    //lexer->parseAdvance();
    //DO WHILE LOOP IS USED BECAUSE AT LEAST ONE SCHEME IS RQUIRED IN GRAMMAR IF SCHEME LIST IS CALLED
    do {
        Scheme * scheme = new Scheme(lexer);
        list.push_back(scheme);//should i break out of loop when failure is made?
    } while (lexer->getCurrentToken()->getTokenType() == ID && lexer->failure == NULL);
    //cout << lexer->failure->getTokensValue() << "is the failure";
}

string SchemeList::toString(){
    string str;
    for (int i = 0; i < list.size(); i++)
        str += list[i]->toString() + "\n";
    return str;
}

int SchemeList::size(){
    return list.size();
}

vector<Scheme*> SchemeList::getSchemes(){
    return list;
}
