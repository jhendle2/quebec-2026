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
