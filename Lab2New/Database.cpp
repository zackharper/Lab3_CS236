//
//  Database.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Database.h"

Database::Database(DataLog * data){
    SchemeList * scheme_list = data->getSchemeList();
    for (int i = 0; i < scheme_list->size(); i++)
        relations.push_back(new Relation( scheme_list->getSchemes() [i]));
        
    MakeTuples(data->getFactList());
    processQueries(data->getQueryList());
    toString(data->getQueryList()->getQueries());
}

Database::~Database(){
    Relation * temp = NULL;
    for (int i = relations.size() - 1; i >= 0; i--){
        temp = relations[i];
        relations.pop_back();
        delete temp;
        temp = NULL;
    }
}

void Database::MakeTuples(FactList * fact_list){
    vector<Facts*> facts;// = fact_list->getFacts();
    for (int i = 0; i < fact_list->getFacts().size(); i++)
        facts.push_back(fact_list->getFacts()[i]);
    
    for (int i = 0; i < facts.size(); i++){
        string fact_name = facts[i]->getTokens()[0]->getTokensValue();//first token is the name of the fact
        for (int j = 0; j < relations.size(); j++){
            string relation_name = relations[j]->getName()->getTokensValue();
            if (fact_name == relation_name){
                relations[j]->addTuple(facts[i]);
                break;
            }
        }
    }
}

void Database::processQueries(QueryList* query_list){
    vector<Query*> queries = query_list->getQueries();
    for (int i = 0; i < queries.size(); i++){
        for (int j = 0; j < relations.size(); j++){
            if (relations[j]->getName()->getTokensValue() == queries[i]->getPred()->getTokens()[0]->getTokensValue())
                new_relations.push_back(new Relation(relations[j], queries[i]));
        }
    }
}


string Database::toString(vector<Query*> queries){
    string str;
    for (int i = 0; i < new_relations.size(); i++)
        str += queries[i]->toString() + " " + new_relations[i]->toString();
    cout << str;
    return str;
}
