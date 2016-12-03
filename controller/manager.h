#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <map>
#include <utility>
#include <cmath>
#include <vector>
#include "../model/symbolTable.h"


class Manager{

public:
	static Manager* getInstance(){
		if(!firstInstance) firstInstance = new Manager;
		return firstInstance;
	}

	void setAstInCS(std::string str, Ast* ast){
		SymbolTable* st = (getCurrentSymbolTable());
		st->setAstFor(str, ast);

	}

	Ast* getAstFromCS(std::string str){
		for(int i=symbolTables.size()-1; i>=0; --i){
			SymbolTable* st = (symbolTables[i]);
			Ast* result = st->getAst(str);
			if(result) return result;
		}

		Ast* ast = new AstNumber('N',0);
		setAstInCS(str, ast);
		return ast;
	}


	void createAstInCS(std::string str, double val, bool anyFloats){
		//SymbolTable* st = static_cast<SymbolTable*>(getCurrentSymbolTable());
		Ast* ast;
		//Ast* ast2 = new AstNumber('F',4.4);
		if((std::floor(val) - val) || anyFloats)  ast = new AstNumber('F',val);
          else ast = new AstNumber('N',val);

        setAstInCS(str, ast);

	}

	// void setAstFor(std::string str, Ast* ast){
	// 	if(mapOfVars.find(str) == mapOfVars.end())
	// 		mapOfVars.insert(std::make_pair(str, ast));
	// 	else
	// 		delete mapOfVars.find(str)->second;
	// 		mapOfVars.find(str)->second = ast;
	// }

	// void createAstFor(std::string str, double val, bool anyFloats){
	// 	Ast* ast;
	// 	//Ast* ast2 = new AstNumber('F',4.4);
	// 	if((std::floor(val) - val) || anyFloats)  ast = new AstNumber('F',val);
 //          else ast = new AstNumber('N',val);

 //        setAstFor(str, ast);
	// }

	// Ast* getAst(std::string str){
	// 	std::map<std::string, Ast*>::iterator it = mapOfVars.find(str);

	// 	if( it != mapOfVars.end() )
	// 		return it->second;
	// 	else{
	// 		// Ast* ast = new AstNumber('N',0);
	// 		// setAstFor(str, ast);
	// 		return NULL;
	// 	}
	// }

	// void freeMap(){
	// 	std::map<std::string, Ast*>::iterator it = mapOfVars.begin();
	// 	while(it != mapOfVars.end()){
	// 		delete it->second;
	// 		mapOfVars.erase(it);
	// 		it++;
	// 	}
	// 	//delete firstInstance;
	// }

	int getSizeOfVector(){
		return symbolTables.size();
	}

	void createSymbolTable(){
		symbolTables.push_back(new SymbolTable());
	}

	void destroySymbolTable(){
		delete symbolTables.back();
		symbolTables.pop_back();
	}

	SymbolTable* getSymbolTable(int index){
		return symbolTables[index];
	}

	SymbolTable* getCurrentSymbolTable(){
		return symbolTables[currentScope];
	}

	void setCurrentScope(int index){
		currentScope = index;
	}

	int getCurrentScope(){
		return currentScope;
	}

private:
	// std::map<std::string, Ast*> mapOfVars;
	std::vector<SymbolTable*> symbolTables;
	static Manager* firstInstance;
	int currentScope = 0;
	 Manager(){
	 	symbolTables.push_back(new SymbolTable());
	 }
	~Manager(){}

};

#endif //MANAGER_H