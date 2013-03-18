//
//  Parameter.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Parameter.h"

Parameter::Parameter(Lex * lexer){
    Parse(lexer);
}

Parameter::~Parameter(){
    for (int i = 0; i < tokens.size(); i++)
        delete tokens[i];
}

void Parameter::Parse(Lex * lexer){
    TokenType type = lexer->getCurrentToken()->getTokenType();
    if (type == STRING || type == ID){
        tokens.push_back(lexer->getCurrentToken());
        if (type == STRING)
            lexer->strings.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
    }
    else if (type == LEFT_PAREN)
        Expression(lexer);
    else
        lexer->failure = lexer->getCurrentToken();
}

void Parameter::Expression(Lex* lexer){
    tokens.push_back(lexer->getCurrentToken());
    lexer->parseAdvance();
    Parse(lexer);
    if (lexer->getCurrentToken()->getTokenType() == ADD || lexer->getCurrentToken()->getTokenType() == MULTIPLY){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
    }
    else
        lexer->failure = lexer->getCurrentToken();
    Parse(lexer);
    if (lexer->getCurrentToken()->getTokenType() == RIGHT_PAREN){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

string Parameter::toString(){
    string str;
    for (int i = 0; i < tokens.size(); i++)
        str += tokens[i]->getTokensValue();
    return str;
}