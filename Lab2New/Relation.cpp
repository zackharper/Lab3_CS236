//RELATION.CPP

#include "Relation.h"

Relation::Relation(Scheme * data){
    vector<Token*> header_tokens = data->getTokens();
    name = header_tokens[0];//first token will be the id that is the name of the relation
    columns = new Schema(header_tokens);
}

Relation::~Relation(){
    //comment
}