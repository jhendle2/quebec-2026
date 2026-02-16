// ================================================================
//        Left         + Right         -> Result
SyntaxMap(PrimitiveType, PrimitiveType  , CompoundType)
SyntaxMap(Const        , PrimitiveType  , CompoundType)
SyntaxMap(Modifier     , PrimitiveType  , CompoundType)
SyntaxMap(CompoundType , PrimitiveType  , CompoundType)
SyntaxMap(CompoundType , CompoundType   , CompoundType)

SyntaxMap(Expression   , Operator       , Expression  )
SyntaxMap(Expression   , Exprand        , Expression  )
SyntaxMap(Operator     , Identifier     , Exprand     )
SyntaxMap(Operator     , ConstInt       , Exprand     )
SyntaxMap(Operator     , ConstFloat     , Exprand     )
SyntaxMap(Operator     , ConstString    , Exprand     )
SyntaxMap(Operator     , ConstChar      , Exprand     )

SyntaxMap(Expression   , Semicolon      , Statement   )

SyntaxMap(PrimitiveType, Identifier     , Declaration )
SyntaxMap(CompoundType , Identifier     , Declaration )

SyntaxMap(ParenOpen    , ParenClose      , Params      )
SyntaxMap(Declaration  , Params          , FnParams    )
SyntaxMap(PrimitiveType, ParenClose      , FnParamsEnd )
SyntaxMap(ParenOpen    , FnParamsEnd     , FnParams    )
SyntaxMap(Declaration  , FnBody    , FnDefn    )

SyntaxMap(ParenOpen    , ConstInt        , ArgsBegin   )
SyntaxMap(ParenOpen    , ConstFloat        , ArgsBegin   )
SyntaxMap(ParenOpen    , ConstString        , ArgsBegin   )
SyntaxMap(ParenOpen    , ConstChar        , ArgsBegin   )
SyntaxMap(ArgsBegin    , ParenClose        , Args   )
SyntaxMap(Identifier    , Args        , FnCall   )
SyntaxMap(FnCall    , Semicolon        , Statement   )

SyntaxMap(BraceOpen   , BraceClose      , Body        )
SyntaxMap(BraceOpen   , BodyEnd         , Body        )

SyntaxMap(ConstInt    , Semicolon       , Statement   )
SyntaxMap(ConstFloat  , Semicolon       , Statement   )
SyntaxMap(ConstString , Semicolon       , Statement   )
SyntaxMap(ConstChar   , Semicolon       , Statement   )
SyntaxMap(Exprand     , Semicolon       , Statement   )
SyntaxMap(Expression  , Semicolon       , Statement   )
SyntaxMap(Return      , Statement       , ReturnStmt  )

SyntaxMap(Statement   , BraceClose      , BodyEnd     )
SyntaxMap(Statements   , BraceClose     , BodyEnd     )
SyntaxMap(ReturnStmt  , BraceClose      , BodyEnd     )
SyntaxMap(FnParams    , Body            , FnBody    )

SyntaxMap(Statement    , Statement            , Statements    )
SyntaxMap(Statement    , ReturnStmt            , Statements    )

SyntaxMap(FnDecl    , FnDecl            , Functions    )