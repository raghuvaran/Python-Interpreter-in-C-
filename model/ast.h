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
  virtual double eval() const { throw std::string("Nothing to evaluate");}
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
protected:
  Ast *left;
  Ast *right;
};

class AstNumber : public Ast {
public:
  AstNumber(char nodetype, double n) : Ast(nodetype), number(n) {} 
  virtual ~AstNumber() {}
  virtual double getNumber() const { return number; }
  virtual double eval() const { return number; }
private:
  double number;
};

class AstStr : public Ast{
public:
    AstStr(char nodetype, std::string str) : Ast(nodetype), str(str) {}
    virtual ~AstStr() {}
    virtual std::string getStr() const  { return str; }
    virtual double eval() const;
private:
    std::string str;
};

class BinaryAddNode : public AstNode{
public:
  BinaryAddNode(Ast* l, Ast* r) : AstNode('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    return ((left->eval()) + (right->eval())); 
  }
};

class PrintNode : public Ast{
public:
    PrintNode();
    // virtual double eval() {
    //     return 0;
    // }
private:
  Ast *ast;
};


double eval(const Ast*);   // Evaluate an AST
void treeFree(Ast*); // delete and free an AST 
bool areInt(const Ast*);
bool anyFloats(const Ast*);



#endif //AST_H