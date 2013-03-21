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
    list<Token*>::iterator it;
    /*for (int i = 1; i < columns.size(); i++){
    	if (columns[i]->getTokenType() == ID)
    		headings.push_back(columns[i]);
    }*/
    //////////////////////////
    for (it = columns.begin(); it != columns.end(); it++){
        if ((*it)->getTokenType() == ID)
            headers.push_back(*it);
    }
    //heads = NULL;
}

Schema::~Schema(){
    headers.erase(headers.begin(),headers.end());
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
}

string Schema::toString(){
    string str = "(";
    for (int i = 0; i < headings.size(); i++){
        str += headings[i]->getTokensValue();
        if (i != headings.size() - 1)
            str += ",";
    }
    str += ")";
    return str;
}

list<Token*> Schema::getHeaders(){
	return headers;
}

void Schema::rename(Token * query_param_token, int rename_index){
    this->headings[rename_index] = query_param_token;
}

void Schema::project(vector<int> indices){
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
}

void Schema::destroy(int index){
    list<Token*>::iterator temp;
    for (temp = headers.begin(); temp != headers.end(); temp++){
        cout << "//////////" << (*temp)->getTokensValue() << endl;
    }
    //Token * temp = headings[index];
    //headings[index] = headings[headings.size() - 1];//swapping with the final element in order to pop the element to be deleted
    //headings.pop_back();
    for(int i =0; i < this->headings.size(); i++){
    
        
    }
    
    //delete temp;
}