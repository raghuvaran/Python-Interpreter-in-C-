// #ifndef MANAGER_H
// #define MANAGER_H

// #include <iostream>
// #include <map>




// class Manager{

// public:
// 	static Manager* getInstance(){
// 		if(!firstInstance) firstInstance = new Manager;
// 		return firstInstance;
// 	}

// 	void setAstFor(std::string str, Ast* ast){
// 		if(mapOfVars.find(str) == mapOfVars.end())
// 			mapOfVars.insert(std::make_pair(str, ast));
// 		else
// 			delete mapOfVars.find(str)->second;
// 			mapOfVars.find(str)->second = ast;
// 	}

// 	void createAstFor(std::string str, double val, bool anyFloats){
// 		Ast* ast;
// 		//Ast* ast2 = new AstNumber('F',4.4);
// 		if((std::floor(val) - val) || anyFloats)  ast = new AstNumber('F',val);
//           else ast = new AstNumber('N',val);

//         setAstFor(str, ast);
// 	}

// 	Ast* getAst(std::string str){
// 		std::map<std::string, Ast*>::iterator it = mapOfVars.find(str);

// 		if( it != mapOfVars.end() )
// 			return it->second;
// 		else{
// 			Ast* ast = new AstNumber('N',0);
// 			setAstFor(str, ast);
// 			return ast;
// 		}
// 	}

// 	void freeMap(){
// 		std::map<std::string, Ast*>::iterator it = mapOfVars.begin();
// 		while(it != mapOfVars.end()){
// 			delete it->second;
// 			mapOfVars.erase(it);
// 			it++;
// 		}
// 		delete firstInstance;
// 	}
// private:
// 	std::map<std::string, Ast*> mapOfVars;
// 	static Manager* firstInstance;
// 	 Manager(){}
// 	~Manager(){}

// }

// #endif //MANAGER_H