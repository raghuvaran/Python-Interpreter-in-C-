#include <iostream>
#include "symbolTable.h"
extern int yyparse();

int main() {
  try {
//    std::cout << "> "; 
    int returnCode = yyparse();
    std::cout << std::endl;
    SymbolTable* instance = SymbolTable::getInstance();
            instance->freeMap();
    return returnCode;
  }
  catch (const std::string& msg) {
//    std::cout << msg << std::endl; 
  }
  catch (...) {
    std::cout << "Oops, need someone behind the plate" << std::endl; 
  }
  return 0;
}
