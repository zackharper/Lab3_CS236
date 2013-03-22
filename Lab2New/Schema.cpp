//
//  Schema.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Schema.h"

Schema::Schema(list<Token*> columns){
    //skip the id at index 0 because it is the title of the relation
    /*for (int i = 1; i < columns.size(); i++){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
    }*/
    //////////////////////////
    for (list<Token*>::iterator it = columns.begin(); it != columns.end(); it++){
        if ((*it)->getTokenType() == ID)
            headings.push_back(new Token((*it)->getTokensValue()));
    }
    //heads = NULL;
}

Schema::Schema(Schema* old_schema){
    for (list<Token*>::iterator old_it = old_schema->headings.begin(); old_it != old_schema->headings.end(); old_it++   )
        this->headings.push_back(new Token((*old_it)->getTokensValue()));
}

Schema::~Schema(){
    //headers.erase(headers.begin(),headers.end());
    /*Token * temp = NULL;
    for (int i = headings.size() - 1; i >= 0; i--){
        temp = headings[i];
        headings.pop_back();
        delete temp;
        temp = NULL;
    }*/
    /////////////////////////
    //list<Token*>::iterator temp;
    //Token * next_ptr = ptr->
    /*for (temp = headers.begin(); i >= 0; i--){
        headers.erase(temp);
        temp = headers[i];
        headers.pop_back();
        delete temp;
        temp = NULL;
    }*/
    headings.erase(headings.begin(),headings.end());
}

string Schema::toString(){
    /*string str = "(";
    for (int i = 0; i < headings.size(); i++){
        str += headings[i]->getTokensValue();
        if (i != headings.size() - 1)
            str += ",";
    }
    str += ")";
    return str;*/
}

/*list<Token*> Schema::getHeaders(){
	return headings;
}*/

void Schema::rename(Token * query_param_token, int rename_index){
    //this->headings[rename_index] = query_param_token;
}

void Schema::listRename(list<Token*> query_params){
    list<Token*>::iterator query_it = query_params.begin();
    list<Token*>::iterator schema_it = headings.begin();
    while (query_it != query_params.end() && schema_it != headings.end()){
        if ((*query_it)->getTokenType() == ID){
            Token * temp = *schema_it;
            *schema_it = new Token((*query_it)->getTokensValue());//changes the name of this schema's tokens
            delete temp;
        }
        query_it++;
        schema_it++;
    }
    cout << "NEW SCHEMA:\n\t";
    for (list<Token*>::iterator it = headings.begin(); it != headings.end(); it++) {
        cout << (*it)->getTokensValue() << " ";
    }
    cout << endl;
}

void Schema::project(list<Token*> query_params){
    /*for (int i = 0; i < indices.size(); i++)
        headings[indices[i]]->setTokenType(COLON);//COLON is a dummy token type that tells us where to delete the items
    for (int i = 0; i < headings.size(); i++){
        if (headings[i]->getTokenType() == COLON){
            destroy(i);
            for(int j = i; j < headings.size(); j++){
                if(j != (headings.size() - 1))
                    headings[j] = headings[j+1];
            }
            headings.pop_back(); //deletes last element which should be a :
            i = 0;//we need to start the loop over because the vector has changed
        }
    }*/
    list<Token*>::iterator token_it = headings.begin();
    list<Token*>::iterator query_it = query_params.begin();
    //cout << "token list beginning value: " << (*token_it)->getTokensValue() << endl;
    //cout << "query list beginning value: " << (*query_it)->getTokensValue() << endl;
    //cout << "before the project loop" << endl;
    while (query_it != query_params.end() && token_it != headings.end()) {
        //cout << "token list value: " << (*token_it)->getTokensValue() << endl;
        //cout << "query list value: " << (*query_it)->getTokensValue() << endl;
        
        if ((*query_it)->getTokenType() == STRING)
            headings.erase(token_it);
        //QUERY TOKEN IS ID--don't do anything with the tuple
        token_it++;
        query_it++;
    }
    cout << "FINAL PROJECTED SCHEMA IS: ";
    for (list<Token*>::iterator it = headings.begin(); it != headings.end(); it++)
        cout << (*it)->getTokensValue() << " ";
    cout << endl;

    //cout << "PROJECTED TOKENS ARE: ";
    //printTokenList();
}

void Schema::destroy(int index){
    /*for (int i = 0; i != headers.end(); temp++){
        cout << "//////////" << (*temp)->getTokensValue() << endl;
    }
    //Token * temp = headings[index];
    //headings[index] = headings[headings.size() - 1];//swapping with the final element in order to pop the element to be deleted
    //headings.pop_back();
    for(int i =0; i < this->headings.size(); i++){
    
        
    }
    
    //delete temp;*/
}