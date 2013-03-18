//
//  Rule.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Rule.h"

Rule::Rule(Lex * lexer){
    Parse(lexer);
}

Rule::~Rule(){
    for (int i = 0; i < preds.size(); i++)
        delete preds[i];
    for (int j = 0; j < tokens.size(); j++)
        delete tokens[j];
}

void Rule::Parse(Lex * lexer){
    HeadPred(lexer);
    /*if (lexer->failure != NULL){
        cout << lexer->failure->toString() << endl;
        return;
    }
    cout << "we are here" << endl;*/
    
    if (lexer->getCurrentToken()->getTokenType() == COLON_DASH){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        addPred(lexer);
        if (lexer->failure != NULL) return;
        
        if (lexer->getCurrentToken()->getTokenType() == PERIOD){
            tokens.push_back(lexer->getCurrentToken());
            lexer->parseAdvance();
        }
        else
            lexer->failure = lexer->getCurrentToken();
    }
    else
        lexer->failure = lexer->getCurrentToken();
}

void Rule::addPred(Lex * lexer){
    Predicate * pred = new Predicate(lexer);
    preds.push_back(pred);//should i break out of loop when failure is made?
    if (lexer->getCurrentToken()->getTokenType() == COMMA && lexer->failure == NULL){
        tokens.push_back(lexer->getCurrentToken());
        lexer->parseAdvance();
        addPred(lexer);
    }
}

/////////////////HEAD PREDICATE FUNCTIONS/////////////////

void Rule::HeadPred(Lex * lexer){
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

void Rule::IdentifierList(Lex * lexer){
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

void Rule::IDTail(Lex * lexer){
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

string Rule::toString(){
    string str = "  " + printHead();
    return str;
}

string Rule::printHead(){
    int i = 0;
    string str;
    while (tokens[i]->getTokenType() != COLON_DASH){
        str += tokens[i]->getTokensValue();
        i++;
    }
    str += " " + tokens[i]->getTokensValue() + " " + printList(i+1);
    return str;
}

string Rule::printList(int x){
    string str;
    int i = 0;
    while (i < preds.size() && x < tokens.size()){
        str += preds[i]->toString() + tokens[x]->getTokensValue();
        x++;
        i++;
    }
    return str;
}
