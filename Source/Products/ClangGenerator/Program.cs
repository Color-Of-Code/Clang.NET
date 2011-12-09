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
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

using Clang;

namespace ClangGenerator {
	class Program {

		private static FileInfo fi;

		static void Main (string[] arguments)
		{
			if (arguments.Count () != 1) {
				Console.WriteLine ("Needs one argument: path to Index.h");
			}
			fi = new FileInfo (arguments[0]);
			if (!fi.Exists) {
				Console.WriteLine ("Could not find file '{0}'", fi.FullName);
			}

			using (var context = new Context ()) {

				Console.WriteLine ("Information: {0}", context.ClangVersion);

				List<string> parameters = new List<string> ();
				parameters.Add ("-std=c99");

				using (var translationUnit = new TranslationUnit (context, fi.FullName,
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
			if (cursor.Location.SpellingPosition.File.Path == fi.FullName) {
				_locked = false;
				StringBuilder sb = new StringBuilder ();
				sb.Append ("  ");
				sb.Append (' ', _depth * 2);
				sb.Append ("L");
				sb.Append (cursor.Location.SpellingPosition.Line);
				sb.Append (" C");
				sb.Append (cursor.Location.SpellingPosition.Column);
				sb.Append (" - ");
				sb.Append (cursor.Kind);
				sb.Append (" - ");
				sb.Append (cursor.Spelling);
				Console.WriteLine (sb);
				if (cursor.Kind == CursorKind.EnumerationDeclaration) {
					GenerateEnumerationWrapper (cursor);
				} else {
					_depth++;
					cursor.VisitChildren (RecursiveCursorVisitor);
					_depth--;
				}
			} else {
				if (!_locked) {
					Console.WriteLine ("<inside '{0}'>", cursor.Location.SpellingPosition.File.Path);
					_locked = true;
				}
			}

			return CursorVisitResult.Continue;
		}

		private static StringBuilder _sb;

		private static void GenerateEnumerationWrapper (Cursor cursor)
		{
			if (String.IsNullOrEmpty (cursor.Name))
				return;
			String enumName = cursor.Name.Substring (2).Replace ("_", "");
			String filename = Path.Combine (fi.DirectoryName, enumName + ".h");
			StringBuilder contents = new StringBuilder ();
			contents.AppendLine (Template.Header);
			contents.Append ("    public enum class ");
			contents.Append (enumName);
			contents.AppendLine ("    {");

			// add values
			_sb = contents;
			cursor.VisitChildren (EnumVisitor);

			contents.AppendLine ("    };");
			contents.AppendLine (Template.Footer);
			File.WriteAllText (filename, contents.ToString ());
		}

		private static CursorVisitResult EnumVisitor (Cursor cursor, Cursor parent)
		{
			String name = cursor.Name;
			String typename = Regex.Replace(parent.Name, "^(.*)Kind$", "$1");
			String newName = Regex.Replace(name, typename + "_", "");
			newName = Regex.Replace(newName, "Stmt$", "Statement");
			newName = Regex.Replace(newName, "Decl$", "Declaration");
			newName = Regex.Replace(newName, "Attr$", "Attribute");
			newName = Regex.Replace(newName, "Expr$", "Expression");
			newName = Regex.Replace(newName, "Spec$", "Specification");
			newName = Regex.Replace(newName, "Ptr$", "Pointer");
			newName = Regex.Replace(newName, "Ref$", "Reference");
			newName = Regex.Replace(newName, "Proto$", "Prototype");

			newName = Regex.Replace(newName, "^Stmt", "Statement");
			newName = Regex.Replace(newName, "^Decl([^a])", "Declaration$1");
			newName = Regex.Replace(newName, "^Enum([^e])", "Enumeration$1");
			newName = Regex.Replace(newName, "^Parm", "Parameter");
			newName = Regex.Replace(newName, "^Var([^i])", "Variable$1");
			newName = Regex.Replace(newName, "^CXX", "CPlusPlus");
			newName = Regex.Replace(newName, "^GNU", "Gnu");
			newName = Regex.Replace(newName, "^SEH", "WinSeh");
			newName = Regex.Replace(newName, "^ObjC", "ObjectiveC");

			newName = Regex.Replace(newName, "LitteralExpression$", "Litteral");

			_sb.Append("        ");
			if (newName.StartsWith("Last") || newName.StartsWith("First"))
				_sb.Append("// ");
			_sb.Append(newName);
			_sb.Append(" = ");
			_sb.Append(name);
			_sb.AppendLine(",");
			if (newName.StartsWith("Last"))
				_sb.AppendLine();

			return CursorVisitResult.Continue;
		}
	}
}
