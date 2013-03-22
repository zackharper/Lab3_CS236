//THIS IS RELATION .H YO!

#ifndef __Lab2New__Relation__
#define __Lab2New__Relation__

#include <iostream>
#include <sstream>
#include "Schema.h"
#include "Tuple.h"

class Relation {
public:
    Relation(Scheme*);
    Relation(Relation*, Query*);
    ~Relation();
    void addTuple(Facts*);
    string toString();
    string sortTuples();
    void select(Relation*);
    void rename();
    void project();
    
    Token * getName();
    Schema * getColumns();
    vector<Tuple*> getRows();
    list<Tuple*> getRowsList();
    void printVect(list<Token*> vect);
    list<Tuple*> rows_list;
    Schema * columns;

private:
	Token * name;
    //vector<Tuple*> rows;
    list<Token*> query_params;
    //vector<int> id_vec;
    //vector<int> str_vec;
    
    
};

#endif /* defined(__Lab2New__Relation__) */
