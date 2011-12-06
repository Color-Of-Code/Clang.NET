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
using System.Text;
using System.Collections.Generic;
using Clang;

namespace AstPrint {
	class Program {

		public static readonly String FILENAME = "Demo.c";

		static void Main (string[] arguments)
		{
			using (var context = new Context ()) {
				
				Console.WriteLine("Information: {0}", context.ClangVersion);

				// example of use of arguments
				List<string> parameters = new List<string>();
				
				//parameters.Add("-std=c89"); // works only for C of course
				//parameters.Add("-nostdinc");

				using (var translationUnit = new TranslationUnit (context, FILENAME, 
					TranslationUnitFlags.DetailedPreprocessingRecord,
					parameters)) {
					if (translationUnit.Diagnostics.Count > 0) {
						foreach (var diagnostic in translationUnit.Diagnostics) {
							Console.WriteLine (diagnostic.Spelling);
						}
					} else {
						_depth = 0;
						_locked = true;
						new Cursor (translationUnit).VisitChildren (RecursiveCursorVisitor);
					}
				}
			}
		}

		private static int _depth = 0;
		private static bool _locked = true;

		private static CursorVisitResult RecursiveCursorVisitor (Cursor cursor, Cursor parent)
		{
			if (cursor.Location.SpellingPosition.File.Path == FILENAME) 
			{
				_locked = false;
				StringBuilder sb = new StringBuilder();
				sb.Append("  ");
				sb.Append(' ', _depth*2);
				sb.Append("L");
				sb.Append(cursor.Location.SpellingPosition.Line);
				sb.Append(" C");
				sb.Append(cursor.Location.SpellingPosition.Column);
				sb.Append(" - ");
				sb.Append(cursor.Kind);
				sb.Append(" - ");
				sb.Append(cursor.Spelling);
				Console.WriteLine (sb);
				_depth++;
				cursor.VisitChildren(RecursiveCursorVisitor);
				_depth--;
			} else {
				if (!_locked) {
					Console.WriteLine ("<inside '{0}'>", cursor.Location.SpellingPosition.File.Path);
					_locked = true;
				}
			}

			return CursorVisitResult.Continue;
		}

	}
}
