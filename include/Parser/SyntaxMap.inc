// ================================================================
// Types
SyntaxMap(PrimitiveType, PrimitiveType, CompoundType)
SyntaxMap(Modifier     , PrimitiveType, CompoundType)
SyntaxMap(Modifier     , CompoundType , CompoundType)
SyntaxMap(Modifier     , Modifier     , Modifier    )
SyntaxMap(CompoundType , CompoundType , CompoundType)

SyntaxMap(PrimitiveType, Multiply     , CompoundType)
SyntaxMap(Modifier     , Multiply     , CompoundType)
SyntaxMap(CompoundType , Multiply     , CompoundType)

// ================================================================
// Declarations
SyntaxMap(PrimitiveType, Identifier, Declaration)
SyntaxMap(CompoundType , Identifier, Declaration)

// ================================================================
// Function Params
SyntaxMap(Declaration, ParenOpen, FnDeclOpen)
SyntaxMap(FnDeclOpen, ParenClose, FnDecl)
SyntaxMap(Declaration, Comma, Param)
SyntaxMap(PrimitiveType, Comma, Param)
SyntaxMap(CompoundType, Comma, Param)
SyntaxMap(Declaration, ParenClose, FinalParam)
SyntaxMap(PrimitiveType, ParenClose, FinalParam)
SyntaxMap(CompoundType, ParenClose, FinalParam)
SyntaxMap(Ellipse, ParenClose, FinalParam)
SyntaxMap(Param , Param     , Params)
SyntaxMap(Param , FinalParam, ParamList)
SyntaxMap(Params, FinalParam, ParamList)
SyntaxMap(FnDeclOpen, FinalParam, FnDecl)
SyntaxMap(FnDeclOpen, ParamList, FnDecl)

// ================================================================
// Bodies
SyntaxMap(BraceOpen, BraceClose, Body)
SyntaxMap(FnDecl, Body, FnBody)
SyntaxMap(Statement, BraceClose, BodyEnd)
SyntaxMap(Statements, BraceClose, BodyEnd)
SyntaxMap(BraceOpen, BodyEnd, Body)
SyntaxMap(FnBody, FnBody, Bodies)
SyntaxMap(FnBody, Body, Bodies)
SyntaxMap(FnBody, Bodies, Bodies)
SyntaxMap(Body, FnBody, Bodies)
SyntaxMap(Bodies, FnBody, Bodies)
SyntaxMap(Statement, Body, Bodies)
SyntaxMap(Statement, FnBody, Bodies)
SyntaxMap(Statement, Bodies, Bodies)
SyntaxMap(Body, Statement, Bodies)
SyntaxMap(FnBody, Statement, Bodies)
SyntaxMap(Bodies, Statement, Bodies)

// ================================================================
// Statements
SyntaxMap(Declaration, Semicolon, Statement)
SyntaxMap(FnDecl, Semicolon, Statement)
SyntaxMap(Statement, Statement, Statements)
SyntaxMap(Statements, Statement, Statements)

// ================================================================
// Function Calls
SyntaxMap(Identifier, ParenOpen, FnCallOpen)

SyntaxMap(Identifier, ParenClose, FinalArg)
SyntaxMap(ConstInt, ParenClose, FinalArg)
SyntaxMap(ConstFloat, ParenClose, FinalArg)
SyntaxMap(ConstString, ParenClose, FinalArg)
SyntaxMap(ConstChar, ParenClose, FinalArg)

SyntaxMap(Identifier, Comma, Arg)
SyntaxMap(ConstInt, Comma, Arg)
SyntaxMap(ConstFloat, Comma, Arg)
SyntaxMap(ConstString, Comma, Arg)
SyntaxMap(ConstChar, Comma, Arg)

SyntaxMap(Arg, FinalArg, ArgsEnd)

SyntaxMap(FnCallOpen, FinalArg, FnCall)
SyntaxMap(FnCallOpen, ArgsEnd, FnCall)
SyntaxMap(FnCall, Semicolon, Statement)

// ================================================================
// Expressions
SyntaxMap(Identifier , Plus, Exprand)
SyntaxMap(ConstInt   , Plus, Exprand)
SyntaxMap(ConstFloat , Plus, Exprand)
SyntaxMap(ConstString, Plus, Exprand)
SyntaxMap(ConstChar  , Plus, Exprand)
SyntaxMap(Expression , Plus, Exprand)

SyntaxMap(Identifier , Minus, Exprand)
SyntaxMap(ConstInt   , Minus, Exprand)
SyntaxMap(ConstFloat , Minus, Exprand)
SyntaxMap(ConstString, Minus, Exprand)
SyntaxMap(ConstChar  , Minus, Exprand)
SyntaxMap(Expression , Minus, Exprand)

SyntaxMap(Identifier , Multiply, Exprand)
SyntaxMap(ConstInt   , Multiply, Exprand)
SyntaxMap(ConstFloat , Multiply, Exprand)
SyntaxMap(ConstString, Multiply, Exprand)
SyntaxMap(ConstChar  , Multiply, Exprand)
SyntaxMap(Expression , Multiply, Exprand)

SyntaxMap(Identifier , Divide, Exprand)
SyntaxMap(ConstInt   , Divide, Exprand)
SyntaxMap(ConstFloat , Divide, Exprand)
SyntaxMap(ConstString, Divide, Exprand)
SyntaxMap(ConstChar  , Divide, Exprand)
SyntaxMap(Expression , Divide, Exprand)

SyntaxMap(Identifier , Assign, Exprand)
SyntaxMap(ConstInt   , Assign, Exprand)
SyntaxMap(ConstFloat , Assign, Exprand)
SyntaxMap(ConstString, Assign, Exprand)
SyntaxMap(ConstChar  , Assign, Exprand)
SyntaxMap(Expression , Assign, Exprand)

SyntaxMap(Exprand, Identifier , Expression)
SyntaxMap(Exprand, ConstInt   , Expression)
SyntaxMap(Exprand, ConstFloat , Expression)
SyntaxMap(Exprand, ConstString, Expression)
SyntaxMap(Exprand, ConstString, Expression)

SyntaxMap(Declaration, Assign, Exprand)

SyntaxMap(Expression, Semicolon  , Statement)

// ================================================================
// Returns
SyntaxMap(Return    , Semicolon  , Statement)
SyntaxMap(ReturnExpr, Semicolon  , Statement)

SyntaxMap(Return, Expression , ReturnExpr)
SyntaxMap(Return, ConstInt , ReturnExpr)
SyntaxMap(Return, ConstFloat , ReturnExpr)
SyntaxMap(Return, ConstString , ReturnExpr)
SyntaxMap(Return, ConstChar , ReturnExpr)
SyntaxMap(Return, FnCall   , ReturnExpr)