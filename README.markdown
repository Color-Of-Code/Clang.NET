Clang.Net
=========

A managed wrapper for [clang](http://clang.llvm.org/).

[Documentation](http://clang.llvm.org/doxygen/group__CINDEX.html)

Fully supported
===============
- String manipulation routines (transparent handling)
- Traversing the AST with cursors
- C++ AST introspection
- File manipulation routines
- Physical source locations

Partially supported
===================
- Cursor manipulations
- Translation unit manipulation
- Mapping between cursors and source code
- Diagnostic reporting
- Type information for CXCursors

TODO
====
- Higher level API functions (Indexing)
- Token extraction and manipulation
- Information for attributes
- Cross-referencing in the AST
- Debugging facilities
- Miscellaneous utility functions
- Remapping functions

- implement CXDiagnosticSet wrapper
- FixIts support

NOT IMPLEMENTED YET
===================
And not yet planned because not part of my intended use:

- Code completion

Dependencies
============

C-Runtime. In order to load the libclang.dll, this specific C Run-Time is needed

- http://www.microsoft.com/download/en/details.aspx?id=5555

.NET 4. Is required to run the wrapper.

- http://www.microsoft.com/download/en/details.aspx?id=17851

An alternative is to recompile llvm + clang using the runtime of your choice.

