#include "Relation.h"

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
    this->name = data->getTokens()[0];
    this->columns = new Schema(header_tokens);
    /*cout << "schema for " << name->getTokensValue() << " is: ";
    for (int i = 0; i < columns->getHeadings().size(); i++)
        cout << columns->getHeadings()[i]->getTokensValue() << ",";
    cout << endl;*/
}

Relation::Relation(Relation * old_relation, Query * q){
    this->name = old_relation->getName();
    this->columns = old_relation->getColumns();////////////////WILL THIS PERMANENTLY RENAME THE SCHEMA OF THE ORIGINAL RELATION WHEN RENAMING?
        
    for (int i = 0; i < q->getPred()->getParams().size(); i++){
        /*if (q->getPred()->getParams()[i]->getTokens()[0]->getTokenType() == ID)
            id_vec.push_back(i);//by pushing back the index, we can track which indices of the facts and queries must match exactly when SELECTING
        else//the token will be a STRING
            str_vec.push_back(i);*/
        this->query_params.push_back(q->getPred()->getParams()[i]->getTokens()[0]);//because there aren't any expressions within these queries, index 0 will only have an ID or a string.
    }
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
    this->rename();
    
    //this->project(str_vec);
    
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

Relation::~Relation(){
    
    /*delete name;
    delete columns;
    Tuple * temp = NULL;
    for (int i = rows.size() - 1; i >= 0; i--){
        temp = rows[i];
        rows.pop_back();
        delete temp;
        temp = NULL;
    }*/
}

void Relation::addTuple(Facts * new_tuple){
    //check if tuple exists already????; push back new tuple
    Tuple * tuple = new Tuple(new_tuple);
    /*for (int i = 0; i < rows.size(); i++){
        if (
    }
    for (int i = 0; i < tuple->getTokens().size(); i++)
        cout << tuple->getTokens()[i]->getTokensValue() << ",";
    cout << endl;*/
    rows.push_back(tuple);
    cout << "ROW BEING PUSHED BACK INTO RELATION " << name->getTokensValue() << ": ";
    tuple->printTokenList();
}

string Relation::toString(){
    string str = name->getTokensValue() + columns->toString();
}

void Relation::select(Relation * old_relation ){
    list<Tuple*>::iterator it;
    //vector<Tuple*> new_tuples;
    cout << "size of first row: " << old_relation->getRows().size() << endl;
    for (it = old_relation->getRows().begin(); it != old_relation->getRows().end(); it++){
        //cout << "current size of row value is: ";
        //cout << (*it)->getTokens().size() << endl;
        //for (int i = 0; i < (*it)->getTokens().size(); i++){
            //cout << (*it)->getTokens()
        cout << "entered relation loop, old rel size:" << old_relation->getRows().size() << this->getRows().size()<< endl;
        
        list<Tuple*>::iterator it2, it3;
        cout << "name of old relation: " << old_relation->getName()->getTokensValue() << endl;
        it2 = old_relation->getRows().end();
        it3 = old_relation->getRows().begin();
        it2--;
        (*it3)->printTokenList();
        (*it2)->printTokenList();
        for(it2 = old_relation->getRows().begin(); it2 != old_relation->getRows().end(); it2++){
        
            cout << ";;;;;;;; tuple:" ;
            (*it2)->printTokenList();
            cout << endl << endl;
        }
        
        //for(it )
        if ((*it)->select(query_params))
            rows.push_back(*it);
        
        
        /*for (int j = 0; j < str_vec.size(); j++){
//K. Try and top this for weirdest line of code ever: ftw. #YOLO
            if (old_relation->getRows()[i]->getTokens()[this->str_vec[j]]->getTokensValue() != this->query_params[this->str_vec[j]]->getTokensValue())
                break;
            if (j == str_vec.size() - 1)//all possible strings will have been tested already.
                rows.push_back(old_relation->getRows()[i]);
        }*/
    }
    
    /*
    cout << "Queries are: ";
    printVect(query_params);
    for (int i = 0; i < rows.size(); i++){
        cout << "\tPRINTING SELECTED LIST: ";

        printVect(rows[i]->getTokens());
    }
     */
    //return new_tuples;
}

void Relation::rename(){
    for(int i=0; i < id_vec.size(); i++){
        //columns->getHeadings()[ id_vec[i] ] = query_params[ id_vec[i]];
        
        //columns->rename(query_params[ id_vec[i] ], id_vec[i]);
        
    }
}
void Relation::project(vector<int> indices){
    /*
    for (int c = 0; c < rows.size(); c++){
        for (int i = 0; i < indices.size(); i++)
            rows[c]->getTokens()[indices[i]]->setTokenType(COLON);//COLON is a dummy token type that tells us where to delete the items
        for (int i = 0; i < rows[c]->getTokens().size(); i++){
            if (rows[c]->getTokens()[i]->getTokenType() == COLON){
                //destroy(i);
                for(int j = i; j < rows[c]->getTokens().size(); j++){
                    //if(j != (rows[c]->getTokens().size() - 1))//NEED TO MAKE A FUNCTION IN TUPLE THAT ALLOWS ME TO CHANGE THE TUPLE VALUES
                        //headings[j] = headings[j+1];
                }
                //headings.pop_back(); //deletes last element which should be a :
                i = 0;//we need to start the loop over because the vector has changed
            }
        }
    }*/
}

list<Tuple*> Relation::getRows(){
    return rows;
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