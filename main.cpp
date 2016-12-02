#include <iostream>
#include "controller/manager.h"
extern int yyparse();

int main() {
  try {
//    std::cout << "> "; 
     extern int yydebug;
  yydebug = 1;
    int returnCode = yyparse();
    std::cout << std::endl;
    // SymbolTable* instance = SymbolTable::getInstance();
    // instance->freeMap();
    Manager* instance = Manager::getInstance();
    std::cout << "Size of vector" << instance->getSizeOfVector() << '\n';
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
