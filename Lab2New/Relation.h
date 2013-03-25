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
    void projectDuplicates(list<Token*>::iterator, list<Token*>::iterator, Tuple*);
    void rename();
    void project(Relation*, Query*);
    void deleteSchemaStrings();
    void projectSchema(list<Token*>::iterator, list<Token*>::iterator);
    
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
    bool hasId();
    void clearDuplicates();
    //vector<int> str_vec;
    void clearQueryParams(Relation*, Query*);
    
    
};

#endif /* defined(__Lab2New__Relation__) */
