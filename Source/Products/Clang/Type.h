// Copyright (c) 2011 Jaap de Haan
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
#include "TypeKind.h"

namespace Clang {

	public ref class Type
	{
	public:
		property TypeKind Kind {
			TypeKind get();
		}

		property Clang::Type^ PointeeType {
			Clang::Type^ get();
		}

		property Clang::Type^ ResultType {
			Clang::Type^ get();
		}

		property Clang::Type^ CanonicalType {
			Clang::Type^ get();
		}

		property Clang::Type^ ArrayElementType {
			Clang::Type^ get();
		}

		property bool IsConst {
			bool get();
		}

		property bool IsVolatile {
			bool get();
		}

		property bool IsRestrict {
			bool get();
		}

		//TODO:
		//unsigned clang_equalTypes(CXType A, CXType B);
		//CXCursor clang_getTypeDeclaration(CXType T);

		//CXString clang_getTypeKindSpelling(enum CXTypeKind K);
		//unsigned clang_isPODType(CXType T);
		//long long clang_getArraySize(CXType T);

	internal:
		Type(const CXType& native);

		property CXType Native {
			CXType get();
		}

	private:		
		// CXType is a structure, and thus cannot be directly contained
		// inside a reference type. Instead, the members of CXType are
		// directly contained in this class and CXType instances are
		// rebuilt as needed.
		CXTypeKind kind;
		void* data0;
		void* data1;
	};
}
