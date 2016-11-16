//  Declarations for an AST calculator
//  From "flex & bison", fb3-1, by John Levine
//  Adapted by Brian Malloy

#ifndef AST_H
#define AST_H

#include <string>
#include <fstream>

extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class Ast {
public:
  Ast(int n) : nodetype(n){}
  virtual ~Ast() {}
  char getNodetype() const { return nodetype; }
  virtual Ast* getLeft() const { throw std::string("No Left"); }
  virtual Ast* getRight() const { throw std::string("No Right"); }
  virtual double getNumber() const { throw std::string("No Number"); }
  virtual Ast* getNode() const  { throw std::string("No Node");}
  virtual std::string getStr() const { throw std::string("No String");}
private:
  char nodetype;
};

class AstNode : public Ast {
public:
  AstNode(char nodetype, Ast* l, Ast* r) : 
    Ast(nodetype), left(l), right(r) 
  {}
  virtual ~AstNode() {}
  virtual Ast* getLeft() const  { return left; }
  virtual Ast* getRight() const { return right; }
private:
  Ast *left;
  Ast *right;
};

class AstNumber : public Ast {
public:
  AstNumber(char nodetype, double n) : Ast(nodetype), number(n) {} 
  virtual ~AstNumber() {}
  virtual double getNumber() const { return number; }
private:
  double number;
};

class AstStr : public Ast{
public:
    AstStr(char nodetype, std::string str) : Ast(nodetype), str(str) {}
    virtual ~AstStr() {}
    virtual std::string getStr() const  { return str; }
private:
    std::string str;
};


double eval(const Ast*);   // Evaluate an AST
void treeFree(Ast*); // delete and free an AST 
bool areInt(const Ast*, const Ast*);
bool anyFloats(const Ast*);

void buildTree(Ast*,int);
void fillGraphHeader(const Ast*, std::fstream&);
void getVal(Ast*);
void printTree(const Ast*, std::ostringstream&) ;
void makeGraph(const Ast*, std::fstream&);


#endif //AST_H