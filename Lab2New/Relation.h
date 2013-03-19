//THIS IS RELATION .H YO!

#ifndef __Lab2New__Relation__
#define __Lab2New__Relation__

#include <iostream>
#include "Schema.h"
#include "Tuple.h"

class Relation {
public:
    Relation(Scheme*);
    ~Relation();
    void addTuple(Facts*);
    
    Token * getName();
    Schema * getColumns();
private:
	Token * name;
    Schema * columns;
    vector<Tuple*> rows;
};

#endif /* defined(__Lab2New__Relation__) */