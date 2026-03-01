// ================================================================
#include "Typing.inc"

// ================================================================
#include "Functions.inc"

// ================================================================
// Monops
#include "Monops.inc"

// ================================================================
// Binops
#include "Binops.inc"

// ================================================================
// Args
SyntaxMap(Identifier , Comma, Arg)
SyntaxMap(ConstInt   , Comma, Arg)
SyntaxMap(ConstFloat , Comma, Arg)
SyntaxMap(ConstString, Comma, Arg)
SyntaxMap(ConstChar  , Comma, Arg)
SyntaxMap(Expression , Comma, Arg)
SyntaxMap(Parentheses, Comma, Arg)
SyntaxMap(FnCall     , Comma, Arg)

// Arg concatenation
SyntaxMap(Arg        , Arg       , Args)
SyntaxMap(Args       , Arg       , Args)
SyntaxMap(Args       , ArgListEnd, ArgListEnd)
SyntaxMap(Arg        , ArgListEnd, ArgListEnd)

// Arg ending
SyntaxMap(Identifier , ParenClose, ArgListEnd)
SyntaxMap(ConstInt   , ParenClose, ArgListEnd)
SyntaxMap(ConstFloat , ParenClose, ArgListEnd)
SyntaxMap(ConstString, ParenClose, ArgListEnd)
SyntaxMap(ConstChar  , ParenClose, ArgListEnd)
SyntaxMap(Expression , ParenClose, ArgListEnd)
SyntaxMap(Parentheses, ParenClose, ArgListEnd)
SyntaxMap(FnCall     , ParenClose, ArgListEnd)

// Arg/parentheses beginning
SyntaxMap(ParenOpen, Arg       , ArgListBegin)
SyntaxMap(ParenOpen, ArgListEnd, Parentheses)

// Expression building
SyntaxMap(Exprand, Identifier , Expression)
SyntaxMap(Exprand, ConstInt   , Expression)
SyntaxMap(Exprand, ConstFloat , Expression)
SyntaxMap(Exprand, ConstString, Expression)
SyntaxMap(Exprand, ConstChar  , Expression)
SyntaxMap(Exprand, Expression , Expression)
SyntaxMap(Exprand, Parentheses, Expression)
SyntaxMap(Exprand, FnCall     , Expression)

// ================================================================
// Statements
// ----------------------------------------------------------------
// Statement building
SyntaxMap(Declaration, Semicolon, Statement)
SyntaxMap(Expression , Semicolon, Statement)
SyntaxMap(Parentheses, Semicolon, Statement)
SyntaxMap(FnCall     , Semicolon, Statement)

SyntaxMap(Identifier , Semicolon, Statement)
SyntaxMap(ConstInt   , Semicolon, Statement)
SyntaxMap(ConstFloat , Semicolon, Statement)
SyntaxMap(ConstString, Semicolon, Statement)
SyntaxMap(ConstChar  , Semicolon, Statement)
SyntaxMap(Expression , Semicolon, Statement)
SyntaxMap(Parentheses, Semicolon, Statement)
SyntaxMap(FnCall     , Semicolon, Statement)
SyntaxMap(FnDecl     , Semicolon, Statement)

SyntaxMap(Return     , Expression, ReturnExpr)
SyntaxMap(ReturnExpr , Statement , ReturnStmt)
SyntaxMap(ReturnExpr , Semicolon , ReturnStmt)
SyntaxMap(Return     , Statement , ReturnStmt)

SyntaxMap(Statement , Statement, Statements)

// ================================================================
// Return
#include "Return.inc"

// ================================================================
// Bodies
#include "Body.inc"

// ================================================================
// Conditionals
#include "Conditionals.inc"

