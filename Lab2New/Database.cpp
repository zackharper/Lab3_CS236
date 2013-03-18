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
    for (int i = 0; i < scheme_list->getSchemes().size(); i++){
        relations.push_back(new Relation(scheme_list->getSchemes()[i]);
    }
    
}

Database::~Database(){
    
}