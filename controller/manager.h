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

	void setAstFor(std::string str, Ast* ast){
		if(mapOfVars.find(str) == mapOfVars.end())
			mapOfVars.insert(std::make_pair(str, ast));
		else
			delete mapOfVars.find(str)->second;
			mapOfVars.find(str)->second = ast;
	}

	void createAstFor(std::string str, double val, bool anyFloats){
		Ast* ast;
		//Ast* ast2 = new AstNumber('F',4.4);
		if((std::floor(val) - val) || anyFloats)  ast = new AstNumber('F',val);
          else ast = new AstNumber('N',val);

        setAstFor(str, ast);
	}

	Ast* getAst(std::string str){
		std::map<std::string, Ast*>::iterator it = mapOfVars.find(str);

		if( it != mapOfVars.end() )
			return it->second;
		else{
			Ast* ast = new AstNumber('N',0);
			setAstFor(str, ast);
			return ast;
		}
	}

	void freeMap(){
		std::map<std::string, Ast*>::iterator it = mapOfVars.begin();
		while(it != mapOfVars.end()){
			delete it->second;
			mapOfVars.erase(it);
			it++;
		}
		//delete firstInstance;
	}

	int getSizeOfVector(){
		return symbolTables.size();
	}

	void createSymbolTable(){
		symbolTables.push_back(new SymbolTable());
	}

	Ast* getSymbolTable(int index){
		return symbolTables[index];
	}

	Ast* getCurrentSymbolTable(){
		return symbolTables[currentScope];
	}

	void setCurrentScope(int index){
		currentScope = index;
	}

	int getCurrentScope(){
		return currentScope;
	}

private:
	std::map<std::string, Ast*> mapOfVars;
	std::vector<Ast*> symbolTables;
	static Manager* firstInstance;
	int currentScope = 0;
	 Manager(){
	 	symbolTables.push_back(new SymbolTable());
	 }
	~Manager(){}

};

#endif //MANAGER_H