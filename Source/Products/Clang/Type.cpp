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

	CallingConvention Type::CallingConvention::get() {
		return static_cast<Clang::CallingConvention>(clang_getFunctionTypeCallingConv(Native));
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

	Type^ Type::ElementType::get() {
		CXType t = clang_getElementType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	Clang::Type^ Type::GetArgumentType(unsigned i) {
		CXType t = clang_getArgType(Native, i);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	unsigned Type::ArgumentCount::get() {
		return clang_getNumArgTypes(Native);
	}

	long long Type::ElementCount::get() {
		return clang_getNumElements(Native);
	}

	bool Type::IsFunctionVariadic::get() {
		return clang_isFunctionTypeVariadic(Native) != 0;
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

	bool Type::IsPOD::get() {
		return clang_isPODType(Native) != 0;
	}
}
