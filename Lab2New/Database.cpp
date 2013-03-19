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
    for (int i = 0; i < scheme_list->size(); i++){
        relations.push_back(new Relation( scheme_list->getSchemes() [i]));
        //cout << "i value is: " << i << endl;
    }
    //for (int i = 0; i < relations.size(); i++)
        //cout << relations[i]->getName()->getTokensValue() << endl;
    MakeTuples(data->getFactList());
}

Database::~Database(){
    for (int i = 0; i < relations.size(); i++)
        delete relations[i];
}

void Database::MakeTuples(FactList * fact_list){
    vector<Facts*> facts;// = fact_list->getFacts();
    for (int i = 0; i < fact_list->getFacts().size(); i++)
        facts.push_back(fact_list->getFacts()[i]);
    
    /*for (int i = 0; i < facts.size(); i++){
        cout << facts[i]->toString() << endl;
    }*/
    //cout << "size of fact vector is: " << facts.size() << endl;
    for (int i = 0; i < facts.size(); i++){
        //compare the name of the fact with the names of the schemes (relations). when equal, change the fact to a tuple (within the relation), and add to the relation.
        string fact_name = facts[i]->getTokens()[0]->getTokensValue();//first token is the name of the fact
        for (int j = 0; j < relations.size(); j++){
            string relation_name = relations[j]->getName()->getTokensValue();
            //cout << "fact name is: " << fact_name << "...relation name is: " << relation_name << endl;
            if (fact_name == relation_name){
                cout << "current relation is: " << relation_name << endl;
                relations[j]->addTuple(facts[i]);
                break;
            }
        }
    }
    for (int i = 0; i < relations.size(); i++){
        cout << "relation is: " << relations[i]->getName()->getTokensValue() << endl;
        for (int q = 0; q < relations[i]->getRows().size(); q++){
            for (int w = 0; w < relations[i]->getRows()[q]->getTokens().size(); w++)
                cout << relations[i]->getRows()[q]->getTokens()[w]->getTokensValue() + ", ";
            cout << endl;
        }
    }

    /*for (int i = 0; i < relations.size(); i++){
        cout << relations[i]->getName()->getTokensValue() << " row size: " << relations[i]->getRows().size() << endl;
    }*/
}

string Database::toString(){
    string str = "Relations:\n\t";
    for (int i = 0; i < relations.size(); i++){
        str += relations[i]->toString() + "\n\t";
    }
}
