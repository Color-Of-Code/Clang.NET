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

using Clang;

namespace Analyze.Visitors {

	public static class CompoundStatementVisitor {

		public static void Parse(Cursor cursor, int depth)
		{
			StringBuilder sb = new StringBuilder();
			sb.Append(' ', depth*2);
			Console.WriteLine ("{0}{{", sb);
			cursor.VisitChildren(Visitor);
			Console.WriteLine ("{0}}}", sb);
		}

		public static CursorVisitResult Visitor (Cursor cursor, Cursor parent)
		{
			switch (cursor.Kind)
			{
			case CursorKind.IfStatement:
				IfStatementVisitor.Parse(cursor);
				break;

			case CursorKind.CompoundStatement:
				Parse(cursor, 1);
				break;

			case CursorKind.CallExpression:
				CallExpressionVisitor.Parse(cursor);
				break;

			case CursorKind.DeclarationStatement:
				cursor.VisitChildren(Visitor);
				break;

			case CursorKind.ReturnStatement:
				Console.WriteLine ("  return ?;");
				break;

			case CursorKind.UnexposedExpression:
				if (cursor.Type.Kind == TypeKind.Pointer)
					Console.WriteLine ("   expression type pointer to {0}", cursor.Type.PointeeType.Kind);
				else
					Console.WriteLine ("   expression type {0}", cursor.Type.Kind);
				break;
			default:
				Console.WriteLine ("  {0} (name:{1}) [spelling:{2}] L{3}C{4}",
					cursor.Kind, cursor.Name, cursor.Spelling, 
					cursor.Location.SpellingPosition.Line,
					cursor.Location.SpellingPosition.Column);
				break;
			}
			return CursorVisitResult.Continue;
		}
	}
}
