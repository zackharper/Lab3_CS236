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
        if (temp->getTokenType() == ID || temp->getTokenType() == STRING){
            //token_vec.push_back(temp);
            token_list.push_back(new Token(temp->getTokensValue(),temp->getTokenType()));
        }
    }
}

Tuple::Tuple(Tuple* old_tuple){
    for (list<Token*>::iterator old_it = old_tuple->token_list.begin(); old_it != old_tuple->token_list.end(); old_it++)
        this->token_list.push_back(new Token((*old_it)->getTokensValue(),(*old_it)->getTokenType()));
}

Tuple::~Tuple(){
    token_list.erase(token_list.begin(),token_list.end());
}

bool Tuple::select(vector<Token*> query_params){
    /*cout << "size of token list: " << token_list.size() << endl;
    //list<Token*>::iterator query_it = query_params.begin();
    //list<Token*>::iterator tuple_it = token_list.begin();
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
    for (int i = 0; i < query_params.size(); i++){
        if (query_params[i]->getTokenType() == STRING){
            if (query_params[i]->getTokensValue() != token_vec[i]->getTokensValue())
                return false;
        }
    }
    return true;*/
}

bool Tuple::listSelect(list<Token*> query_params){
    list<Token*>::iterator query_it = query_params.begin();
    list<Token*>::iterator token_it = token_list.begin();
    while (query_it != query_params.end() && token_it != token_list.end()) {
        if ((*query_it)->getTokenType() == STRING){
            if ((*query_it)->getTokensValue() != (*token_it)->getTokensValue())
                return false;
        }
        query_it++;
        token_it++;
    }
    return true;
}

void Tuple::project(list<Token*> query_params){
    list<Token*>::iterator token_it = token_list.begin();    
    list<Token*>::iterator query_it = query_params.begin();
    //cout << "token list beginning value: " << (*token_it)->getTokensValue() << endl;
    //cout << "query list beginning value: " << (*query_it)->getTokensValue() << endl;
    
    //cout << "before the project loop" << endl;
    while (query_it != query_params.end() && token_it != token_list.end()) {
        //cout << "token list value: " << (*token_it)->getTokensValue() << endl;
        //cout << "query list value: " << (*query_it)->getTokensValue() << endl;
        
        if ((*query_it)->getTokenType() == STRING)
            token_list.erase(token_it);
        
        //QUERY TOKEN IS ID--don't do anything with the tuple
        token_it++;
        query_it++;
    }
    //cout << "PROJECTED TOKENS ARE: ";
    //printTokenList();
    //cout << endl;
}

void Tuple::destroy(){
  /*  for (int i = 0; i < token_list.size(); i++){
        while (token_list[i]->getTokenType() == COLON){
            for(int j = i; j < rows[c]->getTokens().size(); j++){
                //if(j != (rows[c]->getTokens().size() - 1))//NEED TO MAKE A FUNCTION IN TUPLE THAT ALLOWS ME TO CHANGE THE TUPLE VALUES
                //headings[j] = headings[j+1];
            }
            //headings.pop_back(); //deletes last element which should be a :
            i = 0;//we need to start the loop over because the vector has changed
        }
    }*/
}

/*vector<Token*> Tuple::getTokens(){
    return token_vec;
}*/

void Tuple::printTokenList(){
    list<Token*>::iterator it;

    for(it = token_list.begin(); it != token_list.end(); it++){
        cout << (*it)->getTokensValue();
    
    }
    cout << endl;
    /*for (int i = 0; i < token_vec.size(); i++)
        cout << token_vec[i]->getTokensValue();*/
}
