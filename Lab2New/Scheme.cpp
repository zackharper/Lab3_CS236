//
//  Scheme.cpp
//  Lab 2
//
//  Created by Samuel Turner on 2/5/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Scheme.h"

Scheme::Scheme(Lex * lexer){
    /*
     the current token is an identifier (it was checked in SchemeList). next token should be (
     do a loop that will analyze the next characters. they must by ID's, if not, break from the loop and the next char should be ). NOTE: IT MUST HAVE AT LEAST ONE IDENTIFIER*/
    Parse(lexer);
}

Scheme::~Scheme(){
    for (int i = 0; i < tokens.size(); i++)
        delete tokens[i];
}

void Scheme::Parse(Lex * lexer){
    //cout << "parsing scheme" << endl;
    //cout << "current token is " << lexer->getCurrentToken()->getTokensValue();
    if (lexer->getCurrentToken()->getTokenType() == ID){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        if (lexer->getCurrentToken()->getTokenType() == LEFT_PAREN){
            tokens.push_back(lexer->getCurrentToken());
            lexer->parseAdvance();
            IdentifierList(lexer);
        }
        else
            lexer->failure = lexer->getCurrentToken();
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

void Scheme::IdentifierList(Lex * lexer){
    /*
     start with an ID. then call the tail function, which will recursively call itself*/
    if (lexer->getCurrentToken()->getTokenType() == ID){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        IDTail(lexer);
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

void Scheme::IDTail(Lex * lexer){
    Token * token = lexer->getCurrentToken();
    if (token->getTokenType() == COMMA){
        tokens.push_back(token);
        lexer->parseAdvance();
        IdentifierList(lexer);
    }
    else if (token->getTokenType() == RIGHT_PAREN){
        tokens.push_back(token);
        lexer->parseAdvance();
    }
    else
        lexer->failure = token;
}

string Scheme::toString(){
    string str = "  ";
    for (int i = 0; i < tokens.size(); i++)
        str += tokens[i]->getTokensValue();
    return str;
}

vector<Token*> Scheme::getTokens(){
    return tokens;
}