//
//  Schema.cpp
//  Lab2New
//
//  Created by Samuel Turner on 3/16/13.
//  Copyright (c) 2013 Samuel Turner. All rights reserved.
//

#include "Schema.h"

Schema::Schema(Scheme* scheme){
    //skip the id at index 0 because it is the title of the relation
    for (int i = 1; i < scheme->getTokens().size(); i++){
        if (scheme->getTokens()[i]->getTokenType() == ID) 
            headings.push_back(new Token(scheme->getTokens()[i]->getTokensValue(),scheme->getTokens()[i]->getTokenType()));
    }
    
    //////////////////////////
    
    
    /*for (list<Token*>::iterator it = columns.begin(); it != columns.end(); it++){
        if ((*it)->getTokenType() == ID)
            //headings.push_back(new Token((*it)->getTokensValue(),(*it)->getTokenType()));
            headings.push_back(new Token((*it)->getTokensValue(),(*it)->getTokenType()));
    }*/
}

Schema::Schema(Schema* old_schema){
    for (list<Token*>::iterator old_it = old_schema->headings.begin(); old_it != old_schema->headings.end(); old_it++)
        this->headings.push_back(new Token((*old_it)->getTokensValue(),(*old_it)->getTokenType()));
}

Schema::~Schema(){
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

void Schema::rename(Token * query_param_token, int rename_index){
    //this->headings[rename_index] = query_param_token;
}

void Schema::listRename(list<Token*> query_params){
    list<Token*>::iterator query_it = query_params.begin();
    list<Token*>::iterator schema_it = headings.begin();

    /*cout << "OLD SCHEMA:\n\t";
    for (list<Token*>::iterator it = headings.begin(); it != headings.end(); it++) {
        cout << (*it)->getTokensValue() << " ";
    }
    cout << endl;*/

    while (query_it != query_params.end() && schema_it != headings.end()){
        if ((*query_it)->getTokenType() == ID){
            /*Token * temp = *schema_it;
            *schema_it = new Token((*query_it)->getTokensValue(),(*query_it)->getTokenType());//changes the name of this schema's tokens
            delete temp;*/
            //headings.erase(schema_it);
            //schema_it++;
            //headings.insert(schema_it, new Token((*query_it)->getTokensValue(),(*query_it)->getTokenType()));
            (*schema_it)->setTokenValue((*query_it)->getTokensValue());
        }
        //else
            //headings.erase(schema_it);//because it will be a string and we don't need those
        query_it++;
        schema_it++;
    }
    /*cout << "NEW SCHEMA:\n\t";
    for (list<Token*>::iterator it = headings.begin(); it != headings.end(); it++) {
        cout << (*it)->getTokensValue() << " ";
    }
    cout << endl;*/
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
    
    
    list<Token*>::iterator schema_it = headings.begin();
    list<Token*>::iterator query_it = query_params.begin();
    //cout << "token list beginning value: " << (*token_it)->getTokensValue() << endl;
    //cout << "query list beginning value: " << (*query_it)->getTokensValue() << endl;
    //cout << "before the project loop" << endl;
    
    
    
    while (query_it != query_params.end() && schema_it != headings.end()) {
        //cout << "token list value: " << (*token_it)->getTokensValue() << endl;
        //cout << "query list value: " << (*query_it)->getTokensValue() << endl;
        
        if ((*query_it)->getTokenType() == STRING){
            headings.erase(schema_it);
            //query_params.erase(query_it);
        }
        //QUERY TOKEN IS ID--don't do anything with the tuple
        schema_it++;
        query_it++;
        //cout << "stuck in this loop? " << endl;
    }
    query_it = query_params.begin();
    schema_it = headings.begin();
    
    while ((*query_it)->getTokenType() != ID && query_it != query_params.end())
        query_it++;
    dupes.push_back((*query_it)->getTokensValue());

    cout << "query currently is: ";
    for (list<Token*>::iterator it = query_it; it != query_params.end(); it++) {
        cout << (*it)->getTokensValue() + ", ";
    }
    cout << endl;
    cout << "schema currently is: ";
    for (list<Token*>::iterator it = schema_it; it != headings.end(); it++) {
        cout << (*it)->getTokensValue() + ", ";
        //cout << " infinite loop?" << endl;
    }
    cout << endl;
    //checkDupes(query_it, schema_it, query_params);
     
}

void Schema::checkDupes(list<Token*>::iterator query_it,list<Token*>::iterator schema_it,list<Token*> query_params){
    string query_master;
    if (query_it != query_params.end()){
        query_master = (*query_it)->getTokensValue();
        query_it++;
        schema_it++;
        cout << "incremented and made query master value of: " << query_master << endl;
    }
    while (query_it != query_params.end()){
        
        if ((*query_it)->getTokensValue() == query_master){
            //cout << "query matches the query master value of: " << query_master << endl;
            //query_params.erase(query_it);
            query_it++;
            //headings.erase(schema_it);
            schema_it++;
        }
        else if ((*query_it)->getTokenType() == STRING){
            //cout << "string found, do nothing: " << (*query_it)->getTokensValue() << endl;
            query_it++;
        }
        else if (seen((*query_it)->getTokensValue())){
            //cout << "already seen query value of: " << (*query_it)->getTokensValue() << endl;
            query_it++;
            schema_it++;
        }
        else{//a new variable to check for has been found
            
            cout << "values in dupes are: ";
            for (int i = 0; i < dupes.size(); i++) {
                cout << dupes[i] << ", ";
            }
            cout << endl;
            
            dupes.push_back((*query_it)->getTokensValue());
            checkDupes(query_it, schema_it, query_params);
        }
    }

    //cout << "coming into recursion" << endl;
    //cout << "value of query is " << (*query_it)->getTokensValue() << endl;
    /*string query_master;
    if (query_it != query_params.end() && schema_it != headings.end()){
        //cout << "went past if statement" << endl;
        //cout << "schema value is: " << (*schema_it)->getTokensValue() << endl;
        query_master = (*query_it)->getTokensValue();
        //cout << "got the token value for query master: " << query_master << endl;
        query_it++;
        schema_it++;
        cout << "beginning query master is: " << query_master << endl;
    }
    //else
        //cout << "something is wrong" << endl;
    while (query_it != query_params.end() && schema_it != headings.end()){
        if ((*query_it)->getTokensValue() == query_master){
            cout << "query master entered with value of: " << query_master << endl;
            //query_params.erase(query_it);
            query_it++;
            //list<Token*>::iterator temp = schema_it;
            cout << "query value after incrementing is now: " << (*query_it)->getTokensValue() << endl;
            cout << "schema value is still: " << (*schema_it)->getTokensValue() << endl;
            //headings.erase(schema_it);
            schema_it++;
            //if (schema_it == headings.end())
                //cout << "schema is at an end" << endl;
            //cout << "schema value is " << (*schema_it)->getTokensValue();
        }
        else if ((*query_it)->getTokenType() == STRING){
            cout << "entered the string part" << endl;
            cout << (*schema_it)->getTokensValue() << " is about to be erased" << endl;
            //list<Token*>::iterator temp = schema_it;
            
            //headings.erase(schema_it);
            //schema_it++;

            
            //query_params.erase(query_it);

            query_it++;
            //schema_it++;
            cout << "new value of schema is: " << (*schema_it)->getTokensValue() << endl;

        }
        else if (seen((*query_it)->getTokensValue())){
            query_it++;
            schema_it++;
        }
        else{//a new variable to check for has been found
            cout << "pushing back: " << (*query_it)->getTokensValue() << endl;
            dupes.push_back((*query_it)->getTokensValue());
            cout << "about to recurse" << endl;
            checkDupes(query_it, schema_it, query_params);
        }
    }
    cout << "returning with query master of: " << query_master << endl;*/
}

bool Schema::seen(string str){
    for (int i = 0; i < dupes.size(); i++){
        if (dupes[i] == str)
            return true;
    }
    return false;
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