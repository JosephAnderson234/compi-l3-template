#include <iostream>
#include <stdexcept>
#include "token.h"
#include "scanner.h"
#include "ast.h"
#include "parser.h"

using namespace std;

// =============================
// Métodos de la clase Parser
// =============================

Parser::Parser(Scanner* sc) : scanner(sc) {
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        throw runtime_error("Error léxico");
    }
}

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;

        if (check(Token::ERR)) {
            throw runtime_error("Error lexico");
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}


// =============================
// Reglas gramaticales
// =============================

Program* Parser::parseProgram() {
    Program* ast = parseP();
    if (!isAtEnd()) {
        throw runtime_error("Error sintáctico");
    }
    cout << "Parseo exitoso" << endl;
    return ast;
}


Program* Parser::parseP() {
    Program* program = new Program();
    program->slist.push_back(parseStmt());
    while(match(Token::SEMICOLON)) {
        program->slist.push_back(parseStmt());
    }
    return program;
}


Stmt* Parser::parseStmt() {
    Exp* e;
    if (match(Token::ID)){
        string id = previous->text;
        match(Token::ASSIGN);
        e = parseCExp();
        return new AssignStmt(e, id);
    }
    if (match(Token::PRINT)){
        match(Token::LPAREN);
        e = parseCExp();
        match(Token::RPAREN);
        return new PrintStmt(e);
    }
    return nullptr; // En caso de no coincidir con ninguna regla de sentencia
}
Exp* Parser::parseCExp() {
    Exp* l = parseE();
    while (match(Token::PLUS) || match(Token::MINUS)) {
        BinaryOp op;
        if (previous->type == Token::PLUS){
            op = PLUS_OP;
        }
        else{
            op = MINUS_OP;
        }
        Exp* r = parseE();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseE() {
    Exp* l = parseT();
    while (match(Token::MUL) || match(Token::DIV)) {
        BinaryOp op;
        if (previous->type == Token::MUL){
            op = MUL_OP;
        }
        else{
            op = DIV_OP;
        }
        Exp* r = parseT();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseT() {
    Exp* l = parseF();
    if (match(Token::POW)) {
        BinaryOp op = POW_OP;
        Exp* r = parseF();
        l = new BinaryExp(l, r, op);
    }
    return l;
}

Exp* Parser::parseF() {
    Exp* e; 
    if (match(Token::NUM)) {
        return new NumberExp(stoi(previous->text));
    } 
    else if (match(Token::ID)) {
        return new IdExp(previous->text);
    }
    else if (match(Token::LPAREN))
    {
        e = parseCExp();
        match(Token::RPAREN);
        return e;
    }
    else if (match(Token::SQRT))
    {   
        match(Token::LPAREN);
        e = parseCExp();
        match(Token::RPAREN);
        return new SqrtExp(e);
    } else if (match(Token::ABS_OP)) {
        match(Token::LPAREN);
        e = parseCExp();
        match(Token::RPAREN);
        return new AbsExp(e);
    } else if (match(Token::MIN_OP)) {
        match(Token::LPAREN);
        list<Exp*> values;
        values.push_back(parseCExp());
        while (match(Token::COMMA)) {
            values.push_back(parseCExp());
        }
        match(Token::RPAREN);
        return new MinExp(values);
    } else if (match(Token::POW_OP)) {
        match(Token::LPAREN);
        Exp* base = parseCExp();
        match(Token::COMMA);
        Exp* exponent = parseCExp();
        match(Token::RPAREN);
        return new PowExp(base, exponent);
    }
    else {
        throw runtime_error("Error sintáctico");
    }
}
