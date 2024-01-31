//pish.cpp
//Notes: For Question 2b I implemented Short-Circuit Evaluation, elif/else, and break
#include "hash.h"
#include "Scanner.h"
#include "Parse.h"
#include "assert.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#define tabstop 4

class var {
public:
    //Attributes
    string key;
    int data;
    bool inLoop;

    //Methods
    var() : key(""), data(0), inLoop(false)
    {} //default constructor

    var(string k, int dt) : key(k), data(dt), inLoop(false)
    {} //constructor

    void setLoop(bool loop){ inLoop = loop; }
    bool getLoop() const { return inLoop; }
};
var v;

//* Declarations
Set<var> memmap; //Hash table for idents
int run(StmtsNode *stmts);
int eval(ExpnNode *expn);
void assignStmt(StmtNode *stmt);
void whileStmt(StmtNode *stmt);
void ifStmt(StmtNode *stmt);
bool basicOps(ExpnNode *n);

//* Definitions
int eval(ExpnNode *expn){ 
    ExpnNode *n = expn; //simplify name
    //Base Cases
    if(n == nullptr){
        return stoi(n->text);
    }
    if(n->left_operand == nullptr && n->tok == mitok){
        return 0 - eval(n->right_operand);
    }

    if(n->tok == integer){ //integer
        return stoi(n->text);
    }
    else if(n->tok == ident){ //identifer
        var *vData = memmap.search(n->text);
        return vData->data;
    }
    else if(n->tok == andtok){ //and
        int a, b;
        if(n->left_operand->tok != integer){
            a = eval(n->left_operand);
        }
        if(n->right_operand->tok != integer){
            b = eval(n->right_operand);
        }
        a = eval(n->left_operand); //numerator
        if(!a) return 0; //*Short-Circuit Eval
        b = eval(n->right_operand); //denominator
        return a && b;
    }
    else if(n->tok == ortok){ //or
        int a, b;
        if(n->left_operand->tok != integer){
            a = eval(n->left_operand);
        }
        if(n->right_operand->tok != integer){
            b = eval(n->right_operand);
        }
        a = eval(n->left_operand); //numerator
        if(a) return 1;
        b = eval(n->right_operand); //denominator
        return a || b;
    }
    else if(n->tok == slashtok){ //divide
        int a, b;
        if(n->left_operand->tok != integer){
            a = eval(n->left_operand);
        }
        if(n->right_operand->tok != integer){
            b = eval(n->right_operand);
        }
        a = eval(n->left_operand); //numerator
        if(a == 0) return 0; //*Short-Circuit Eval
        b = eval(n->right_operand); //denominator
        
        //Special division rules
        if(a < 0 && b > 0){ //when b is positive
            return a / b - 1;
        }
        else if(b < 0 && a > 0){ //when b is negative
            return a / b - 1;
        }
        else{
            return a / b;
        }
    }
    else if(n->tok == asttok){ //multiply
        int a, b;
        if(n->left_operand->tok != integer){ 
            a = eval(n->left_operand);
        }
        if(n->right_operand->tok != integer){
            b = eval(n->right_operand);
        }
        a = eval(n->left_operand);
        if(a == 0) return 0; //*Short-Circuit Eval
        b = eval(n->right_operand);
        return a * b;
    }
    else if(n->tok == pltok){ //plus
        int a, b;
        if(n->left_operand->tok != integer){ 
            a = eval(n->left_operand);
        }
        if(n->right_operand->tok != integer){
            b = eval(n->right_operand);
        }
        a = eval(n->left_operand);
        b = eval(n->right_operand);
        return a + b;
    }
    else if(n->tok == mitok){ //minus
        int a, b;
        if(n->left_operand->tok != integer){ 
            a = eval(n->left_operand);
        }
        if(n->right_operand->tok != integer){
            b = eval(n->right_operand);
        }
        a = eval(n->left_operand);
        b = eval(n->right_operand);
        return a - b;
    }
    return -1;
} //eval

void assignStmt(StmtNode *stmt){
    StmtNode *s = stmt;
    int dt = eval(s->expn);
    var *newVar = new var(s->ident, dt);
    memmap.insert(newVar); //insert into hashtable
} //assignStmt

void whileStmt(StmtNode *stmt){
    ExpnNode *n = stmt->expn;
    StmtNode *s = stmt;
    if(n->tok == andtok){ //and
        bool left = basicOps(n->left_operand);
        if(!left){ //left == false, dont enter loop
            return;
        } //*Short-Circuit Eval

        bool right = basicOps(n->right_operand);
        while(left && right){
            cout << "IN-While\n";
            if(run(s->stmts) == -1) break;
            left = basicOps(n->left_operand);
            right = basicOps(n->right_operand);
        }
    }
    else if(n->tok == ortok){ //or
        bool left = basicOps(n->left_operand);
        while(left){ //left == true, enter loop
            if(run(s->stmts) == -1) break;
            left = basicOps(n->left_operand);
        } //*Short-Circuit Eval

        bool right = basicOps(n->right_operand);
        while(left || right){
            if(run(s->stmts) == -1) break;
            left = basicOps(n->left_operand);
            right = basicOps(n->right_operand);
        }
    }   
    else if(n->tok == nottok){ //not
        bool check = basicOps(n->right_operand);
        while(!check){
            if(run(s->stmts) == -1) break;
            check = basicOps(n->right_operand);
        }
    }
    else{
        bool check = basicOps(n);
        while(check){ //check == true
            if(run(s->stmts) == -1) break;
            check = basicOps(n);
        }
    }
} //whileStmt

void ifStmt(StmtNode *stmt){
    ExpnNode *n = stmt->expn;
    StmtNode *s = stmt;
    if(n->tok == andtok){ //and
        bool left = basicOps(n->left_operand);
        if(!left){ //left == false, dont enter if
            if(s->elif != nullptr){
                if(s->elif->tok == eliftok){
                    ifStmt(s->elif);
                }
                else if(s->elif->tok == elsetok){
                    run(s->elif->stmts);
                }
            }
            return;
        } //*Short-Circuit Eval
        bool right = basicOps(n->right_operand);
        if(left && right){ //left == true && right == true
            run(s->stmts);
        }
        else if(s->elif != nullptr){
            if(s->elif->tok == eliftok){
                ifStmt(s->elif);
            }
            else if(s->elif->tok == elsetok){
                run(s->elif->stmts);
            }
        }
    }
    else if(n->tok == ortok){ //or
        bool left = basicOps(n->left_operand);
        if(left){ //left == true, enter if
            run(s->stmts); 
            return; 
        } //*Short-Circuit Eval
        bool right = basicOps(n->right_operand);
        if(left || right){ //left == true || right == true
            run(s->stmts);
        }
        else if(s->elif != nullptr){
            if(s->elif->tok == eliftok){
                ifStmt(s->elif);
            }
            else if(s->elif->tok == elsetok){
                run(s->elif->stmts);
            }
        }
    }   
    else if(n->tok == nottok){ //not
        bool child = basicOps(n->right_operand);
        if(!child){
            run(s->stmts);
        }
        else if(s->elif != nullptr){
            if(s->elif->tok == eliftok){
                ifStmt(s->elif);
            }
            else if(s->elif->tok == elsetok){
                run(s->elif->stmts);
            }
        }
    }
    else{
        bool check = basicOps(n);
        if(check){ //check == true
            run(s->stmts);
        }
        else if(s->elif != nullptr){
            if(s->elif->tok == eliftok){
                ifStmt(s->elif);
            }
            else if(s->elif->tok == elsetok){
                run(s->elif->stmts);
            }
        }
    }
} //ifStmt

bool basicOps(ExpnNode *n){
    if(n->tok == lttok){ // <
        int a = eval(n->left_operand);
        int b = eval(n->right_operand);
        if(a < b){
            return true;
        }
    }
    else if(n->tok == gttok){ // >
        int a = eval(n->left_operand);
        int b = eval(n->right_operand);
        if(a > b){
            return true;
        }
    }
    else if(n->tok == eqtok){ // ==
        int a = eval(n->left_operand);
        int b = eval(n->right_operand);
        if(a == b){
            return true;
        }
    }
    else if(n->tok == netok){ //' !=
        int a = eval(n->left_operand);
        int b = eval(n->right_operand);
        if(a != b){
            return true;
        }
    }
    else if(n->tok == letok){ // <=
        int a = eval(n->left_operand);
        int b = eval(n->right_operand);
        if(a <= b){
            return true;
        }
    }
    else if(n->tok == getok){ // >=
        int a = eval(n->left_operand);
        int b = eval(n->right_operand);
        if(a >= b){
            return true;
        }
    }
    return false;
} //basicOps

int run(StmtsNode *stmts){
    StmtsNode *curr = stmts;
    while (curr != NULL) {
        assert(curr->stmt != NULL);
        //print statement
        if(curr->stmt->tok == printtok){
            //cout << "RUN-print: ";
            cout << eval(curr->stmt->expn) << endl;
        }
        //assignment statement)
        else if(curr->stmt->tok == asgntok){
            //cout << "RUN-Assign\n";
            assignStmt(curr->stmt);
        }
        //while statement
        else if(curr->stmt->tok == whiletok){
            //cout << "RUN-While\n";
            v.setLoop(true);
            whileStmt(curr->stmt);
            v.setLoop(false);
        }
        //if/elif/else statement
        else if(curr->stmt->tok == iftok){
            //cout << "RUN-If\n";
            ifStmt(curr->stmt);
        }
        //break statement
        else if(curr->stmt->tok == breaktok){ //TODO: only breaks if-stmt, not while
            cout << "RUN-Break\n";
            if(v.getLoop()) return -1;
            else throw std::runtime_error("break must be used within a loop");
        }
        else { assert(0); }
        //next node in the chain
        curr = curr->stmts;
    }
    return 0;
}

/* program0.pish
print  7 /  3;
print -7 /  3;
print  7 / -3;
print -7 / -3;
*/

///////////////////////////////////////////////
//----- carried over from testParse.cpp -----//
//cout << print(pTree); 
///////////////////////////////////////////////

int main () {
    StmtsNode *pTree;
    try {
        pTree = Parse(cin);
    }
    catch(string s) {
        cout << "Parse error: " << s << endl;
        return 0;
    }
    cout << "Parse Successful!\n";
    cout << "=================\n";
    run(pTree);
    delete pTree;
}

