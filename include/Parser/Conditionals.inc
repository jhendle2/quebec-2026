SyntaxMap(If         , Parentheses, IfCondition)
SyntaxMap(If         , Body       , SyntaxErrorIfMissingCondition)
SyntaxMap(IfCondition, Body       , IfBody)
SyntaxMap(IfCondition, WhileBody  , IfBody) // `if (...) while (...)`
SyntaxMap(IfCondition, IfBody     , IfBody) // `if (...) if (...)`
SyntaxMap(IfCondition, Statement  , IfBody)
// SyntaxMap(IfCondition, FnCall     , IfBody)
SyntaxMap(IfCondition, Statements , SyntaxErrorIfBodyAmbiguous) // FIXME: Is this really a problem?

SyntaxMap(While      , Parentheses   , WhileCondition)
SyntaxMap(While      , Body          , SyntaxErrorWhileMissingCondition)
SyntaxMap(WhileCondition, Body       , WhileBody)
SyntaxMap(WhileCondition, IfBody     , SyntaxErrorDontDoThis)
SyntaxMap(WhileCondition, IfElseBody , SyntaxErrorDontDoThis)
SyntaxMap(WhileCondition, Statement  , WhileBody)
SyntaxMap(WhileCondition, Statements , SyntaxErrorWhileBodyAmbiguous) // FIXME: Is this really a problem?

SyntaxMap(Else       , Body       , ElseBody)
SyntaxMap(Else       , IfBody     , ElseBody) // Supports `else if`
SyntaxMap(Else       , Statement  , ElseBody)
// SyntaxMap(Else       , FnCall     , ElseBody)
SyntaxMap(Else       , Statements , SyntaxErrorUnmatchedElse )
SyntaxMap(IfBody     , ElseBody   , IfElseBody )
SyntaxMap(IfElseBody , ElseBody   , IfElseBody )

SyntaxMap(For         , ParenOpen   , ForBegin )
SyntaxMap(ForBegin    , Statement   , For1     )
SyntaxMap(For1        , Statement   , For2     )
SyntaxMap(For2        , ArgListEnd  , ForCondition)
SyntaxMap(ForCondition, Body        , ForBody)
SyntaxMap(ForBody     , Body        , Bodies)
SyntaxMap(Body        , ForBody     , Bodies)
SyntaxMap(ForBody     , Bodies      , Bodies)
SyntaxMap(Bodies      , ForBody     , Bodies)
SyntaxMap(Statements, ForBody   , Bodies)
SyntaxMap(ForBody  , Statements , Bodies)