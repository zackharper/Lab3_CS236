//
//  RuleList.cpp
//  Lab2New
//
//  Created by Samuel Turner on 2/8/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "RuleList.h"

RuleList::RuleList(){
    /*
     have a loop that analyzes each next token. this will provide a potentially infinite loop of schemes until the appropriate token is considered. the loop creates the "scheme list tail"*/
}

RuleList::~RuleList(){
    for (int i = 0; i < rule_list.size(); i++)
        delete rule_list[i];
}

void RuleList::Parse(Lex * lexer){
    //lexer->parseAdvance();
    //cout << lexer->getCurrentToken()->getTokensValue() + " is current token." << endl << endl;
    //NO RULES ARE NEEDED, SO WHILE LOOP IS USED, NOT DO WHILE LOOP
    while (lexer->getCurrentToken()->getTokenType() == ID && lexer->failure == NULL){
            Rule * rule = new Rule(lexer);
            rule_list.push_back(rule);
    }
}

string RuleList::toString(){
    string str;
    for (int i = 0; i < rule_list.size(); i++)
        str += rule_list[i]->toString() + "\n";
    return str;
}

int RuleList::size(){
    return rule_list.size();
}

vector<Rule*> RuleList::getRules(){
    return rule_list;
}
