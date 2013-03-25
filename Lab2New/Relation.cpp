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
        while ((*query)->getTokenType() != ID){
            tuple_tokens++;
            query++;
        }
        duplicate_values.push_back((*query)->getTokensValue());//pushed back first ID
        if (!duplicates(query, tuple_tokens))
            rows_list.erase(tuple);
        clearDuplicates();
    }
}


/*THREE FUNCTIONS (duplicates,project_schema, and project_duplicates) ARE ALL VERY SIMILAR, WITH MINOR TWEAKS IN EACH FUNCTION TO ALLOW FOR OTHER INPUTS. The algorithm is as follows:
 starting at the first ID, make a master query string from the current ID pointed to. At the next character in the query:
 if the current token pointed by the query iterator is equal to the master string
    process the duplicate value within the SCHEMA or TUPLE (not the query), mostly by erasing
    increment the iterators
 else if token pointed to is a STRING type
    erase and/or simply increment (depening on the function)
 else if the token is a different variable that has already been seen (this is known by checking a vector of strings to compare the current token to the strings in the vector)
    simply increment
 else //the current token is an unseen ID type which must also be checked for duplicate values within the query
    push back the value into the duplicate value vector, which will tell other recursive calls that we have processed, or are currently processing that value as a duplicate
    recursively call the duplicate function, using the current token value as a new query master
 */
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
    projectSchema(query_params.begin(), columns->headings.begin());
    clearDuplicates();
    
    for (list<Tuple*>::iterator it = this->rows_list.begin(); it != this->rows_list.end(); it++)
        (*it)->project(query_params);
    
}

void Relation::projectSchema(list<Token*>::iterator query_it, list<Token*>::iterator schema_it){
    string query_master;
    if (query_it != query_params.end() && (*query_it)->getTokenType() == ID && schema_it != columns->headings.end()){
        query_master = (*query_it)->getTokensValue();
        query_it++;
        schema_it++;
    }
    while (query_it != query_params.end() && schema_it != columns->headings.end()){
        if ((*query_it)->getTokenType() == STRING || (*query_it)->getTokensValue() == query_master){
            query_it++;
            columns->headings.erase(schema_it);
            if (query_it != query_params.end())
                schema_it++;
        }
        
        else if (already_seen((*query_it)->getTokensValue())){
            query_it++;
            if (query_it != query_params.end())
                schema_it++;
        }
        else{//a new variable to check for has been found
            duplicate_values.push_back((*query_it)->getTokensValue());
            projectSchema(query_it, schema_it);
        }
    }
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