//
//  QueryList.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "QueryList.h"

QueryList::QueryList(){
    
}

QueryList::~QueryList(){
    for (int i = 0; i < query_list.size(); i++)
        delete query_list[i];
}

void QueryList::Parse(Lex * lexer){
    //lexer->parseAdvance();
    do {
        Query * query = new Query(lexer);
        query_list.push_back(query);//should i break out of loop when failure is made?
    } while (lexer->getCurrentToken()->getTokenType() == ID && lexer->failure == NULL);
}

///////////QUERY REQUIRES PARAMETERS AND SUCH. FINISH THIS LATER.

string QueryList::toString(){
    string str;
    for (int i = 0; i < query_list.size(); i++)
        str += query_list[i]->toString() + "\n";
    return str;
}

int QueryList::size(){
    return query_list.size();
}

vector<Query*> QueryList::getQueries(){
    return query_list;
}