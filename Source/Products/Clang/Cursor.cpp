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

#include "Cursor.h"
#include "SourceLocation.h"
#include "SourceRange.h"
#include "TranslationUnit.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace {
	CXChildVisitResult VisitorThunk(CXCursor cursor, CXCursor parent, CXClientData data) {
		IntPtr pointer = IntPtr(data);
		Delegate^ wrapped = Marshal::GetDelegateForFunctionPointer(pointer,Clang::CursorVisitorCallback::typeid);
		Clang::CursorVisitorCallback^ callback = (Clang::CursorVisitorCallback^)wrapped;

		return static_cast<CXChildVisitResult>(callback(gcnew Clang::Cursor(cursor), gcnew Clang::Cursor(parent)));
	}
}

namespace Clang {

	Cursor::Cursor(TranslationUnit^ translationUnit) {
		CXCursor native = clang_getTranslationUnitCursor(translationUnit->Native);
		kind = native.kind;
		xdata = native.xdata;
		data0 = native.data[0];
		data1 = native.data[1];
		data2 = native.data[2];
	}

	Cursor::Cursor(const CXCursor& native) {
		kind = native.kind;
		xdata = native.xdata;
		data0 = native.data[0];
		data1 = native.data[1];
		data2 = native.data[2];
	}

	String^ Cursor::Name::get() {
		if(cachedName == nullptr) {
			CXString name = clang_getCursorDisplayName(Native);
			const char* bytes = clang_getCString(name);
			cachedName = gcnew String(bytes);
			clang_disposeString(name);
		}

		return cachedName;
	}

	String^ Cursor::Spelling::get() {
		if(cachedSpelling == nullptr) {
			CXString spelling = clang_getCursorSpelling(Native);
			const char* bytes = clang_getCString(spelling);
			cachedSpelling = gcnew String(bytes);
			clang_disposeString(spelling);
		}

		return cachedSpelling;
	}

	LinkageKind Cursor::Linkage::get() {
		return static_cast<LinkageKind>(clang_getCursorLinkage(Native));
	}

	SourceLocation Cursor::Location::get() {
		CXSourceLocation location = clang_getCursorLocation(Native);
		return SourceLocation(location);
	}

	SourceRange Cursor::Extent::get() {
		CXSourceRange location = clang_getCursorExtent(Native);
		return SourceRange(location);
	}

	bool Cursor::IsUnexposed::get() {
		return clang_isUnexposed(kind) != 0;
	}

	bool Cursor::IsDeclaration::get() {
		return clang_isDeclaration(kind) != 0;
	}

	bool Cursor::IsReference::get() {
		return clang_isReference(kind) != 0;
	}

	bool Cursor::IsExpression::get() {
		return clang_isExpression(kind) != 0;
	}

	bool Cursor::IsStatement::get() {
		return clang_isStatement(kind) != 0;
	}

	bool Cursor::IsAttribute::get() {
		return clang_isAttribute(kind) != 0;
	}

	bool Cursor::IsInvalid::get() {
		return clang_isInvalid(kind) != 0;
	}

	bool Cursor::IsTranslationUnit::get() {
		return clang_isTranslationUnit(kind) != 0;
	}

	bool Cursor::IsPreprocessing::get() {
		return clang_isPreprocessing(kind) != 0;
	}

	bool Cursor::IsVirtualBase::get() {
		return clang_isVirtualBase(Native) != 0;
	}

	bool Cursor::IsCursorDefinition::get() {
		return clang_isCursorDefinition(Native) != 0;
	}

	bool Cursor::IsCxxMethodStatic::get() {
		return clang_CXXMethod_isStatic(Native) != 0;
	}

	bool Cursor::IsCxxMethodVirtual::get() {
		return clang_CXXMethod_isVirtual(Native) != 0;
	}

	//bool Cursor::IsNull::get() {
	//	return clang_Cursor_isNull(Native) != 0;
	//}

	unsigned Cursor::Hash::get() {
		return clang_hashCursor(Native);
	}

	CursorKind Cursor::Kind::get() {
		return static_cast<CursorKind>(kind);
	}

	LanguageKind Cursor::Language::get() {
		return static_cast<LanguageKind>(clang_getCursorLanguage(Native));
	}

	Cursor^ Cursor::GetLexicalParent() {
		return gcnew Cursor(clang_getCursorLexicalParent(Native));
	}

	Cursor^ Cursor::GetSemanticParent() {
		return gcnew Cursor(clang_getCursorSemanticParent(Native));
	}

	Type^ Cursor::Type::get() {
		CXType t = clang_getCursorType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	Type^ Cursor::ResultType::get() {
		CXType t = clang_getCursorResultType(Native);
		if (t.kind == CXType_Invalid)
			return nullptr;
		else
			return gcnew Clang::Type(t);
	}

	bool Cursor::VisitChildren(CursorVisitorCallback^ visitor) {
		GCHandle handle = GCHandle::Alloc(visitor);
		try {
			IntPtr callback = Marshal::GetFunctionPointerForDelegate(visitor);
			return clang_visitChildren( Native, VisitorThunk, callback.ToPointer()) == 0;
		} finally {
			handle.Free();
		}
	}

	CXCursor Cursor::Native::get() {
		CXCursor native;
		native.kind = kind;
		native.xdata = xdata;
		native.data[0] = data0;
		native.data[1] = data1;
		native.data[2] = data2;
		return native;
	}
}
