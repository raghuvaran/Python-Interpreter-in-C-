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
  Ast(char nodetype, Ast* l, Ast* r) : 
    nodetype(nodetype), left(l), right(r) 
  {}
  virtual ~Ast() {}
  char getNodetype() const { return nodetype; }
  // virtual Ast* getLeft() const { throw std::string("No Left"); }
  // virtual Ast* getRight() const { throw std::string("No Right"); }
  virtual Ast* getLeft() const  { return left; }
  virtual Ast* getRight() const { return right; }
  virtual double getNumber() const { throw std::string("No Number"); }
  virtual Ast* getNode() const  { throw std::string("No Node");}
  virtual std::string getStr() const { throw std::string("No String");}
  virtual double eval() const { throw std::string("Nothing to evaluate");}

  bool areInt(const Ast*) const;
  bool anyFloats(const Ast*) const;
  bool isDetermined(Ast* ast);
protected:
  char nodetype;
  Ast *left;
  Ast *right;
};

class AstNode : public Ast {
public:
  AstNode(char nodetype, Ast* l, Ast* r) : 
    Ast(nodetype), left(l), right(r) 
  {}
  virtual ~AstNode() {}
  virtual Ast* getLeft() const  { return left; }
  virtual Ast* getRight() const { return right; }
  virtual double eval() const { throw std::string("Nothing to evaluate");}
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

class BinaryAddNode : public Ast{
public:
  BinaryAddNode(Ast* l, Ast* r) : Ast('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    return ((left->eval()) + (right->eval())); 
  }
};

class BinaryMinNode : public Ast{
public:
  BinaryMinNode(Ast* l, Ast* r) : Ast('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    return ((left->eval()) - (right->eval())); 
  }
};

class BinaryMulNode : public Ast{
public:
  BinaryMulNode(Ast* l, Ast* r) : Ast('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    double l = left->eval(), r = right->eval();
            if(areInt(this))
                return (int)l * (int)r;
            else
                return l * r;
  }
};

class BinaryDivNode : public Ast{
public:
  BinaryDivNode(Ast* l, Ast* r) : Ast('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    double l = left->eval(), r = right->eval();
            if( areInt(this) && r){
              //std::cout << "Right operand is" << eval(a->getRight()) << std::endl;
                double v = (double)l / r;
                return std::floor(v);
            }
            else
                // std::cout << "In else \n" ;
                return l / r;
  }
};

class BinaryDDivNode : public Ast{
public:
  BinaryDDivNode(Ast* l, Ast* r) : Ast('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    double l = left->eval(), r = right->eval();
            if(r){
              //std::cout << "Right operand is" << eval(a->getRight()) << std::endl;
                double v = (double)l / r;
                return std::floor(v);
            }
            else
                // std::cout << "In else \n" ;
                return l / r;
  }
};

class BinaryModNode : public Ast{
public:
  BinaryModNode(Ast* l, Ast* r) : Ast('B', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    double l = left->eval(), r = right->eval();         
            if( (l >=0 && r >= 0) ||
                (l <=0 && r <= 0) ){
                return std::fmod( l, r);
            }else{
                double temp = std::fmod(l, r);
                if(temp) return r + temp;
                else   return 0;
            }
  }
};

class BinaryExpNode : public Ast{
public:
  BinaryExpNode(Ast* l, Ast* r) : Ast('E', l, r) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
     return std::pow(left->eval(),right->eval());
  }
};

class UnaryNode : public Ast{
public:
  UnaryNode(char type, Ast* node) : Ast('U', node, NULL), type(type) {}
  virtual double eval() const { 
    
    // printf("Left : %f, Right : %f",left->eval(),right->eval());
    switch(type){
      case '+': return  left->eval();
      case '-': return -left->eval();
      case '~': 
      {    double v = (-1) * ( 1+ left->eval());
                   if(!v) return v*v;
                   else return v;} 
      default: std::cout << "internal error: bad node in UnaryNode"
                           << type << std::endl;
    }
    return -1;
  }

private:
  char type;
};

class PrintNode : public Ast{
public:
    PrintNode(Ast* node) : Ast('S', node, NULL) {};
    virtual double eval() const {
          double temp = (left->eval());
          if(isinf(temp) || temp != temp)
            std::cout << "ZeroDivisionError" << std::endl;
          else
            {  std::cout << temp;
               if(!(std::floor(temp) - temp) && anyFloats(left))  std::cout << ".0";
               std::cout << std::endl;
             }
      return 0;
    }
};


class ExprNode : public Ast{
public:
  ExprNode(Ast* left, Ast* right) : Ast('S', left, right) {}
  virtual double eval() const;
};

double eval(const Ast*);   // Evaluate an AST
void treeFree(Ast*); // delete and free an AST 
bool areInt(const Ast*);
bool anyFloats(const Ast*);



#endif //AST_H