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

#include "Type.h"
#include "SourceLocation.h"
#include "SourceRange.h"
#include "TranslationUnit.h"

namespace Clang {

	Type::Type(const CXType& native) {
		kind = native.kind;
		data0 = native.data[0];
		data1 = native.data[1];
	}

	CXType Type::Native::get() {
		CXType native;
		native.kind = kind;
		native.data[0] = data0;
		native.data[1] = data1;
		return native;
	}

	TypeKind Type::Kind::get() {
		return static_cast<TypeKind>(kind);
	}

	Type^ Type::PointeeType::get() {
		CXType t = clang_getPointeeType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	Type^ Type::ResultType::get() {
		CXType t = clang_getResultType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	Type^ Type::CanonicalType::get() {
		CXType t = clang_getCanonicalType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	Type^ Type::ArrayElementType::get() {
		CXType t = clang_getArrayElementType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	bool Type::IsConst::get() {
		return clang_isConstQualifiedType(Native) != 0;
	}

	bool Type::IsVolatile::get() {
		return clang_isVolatileQualifiedType(Native) != 0;
	}

	bool Type::IsRestrict::get() {
		return clang_isRestrictQualifiedType(Native) != 0;
	}

}
