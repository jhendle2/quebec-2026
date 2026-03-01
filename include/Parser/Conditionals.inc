SyntaxMap(If         , Parentheses, IfCondition)
SyntaxMap(If         , Body       , SyntaxErrorIfMissingCondition)
SyntaxMap(IfCondition, Body       , IfBody)
SyntaxMap(IfCondition, Statement  , IfBody)
SyntaxMap(IfCondition, Statements , SyntaxErrorIfBodyAmbiguous) // FIXME: Is this really a problem?

SyntaxMap(Else       , Body       , ElseBody)
SyntaxMap(Else       , IfBody     , ElseBody) // Supports `else if`
SyntaxMap(Else       , Statement  , ElseBody)
SyntaxMap(Else       , Statements , SyntaxErrorUnmatchedElse )
SyntaxMap(IfBody     , ElseBody   , IfElseBody )