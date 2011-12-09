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

using System;
using System.Collections.Generic;
using Clang;

namespace Analyze {

	using Analyze.Visitors;

	class Program {

		public static readonly String FILENAME = "Demo.c";

		static void Main (string[] arguments)
		{
			using (var context = new Context ()) {
				
				Console.WriteLine("Information: {0}", context.ClangVersion);

				// example of use of arguments
				List<string> parameters = new List<string>();
				
				parameters.Add("-std=c89"); // works only for C of course
				//parameters.Add("-nostdinc");
				//parameters.Add("-I/mypath/include/posix");

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

		private static Stack<Cursor> _last = new Stack<Cursor>();

		private static CursorVisitResult CursorVisitor (Cursor cursor, Cursor parent)
		{
			if (cursor.Location.SpellingPosition.File.Path == FILENAME) 
			{

				//_last.Push(parent);
				switch (cursor.Kind)
				{
				case CursorKind.FunctionDeclaration:
					FunctionVisitor.Parse(cursor);
					break;
				case CursorKind.VariableDeclaration:
					Console.WriteLine ("variable {0} -> recurse", cursor.Name);
					break;
				case CursorKind.EnumerationDeclaration:
					Console.WriteLine ("enum {0} -> recurse", cursor.Name);
					break;
				case CursorKind.ClassDeclaration:
					Console.WriteLine ("class {0} -> recurse", cursor.Name);
					cursor.VisitChildren(ClassVisitor.Visitor);
					break;
				case CursorKind.MacroDefinition:
					Console.WriteLine ("macro {0} -> recurse", cursor.Name);
					break;


				//case CursorKind.EnumerationConstantDeclaration:
				//    Console.WriteLine ("  {0}", cursor.Name);
				//    break;
				//case CursorKind.CxxAccessSpecifier:
				//    break;
				//case CursorKind.UnexposedExpression:
				//    break;

				//case CursorKind.CharacterLiteral:
				//    Console.Write ("char: {0}", cursor.Spelling);
				//    break;
				//case CursorKind.StringLiteral:
				//    Console.Write ("string: {0}", cursor.Spelling);
				//    break;
				//case CursorKind.IntegerLiteral:
				//    //Console.Write ("intval={0}", cursor.Spelling);
				//    break;

				//case CursorKind.CompoundStatement:
				//    Console.WriteLine ("{");
				//    break;
				//case CursorKind.DeclarationReferenceExpression:
				//    Console.Write (" {0}, ", cursor.Name);
				//    break;
				//case CursorKind.CallExpression:
				//    Console.WriteLine ("{0} ();", cursor.Name);
				//    break;

				default:
					Console.WriteLine ("{0} (name:{1}) [spelling:{2}] L{3}C{4}",
						cursor.Kind, cursor.Name, cursor.Spelling, 
						cursor.Location.SpellingPosition.Line,
						cursor.Location.SpellingPosition.Column);
					break;
				}
			}
			return CursorVisitResult.Continue;
		}

	}
}
