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
#  include "../controller/manager.h"

double AstStr::eval() const {
      Manager* instance = Manager::getInstance();
            return static_cast<SymbolTable*>(instance->getCurrentSymbolTable())->getAst(str)->getNumber();//eval();
    }

double ExprNode::eval() const {
    double temp = (right->eval());
    Manager* instance = Manager::getInstance();
    static_cast<SymbolTable*>(instance->getCurrentSymbolTable())->createAstFor(left->getStr(), temp, anyFloats(right));

    return 0;
  }

FuncNode::FuncNode(std::string name, std::vector<Ast*>* suite) : Ast('R', NULL, NULL), name(name), suite(suite) {
    Manager* instance = Manager::getInstance();
    tableIndex = instance->getSizeOfVector();
    instance->createSymbolTable();

  }

double FuncNode::eval() const {
    Manager* instance = Manager::getInstance();
    int prevScope = instance->getCurrentScope();
    instance->setCurrentScope(tableIndex);

    std::vector<Ast*>::const_iterator it = suite->end();
    while(it != suite->begin()){
      --it;
      (*it)->eval();
    }

    instance->setCurrentScope(prevScope);
    return 0;
  }


bool Ast::areInt(const Ast* ast) const{
  double left = (ast->getLeft()->eval()),
                    right = (ast->getRight()->eval());

    return !anyFloats(ast) && !isinf(left) && !isinf(right);

    // return a->getLeft()->getNodetype() != 'F' && a->getRight()->getNodetype() != 'F' && modf(left,&temp) == 0.0 && modf(right,&temp) == 0.0 && !isinf(left) && !isinf(right);
}

void treeFree(Ast *a) {
    switch(a->getNodetype()) {
        // two subtrees
        case 'B':
        case 'E':
            treeFree(a->getRight());

            // one subtrees
        case 'S':
        case 'U':
            treeFree(a->getLeft());

            //no subtree
        case 'R':
        case 'N':
        case 'F':
        case 'C':
            delete a;
            break;
        default: std::cout << "internal error: bad node "
                           << a->getNodetype() << std::endl;;
    }
}

bool Ast::anyFloats(const Ast* ast) const{

    if(ast == NULL) return false;

    switch(ast->getNodetype()){

      //base nodes
        case 'F': return true;
        case 'N': return false;
        case 'C': {
            Manager* instance = Manager::getInstance();
            return (static_cast<SymbolTable*>(instance->getCurrentSymbolTable())->getAst(ast->getStr())->getNodetype() == 'F');
        }
      //Negative exponentials yeild floats
        case 'E': {
            if(ast->getRight()->eval() < 0 ) return true;
        }
      //Check left and right nodes
        default : {
            if(anyFloats(ast->getLeft()) || anyFloats(ast->getRight()) ) return true;
        }
    }

    return false;
}






