//
//  FactList.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "FactList.h"

FactList::FactList(){
    /*
     have a loop that analyzes each next token. this will provide a potentially infinite loop of schemes until the appropriate token is considered. the loop creates the "scheme list tail"*/
}

FactList::~FactList(){
    for (int i = 0; i < fact_list.size(); i++)
        delete fact_list[i];
}

void FactList::Parse(Lex * lexer){
    //lexer->parseAdvance();
    //NO FACTS ARE REQUIRED IN THE LIST. SO WHILE LOOP IS USED
    while (lexer->getCurrentToken()->getTokenType() == ID && lexer->failure == NULL){
        Facts * fact = new Facts(lexer);
        fact_list.push_back(fact);
    }
}

string FactList::toString(){
    string str;
    for (int i = 0; i < fact_list.size(); i++)
        str += fact_list[i]->toString() + "\n";
    return str;
}

int FactList::size(){
    return fact_list.size();
}

vector<Facts*> FactList::getFacts(){
    return fact_list;
}