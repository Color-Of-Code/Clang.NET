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

#include "SourceRange.h"
#include "SourceLocation.h"

using namespace System;

namespace Clang {
	SourceRange::SourceRange(const CXSourceRange& native) {
		pointer0 = native.ptr_data[0];
		pointer1 = native.ptr_data[1];
		integer0 = native.begin_int_data;
		integer1 = native.end_int_data;
	}

	SourceRange SourceRange::GetRange(SourceLocation begin, SourceLocation end) {
		CXSourceRange native = clang_getRange(begin.Native, end.Native);
		return SourceRange(native);
	}

	SourceRange SourceRange::Null::get() {
		CXSourceRange range = clang_getNullRange();
		return SourceRange(range);
	}

	bool SourceRange::IsNull::get() {
		return clang_Range_isNull(Native) != 0;
	}

	SourceLocation SourceRange::Start::get() {
		return SourceLocation(clang_getRangeStart(Native));
	}

	SourceLocation SourceRange::End::get() {
		return SourceLocation(clang_getRangeEnd(Native));
	}

	CXSourceRange SourceRange::Native::get() {
		CXSourceRange native;
		native.ptr_data[0] = pointer0;
		native.ptr_data[1] = pointer1;
		native.begin_int_data = integer0;
		native.end_int_data = integer1;
		return native;
	}
}
