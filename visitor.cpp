#include <iostream>
#include <fstream>
#include <cmath>
#include "ast.h"
#include "visitor.h"


using namespace std;
unordered_map<std::string, int> memoria;
const int MAX_INT = 2147483647;
///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int SqrtExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int PowExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AbsExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int MinExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Program::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int PrintStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AssignStmt::accept(Visitor* visitor) {
    return visitor->visit(this);
}

///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp* exp) {
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(SqrtExp* exp) {
    cout << "sqrt(";
    exp->value->accept(this);
    cout <<  ")";
    return 0;
}

int PrintVisitor::visit(PowExp* exp) {
    cout << "pow(";
    exp->base->accept(this);
    cout << ", ";
    exp->exponent->accept(this);
    cout << ")";
    return 0;
}

int PrintVisitor::visit(AbsExp* exp) {
    cout << "abs(";
    exp->value->accept(this);
    cout << ")";
    return 0;
}

int PrintVisitor::visit(MinExp* exp) {
    cout << "min(";
    bool first = true;
    for (Exp* e : exp->values) {
        if (!first) {
            cout << ", ";
        }
        e->accept(this);
        first = false;
    }
    cout << ")";
    return 0;
}


void PrintVisitor::imprimir(Program* programa){
    if (programa)
    {
        cout << "Codigo:" << endl; 
        programa->accept(this);
        cout << endl;
    }
    return ;
}

///////////////////////////////////////////////////////////////////////////////////
int EVALVisitor::visit(BinaryExp* exp) {
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    switch (exp->op) {
        case PLUS_OP:
            result = v1 + v2;
            break;
        case MINUS_OP:
            result = v1 - v2;
            break;
        case MUL_OP:
            result = v1 * v2;
            break;
        case DIV_OP:
            if (v2 != 0)
                result = v1 / v2;
            else {
                cout << "Error: división por cero" << endl;
                result = 0;
            }
            break;
        case POW_OP:
            result = pow(v1,v2);
            break;
        default:
            cout << "Operador desconocido" << endl;
            result = 0;
    }
    return result;
}

int EVALVisitor::visit(NumberExp* exp) {
    return exp->value;
}

int EVALVisitor::visit(SqrtExp* exp) {
    return floor(sqrt( exp->value->accept(this)));
}

int EVALVisitor::visit(PowExp* exp) {
    return pow(exp->base->accept(this), exp->exponent->accept(this));
}

int EVALVisitor::visit(AbsExp* exp) {
    return abs(exp->value->accept(this));
}

int EVALVisitor::visit(MinExp* exp) {
    int minValue = MAX_INT;
    for (Exp* e : exp->values) {
        int val = e->accept(this);
        if (val < minValue) {
            minValue = val;
        }
    }
    return minValue;
}

void EVALVisitor::interprete(Program* programa){
    if (programa)
    {
        cout << "Interprete:" << programa->accept(this)<<endl;
    }
    return;

}

///////////////////////////////////

int EVALVisitor::visit(Program *p) {
    for (auto stmt : p->slist) {
        stmt->accept(this);
    }
    return 0;
}

int EVALVisitor::visit(AssignStmt *p) {
    int v = p->e->accept(this);
    memoria[p->id] = v;
    return 0;
}

int EVALVisitor::visit(PrintStmt *p) {
    int v = p->e->accept(this);
    cout << v << endl;
    return 0;
}

int EVALVisitor::visit(IdExp *p) {
    return memoria[p->id];
}

int PrintVisitor::visit(IdExp *p) {
    cout << p->id;
    return 0;
}

int PrintVisitor::visit(Program *p) {
    for (auto stmt : p->slist) {
        stmt->accept(this);
    }
    return 0;
}

int PrintVisitor::visit(AssignStmt *p) {
    cout << p->id << " = ";
    p->e->accept(this);
    cout << endl;
    return 0;
}

int PrintVisitor::visit(PrintStmt *p) {
    cout << "print(";
    p->e->accept(this);
    cout << ")" << endl;
    return 0;
}
