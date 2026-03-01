// Body concatenation
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

SyntaxMap(Body, Body, Bodies)
SyntaxMap(Body, Bodies, Bodies)
SyntaxMap(Bodies, Body, Bodies)
SyntaxMap(Bodies, Bodies, Bodies)

SyntaxMap(FnBody, FnBody, Bodies)
SyntaxMap(FnBody, Body, Bodies)
SyntaxMap(Body, FnBody, Bodies)
SyntaxMap(FnBody, Bodies, Bodies)
SyntaxMap(Bodies, FnBody, Bodies)

SyntaxMap(IfBody    , Body     , Bodies)
SyntaxMap(IfBody    , Bodies   , Bodies)
SyntaxMap(IfBody    , Statement, Bodies)
SyntaxMap(ElseBody  , Body     , Bodies)
SyntaxMap(ElseBody  , Bodies   , Bodies)
SyntaxMap(ElseBody  , Statement, Bodies)
SyntaxMap(IfElseBody, Body     , Bodies)
SyntaxMap(IfElseBody, Bodies   , Bodies)
SyntaxMap(IfElseBody, Statement, Bodies)

SyntaxMap(Body     , IfBody    , Bodies)
SyntaxMap(Bodies   , IfBody    , Bodies)
SyntaxMap(Statement, IfBody    , Bodies)
SyntaxMap(Body     , ElseBody  , Bodies)
SyntaxMap(Bodies   , ElseBody  , Bodies)
SyntaxMap(Statement, ElseBody  , Bodies)
SyntaxMap(Body     , IfElseBody, Bodies)
SyntaxMap(Bodies   , IfElseBody, Bodies)
SyntaxMap(Statement, IfElseBody, Bodies)


SyntaxMap(Statement, ElseBody, SyntaxErrorUnmatchedElse)
SyntaxMap(Body     , ElseBody, SyntaxErrorUnmatchedElse)
SyntaxMap(Bodies   , ElseBody, SyntaxErrorUnmatchedElse)

// Body building
SyntaxMap(Statement , BraceClose, BodyEnd)
SyntaxMap(ReturnStmt, BraceClose, BodyEnd)
SyntaxMap(Statements, BraceClose, BodyEnd)

SyntaxMap(BraceOpen , BraceClose, Body) // Simplest body, `{ }`
SyntaxMap(BraceOpen , BodyEnd, Body)
