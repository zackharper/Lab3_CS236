#include "State.h"

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
        case Q_mark:                     result = "Q_mark"; break;
        case Left_Paren:                 result = "Left_Paren"; break;
        case Right_Paren:                result = "Right_Paren"; break;
        case Multiply:                   result = "Multiply"; break;
        case Add:                        result = "Add"; break;
        case SawColon:                   result = "SawColon"; break;
        case Colon_Dash:                 result = "Colon_Dash"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
        case CommentBegin:               result = "CommentBegin"; break;
        case MultiLine:                  result = "MultiLine"; break;
        case CommentEnd:                 result = "CommentEnd"; break;
        case SingleLine:                 result = "SingleLine"; break;
        case Whitespace:                 result = "Whitespace"; break;
        case Id:                         result = "Id"; break;
        case Start:                      result = "Start"; break;
        case End:                        result = "End"; break;
        case Undefined:                  result = "Undefined"; break;
    }
    return result;
};
