#include "ast.h"
#include <iostream>

using namespace std;

// ------------------ Exp ------------------
Exp::~Exp() {}

string Exp::binopToChar(BinaryOp op) {
    switch (op) {
        case PLUS_OP:  return "+";
        case MINUS_OP: return "-";
        case MUL_OP:   return "*";
        case DIV_OP:   return "/";
        case POW_OP:   return "**";
        default:       return "?";
    }
}

// ------------------ BinaryExp ------------------
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp o)
    : left(l), right(r), op(o) {}

    
BinaryExp::~BinaryExp() {
    delete left;
    delete right;
}



// ------------------ NumberExp ------------------
NumberExp::NumberExp(int v) : value(v) {}

NumberExp::~NumberExp() {}


IdExp::IdExp(string id) : id(id) {}
IdExp::~IdExp() {}

// ------------------ SqrtExp ------------------
SqrtExp::SqrtExp(Exp* v) : value(v) {}

SqrtExp::~SqrtExp() {}


PowExp::PowExp(Exp* b, Exp* e) : base(b), exponent(e) {}
PowExp::~PowExp() {
    delete base;
    delete exponent;
}

AbsExp::AbsExp(Exp* v) : value(v) {}
AbsExp::~AbsExp() {}

MinExp::MinExp(list<Exp*> v) : values(v) {}
MinExp::~MinExp() {
    for (Exp* exp : values) {
        delete exp;
    }
}

// ------------------------------------------------


Program::Program() {}
Program::~Program() {}
Stmt::~Stmt(){}
PrintStmt::~PrintStmt() {}
AssignStmt::~AssignStmt() {}
PrintStmt::PrintStmt(Exp *exp) {e=exp;}
AssignStmt::AssignStmt(Exp *exp, string ide) {e=exp;id=ide;}


