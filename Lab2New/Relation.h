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
    Token * getName();
    
    list<Tuple*> rows_list;
    Schema * columns;

private:
	Token * name;
    list<Token*> query_params;
    vector<string> duplicate_values;
    
    void select(Relation*);
    void startDuplicateCheck();
    void projectDuplicates(list<Token*>::iterator, list<Token*>::iterator, Tuple*);
    
    void project();
    void projectSchema(list<Token*>::iterator, list<Token*>::iterator);

    bool duplicates(list<Token*>::iterator, list<Token*>::iterator);

    bool already_seen(string);
    bool hasId();
    void clearDuplicates();
};

#endif /* defined(__Lab2New__Relation__) */
