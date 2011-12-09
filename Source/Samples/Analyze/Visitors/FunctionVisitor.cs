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
	public static class FunctionVisitor {
		public static void Parse (Cursor cursor)
		{
			Console.Write ("function: {1} {0} ({2} params) (", cursor.Spelling, cursor.ResultType.Kind, cursor.Type.ArgumentCount);
			cursor.VisitChildren(Visitor);
		}

		public static CursorVisitResult Visitor (Cursor cursor, Cursor parent)
		{
			switch (cursor.Kind)
			{
			case CursorKind.ParameterDeclaration:
				Console.Write (" | {1} {0}", cursor.Name, Utils.TypeToString.Convert(cursor.Type));
				break;

			// parse function body
			case CursorKind.CompoundStatement:
				Console.WriteLine (")");
				CompoundStatementVisitor.Parse(cursor, 0);
				break;

			default:
				throw new NotImplementedException(cursor.Kind + "in FunctionVisitor");
			}
			return CursorVisitResult.Continue;
		}
	}
}
