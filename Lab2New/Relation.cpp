//RELATION.CPP

#include "Relation.h"

Relation::Relation(Scheme * data){
    vector<Token*> header_tokens = data->getTokens();
    name = header_tokens[0];//first token will be the id that is the name of the relation. should we check for invalid first tokens? probably not, because it will have been checked for when parsing
    columns = new Schema(header_tokens);
}

Relation::~Relation(){
    delete name;
    delete columns;
    for (int i = 0; i < rows.size(); i++)
        delete rows[i];
}