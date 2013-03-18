//
//  Facts.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Facts.h"

Facts::Facts(Lex * lexer){
    /*
     the current token is an identifier (it was checked in FactsList). next token should be (
     do a loop that will analyze the next characters. they must by ID's, if not, break from the loop and the next char should be ). NOTE: IT MUST HAVE AT LEAST ONE IDENTIFIER*/
    Parse(lexer);
}

Facts::~Facts(){
    for (int i = 0; i < tokens.size(); i++)
        delete tokens[i];
}

void Facts::Parse(Lex * lexer){
    if (lexer->getCurrentToken()->getTokenType() == ID){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        if (lexer->getCurrentToken()->getTokenType() == LEFT_PAREN){
            tokens.push_back(lexer->getCurrentToken());
            lexer->parseAdvance();
            ConstantList(lexer);
        }
        else
            lexer->failure = lexer->getCurrentToken();
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

void Facts::ConstantList(Lex * lexer){
    /*
     start with an ID. then call the tail function, which will recursively call itself*/
    if (lexer->getCurrentToken()->getTokenType() == STRING){
        tokens.push_back(lexer->getCurrentToken());
        lexer->strings.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        ConstantTail(lexer);
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

void Facts::ConstantTail(Lex * lexer){
    Token * token = lexer->getCurrentToken();
    if (token->getTokenType() == COMMA){
        tokens.push_back(token);
        lexer->parseAdvance();
        ConstantList(lexer);
    }
    else if (token->getTokenType() == RIGHT_PAREN){
        tokens.push_back(token);
        lexer->parseAdvance();
        if (lexer->getCurrentToken()->getTokenType() == PERIOD){
            tokens.push_back(lexer->getCurrentToken());
            lexer->parseAdvance();
        }
        else
            lexer->failure = lexer->getCurrentToken();
    }
    else
        lexer->failure = token;
}

string Facts::toString(){
    string str = "  ";
    for (int i = 0; i < tokens.size(); i++)
        str += tokens[i]->getTokensValue();
    return str;
}

vector<Token*> Facts::getTokens(){
    return tokens;
}
