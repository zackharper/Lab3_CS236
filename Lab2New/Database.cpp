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
        relations.push_back(new Relation(scheme_list->getSchemes()[i]));
    MakeTuples(data->getFactList());
}

Database::~Database(){
    for (int i = 0; i < relations.size(); i++)
        delete relations[i];
}

void Database::MakeTuples(FactList * fact_list){
    for (int i = 0; i < fact_list->size(); i++)
}