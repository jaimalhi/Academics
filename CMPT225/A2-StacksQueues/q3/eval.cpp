//eval.cpp
#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

#include <iostream>
#include <string>
using namespace std;

int main () {
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack;  // 2x Stacks of type Token

    t = S.getnext(); //get first token

   //Infix Algorithm start
   while(t.tt != eof || !(opstack.isEmpty())){
        if(t.tt == integer){ //if t is a number
            numstack.push(t); //push t to numstack
            t = S.getnext(); //get next token
        }
        else if(t.tt == lptok){ //if t is a left parenthesis '('
            opstack.push(t); //push t to opstack
            t = S.getnext(); //get next token
        }
        else if(t.tt == rptok){ //if t is a right parenthesis ')'
            if(opstack.peek().tt == lptok){ //if top of opstack is left parenthesis '('
                opstack.pop(); //pop it from the opstack
                t = S.getnext(); //get next token
            }
            else{
                int first = numstack.pop().val; //pop first number
                int second = numstack.pop().val; //pop second number
                TokenType op = opstack.pop().tt; //pop top operator

                int num; //perform the operation
                if(op == pltok) num = second + first;
                else if(op == mitok) num = second - first;
                else if(op == asttok) num = second * first;
                else if(op == slashtok) num = second / first;

                Token result; 
                result.tt = integer;
                result.text = to_string(num);
                result.val = num;
                
                numstack.push(result); //push result to top of numstack
            }
        }
        else if(t.tt == pltok || t.tt == mitok || t.tt == eof){ //if t = +,-,eof
            if(!(opstack.isEmpty()) && (opstack.peek().tt == pltok ||
                                        opstack.peek().tt == mitok || 
                                        opstack.peek().tt == asttok || 
                                        opstack.peek().tt == slashtok)){
                int first = numstack.pop().val; //pop first number
                int second = numstack.pop().val; //pop second number
                TokenType op = opstack.pop().tt; //pop top operator

                int num; //perform the operation
                if(op == pltok) num = second + first;
                else if(op == mitok) num = second - first;
                else if(op == asttok) num = second * first;
                else if(op == slashtok) num = second / first;

                Token result; 
                result.tt = integer;
                result.text = to_string(num);
                result.val = num;
                
                numstack.push(result); //push result to top of numstack
            }
            else{
                opstack.push(t); //push t to opstack
                t = S.getnext(); //get next token
            }
        }
        else if(t.tt == asttok || t.tt == slashtok){ //if t = * or /
            if(!(opstack.isEmpty()) && (opstack.peek().tt == asttok || 
                                        opstack.peek().tt == slashtok)){
                int first = numstack.pop().val; //pop first number
                int second = numstack.pop().val; //pop second number
                TokenType op = opstack.pop().tt; //pop top operator

                int num; //perform the operation
                if(op == pltok) num = second + first;
                else if(op == mitok) num = second - first;
                else if(op == asttok) num = second * first;
                else if(op == slashtok) num = second / first;

                Token result; 
                result.tt = integer;
                result.text = to_string(num);
                result.val = num;
                
                numstack.push(result); //push result to top of numstack
            }
            else{
                opstack.push(t); //push t to opstack
                t = S.getnext(); //get next token
            }
        }
   }
   cout << numstack.peek().val << endl;

   return 0;
}

