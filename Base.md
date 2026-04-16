# Lenguaje implementado en parser.cpp

El parser implementa un lenguaje imperativo muy pequeño de **asignaciones** y **salida por impresión** con expresiones aritméticas.

## Estructura general

Un programa es una lista de sentencias separadas por `;`.

Gramática aproximada (EBNF):

```ebnf
Program   ::= Stmt (';' Stmt)*
Stmt      ::= ID '=' CExp
           | 'print' '(' CExp ')'

CExp      ::= E (('+' | '-') E)*
E         ::= T (('*' | '/') T)*
T         ::= F ('**' F)?
F         ::= NUM
           | ID
           | '(' CExp ')'
           | 'sqrt' '(' CExp ')'
```

Voy a extenderlo a 
```ebnf
Program   ::= Stmt (';' Stmt)*
Stmt      ::= ID '=' CExp
           |  'print' '(' PrintArg (',' PrintArg)* ')' 
PrintArg ::= CExp | String
CExp      ::= E (('+' | '-') E)*
E         ::= T (('*' | '/') T)*
T         ::= F ('**' F)?
F         ::= NUM
           | ID
           | '(' CExp ')'
           | 'sqrt' '(' CExp ')'
           | 'pow' '(' CExp ',' CExp ')'
           | 'abs' '(' CExp ')'
           | 'min' '(' CExp (',' CExp)* ')'
```

## Tokens y construcciones soportadas

- Variables: `ID`
- Números enteros: `NUM`
- Asignación: `=`
- Separador de sentencias: `;`
- Impresión: `print(...)`
- Operadores aritméticos: `+`, `-`, `*`, `/`, `**`
- Función unaria: `sqrt(...)`
- Paréntesis para agrupar: `(` `)`

## Observaciones de precedencia

- Menor precedencia: `+` y `-`
- Intermedia: `*` y `/`
- Mayor: `**` (potencia)
- También existe `sqrt(...)` como forma atómica en `F`

## Nota técnica

En `parseStmt()` se hace `match(Token::ASSIGN)` y otros `match(...)` sin validar explícitamente el resultado; por eso, el parser actual puede aceptar algunas entradas inválidas hasta fallar más adelante en otra regla.
