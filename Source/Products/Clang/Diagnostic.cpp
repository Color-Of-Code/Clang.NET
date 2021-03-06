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
#include "StringHelper.h"
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
		return StringHelper::ConvertAndDispose(formattedNative);
	}
				
	unsigned Diagnostic::DefaultDisplayOptions::get() {
		return clang_defaultDiagnosticDisplayOptions();
	}

	System::String^ Diagnostic::Spelling::get() {
		if(cachedSpelling == nullptr) {
			CXString spelling = clang_getDiagnosticSpelling(Native);
			cachedSpelling = StringHelper::ConvertAndDispose(spelling);
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

	System::String^ Diagnostic::CategoryText::get() {
		return GetCategoryText(Native);
	}

	System::String^ Diagnostic::GetCategoryText(CXDiagnostic category) {
		CXString categoryName = clang_getDiagnosticCategoryText(category);
		return StringHelper::ConvertAndDispose(categoryName);
	}

	DiagnosticSeverity Diagnostic::Severity::get() {
		return static_cast<DiagnosticSeverity>(clang_getDiagnosticSeverity(Native));
	}

	CXDiagnostic Diagnostic::Native::get() {
		return native;
	}
}
