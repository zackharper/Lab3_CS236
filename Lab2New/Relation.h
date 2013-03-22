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
    bool duplicates(list<Token*>::iterator, list<Token*>::iterator);
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
    vector<int> id_vec;
    //vector<vector<int>> duplicate_vec;
    vector<string> duplicate_values;
    void startDuplicateCheck();
    bool already_seen(string);
    //vector<int> str_vec;
    
    
};

#endif /* defined(__Lab2New__Relation__) */
