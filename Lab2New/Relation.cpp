#include "Relation.h"

Relation::Relation(Scheme * data){
    vector<Token*> header_tokens;//(data->getTokens().begin(),data->getTokens().end()); //= data->getTokens();//wait...do i need to copy each token? or is this done automatically?
    for (int i = 0; i < data->getTokens().size(); i++){
        //cout << "R3lation i is: " << i << " tostring:" << data->toString() << endl;
        header_tokens.push_back(data->getTokens()[i]);
    }
//DEBUGGING OUTPUT 
    //printVect(header_tokens);
    //cout << "exited for lop relation" << endl;
    name = header_tokens[0];//first token will be the id that is the name of the relation. should we check for invalid first tokens? probably not, because it will have been checked for when parsing
    columns = new Schema(header_tokens);
    /*cout << "schema for " << name->getTokensValue() << " is: ";
    for (int i = 0; i < columns->getHeadings().size(); i++)
        cout << columns->getHeadings()[i]->getTokensValue() << ",";
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
}

string Relation::toString(){
    string str = name->getTokensValue() + columns->toString();
}

vector<Tuple*> Relation::getRows(){
    return rows;
}

Token * Relation::getName(){
    return name;
}

Schema * Relation::getColumns(){
    return columns;
}

void Relation::printVect(vector<Token*> vect){
    for(int i=0; i < vect.size(); i++){
        cout << vect[i]->getTokensValue() << endl;
    }

}