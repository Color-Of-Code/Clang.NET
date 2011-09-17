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
		data0 = native.data[0];
		data1 = native.data[1];
		data2 = native.data[2];
	}

	Cursor::Cursor(const CXCursor& native) {
		kind = native.kind;
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

	bool Cursor::IsUnexposed::get() {
		return clang_isUnexposed(kind) != 0;
	}

	CursorKind Cursor::Kind::get() {
		return static_cast<CursorKind>(kind);
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
		native.data[0] = data0;
		native.data[1] = data1;
		native.data[2] = data2;
		return native;
	}
}
