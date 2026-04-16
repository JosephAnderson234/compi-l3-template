#ifndef AST_H
#define AST_H

#include <string>
#include <unordered_map>
#include <list>
#include <vector>
#include <ostream>

using namespace std;

class Visitor;

// Operadores binarios soportados
enum BinaryOp
{
    PLUS_OP,
    MINUS_OP,
    MUL_OP,
    DIV_OP,
    POW_OP
};

// Clase abstracta Exp
class Exp
{
public:
    virtual int accept(Visitor *visitor) = 0;
    virtual ~Exp() = 0;                     // Destructor puro → clase abstracta
    static string binopToChar(BinaryOp op); // Conversión operador → string
};

// Expresión binaria
class BinaryExp : public Exp
{
public:
    Exp *left;
    Exp *right;
    BinaryOp op;
    int accept(Visitor *visitor);
    BinaryExp(Exp *l, Exp *r, BinaryOp op);
    ~BinaryExp();
};

// Expresión numérica
class NumberExp : public Exp
{
public:
    int value;
    int accept(Visitor *visitor);
    NumberExp(int v);
    ~NumberExp();
};

class IdExp : public Exp
{
public:
    string id;
    int accept(Visitor *visitor);
    IdExp(string id);
    ~IdExp();
};

// Raiz cuadrada
class SqrtExp : public Exp
{
public:
    Exp *value;
    int accept(Visitor *visitor);
    SqrtExp(Exp *v);
    ~SqrtExp();
};

class PowExp : public Exp
{
public:
    Exp *base;
    Exp *exponent;
    int accept(Visitor *visitor);
    PowExp(Exp *b, Exp *e);
    ~PowExp();
};

class AbsExp : public Exp
{
public:
    Exp *value;
    int accept(Visitor *visitor);
    AbsExp(Exp *v);
    ~AbsExp();
};

class MinExp : public Exp
{
public:
    list<Exp*> values;
    int accept(Visitor *visitor);
    MinExp(list<Exp*> v);
    ~MinExp();
};

class LiteralExp : public Exp
{
public:
    string value;
    int accept(Visitor *visitor);
    LiteralExp(string v);
    ~LiteralExp();
};

class Stmt
{

public:
    virtual int accept(Visitor *visitor) = 0;
    ~Stmt();
};

class PrintStmt : public Stmt
{

public:
    int accept(Visitor *visitor);
    list<Exp*> values;
    ~PrintStmt();
    PrintStmt(list<Exp*> exp);
};

class AssignStmt : public Stmt
{

public:
    int accept(Visitor *visitor);
    vector<Exp *> exs;
    vector<string> ids;
    ~AssignStmt();
    AssignStmt(vector<Exp*> es, vector<string> ids);
};

class Program
{

public:
    list<Stmt *> slist;
    Program();
    int accept(Visitor *visitor);
    ~Program();
};
#endif // AST_H
