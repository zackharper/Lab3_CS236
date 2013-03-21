//
//  Tuple.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Tuple.h"

Tuple::Tuple(Facts* fact){
    //vector<Token*> fact_tokens;
    for (int i = 1; i < fact->getTokens().size(); i++){//start at index one to skip the title of the fact, associated with the relation
        Token * temp = fact->getTokens()[i];
        if (temp->getTokenType() == ID || temp->getTokenType() == STRING)
            token_list.push_back(temp);
            //tokens.push_back(temp);
    }
}

Tuple::~Tuple(){
    token_list.erase(token_list.begin(),token_list.end());
}

bool Tuple::select(list<Token*> query_params){
    cout << "size of token list: " << token_list.size() << endl;
    list<Token*>::iterator query_it = query_params.begin();
    list<Token*>::iterator tuple_it = token_list.begin();
    cout << "front value is: ";
    cout << token_list.front()->getTokensValue() << endl;
    
    //this->printTokenList();
  //  cout << "value at query_it: " << (*query_it)->getTokensValue() << endl;
    //this->printTokenList();
  //  cout << "value at tuple_it: " << (*tuple_it)->getTokensValue() << endl;
    while (query_it != query_params.end() && tuple_it != token_list.end()){
     
        cout << "query_it value:" << (*query_it)->getTokensValue() << endl;
        if ((*query_it)->getTokenType() == STRING) {
            if ((*query_it)->getTokensValue() != (*tuple_it)->getTokensValue())
                return false;
        }
        query_it++;
        tuple_it++;
    }
    return true;
}

list<Token*> Tuple::getTokens(){
    return token_list;
}

void Tuple::printTokenList(){
    cout << "token_list:";
    list<Token*>::iterator it;

    for(it = token_list.begin(); it != token_list.end(); it++){
        cout << (*it)->getTokensValue();
    
    }
    cout << endl;

}
