#include "Lex.h"

#include "Input.h"
#include "TokenType.h"
#include "Utils.h"
#include "DataLog.h"
#include "Database.h"
#include <iostream>
#include <ctype.h>

using namespace std;

Lex::Lex() {
    failure = NULL;
	input = new Input();
    generateTokens(input);
}

Lex::Lex(const char* filename) {
    failure = NULL;
    input = new Input(filename);
    generateTokens(input);
}

Lex::Lex(istream& istream) {
    failure = NULL;
    input = new Input(istream);
    generateTokens(input);
}

Lex::Lex(const Lex& lex) {
    failure = NULL;
    input = new Input(*lex.input);
    tokens = new vector<Token*>();
    
    vector<Token*>::iterator iter;
    for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
        Token* newToken = new Token(**iter);
        tokens->push_back(newToken);
    }
    
    index = lex.index;
    state = lex.state;
}

Lex::~Lex(){
    /*for (int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
    }
    delete tokens;
    delete input;*/
}

bool Lex::operator==(const Lex& lex) {
    bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
    if(result) {
        vector<Token*>::iterator iter1;
        vector<Token*>::iterator iter2;
        iter1 = tokens->begin();
        iter2 = lex.tokens->begin();
        while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
            result = **iter1 == **iter2;
            iter1++;
            iter2++;
        }
        result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
    }
    return result;
}

string Lex::toString() const {
    int count = 0;
    string result;
    while(count < tokens->size()) {
        Token* token = (*tokens)[count];
        result += token->toString();
        count++;
    }
    result += "Total Tokens = ";
    string countToString;
    result += itoa(countToString, count);
    result += "\n";
    return result;
}

void Lex::generateTokens(Input* input) {
    tokens = new vector<Token*>();
    index = 0;
    
    state = Start;
    
    while(state != End) {
        state = nextState();
    }
    emit(END);
}

Token* Lex::getCurrentToken() {
    return (*tokens)[index];
}

void Lex::advance() {
    index++;
}

void Lex::parseAdvance(){
    advance();
    while (getCurrentToken()->getTokenType() == COMMENT)
        advance();
}

void Lex::commentAdvance(){
    while (getCurrentToken()->getTokenType() == COMMENT)
        advance();
}

bool Lex::hasNext() {
    return index < tokens->size();
}

State Lex::nextState() {
    State result;
    char character;
    switch(state) {
        case Start:               result = getNextState(); break;
        case Comma:               emit(COMMA); result = getNextState(); break;
        case Period:              emit(PERIOD); result = getNextState(); break;
        case Q_mark:              emit(Q_MARK); result = getNextState(); break;
        case Left_Paren:          emit(LEFT_PAREN); result = getNextState(); break;
        case Right_Paren:         emit(RIGHT_PAREN); result = getNextState(); break;
        case Multiply:            emit(MULTIPLY); result = getNextState(); break;
        case Add:                 emit(ADD); result = getNextState(); break;
        case SawColon:
            character = input->getCurrentCharacter();
            if(character == '-') {
                result = Colon_Dash;
                input->advance();
            } else { //Every other character
                //throw "ERROR:: in case SawColon:, Expecting  '-' but found " + character + '.';
                emit(COLON);
                result = getNextState();
            }
            break;
        case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
        case SawAQuote:
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case ProcessingString:
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case PossibleEndOfString:
            if(input->getCurrentCharacter() == '\'') {
                input->advance();
                result = ProcessingString;
            } else { //Every other character
                emit(STRING);
                result = getNextState();
            }
            break;
        case CommentBegin:
            character = input->getCurrentCharacter();
            if (character == '|')//do an && tolken value == "#"
                result = MultiLine;
            else if (character == '\n' || character == -1){//EOF or EOL
                emit(COMMENT);
                result = getNextState();
            }
            else
                result = SingleLine;
            break;
        case MultiLine:
            character = input->getCurrentCharacter();
            if (character == '|')
                result = CommentEnd;
            else if(character == -1){
                result = Undefined;
            }
            else{
                input->advance();
                result = MultiLine;
            }
            break;
        case CommentEnd:
            character = input->getCurrentCharacter();
            //cout << "VALUE IS: " << input->getTokensValue() << endl << endl;
            //cout << "CHAR IS:" << character << endl;
            if (character == '#'){
                input->advance();
                emit(COMMENT);
                result = getNextState();
                
            }
            else if (character == '|'){
                input->advance();
                result = CommentEnd;
            }
            else if (character == -1){
                result = Undefined;
            }
            else{
                input->advance();
                result = MultiLine;
            }
            break;
        case SingleLine:
            character = input->getCurrentCharacter();
            if (character == -1 || character == '\n'){
                emit(COMMENT);
                result = getNextState();
            }
            else{
                input->advance();
                result = SingleLine;
            }
            break;
        case Whitespace:             result = getNextState();    break;
        case Id:
            character = input->getCurrentCharacter();
            if (isalpha(character) || isdigit(character)){
                input->advance();
                result = Id;
            }
            else{
                string value = input->getTokensValue();//how do i get rid of the end character i'm currently pointing at?
                //cout << endl << endl << "VALUE IS: " << value << endl << endl;
                if (value == "Schemes")
                    emit(SCHEMES);
                else if (value == "Rules")
                    emit(RULES);
                else if (value == "Facts")
                    emit(FACTS);
                else if (value == "Queries")
                    emit(QUERIES);
                else
                    emit(ID);
                result = getNextState();
            }
            break;
        case End:
            //throw "ERROR:: in End state:, the Input should be empty once you reach the End state.";
            emit(END);
            break;
        case Undefined:
            emit(UNDEFINED);
            result = getNextState();
            break;
    };
    return result;
}

State Lex::getNextState() {
    State result;
    char currentCharacter = input->getCurrentCharacter();
    
    //The handling of checking for whitespace and setting the result to Whitespace and
    //checking for letters and setting the result to Id will probably best be handled by
    //if statements rather then the switch statement.
    
    //BE SURE TO HANDLE NEW LINES WHEN CHECKING WHITE SPACE
    if (isspace(currentCharacter)){
        result = Whitespace;
        input->advance();
        input->mark();
        return result;
    }
    else if (isalpha(currentCharacter)){
        input->advance();
        result = Id;
        return result;
    }
    switch(currentCharacter) {
        case ','  : result = Comma; break;
        case '.'  : result = Period; break;
        case '?'  : result = Q_mark; break;
        case '('  : result = Left_Paren; break;
        case ')'  : result = Right_Paren; break;
        case '*'  : result = Multiply; break;
        case '+'  : result = Add; break;
        case ':'  : result = SawColon; break;
        case '\'' : result = SawAQuote; break;//???????ProcessingString; break;
        case '#'  : result = CommentBegin; break;
        case -1   : result = End; break;
        default://for all other characters
            result = Undefined; break;
            /*string error = "ERROR:: in Lex::getNextState, Expecting  ";
             error += "'\'', '.', '?', '(', ')', '+', '*', '=', '!', '<', '>', ':' but found ";
             error += currentCharacter;
             error += '.';
             throw error.c_str();*/
    }
    input->advance();
    return result;
}

void Lex::emit(TokenType tokenType) {
    Token* token = new Token(tokenType, input->getTokensValue(), input->getCurrentTokensLineNumber());
    storeToken(token);
    input->mark();
}

void Lex::storeToken(Token* token) {
    //This section shoud ignore whitespace and change the token type to the appropriate value
    //if the value of the token is "Schemes", "Facts", "Rules", or "Queries".
    tokens->push_back(token);
}
//THIS PART IS JUST SLIGHTLY DIFFERENT SO I CAN INITIALIZE THE PARSER
int main(int argc, char* argv[]) {
    cout << "Before Lex" << endl;
    Lex lex(argv[1]);
    cout << "After lex" << endl;
    DataLog parser = DataLog(&lex);
	cout <<"START UNNECESSARY PARSER.TOSTRING():\n" << parser.toString(&lex) << "\nEND UNNEC PARSER.TOSTRING()" << endl;
    Database DB = Database(&parser);
  cout << "\n After DB" << endl;

/*  if (lex.failure != NULL)
        //cout << parser.toString(&lex);
    //else
        cout << "Failure!\n  " << lex.failure->toString();
    else{
        cout << DB.toString();
    }
*/
    return 0;


}

