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

#include "TranslationUnit.h"
#include "Context.h"
#include "Diagnostic.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Text;

namespace Clang {
	TranslationUnit::TranslationUnit(Context^ context, String^ file, TranslationUnitFlags flags) {
		array<System::Byte>^ fileBytes = ASCIIEncoding::ASCII->GetBytes(file);
		pin_ptr<unsigned char> pinnedFile = &fileBytes[0];

		native = clang_parseTranslationUnit(
			context->Native,
			reinterpret_cast<const char*>(pinnedFile),
			0,
			0,
			0,
			0,
			static_cast<unsigned int>(flags)
		);
	}

	TranslationUnit::~TranslationUnit() {
		clang_disposeTranslationUnit(Native);
	}

	TranslationUnit::!TranslationUnit() {
		clang_disposeTranslationUnit(Native);
	}

	ReadOnlyCollection<Diagnostic^>^ TranslationUnit::Diagnostics::get() {
		if(diagnostics == nullptr) {
			List<Diagnostic^>^ results = gcnew List<Diagnostic^>();
			for(unsigned int diagnosticIndex = 0; diagnosticIndex < clang_getNumDiagnostics(Native); ++diagnosticIndex) {
				results->Add(gcnew Diagnostic(clang_getDiagnostic(Native, diagnosticIndex)));
			}

			diagnostics = results->AsReadOnly();
		}

		return diagnostics;
	}

	CXTranslationUnit TranslationUnit::Native::get() {
		return native;
	}
}
