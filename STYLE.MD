# style guide

These guidelines are personal choice. Many of them should be followed
consistently, but there are always exceptions where it makes sense to change.

- not enforced by clang-format as of now
- try to keep lines at most 80 chars if it is reasonable
- use `struct` if everything is public, `class` otherwise
- explicitly include the `private:` in a class
- put private class members before public ones
- make reasonable documentation for everything

# indentation/whitespace

- use 4 space indents
- do not indent within namespace
- always put preprocessor `#` at start of line
- keep `case` on the same indent level as `switch`
- put opening curly brace `{` on next line
- single statement if/else/etc are ok but indent them on next line
- match indentation to previous lines if it makes long statements look nicer
- extra spaces can be used to align things if it looks nice (such as tables)
- separate type from name with a space for variables and parameters
  - multiple spaces for aligning things to look nice is ok sometimes
  - group `&` and `*` with the variable name
  - example: `int &reference;`, `int *pointer;`, `int *&ref_to_ptr;`
- keep `&` and `*` with function return type
  - example: `Type& operator=(const Type &other);`
  - example: `const Type* data() const { return _data; }`
- separate function parameters with spaces
  - example: `int& getIntRef(int a, int *b, intn &c, int *&d);`
- separate complex function arguments with spaces, but not simple ones
  - example: `int value = function(a,b,c);`
  - example: `function( (a+b)/2, (a-b)*2 );

# naming

- macros
  - `ALL_CAPS_SEPARATED_BY_UNDERSCORE`
  - `_START_PRIVATE_WITH_UNDERSCORE`
- classes/structs
  - `class CapitalizeEachWord;`
- functions
  - `void useCamelCase();`
  - `void _privateClassMember();`
- variables
  - `char localVariable;`
  - `long cConstantValue;`
  - `float mClassMember;`
  - `int sStaticVariable;`
  - `double gGlobalVariable;`
- namespaces
  - `namespace camelCase`
- consider acronyms to be words
  - example: use `HtmlParser` instead of `HTMLParser`
- files
  - use `.cpp` and `.hpp` extensions
  - name by the main class they contain
  - match paths to namespaces usually unless something else makes sense
  - each file should mainly contain
    - one class and related functions
    - a grouping of similar/related functions
    - constants/typedefs
- try to use `_detail` namespaces instead of anonymous ones

# things to remember

- consider pass/return by reference/value
- make variables/functions const when appropriate
- use `[[nodiscard]]` on functions that return non void with no side effects
- consider if it makes sense to have `[[likely]]` or `[[unlikely]]` on branches
- give functions `noexcept` when appropriate
- declare most small functions as `inline` even though this means little
- when to use `constexpr` and `consteval`

# documentation

- use doxygen `///` style comments
- try to document everything that is public
- try to document all parameters (including templates)
- use backslashes (`\brief`,`\tparam tvar`,`\param var`,`\return`,...)
- include extended explanations when there is additional important information

# design patterns to consider
