// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <cmath>
#  include <sstream>
#  include <stdlib.h>
#  include <fstream>
#  include <iomanip>
#  include "ast.h"


double eval(const Ast* a, bool hasFloats = true) {
  // std::cout << "Called for : " << a->getNodetype() << std::endl;
  double v = 0;
  switch( a->getNodetype() ) {
  case 'N': //std::cout << "Returned 'N' : " << (int)a->getNumber() << std::endl;
   return (int)a->getNumber();  break;
  case 'F': //std::cout << "Returned 'F' : " << (float)a->getNumber() << std::endl;
   return (float)a->getNumber();break;
  case '+': v = eval(a->getLeft()) + eval(a->getRight());break;
  case '-': v = eval(a->getLeft()) - eval(a->getRight());break;
  case '*': 
  {double left = eval(a->getLeft()),
    right = eval(a->getRight());
          v = left * right;
    break;
  }
  case '/':
  {double left = eval(a->getLeft()),
    right = eval(a->getRight());
       v = left / right;
       break;
  }
  case 'D': 
  {double left = eval(a->getLeft()),
    right = eval(a->getRight());
       v = left / right;
       break;
  }
  case '%': 
            if( (eval(a->getLeft()) >=0 && eval(a->getRight()) >= 0) ||
                (eval(a->getLeft()) <=0 && eval(a->getRight()) <= 0) ){
            v = std::fmod( eval(a->getLeft()) , eval(a->getRight()) );
            }else{
              double temp = std::fmod( eval(a->getLeft()) , eval(a->getRight()) );
                if(temp) v = eval(a->getRight()) + temp;
                  else   v = 0;
            }
            break;
  case '^': v = std::pow(eval(a->getLeft()),eval(a->getRight()));break;
  //MINUS
  case 'M': v = -eval(a->getLeft());break;
  //PLUS
  case 'P': v = eval(a->getLeft());break;
  //TILDE
  case 'T': v = (-1) * ( 1+ eval(a->getLeft()));
    if(!v) v= v*v; break;
  case 'B': v = eval(a->getNode());break;
  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
  // std::cout << "Eval returned : " << v << std::endl;
  return v;
}

bool areInt(const Ast* a, const Ast* b){
  double left = eval(a->getLeft()),
   right = eval(a->getRight()),
   temp;

   return !isinf(left) && !isinf(right) && modf(left,&temp) == 0.0 && modf(right,&temp) == 0.0 && !left && !right;
}

void treeFree(Ast *a) {
  switch(a->getNodetype()) {
   // two subtrees
  case '+':
  case '-':
  case '*':
  case '/':
  case 'P':
    treeFree(a->getRight());

   // one subtrees
  case 'M':
    treeFree(a->getLeft());

   //no subtree
  case 'K':
    delete a;
    break;
  case 'B': treeFree(a->getNode()); delete a; break;
  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
}





