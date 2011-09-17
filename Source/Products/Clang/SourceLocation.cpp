// Copyright (c) 2011 Josh Petrie
//	
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "SourceLocation.h"
#include "File.h"
#include "Location.h"

using namespace System;

namespace Clang {
	SourceLocation::SourceLocation(const CXSourceLocation& native) {
		pointer0 = native.ptr_data[0];
		pointer1 = native.ptr_data[1];
		integer = native.int_data;
	}

	Location SourceLocation::SpellingPosition::get() {
		CXFile file;
		unsigned int line;
		unsigned int column;
		unsigned int offset;
		clang_getSpellingLocation(Native, &file, &line, &column, &offset);
		
		Location result;
		result.File = File(file);
		result.Line = line;
		result.Column = column;
		result.Offset = offset;
		return result;
	}

	Location SourceLocation::ExpansionPosition::get() {
		CXFile file;
		unsigned int line;
		unsigned int column;
		unsigned int offset;
		clang_getExpansionLocation(Native, &file, &line, &column, &offset);
		
		Location result;
		result.File = File(file);
		result.Line = line;
		result.Column = column;
		result.Offset = offset;
		return result;
	}

	CXSourceLocation SourceLocation::Native::get() {
		CXSourceLocation native;
		native.ptr_data[0] = pointer0;
		native.ptr_data[1] = pointer1;
		native.int_data = integer;
		return native;
	}
}
