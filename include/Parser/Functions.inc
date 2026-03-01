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

// FnCall collapser
SyntaxMap(FnCallOpen, ArgListEnd, FnCall)

SyntaxMap(PrimitiveType, ParenClose, FnDeclClose)
SyntaxMap(CompoundType , ParenClose, FnDeclClose)
SyntaxMap(FnDeclOpen , FnDeclClose, FnDecl)

// Special look-ahead twice for FnCalls
SyntaxMap(Identifier, ParenOpen, FnCallOpen)
