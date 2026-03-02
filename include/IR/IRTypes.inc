IRType(Noop   , 0) // Noop
IRType(Declare, 2) // Declare Type Identifier
IRType(Test   , 1) // Test Identifier
// IRType(Define , 2) // Define  Identifier Type

IRType(Load, 2) // Load Identifier Value 
IRType(Move, 2) // Load Identifier Identifier 

IRType(Return , 0) // Declare Identifier Type

IRType(Enter , 0) // Enter -- Create stack frame
IRType(Exit  , 0) // Exit  -- Delete stack frame

// IRType(Label  , 1) // Label   Identifier