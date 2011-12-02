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
#include "CursorKind.h"
#include "CursorLinkage.h"
#include "CursorVisitorCallback.h"
#include "CursorVisitResult.h"
#include "Type.h"

namespace Clang {
	ref class TranslationUnit;
	ref class Type;
	value class SourceLocation;
	value class SourceRange;

	public ref class Cursor
	{
	public:
		Cursor(TranslationUnit^ translationUnit);

		property CursorKind Kind {
			CursorKind get();
		}

		property System::String^ Name {
			System::String^ get(); 
		}

		property System::String^ Spelling {
			System::String^ get(); 
		}

		property CursorLinkage Linkage {
			CursorLinkage get(); 
		}

		property SourceLocation Location {
			SourceLocation get();
		}

		property SourceRange Extent {
			SourceRange get();
		}

		property bool IsUnexposed {
			bool get();
		}

		property bool IsDeclaration {
			bool get();
		}

		property bool IsReference {
			bool get();
		}

		property bool IsExpression {
			bool get();
		}

		property bool IsStatement {
			bool get();
		}

		property bool IsAttribute {
			bool get();
		}

		property bool IsInvalid {
			bool get();
		}

		property bool IsTranslationUnit {
			bool get();
		}

		property bool IsPreprocessing {
			bool get();
		}

		property bool IsVirtualBase {
			bool get();
		}

		property bool IsCursorDefinition {
			bool get();
		}

		property bool IsCxxMethodStatic {
			bool get();
		}

		property bool IsCxxMethodVirtual {
			bool get();
		}

		Cursor^ GetLexicalParent();
		Cursor^ GetSemanticParent();

		bool VisitChildren(CursorVisitorCallback^ visitor);

		property Clang::Type^ Type {
			Clang::Type^ get();
		}

		property Clang::Type^ ResultType {
			Clang::Type^ get();
		}

		//TODO:
		//CXString clang_getDeclObjCTypeEncoding(CXCursor C);
		//enum CX_CXXAccessSpecifier clang_getCXXAccessSpecifier(CXCursor);
		//unsigned clang_getNumOverloadedDecls(CXCursor cursor);
		//CXCursor clang_getOverloadedDecl(CXCursor cursor, unsigned index);
		//CXType clang_getIBOutletCollectionType(CXCursor);
		//CXString clang_getCursorUSR(CXCursor);
		//enum CXCursorKind clang_getTemplateCursorKind(CXCursor C);

	internal:
		Cursor(const CXCursor& native);

		property CXCursor Native {
			CXCursor get();
		}

	private:
		System::String^ cachedName;
		System::String^ cachedSpelling;
		
		// CXCursor is a structure, and thus cannot be directly contained
		// inside a reference type. Instead, the members of CXCursor are
		// directly contained in this class and CXCursor instances are
		// rebuilt as needed.
		CXCursorKind kind;
		int xdata;
		void* data0;
		void* data1;
		void* data2;
	};
}
