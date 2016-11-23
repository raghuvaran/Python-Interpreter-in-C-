#include <iostream>
#include "symbolTable.h"

SymbolTable* SymbolTable::firstInstance = NULL;

void fun(){
std::cout << SymbolTable::getInstance() << std::endl;

}

int main(){

	Ast* ast = new AstNumber('N',12);
	Ast* ast2= new AstNumber('N',24);
	std::string ch = "Number";

	SymbolTable* instance = SymbolTable::getInstance();

	instance->setAstFor(ch, ast);
	instance->setAstFor(ch, ast2);

	if(instance->getAst(ch) != NULL) std::cout << instance->getAst(ch)->getNumber() << std::endl;
	  else std::cout << "Null" << std::endl;
}