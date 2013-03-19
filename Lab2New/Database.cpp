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
    for (int i = 0; i < scheme_list->getSchemes().size(); i++)
        relations.push_back(new Relation( (scheme_list->getSchemes()) [i]));
    MakeTuples(data->getFactList());
}

Database::~Database(){
    for (int i = 0; i < relations.size(); i++)
        delete relations[i];
}

void Database::MakeTuples(FactList * fact_list){
    vector<Facts*> facts; //= fact_list->getFacts();
    for (int i = 0; i < fact_list->getFacts().size(); i++)
        facts.push_back(fact_list->getFacts()[i]);
    
    for (int i = 0; i < facts.size(); i++){
        //compare the name of the fact with the names of the schemes (relations). when equal, change the fact to a tuple (within the relation), and add to the relation.
        int j = 0;
        Token * fact_name = (facts[i]->getTokens())[0];//first token is the name of the fact
        while (j < relations.size()){
            Token * relation_name = relations[j]->getName();
            if (fact_name == relation_name){
                relations[j]->addTuple(facts[i]);
                break;
            }
            j++;
        }
    }
}