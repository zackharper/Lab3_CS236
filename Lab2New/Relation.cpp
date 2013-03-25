#include "Relation.h"
#include <assert.h>

Relation::Relation(Scheme * data){
    
    this->name = new Token(data->getTokens()[0]->getTokensValue(), data->getTokens()[0]->getTokenType());
    this->columns = new Schema(data);
    
}

Relation::Relation(Relation * old_relation, Query * q){
    this->name = new Token(old_relation->getName()->getTokensValue(),old_relation->getName()->getTokenType());
    
    for (int i = 0; i < q->getPred()->getParams().size(); i++){
        this->query_params.push_back(new Token(q->getPred()->getParams()[i]->getTokens()[0]->getTokensValue(),q->getPred()->getParams()[i]->getTokens()[0]->getTokenType()));
    }
    
    this->columns = new Schema(old_relation->columns);
    
    this->select(old_relation);
    
    this->columns->listRename(query_params);
    
    bool id_found = hasId();
    if(id_found)
        this->startDuplicateCheck();
        
    this->project();
    
    if(id_found){
        for (list<Tuple*>::iterator tuple = rows_list.begin(); tuple != rows_list.end(); tuple++){
            clearDuplicates();
            list<Token*>::iterator query_it = query_params.begin();
            list<Token*>::iterator token_it = (*tuple)->token_list.begin();
            while ((*query_it)->getTokenType() != ID)
                query_it++;
            
            duplicate_values.push_back((*query_it)->getTokensValue());
            
            this->projectDuplicates(query_it, token_it, (*tuple));
        }
    }
}

Relation::~Relation(){
    delete name;
    delete columns;
    rows_list.erase(rows_list.begin(),rows_list.end());
}

void Relation::addTuple(Facts * new_tuple){
    rows_list.push_back(new Tuple(new_tuple));
}

string Relation::toString(){
    string str;
    if (rows_list.size() == 0)
        str = "No\n";
    else
        str += sortTuples();
    return str;
}

string Relation::sortTuples(){
    list<string> strings;
    for (list<Tuple*>::iterator tuple_it = rows_list.begin(); tuple_it != rows_list.end(); tuple_it++){
        string str;
        list<Token*>::iterator schema_it = columns->headings.begin();
        list<Token*>::iterator token_it = (*tuple_it)->token_list.begin();
        while (schema_it != columns->headings.end() && token_it != (*tuple_it)->token_list.end()){
            if (schema_it != columns->headings.begin())
                str += ", ";
            str += (*schema_it)->getTokensValue() + "=" + (*token_it)->getTokensValue();
            schema_it++;
            token_it++;
        }
        strings.push_back(str);
    }
    strings.sort();
    strings.unique();
    string output;
    output = "Yes(";
    int Number = strings.size();
    output += static_cast<ostringstream*>( &(ostringstream() << Number) )->str();;
    output += ")\n";
    for (list<string>::iterator str_it = strings.begin(); str_it != strings.end(); str_it++){
        if (*str_it != "")
            output += "  " + *str_it + "\n";
    }
    return output;
}

Token * Relation::getName(){
    return name;
}

///////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////

void Relation::select(Relation * old_relation ){
    for(list<Tuple*>::iterator it = old_relation->rows_list.begin(); it != old_relation->rows_list.end(); it++){
        if ((*it)->listSelect(query_params))
            this->rows_list.push_back(new Tuple(*it));
    }
}

void Relation::startDuplicateCheck(){
    for (list<Tuple*>::iterator tuple = rows_list.begin(); tuple != rows_list.end(); tuple++){
        list<Token*>::iterator tuple_tokens = (*tuple)->token_list.begin();
        list<Token*>::iterator query = query_params.begin();
        while ((*query)->getTokenType() != ID && query != query_params.end()){
            tuple_tokens++;
            query++;
        }
        duplicate_values.push_back((*query)->getTokensValue());//pushed back first ID
        if (!duplicates(query, tuple_tokens))
            rows_list.erase(tuple);
        clearDuplicates();
    }
}


//Soooooooo, a couple of these functions are really complicated. We tried for hours to implement one of them until we ofund an easier method that we coded up in 15 minutes. That code is in the function projectSchema(). The other functions used recursion in a very complicated method. Just pay attention to the projectSchema method.

bool Relation::duplicates(list<Token*>::iterator query_it, list<Token*>::iterator tuple_it){
    string query_master = (*query_it)->getTokensValue();
    string tuple_master = (*tuple_it)->getTokensValue();
    
    while (query_it != query_params.end()){
        if ((*query_it)->getTokensValue() == query_master){
            if ((*tuple_it)->getTokensValue() != tuple_master)
                return false;
            else{
                query_it++;
                tuple_it++;
            }
        }
        else if ((*query_it)->getTokenType() == STRING || already_seen((*query_it)->getTokensValue())){
            query_it++;
            tuple_it++;
        }
        else{//a new variable to check for has been found
            duplicate_values.push_back((*query_it)->getTokensValue());
            if (!duplicates(query_it, tuple_it))//if the other recursive calls are all true, this current recursion will finish checking this variable of the query
                return false;            
        }
    }
    return true;
}

void Relation::project(){
    
    /*cout << "query is currently: ";
    for (list<Token*>::iterator it = query_params.begin(); it != query_params.end(); it++)
        cout << (*it)->getTokensValue() << " ";
    cout << endl << endl;*/
    
    projectSchema();
    
    /*cout << "schema is now: ";
    for (list<Token*>::iterator it = columns->headings.begin(); it != columns->headings.end(); it++)
        cout << (*it)->getTokensValue() << " ";
    cout << endl;*/
    
    clearDuplicates();
    
    for (list<Tuple*>::iterator it = this->rows_list.begin(); it != this->rows_list.end(); it++)
        (*it)->project(query_params);
    
}

void Relation::projectSchema(){
    list<Token*>::iterator s = columns->headings.begin();
    list<Token*>::iterator q = query_params.begin();
    while (q != query_params.end() && s != columns->headings.end()) {
        if ((*q)->getTokenType() == STRING || already_seen((*q)->getTokensValue())) 
            (*s)->setTokenType(COLON);
        else
            duplicate_values.push_back((*q)->getTokensValue());
        q++;
        s++;
    }
    s--;
    while (s != columns->headings.begin()) {
        if ((*s)->getTokenType() == COLON) 
            columns->headings.erase(s);
        s--;
    }
    if ((*s)->getTokenType() == COLON)
        columns->headings.erase(s);
}


void Relation::projectDuplicates(list<Token*>::iterator query_it, list<Token*>::iterator tuple_it, Tuple * current_tuple){
    string query_master;
    if (query_it != query_params.end()){
        query_master = (*query_it)->getTokensValue();
        query_it++;
        tuple_it++;
    }
    while (query_it != query_params.end() && tuple_it != current_tuple->token_list.end()){
        
        if ((*query_it)->getTokensValue() == query_master){
            query_it++;
            current_tuple->token_list.erase(tuple_it);
            tuple_it++;
        }
        else if ((*query_it)->getTokenType() == STRING)
            query_it++;
        else if (already_seen((*query_it)->getTokensValue())){
            query_it++;
            tuple_it++;
        }
        else{//a new variable to check for has been found
            duplicate_values.push_back((*query_it)->getTokensValue());
            projectDuplicates(query_it, tuple_it, current_tuple);
        }
    }    
}

//////////////////////////OTHER PRIVATE FUNCTIONS

bool Relation::already_seen(string check){
    for (int i = 0; i < duplicate_values.size(); i++){
        if (duplicate_values[i] == check)
            return true;
    }
    return false;
}

bool Relation::hasId(){
    for (list<Token*>::iterator it = query_params.begin(); it != query_params.end(); it++){
        if ((*it)->getTokenType() == ID)
            return true;
    }
    return false;
}

void Relation::clearDuplicates(){
    for (int i = duplicate_values.size() - 1; i >= 0; i--)
        duplicate_values.pop_back();
}