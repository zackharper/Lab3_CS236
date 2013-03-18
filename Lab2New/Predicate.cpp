//
//  Predicate.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Predicate.h"

Predicate::Predicate(Lex* lexer){
    Parse(lexer);
}

Predicate::~Predicate(){
    for (int i = 0; i < params.size(); i++)
        delete params[i];
    for (int j = 0; j < tokens.size(); j++)
        delete tokens[j];
}

void Predicate::Parse(Lex * lexer){
    if (lexer->getCurrentToken()->getTokenType() == ID){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        if (lexer->getCurrentToken()->getTokenType() == LEFT_PAREN){
            tokens.push_back(lexer->getCurrentToken());
            lexer->parseAdvance();
            ParameterList(lexer);
        }
        else
            lexer->failure = lexer->getCurrentToken();
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

void Predicate::ParameterList(Lex * lexer){
    Parameter * param = new Parameter(lexer);
    //cout << param->toString() << endl;
    //if (lexer->failure != NULL)
        //cout << "failure is " << lexer->failure->toString() << endl;
    params.push_back(param);
    if (lexer->failure == NULL)
        ParameterTail(lexer);
}

void Predicate::ParameterTail(Lex * lexer){
    Token * token = lexer->getCurrentToken();
    if (token->getTokenType() == COMMA){
        tokens.push_back(token);
        lexer->parseAdvance();
        ParameterList(lexer);
    }
    else if (token->getTokenType() == RIGHT_PAREN){
        tokens.push_back(token);
        lexer->parseAdvance();
    }
    else
        lexer->failure = token;
}

string Predicate::toString(){
    string str;
    int i = 0;
    int x = 0;
    while (i < tokens.size() && tokens[i]->getTokenType() != COMMA && tokens[i]->getTokenType() != RIGHT_PAREN){//will print the ID and left paren
        str += tokens[i]->getTokensValue();
        i++;
    }
    /*cout << "Size of paramater vector: " << params.size() << endl;
    cout << "Size of token vector: " << tokens.size() << endl;
    cout << "Index of token vector: " << i << endl;*/
    while (x < params.size() && i < tokens.size()){
        str += params[x]->toString() + tokens[i]->getTokensValue();
        i++;
        x++;
        //cout << str << endl;
    }
    return str;
}
