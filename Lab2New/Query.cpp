//
//  Query.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Query.h"

Query::Query(Lex * lexer){
    token = NULL;
    pred = NULL;
    Parse(lexer);
}

Query::~Query(){
    delete token;
    delete pred;
}

void Query::Parse(Lex * lexer){
    pred = new Predicate(lexer);
    if (lexer->failure == NULL){
        if (lexer->getCurrentToken()->getTokenType() == Q_MARK){
            token = lexer->getCurrentToken();
            lexer->parseAdvance();
        }
        else
            lexer->failure = lexer->getCurrentToken();
    }
}

string Query::toString(){
    return "  " + pred->toString() + token->getTokensValue();
}

Predicate * Query::getPred(){
    return pred;
}
