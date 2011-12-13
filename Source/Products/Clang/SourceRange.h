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

#pragma once

#include "Index.h"

namespace Clang {
	value class SourceLocation;

	public value class SourceRange
	{
	public:
		property SourceLocation Start {
			SourceLocation get();
		}

		property SourceLocation End {
			SourceLocation get();
		}

		property static SourceRange Null {
			SourceRange get();
		}

		property bool IsNull {
			bool get();
		}

		static SourceRange GetRange(SourceLocation begin, SourceLocation end);

	internal:
		SourceRange(const CXSourceRange& native);

		property CXSourceRange Native {
			CXSourceRange get();
		}

	private:
		// CXSourceRange is a structure, and thus cannot be directly contained
		// inside a managed type. Instead, the members are directly contained in
		// this class and the native object is rebuilt as needed.
		void* pointer0;
		void* pointer1;
		unsigned int integer0;
		unsigned int integer1;
	};
}
