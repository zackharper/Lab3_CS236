//RELATION.CPP

#include "Relation.h"

Relation::Relation(Scheme * data){
    vector<Token*> header_tokens = data->getTokens();//wait...do i need to copy each token? or is this done automatically?
    name = header_tokens[0];//first token will be the id that is the name of the relation. should we check for invalid first tokens? probably not, because it will have been checked for when parsing
    columns = new Schema(header_tokens);
}

Relation::~Relation(){
    delete name;
    delete columns;
    for (int i = 0; i < rows.size(); i++)
        delete rows[i];
}

void Relation::addTuple(Facts * new_tuple){
    //check if tuple exists already????; push back new tuple
    Tuple * tuple = new Tuple(new_tuple);
    /*for (int i = 0; i < rows.size(); i++){
        if (
    }*/
    rows.push_back(tuple);
}


Token * Relation::getName(){
    return name;
}

Schema * Relation::getColumns(){
    return columns;
}