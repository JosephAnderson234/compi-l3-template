#include <iostream>
#include <fstream>
#include <cmath>
#include "ast.h"
#include "visitor.h"

using namespace std;
unordered_map<std::string, int> memoria;
const int MAX_INT = 2147483647;
///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int NumberExp::accept(Visitor *visitor){
    return visitor->visit(this);
}


int SqrtExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int PowExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}


int AbsExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}


int MinExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}

int IdExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}


int Program::accept(Visitor *visitor)
{
    return visitor->visit(this);
}


int PrintStmt::accept(Visitor *visitor)

{
    return visitor->visit(this);
}


int AssignStmt::accept(Visitor *visitor)
{
    return visitor->visit(this);
}


int LiteralExp::accept(Visitor *visitor)
{
    return visitor->visit(this);
}
// asumimos que existen la firma de las siguientes calses
// MaxExp(CExp, CExp,...), IfExp, UnaryExp
int MaxExp::accept(Visitor *visitor) {
    return->visitor->visit(this);
}

int IfExp::accept(Visitor *visitor) {
    return->visitor->visit(this);
}

int UnaryExp::accept(Visitor *visitor) {
    return->visitor->visit(this);
}
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
int PrintVisitor::visit(BinaryExp *exp)
{
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp *exp)
{
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(SqrtExp *exp)
{
    cout << "sqrt(";
    exp->value->accept(this);
    cout << ")";
    return 0;
}

int PrintVisitor::visit(PowExp *exp)
{
    cout << "pow(";
    exp->base->accept(this);
    cout << ", ";
    exp->exponent->accept(this);
    cout << ")";
    return 0;
}

int PrintVisitor::visit(AbsExp *exp)
{
    cout << "abs(";
    exp->value->accept(this);
    cout << ")";
    return 0;
}

int PrintVisitor::visit(MinExp *exp)
{
    cout << "min(";
    bool first = true;
    for (Exp *e : exp->values)
    {
        if (!first)
        {
            cout << ", ";
        }
        e->accept(this);
        first = false;
    }
    cout << ")";
    return 0;
}


int PrintVisitor::visit(LiteralExp *exp)
{
    cout << exp->value;
    return 0;
}

void PrintVisitor::imprimir(Program *programa)
{
    if (programa)
    {
        cout << "Codigo:" << endl;
        programa->accept(this);
        cout << endl;
    }
    return;
}

///////////////////////////////////////////////////////////////////////////////////
int EVALVisitor::visit(BinaryExp *exp)
{
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    switch (exp->op)
    {
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
        else
        {
            cout << "Error: división por cero" << endl;
            result = 0;
        }
        break;
    case POW_OP:
        result = pow(v1, v2);
        break;
    default:
        cout << "Operador desconocido" << endl;
        result = 0;
    }
    return result;
}

int EVALVisitor::visit(NumberExp *exp)
{
    return exp->value;
}

int EVALVisitor::visit(SqrtExp *exp)
{
    return floor(sqrt(exp->value->accept(this)));
}

int EVALVisitor::visit(PowExp *exp)
{
    return pow(exp->base->accept(this), exp->exponent->accept(this));
}

int EVALVisitor::visit(AbsExp *exp)
{
    return abs(exp->value->accept(this));
}

int EVALVisitor::visit(MinExp *exp)
{
    int minValue = MAX_INT;
    for (Exp *e : exp->values)
    {
        int val = e->accept(this);
        if (val < minValue)
        {
            minValue = val;
        }
    }
    return minValue;
}


int EVALVisitor::visit(LiteralExp *exp)
{
    return 0; // No se evalúa a un número, pero se devuelve 0 para cumplir con la firma del método
}

void EVALVisitor::interprete(Program *programa)
{
    if (programa)
    {
        cout << "Interprete:" << programa->accept(this) << endl;
    }
    return;
}

///////////////////////////////////

int EVALVisitor::visit(Program *p)
{
    for (auto stmt : p->slist)
    {
        stmt->accept(this);
    }
    return 0;
}

int EVALVisitor::visit(AssignStmt *p)
{
    for (size_t i = 0; i < p->exs.size(); ++i)
    {
        int v = p->exs[i]->accept(this);
        memoria[p->ids[i]] = v;
    }
    return 0;
}


int EVALVisitor::visit(PrintStmt*  p)
{
    for (Exp *e : p->values)
    {
        if (LiteralExp *lit = dynamic_cast<LiteralExp *>(e))
        {
            cout << lit->value << " ";
        }
        else
        {
            int v = e->accept(this);
            cout << v << " ";
        }
    }
    cout << endl;
    return 0;
}

int EVALVisitor::visit(MaxExp* max) {
    int v = 0;
    for (auto e : max->values) {
        v = e->accept(this);
        if (v > max->value) {
            max->value = v;
        }
    }
    return v;
}

int EVALVisitor::visit(IfExp* ie) {

}

int EVALVisitor::visit(IdExp *p)
{
    return memoria[p->id];
}

int PrintVisitor::visit(IdExp *p)
{
    cout << p->id;
    return 0;
}

int PrintVisitor::visit(Program *p)
{
    for (auto stmt : p->slist)
    {
        stmt->accept(this);
    }
    return 0;
}

int PrintVisitor::visit(AssignStmt *p)
{
    for (size_t i = 0; i < p->exs.size(); ++i)
    {
        cout << p->ids[i] << " = ";
        p->exs[i]->accept(this);
        cout << endl;
    }
    cout << endl;
    return 0;
}

int PrintVisitor::visit(PrintStmt *p)
{
    cout << "print(";
    bool first = true;
    for (Exp *e : p->values)
    {
        if (!first)
        {
            cout << ", ";
        }
        e->accept(this);
        first = false;
    }
    cout << ")" << endl;
    return 0;
}

///////For AstVisitor support
int AstVisitor::visit(BinaryExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\""
        << Exp::binopToChar(exp->op) << "\"];\n";

    if (exp->left)
    {
        int leftId = id;
        exp->left->accept(this);
        out << "  node" << myId << " -> node" << leftId << ";\n";
    }

    if (exp->right)
    {
        int rightId = id;
        exp->right->accept(this);
        out << "  node" << myId << " -> node" << rightId << ";\n";
    }

    return 0;
}

int AstVisitor::visit(NumberExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"" << exp->value << "\"];\n";
    return 0;
}

int AstVisitor::visit(SqrtExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"sqrt\"];\n";
    if (exp->value)
    {
        int childId = id;
        exp->value->accept(this); // genera el nodo hijo
        out << "  node" << myId << " -> node" << childId << ";\n";
    }
    return 0;
}

int AstVisitor::visit(IdExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"" << exp->id << "\"];\n";
    return 0;
}

int AstVisitor::visit(Program *p)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"Program\"];\n";
    for (auto stmt : p->slist)
    {
        int childId = id;
        stmt->accept(this);
        out << "  node" << myId << " -> node" << childId << ";\n";
    }
    return 0;
}

int AstVisitor::visit(PrintStmt *stm)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"PrintStmt\"];\n";
    for (Exp *e : stm->values)
    {
        if (e)
        {
            int childId = id;
            e->accept(this);
            out << "  node" << myId << " -> node" << childId << ";\n";
        }
    }
    return 0;
}

int AstVisitor::visit(AssignStmt *stm)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"AssignStmt\"];\n";
    for (size_t i = 0; i < stm->exs.size(); ++i)
    {
        int childId = id;
        stm->exs[i]->accept(this);
        out << "  node" << myId << " -> node" << childId << " [label=\"" << stm->ids[i] << "\"];\n";
    }
    return 0;
}

int AstVisitor::visit(PowExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"pow\"];\n";
    if (exp->base)
    {
        int baseId = id;
        exp->base->accept(this);
        out << "  node" << myId << " -> node" << baseId << ";\n";
    }
    if (exp->exponent)
    {
        int expId = id;
        exp->exponent->accept(this);
        out << "  node" << myId << " -> node" << expId << ";\n";
    }
    return 0;
}

int AstVisitor::visit(AbsExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"abs\"];\n";
    if (exp->value)
    {
        int childId = id;
        exp->value->accept(this);
        out << "  node" << myId << " -> node" << childId << ";\n";
    }
    return 0;
}

int AstVisitor::visit(MinExp *exp)
{
    int myId = id++;
    out << "  node" << myId << " [label=\"min\"];\n";
    for (Exp *e : exp->values)
    {
        if (e)
        {
            int childId = id;
            e->accept(this);
            out << "  node" << myId << " -> node" << childId << ";\n";
        }
    }
    return 0;
}

void AstVisitor::arbol(Program *programa)
{
    ofstream file("ast.dot");
    out.rdbuf(file.rdbuf()); // redirige el ostream interno al archivo
    id = 0;
    out << "digraph AST {\n";
    if (!programa)
    {
        // Árbol vacío
        out << "  empty [label=\"<arbol vacio>\"];\n";
    }
    else
    {
        programa->accept(this);
    }
    out << "}\n";
}