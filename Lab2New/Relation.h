//THIS IS RELATION .H YO!

#ifndef __Lab2New__Relation__
#define __Lab2New__Relation__

#include <iostream>
#include "Schema.h"
#include "Tuple.h"

class Relation {
public:
    Relation(Scheme*);
    Relation(Relation*, Query*);
    ~Relation();
    void addTuple(Facts*);
    string toString();
    void select(Relation*);
    void rename();
    void project(vector<int>);
    
    Token * getName();
    Schema * getColumns();
    list<Tuple*> getRows();
    void printVect(list<Token*> vect);
private:
	Token * name;
    Schema * columns;
    list<Tuple*> rows;
    list<Token*> query_params;
    vector<int> id_vec;
    vector<int> str_vec;
    
    list<Tuple*> rows_list;
    
};

#endif /* defined(__Lab2New__Relation__) */
