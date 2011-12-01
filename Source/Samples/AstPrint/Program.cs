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

using System;
using System.Collections.Generic;
using Clang;

namespace AstPrint {
	class Program {

		public static readonly String FILENAME = "Demo.c";

		static void Main (string[] arguments)
		{
			using (var context = new Context ()) {
				
				// example of use of arguments
				List<string> parameters = new List<string>();
				parameters.Add("-std=c89"); // works only for C of course

				using (var translationUnit = new TranslationUnit (context, FILENAME, 
					TranslationUnitFlags.DetailedPreprocessingRecord,
					parameters)) {
					if (translationUnit.Diagnostics.Count > 0) {
						foreach (var diagnostic in translationUnit.Diagnostics) {
							Console.WriteLine (diagnostic.Spelling);
						}
					} else {
						new Cursor (translationUnit).VisitChildren (CursorVisitor);
					}
				}
			}
		}

		static CursorVisitResult CursorVisitor (Cursor cursor, Cursor parent)
		{
			if (cursor.Location.SpellingPosition.File.Path == FILENAME) {
				Console.WriteLine ("Line {3}/{4}: {0} ({1}) [{2}]",
					cursor.Name, cursor.Spelling, cursor.Kind,
					cursor.Location.SpellingPosition.Line,
					cursor.Location.SpellingPosition.Column);
			}

			return CursorVisitResult.Recurse;
		}
	}
}
