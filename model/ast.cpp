// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <cmath>
#  include <sstream>
#  include <stdlib.h>
#  include <fstream>
#  include <iomanip>
#  include <typeinfo>
//#  include "ast.h"
#  include "symbolTable.h"

double AstStr::eval() const {
      SymbolTable* instance = SymbolTable::getInstance();
            return instance->getAst(str)->getNumber();//eval();
    }


double eval(const Ast* a) {
     // std::cout << "Called for : " << a->getNodetype() << std::endl;
    double v = 0;
    switch( a->getNodetype() ) {
        case 'N': //std::cout << "Returned 'N' : " << (int)a->getNumber() << std::endl;
            // return (int)a->getNumber();  break;
        case 'F': //std::cout << "Returned 'F' : " << (float)a->getNumber() << std::endl;
            return a->eval();break;
        case 'C':{

            // SymbolTable* instance = SymbolTable::getInstance();
            // return eval(instance->getAst(a->getStr()));
            return a->eval();
        }
        case '+': 
        v = eval(a->getLeft()) + eval(a->getRight()); break;
            // return a->eval();
        case '-': v = eval(a->getLeft()) - eval(a->getRight());break;
        case '*':
        {double left = eval(a->getLeft()), right = eval(a->getRight());
            if(areInt(a))
                v = (int)left * (int)right;
            else
                v = left * right;
            // std::cout << "Type of Left : " << typeid(eval(a->getLeft())).name() << std::endl;
            break;
        }
        case '/':
        {double left = eval(a->getLeft()), right = eval(a->getRight());
            if( (areInt(a)) && right){
              //std::cout << "Right operand is" << eval(a->getRight()) << std::endl;
                v = (double)left / right;
                v = std::floor(v);
            }
            else
                // std::cout << "In else \n" ;
                v = left / right;
            break;
        }
        case 'D':
        {double left = eval(a->getLeft()), right = eval(a->getRight());
            if(right){
                v = (double)left / right;
                v = std::floor(v);
            }
            else
                v = left / right;
            break;
        }
        case '%':
        {double left = eval(a->getLeft()), right = eval(a->getRight());          
            if( (left >=0 && right >= 0) ||
                (left <=0 && right <= 0) ){
                v = std::fmod( left, right);
            }else{
                double temp = std::fmod(left, right);
                if(temp) v = right + temp;
                else   v = 0;
            }
            break;
        }
        case '^': v = std::pow(eval(a->getLeft()),eval(a->getRight()));break;
            //MINUS
        case 'M': v = -eval(a->getLeft());break;
            //PLUS
        case 'P': v = eval(a->getLeft());break;
            //TILDE
        case 'T': v = (-1) * ( 1+ eval(a->getLeft()));
            if(!v) v= v*v; break;
        default: std::cout << "internal error: bad node "
                           << a->getNodetype() << std::endl;;
    }
    return v;
}

bool areInt(const Ast* a){
  double left = eval(a->getLeft()),
                    right = eval(a->getRight());

    return !anyFloats(a) && !isinf(left) && !isinf(right);

    // return a->getLeft()->getNodetype() != 'F' && a->getRight()->getNodetype() != 'F' && modf(left,&temp) == 0.0 && modf(right,&temp) == 0.0 && !isinf(left) && !isinf(right);
}

void treeFree(Ast *a) {
    switch(a->getNodetype()) {
        // two subtrees
        case '+':
        case '-':
        case '*':
        case '/':
        case 'D':
        case '%':
        case '^':
            treeFree(a->getRight());

            // one subtrees
        case 'P':
        case 'M':
        case 'T':
            treeFree(a->getLeft());

            //no subtree
        case 'N':
        case 'F':
        case 'C':
            delete a;
            break;
        // case 'B': treeFree(a->getNode()); delete a; break;
        default: std::cout << "internal error: bad node "
                           << a->getNodetype() << std::endl;;
    }
}

bool anyFloats(const Ast* ast){

    if(ast == NULL) return false;

    switch(ast->getNodetype()){

      //base nodes
        case 'F': return true;
        case 'N': return false;
        case 'C': {
            SymbolTable* instance = SymbolTable::getInstance();
            return (instance->getAst(ast->getStr())->getNodetype() == 'F');
        }
      //Negative exponentials yeild floats
        case '^': {
            if(eval(ast->getRight()) < 0 ) return true;
        }
      //Check left and right nodes
        default : {
            if(anyFloats(ast->getLeft()) || anyFloats(ast->getRight()) ) return true;
        }
    }

    return false;
}




