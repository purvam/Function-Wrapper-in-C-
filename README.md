# Function-Wrapper-in-C-++

Implemented exception-safe subset of std::function by using veriadic function template.

Programmed to work with free functions, lambda functions and functor objects.

Template

Declaration	Description
template <typename> class Function;	Undefined, allows partial specialization.
template <typename ResultType, typename ... ArgumentTypes> class Function<ResultType(ArgumentTypes...)>;	A specialization used to parse function signature types.
Public Member Functions

Prototype	Description
Constructors, Assignment Operators, and Destructor
Function();	Constructs a function wrapper that does not yet reference a target function.
template <typename FunctionType> Function(FunctionType);	Constructs a function wrapper with a function of FunctionType as its target.
Function(const Function &);	Copy construct from an existing cs540::Function
Function &operator=(const Function &);
          	Copy assignment.
Must handle self assignment.
Must be able to freely assign between cs540::Function objects that contain a free function, lambda, or functor given that they have the same type signature.
~Function();	Properly destroy the object and clear any memory as necessary.
Functionality
ResultType operator()(ArgumentTypes...);	Call the wrapped function target with the given arguments and return its result.
Throw cs540::BadFunctionCall if a callable function is not stored.
Observers
explicit operator bool() const;	Return true if the cs540::Function references a callable function and false otherwise.
Non-member (Free) Functions

Prototype	Description
template <typename ResultType, typename... ArgumentTypes>
bool operator==(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t);
template <typename ResultType, typename... ArgumentTypes>
bool operator==(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> & f);	Returns !f.
template <typename ResultType, typename... ArgumentTypes>
bool operator!=(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t);
template <typename ResultType, typename... ArgumentTypes>
bool operator!=(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> & f);	Returns bool(f).
