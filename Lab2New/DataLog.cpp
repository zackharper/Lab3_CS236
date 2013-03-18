//
//  DataLog.cpp
//  Lab 2
//
//  Created by Samuel Turner on 2/5/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//
#include "DataLog.h"

DataLog::DataLog(Lex * lexer){
    types.push_back(SCHEMES);
    types.push_back(FACTS);
    types.push_back(RULES);
    types.push_back(QUERIES);

    schemes = new SchemeList();
    facts = new FactList();
    rules = new RuleList();
    queries = new QueryList();
    Parse(lexer);
}

DataLog::~DataLog(){
    //for (int i = 0; i < domain.size(); i++)
        //delete domain[i];
    delete schemes;
    delete facts;
    delete rules;
    delete queries;
}

string DataLog::toString(Lex * lexer){
    string str = "Success!\n";
    str += "Schemes(" + itoa(schemes->size()) + "):\n" + schemes->toString();
    str += "Facts(" + itoa(facts->size()) + "):\n" + facts->toString();
    str += "Rules(" + itoa(rules->size()) + "):\n" + rules->toString();
    str += "Queries(" + itoa(queries->size()) + "):\n" + queries->toString();
    str += sortDomain(lexer);
    return str;
}

string DataLog::itoa(int num){
    ostringstream strm;
    string str;
    strm << num;
    return strm.str();
}

void DataLog::Parse(Lex * lexer){
    lexer->commentAdvance();
    int i = 0;
    while (i < types.size() && lexer->failure == NULL){
        TokenType type = lexer->getCurrentToken()->getTokenType();
        if (type == types[i]){
            lexer->parseAdvance();
            if (lexer->getCurrentToken()->getTokenType() == COLON){
                lexer->parseAdvance();
                if (type == SCHEMES)
                    schemes->Parse(lexer);
                else if (type == FACTS)
                    facts->Parse(lexer);
                else if (type == RULES)
                    rules->Parse(lexer);
                else if (type == QUERIES)
                    queries->Parse(lexer);
            }
            else
                lexer->failure = lexer->getCurrentToken();
        }
        else{
            lexer->failure = lexer->getCurrentToken();
            break;
        }
        i++;
    }
    if (lexer->failure == NULL && lexer->getCurrentToken()->getTokenType() != END)
        lexer->failure = lexer->getCurrentToken();
}

string DataLog::sortDomain(Lex * lexer){
    for (int i = 0; i < lexer->strings.size(); i++) 
        search(lexer->strings[i]->getTokensValue());
    sort(domain.begin(), domain.end());
    string str = "Domain(" + itoa(domain.size()) + "):";
    for (int j = 0; j < domain.size(); j++)
        str += "\n  " + domain[j];
    return str;
}

void DataLog::search(string str){
    for (int i = 0; i < domain.size(); i++){
        if (domain[i] == str)
            return;
    }
    domain.push_back(str);
}

///////////////////////////////////GET FUNCTIONS///////////////////////////////////////

SchemeList * DataLog::getSchemeList(){
    return schemes;
}

FactList * DataLog::getFactList(){
    return facts;
}

RuleList * DataLog::getRuleList(){
    return rules;
}

QueryList * DataLog::getQueryList(){
    return queries;
}