#include "Relation.h"
#include <assert.h>

Relation::Relation(Scheme * data){
    
    list<Token*> header_tokens;//(data->getTokens().begin(),data->getTokens().end()); //= data->getTokens();//wait...do i need to copy each token? or is this done automatically?
    for (int i = 1; i < data->getTokens().size(); i++){
        //cout << "R3lation i is: " << i << " tostring:" << data->toString() << endl;
        header_tokens.push_back(data->getTokens()[i]);
    }
    //printVect(header_tokens);
    
//DEBUGGING OUTPUT 
    //printVect(header_tokens);
    //cout << "exited for lop relation" << endl;
    //name = header_tokens[0];//first token will be the id that is the name of the relation. should we check for invalid first tokens? probably not, because it will have been checked for when parsing
    this->name = new Token(data->getTokens()[0]->getTokensValue());
    this->columns = new Schema(header_tokens);
    /*cout << "schema for " << name->getTokensValue() << " is: ";
    for (int i = 0; i < columns->getHeadings().size(); i++)
        cout << columns->getHeadings()[i]->getTokensValue() << ",";
    cout << endl;*/
}

Relation::Relation(Relation * old_relation, Query * q){
    this->name = new Token(old_relation->getName()->getTokensValue());
    
        
    for (int i = 0; i < q->getPred()->getParams().size(); i++){
        //if (q->getPred()->getParams()[i]->getTokens()[0]->getTokenType() == ID)
           // id_vec.push_back(i);//by pushing back the index, we can track which indices of the facts and queries must match exactly when SELECTING
        //else//the token will be a STRING
            //str_vec.push_back(i);
        this->query_params.push_back(new Token(q->getPred()->getParams()[i]->getTokens()[0]->getTokensValue()));//do we need to make NEW tokens for the query parameters?
    }
    
    this->columns = new Schema(old_relation->columns);
    //cout << "SIZE OF ID VEC IS: " << id_vec.size() << endl;
    //cout << "SIZE OF STR_VEC IS: " << str_vec.size() << endl;
    /*list<Token*>::iterator it;
    cout << "QUERY PARAMETER LIST: ";
    for (it = query_params.begin(); it != query_params.end(); it++)
        cout << (*it)->getTokensValue();
    cout << endl;*/
    //printVect(query_params);
    this->select(old_relation);
    
    //RENAME
    /*
     if old schema == new schema do not rename
     USE ID VECT.
     
     */
    this->columns->listRename(query_params);
    bool id_found = hasId();
    if(id_found)
        this->startDuplicateCheck();
    
    this->project();
    
    
    if(id_found){
        for (list<Tuple*>::iterator tuple = rows_list.begin(); tuple != rows_list.end(); tuple++){
            clearDuplicates();
            list<Token*>::iterator query_it = query_params.begin();
            list<Token*>::iterator schema_it = columns->headings.begin();
            list<Token*>::iterator token_it = (*tuple)->token_list.begin();
            while ((*query_it)->getTokenType() != ID){
                query_it++;
                schema_it++;
            }
            duplicate_values.push_back((*query_it)->getTokensValue());
            
            //cout << "current query pointed to is: " << (*query_it)->getTokensValue() << endl;
            this->projectDuplicates(query_it, token_it, schema_it, (*tuple));
            cout << "going to start new loop" << endl;
            query_params.erase(query_params.begin(),query_params.end());
            for (int i = 0; i < q->getPred()->getParams().size(); i++)
                this->query_params.push_back(new Token(q->getPred()->getParams()[i]->getTokens()[0]->getTokensValue()));
        }
    }
    
    //this->columns->project(str_vec);
    
    /*cout << "New " << name->getTokensValue() << " relation after selection:\n";
    for (int i = 0; i < rows.size(); i++)
        printVect(this->rows[i]->getTokens());
    cout << "\tNew headings are: ";
    for (int i = 0; i < columns->getHeadings().size(); i++){
        cout << columns->getHeadings()[i]->getTokensValue();
    }
    cout << endl;*/
    
}

bool Relation::hasId(){
    for (list<Token*>::iterator it = query_params.begin(); it != query_params.end(); it++){
        if ((*it)->getTokenType() == ID)
            return true;
    }
    return false;
}

Relation::~Relation(){
    delete name;///////////////////////for some reason deleting specifically the name (just the name) causes a segfault
    delete columns;
    rows_list.erase(rows_list.begin(),rows_list.end());
}

void Relation::addTuple(Facts * new_tuple){
    //check if tuple exists already????; push back new tuple
    //Tuple * tuple = new Tuple(new_tuple);
    /*for (int i = 0; i < rows.size(); i++){
        if (
    }
    for (int i = 0; i < tuple->getTokens().size(); i++)
        cout << tuple->getTokens()[i]->getTokensValue() << ",";
    cout << endl;*/
    //rows.push_back(tuple);
    rows_list.push_back(new Tuple(new_tuple));
    //cout << "tuple just added: ";
    //tuple->printTokenList();
    //cout << endl;
    //cout << "ROW BEING PUSHED BACK INTO RELATION " << name->getTokensValue() << ": ";
    //tuple->printTokenList();
}

string Relation::toString(){
    //cout << "name of relation is : " << name->getTokensValue() << endl;
    string str;
    //cout << "size of list is: " << rows_list.size();
    if (rows_list.size() == 0)
        str = "No\n";
    else{
        
        str += sortTuples();
        //cout << str << endl;
        /*
        vector<Token*> sorted;
        for(list<Tuple*>::iterator tuple_it = rows_list.begin(); tuple_it != rows_list.end(); tuple_it++){
            sorted.push_back(*tuple_it);
        }
        for (list<Tuple*>::iterator tuple_it = rows_list.begin(); tuple_it != rows_list.end(); tuple_it++){
            list<Token*>::iterator schema_it = columns->headings.begin();
            list<Token*>::iterator token_it = (*tuple_it)->token_list.begin();
            str += "\n  ";
            while (schema_it != columns->headings.end() && token_it != (*tuple_it)->token_list.end()){
                str += (*schema_it)->getTokensValue() + "=" + (*token_it)->getTokensValue();
            }
        }*/
    }
    return str;
}

string Relation::sortTuples(){
    list<string> strings;
    for (list<Tuple*>::iterator tuple_it = rows_list.begin(); tuple_it != rows_list.end(); tuple_it++){
        string str;
        list<Token*>::iterator schema_it = columns->headings.begin();
        list<Token*>::iterator token_it = (*tuple_it)->token_list.begin();
        //str += "\n  ";
        while (schema_it != columns->headings.end() && token_it != (*tuple_it)->token_list.end()){
            if (schema_it != columns->headings.begin())
                str += ", ";
            str += (*schema_it)->getTokensValue() + "=" + (*token_it)->getTokensValue();
            schema_it++;
            token_it++;
        }
        //cout << "tuple string: " << str;
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

void Relation::select(Relation * old_relation ){
    //where there is a String in query_param that matches the DB, advance.
    
    /*for(list<Tuple*>::iterator it = old_relation->getRows().begin(); it != old_relation->getRows().end(); it++){
        list<Token*> row = (*it)->getTokens();
        list<Token*>::iterator row_it;
        for(row_it = row.begin(); row_it != row.end(); row_it++){
        
            cout << "BOOOOOM:::::::::::" << (*row_it)->getTokensValue() << endl;
        }
        
    }
     */
    
    /*///////////////////////OLD STUFF THAT WE SHOULD KEEP
    for (int i = 0; i < old_relation->getRows().size(); i++){
        if (old_relation->getRows()[i]->select(query_params))
            this->rows.push_back(old_relation->getRows()[i]);
    }*/
    
    //cout << "entering the dreaded loop" << endl;
    //cout << "size of row list is: " << this->rows_list.size() << endl;
    //cout << "size of old row list is: " << old_relation->rows_list.size() << endl;
    for(list<Tuple*>::iterator it = old_relation->rows_list.begin(); it != old_relation->rows_list.end(); it++){
        if ((*it)->listSelect(query_params))
            this->rows_list.push_back(new Tuple(*it));
    }
    /*cout << "NEW ROWS ARE: " << endl;
    for (list<Tuple*>::iterator it = this->rows_list.begin(); it != this->rows_list.end(); it++){
        (*it)->printTokenList();
        cout << endl;
    }*/
}

void Relation::startDuplicateCheck(){
    for (list<Tuple*>::iterator tuple = rows_list.begin(); tuple != rows_list.end(); tuple++){
        list<Token*>::iterator tuple_tokens = (*tuple)->token_list.begin();
        list<Token*>::iterator query = query_params.begin();
        while ((*query)->getTokenType() != ID){
            tuple_tokens++;
            query++;
        }
        duplicate_values.push_back((*query)->getTokensValue());
        /*cout << "CURRENT SCHEMA TO BE CHECKED IS: ";
        for (list<Token*>::iterator it = columns->headings.begin(); it != columns->headings.end(); it++)
            cout << (*it)->getTokensValue() + ", ";
        cout << "\n\t";*/
        //cout << "QUERY VAL AND TUPLE VAL" << (*query)->getTokensValue() << "\t tuple:\t"<< (*tuple_tokens)->getTokensValue() << endl;
        if (!duplicates(query, tuple_tokens)){
            //cout << "+++++++++++about to delete the tule:" ;
            //(*tuple)->printTokenList();
            //cout << endl;
            rows_list.erase(tuple);
        }
        clearDuplicates();
    }
}

void Relation::clearDuplicates(){
    for (int i = duplicate_values.size() - 1; i >= 0; i--)
        duplicate_values.pop_back();
}

bool Relation::duplicates(list<Token*>::iterator query_it, list<Token*>::iterator tuple_it){
    string query_master = (*query_it)->getTokensValue();
    string tuple_master = (*tuple_it)->getTokensValue();
    //cout << "query master is: " << query_master << endl << "tuple master is: " << tuple_master << endl;
    /*cout << "value in query_it when iterating through: ";
    for (query_it; query_it != query_params.end(); query_it++)
        cout << (*query_it)->getTokensValue() << ", ";
    cout << endl;*/
    while (query_it != query_params.end()){
        //cout << "+++++++++++++STARTIG WHILE WITH: " << (*query_it)->getTokensValue() << endl;

        //cout << "query_it value is currently: " << (*query_it)->getTokensValue() << endl;
        if ((*query_it)->getTokensValue() == query_master){
            if ((*tuple_it)->getTokensValue() != tuple_master){
                //cout << "+++++++++++++++++++++++RETURNING FALSE1" << (*query_it)->getTokensValue() << endl;
                return false;
                //break;
            }
            else{
                //cout << "compared with itself: " << (*query_it)->getTokensValue() << "\t" << (*tuple_it)->getTokensValue() << endl;
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
            if (!duplicates(query_it, tuple_it)){//if the other recursive calls are all true, this current recursion will finish checking this variable of the query
                //cout << "+++++++++++++++++++++++RETURNING FALSE2" << (*query_it)->getTokensValue() << endl;

                return false;
            }// break;
            
        }
    }
    //cout << "+++++++++++++++++++++++RETURNING TRUE" << endl;

    return true;
}

bool Relation::already_seen(string check){
    for (int i = 0; i < duplicate_values.size(); i++){
        if (duplicate_values[i] == check)
            return true;
    }
    return false;
}

void Relation::rename(){
    /*for(int i=0; i < id_vec.size(); i++){
        //this->columns->getHeaders()[ id_vec[i] ] = query_params[ id_vec[i]];
        
        //columns->rename(query_params[ id_vec[i] ], id_vec[i]);
        
    }
    cout << "SIZE OF HEADERS ARE: " << columns->getHeaders().size() << endl;
    for (int i = 0; i < columns->getHeaders().size(); i++){
        cout << this->columns->getHeaders()[i]->getTokensValue();
    }
    cout << endl;*/
    
}

void Relation::project(){
    /*
    for (int c = 0; c < rows.size(); c++){
        for (int i = 0; i < indices.size(); i++)
            rows[c]->getTokens()[indices[i]]->setTokenType(COLON);//COLON is a dummy token type that tells us where to delete the items
        
        rows[c]->destroy();
    }*/
    columns->project(query_params);
    for (list<Tuple*>::iterator it = this->rows_list.begin(); it != this->rows_list.end(); it++)
        (*it)->project(query_params);
    
}

void Relation::projectDuplicates(list<Token*>::iterator query_it, list<Token*>::iterator tuple_it, list<Token*>::iterator schema_it, Tuple * current_tuple){
    //cout << "final projection" << endl;
    /*cout << "duplicate vector has: ";
    for (int i = 0; i < duplicate_values.size(); i++)
        cout << duplicate_values[i];
    cout << endl;
    
    string query_master;
    cout << "value in query_it when iterating through: ";
    for (list<Token*>::iterator it = query_it; it != query_params.end(); it++)
         cout << (*it)->getTokensValue() << ", ";
    cout << endl;
    //int size = duplicate_values.size();
    //cout << "top of duplicate vector is: " << duplicate_values[size - 1];
    if (query_it != query_params.end()){
        query_master = (*query_it)->getTokensValue();
        query_it++;
        //schema_it++;
        tuple_it++;
    
        //cout << "query it is currently at: " << (*query_it)->getTokensValue() << endl;
        //cout << "query master is: " << query_master << endl;
    }
    
    if (query_it == query_params.end())
        cout << "REACHED THE END NIGGAS" << endl;
    while (query_it != query_params.end()){

        cout << "query master IN THE LOOP is " << query_master << endl;
        cout << "query_it value IN THE LOOP is currently: " << (*query_it)->getTokensValue() << endl;
        cout << "tuple_it value IN THE LOOP is currently: " << (*tuple_it)->getTokensValue() << endl << endl;
        if ((*query_it)->getTokensValue() == query_master){
            cout << "about to erase: " << (*tuple_it)->getTokensValue() << endl;
            //query_it++;
            //cout << "next value of query_it is: " << (*query_it)->getTokensValue() << endl;
            query_params.erase(query_it);
            cout << "value of query_it after erasing: " << (*query_it)->getTokensValue() << endl;
            //columns->headings.erase(schema_it);
            current_tuple->token_list.erase(tuple_it);
            query_it++;
            tuple_it++;
            //assert(query_it == query_params.end());
            //schema_it++;
        }
        else if ((*query_it)->getTokenType() == STRING){
            //columns->headings.erase(schema_it);
            //query_params.erase(query_it);
            query_it++;
            //tuple_it++;
            //schema_it++;//don't include the tuple because all strings have already been projected out
        }
        else if (already_seen((*query_it)->getTokensValue())){
            query_it++;
            //schema_it++;
            tuple_it++;
        }
        else{//a new variable to check for has been found
            cout << "pushing back: " << (*query_it)->getTokensValue() << endl;
            duplicate_values.push_back((*query_it)->getTokensValue());
            projectDuplicates(query_it, tuple_it, schema_it, current_tuple);//if the other recursive calls are all true, this current recursion will finish checking this variable of the query
                //return false;
        }
    }
    //return true;*/
    string query_master;
    if (query_it != query_params.end()){
        query_master = (*query_it)->getTokensValue();
        query_it++;
        tuple_it++;
    }
    while (query_it != query_params.end()){
        
        if ((*query_it)->getTokensValue() == query_master){
            query_params.erase(query_it);
            query_it++;
            current_tuple->token_list.erase(tuple_it);
            tuple_it++;
        }
        else if ((*query_it)->getTokenType() == STRING){
            query_params.erase(query_it);
            query_it++;
        }
        else if (already_seen((*query_it)->getTokensValue())){
            query_it++;
            tuple_it++;
        }
        else{//a new variable to check for has been found
            duplicate_values.push_back((*query_it)->getTokensValue());
            projectDuplicates(query_it, tuple_it, schema_it, current_tuple);
        }
    }    
}

/*vector<Tuple*> Relation::getRows(){
    return rows;
}*/

list<Tuple*> Relation::getRowsList(){
    return rows_list;
}

Token * Relation::getName(){
    return name;
}

Schema * Relation::getColumns(){
    return columns;
}

void Relation::printVect(list<Token*> vect){
    list<Token*>::iterator it = vect.begin();
    for(it; it != vect.end(); it++){
        cout << (*it)->getTokensValue();
    }
    cout << endl;
}