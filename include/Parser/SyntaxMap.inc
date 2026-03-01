// Typing
SyntaxMap(PrimitiveType, PrimitiveType, CompoundType) // `long long`
SyntaxMap(CompoundType , CompoundType , CompoundType) // `long long int`
SyntaxMap(PrimitiveType, CompoundType , CompoundType) // FIXME: Does this ever happen?
SyntaxMap(Modifier     , CompoundType , CompoundType) // `const char*`
SyntaxMap(Modifier     , PrimitiveType, CompoundType) // `const int`
SyntaxMap(PrimitiveType, Multiply     , CompoundType) // `char*`
SyntaxMap(CompoundType , Multiply     , CompoundType) // `static const char*`

// Declarations
SyntaxMap(PrimitiveType, Identifier, Declaration)
SyntaxMap(CompoundType , Identifier, Declaration)

// Function declarations
SyntaxMap(PrimitiveType, FnCallOpen, FnDeclOpen)
SyntaxMap(CompoundType , FnCallOpen, FnDeclOpen)
SyntaxMap(FnDeclOpen   , ParenClose, FnDecl)
SyntaxMap(FnDecl       , Body      , FnBody)

// Function parameters
SyntaxMap(PrimitiveType, ParenClose, FnDeclClose)
SyntaxMap(CompoundType , ParenClose, FnDeclClose)
SyntaxMap(Declaration  , ParenClose, FnDeclClose)
SyntaxMap(Ellipse      , ParenClose, FnDeclClose)
SyntaxMap(Declaration  , Comma     , FnParam)
SyntaxMap(PrimitiveType, Comma     , FnParam)
SyntaxMap(CompoundType , Comma     , FnParam)
SyntaxMap(FnParam      , FnParam   , FnParams)
SyntaxMap(FnParam      , FnParams  , FnParams)
SyntaxMap(FnParams     , FnParam   , FnParams)
SyntaxMap(FnParam      , FnDeclClose, FnDeclClose)
SyntaxMap(FnParams     , FnDeclClose, FnDeclClose)

// Monops
SyntaxMap(Identifier , Increment, Expression)
SyntaxMap(ConstInt   , Increment, Expression)
SyntaxMap(ConstFloat , Increment, Expression)
SyntaxMap(ConstString, Increment, Expression)
SyntaxMap(ConstChar  , Increment, Expression)
SyntaxMap(Expression , Increment, Expression)
SyntaxMap(Parentheses, Increment, Expression)
SyntaxMap(FnCall     , Increment, Expression)

// Binops
SyntaxMap(Identifier , Plus, Exprand)
SyntaxMap(ConstInt   , Plus, Exprand)
SyntaxMap(ConstFloat , Plus, Exprand)
SyntaxMap(ConstString, Plus, Exprand)
SyntaxMap(ConstChar  , Plus, Exprand)
SyntaxMap(Expression , Plus, Exprand)
SyntaxMap(Parentheses, Plus, Exprand)
SyntaxMap(FnCall     , Plus, Exprand)

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

// Statement building
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

SyntaxMap(Statement  , Body       , Bodies)
SyntaxMap(Statements , Body       , Bodies)
SyntaxMap(Statement  , Bodies     , Bodies)
SyntaxMap(Statements , Bodies     , Bodies)
SyntaxMap(Statement  , FnBody     , Bodies)
SyntaxMap(Statements , FnBody     , Bodies)

SyntaxMap(Body       , Statement  , Bodies)
SyntaxMap(Body       , Statements , Bodies)
SyntaxMap(Bodies     , Statement  , Bodies)
SyntaxMap(Bodies     , Statements , Bodies)
SyntaxMap(FnBody     , Statement  , Bodies)
SyntaxMap(FnBody     , Statements , Bodies)

SyntaxMap(Return     , Expression, ReturnExpr)
SyntaxMap(ReturnExpr , Statement , ReturnStmt)
SyntaxMap(Return     , Statement , ReturnStmt)

// FnCall collapser
SyntaxMap(FnCallOpen, ArgListEnd, FnCall)

SyntaxMap(PrimitiveType, ParenClose, FnDeclClose)
SyntaxMap(CompoundType , ParenClose, FnDeclClose)
SyntaxMap(FnDeclOpen , FnDeclClose, FnDecl)

// Special look-ahead twice for FnCalls
SyntaxMap(Identifier, ParenOpen, FnCallOpen)

// Statements
SyntaxMap(Statement , Statement, Statements)

SyntaxMap(ReturnStmt, Statement , Statements)
SyntaxMap(Statement , ReturnStmt, Statements)
SyntaxMap(ReturnStmt, ReturnStmt, Statements)

SyntaxMap(ReturnStmt, Statements, Statements)
SyntaxMap(Statements, ReturnStmt, Statements)

// Body building
SyntaxMap(Statement , BraceClose, BodyEnd)
SyntaxMap(ReturnStmt, BraceClose, BodyEnd)
SyntaxMap(Statements, BraceClose, BodyEnd)

SyntaxMap(BraceOpen , BodyEnd, Body)

// Body concatenation
SyntaxMap(Body, Body, Bodies)
SyntaxMap(Body, Bodies, Bodies)
SyntaxMap(Bodies, Body, Bodies)

SyntaxMap(FnBody, Body, Bodies)
SyntaxMap(Body, FnBody, Bodies)
SyntaxMap(FnBody, Bodies, Bodies)
SyntaxMap(Bodies, FnBody, Bodies)