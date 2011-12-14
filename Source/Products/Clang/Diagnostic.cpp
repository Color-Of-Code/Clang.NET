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

#include "Diagnostic.h"
#include "SourceLocation.h"
#include "TranslationUnit.h"

using namespace System;

namespace Clang {
	Diagnostic::Diagnostic(const CXDiagnostic& diagnostic) {
		native = diagnostic;
	}

	Diagnostic::~Diagnostic() {
		clang_disposeDiagnostic(Native);
	}

	Diagnostic::!Diagnostic() {
		clang_disposeDiagnostic(Native);
	}

	System::String^ Diagnostic::Format(unsigned options) {
		CXString formattedNative = clang_formatDiagnostic(Native, options);
		const char* bytes = clang_getCString(formattedNative);
		String^ formatted = gcnew String(bytes);
		clang_disposeString(formattedNative);
		return formatted;
	}
				
	unsigned Diagnostic::DefaultDisplayOptions::get() {
		return clang_defaultDiagnosticDisplayOptions();
	}

	System::String^ Diagnostic::Spelling::get() {
		if(cachedSpelling == nullptr) {
			CXString spelling = clang_getDiagnosticSpelling(Native);
			const char* bytes = clang_getCString(spelling);
			cachedSpelling = gcnew String(bytes);
			clang_disposeString(spelling);
		}

		return cachedSpelling;
	}

	SourceLocation Diagnostic::Location::get() {
		CXSourceLocation location = clang_getDiagnosticLocation(Native);
		return SourceLocation(location);
	}

	unsigned Diagnostic::RangeCount::get() {
		return clang_getDiagnosticNumRanges(Native);
	}

	unsigned Diagnostic::FixItsCount::get() {
		return clang_getDiagnosticNumFixIts(Native);
	}

	unsigned Diagnostic::Category::get() {
		return clang_getDiagnosticCategory(Native);
	}

	System::String^ Diagnostic::CategoryName::get() {
		return GetCategoryName(Category);
	}

	System::String^ Diagnostic::GetCategoryName(unsigned category) {
		CXString categoryName = clang_getDiagnosticCategoryName(category);
		const char* bytes = clang_getCString(categoryName);
		String^ result = gcnew String(bytes);
		clang_disposeString(categoryName);
		return result;
	}

	DiagnosticSeverity Diagnostic::Severity::get() {
		return static_cast<DiagnosticSeverity>(clang_getDiagnosticSeverity(Native));
	}

	CXDiagnostic Diagnostic::Native::get() {
		return native;
	}
}
