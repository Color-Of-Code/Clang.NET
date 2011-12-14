Clang.Net
=========

A managed wrapper for [clang](http://clang.llvm.org/).

TODO
====
- implement CXDiagnosticSet wrapper
- FixIts support

NOT IMPLEMENTED YET
===================
And not yet planned because not part of my intended use:

- support for code completion

Dependencies
============

C-Runtime. In order to load the libclang.dll, this specific C Run-Time is needed

- http://www.microsoft.com/download/en/details.aspx?id=5555

.NET 4. Is required to run the wrapper.

- http://www.microsoft.com/download/en/details.aspx?id=17851

An alternative is to recompile llvm + clang using the runtime of your choice.

