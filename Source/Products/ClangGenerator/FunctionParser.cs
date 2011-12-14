using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

using Clang;

namespace ClangGenerator {
	class FunctionParser {

		public FunctionParser ()
		{
		}

		public String Name { get; private set; }
		public String ReturnType { get; private set; }
		public String FirstParameterType { get; private set; }
		public List<String> Parameters { get; private set; }

		public void Write (StringBuilder sb)
		{
			if (Parameters.Count == 0)
				sb.AppendFormat ("static {0,-20} {1} (", ReturnType, Name);
			else
				sb.AppendFormat ("{0,-20} {1} (", ReturnType, Name);
			foreach (var p in Parameters.Skip (1)) {
				sb.Append (p.Replace (":", " "));
				sb.Append (", ");
			}
			sb.AppendLine (")");
		}

		public void Parse (Cursor cursor)
		{
			Name = cursor.Spelling;

			if (cursor.ResultType.Kind == TypeKind.Typedef) {
				typename = null;
				cursor.VisitChildren (ParseFunctionParameterTypeReference);
				ReturnType = typename;
			} else {
				ReturnType = cursor.ResultType.Kind.ToString ();
			}
			Parameters = new List<string> ();
			cursor.VisitChildren (ParseFunctionParameter);
			if (Parameters.Count > 0) {
				FirstParameterType = Regex.Replace (Parameters[0], "^(.*?):.*$", "$1");
			} else {
				FirstParameterType = ReturnType;
			}
		}

		private String typename;

		private CursorVisitResult ParseFunctionParameter (Cursor cursor, Cursor parent)
		{
			if (cursor.Kind == CursorKind.ParameterDeclaration) {
				typename = null;
				cursor.VisitChildren (ParseFunctionParameterTypeReference);
				StringBuilder sb = new StringBuilder ();
				if (typename != null)
					sb.Append (typename);
				else
					sb.Append (cursor.Type.Kind);
				sb.Append (":");
				sb.Append (cursor.Name);
				Parameters.Add (sb.ToString ());
			}
			return CursorVisitResult.Continue;
		}

		private CursorVisitResult ParseFunctionParameterTypeReference (Cursor cursor, Cursor parent)
		{
			if (cursor.Kind == CursorKind.TypeReference) {
				typename = cursor.Name;
			}
			return CursorVisitResult.Recurse;
		}
	}
}
