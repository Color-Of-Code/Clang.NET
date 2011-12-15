using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

using Clang;

namespace ClangGenerator {
	class EnumWrapper {

		public EnumWrapper (DirectoryInfo di)
		{
			_di = di;
		}

		private StringBuilder _sb;
		private DirectoryInfo _di;

		public void Parse (Cursor cursor)
		{
			if (String.IsNullOrEmpty (cursor.Name))
				return;
			String enumName = cursor.Name.Substring (2).Replace ("_", "");
			if (enumName == "ChildVisitResult")
				enumName = "CursorVisitResult";
			if (enumName == "CallingConv")
				enumName = "CallingConvention";
			String filename = Path.Combine (_di.FullName, enumName + ".h");
			StringBuilder contents = new StringBuilder ();
			contents.AppendLine (Template.Header);
			if (enumName.EndsWith ("Flags"))
				contents.AppendLine ("    [System::Flags]");
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

		private CursorVisitResult EnumVisitor (Cursor cursor, Cursor parent)
		{
			String name = cursor.Name;
			// "CXChildVisit_"
			String typename = Regex.Replace (parent.Name, "^(.*)Kind$", "$1");
			String cut = typename;
			cut = Regex.Replace (cut, "^(.*?)_?Flags$", "$1");
			if (cut == "CXChildVisitResult")
				cut = "CXChildVisit";
			if (cut == "CXDiagnosticSeverity")
				cut = "CXDiagnostic";
			if (cut == "CXDiagnosticDisplayOptions")
				cut = "CXDiagnostic";
			if (cut == "CXNameRef")
				cut = "CXNameRange";

			String newName = Regex.Replace (name, cut + "_", "");
			newName = Regex.Replace (newName, "Stmt$", "Statement");
			newName = Regex.Replace (newName, "Decl$", "Declaration");
			newName = Regex.Replace (newName, "Attr$", "Attribute");
			newName = Regex.Replace (newName, "Expr$", "Expression");
			newName = Regex.Replace (newName, "Spec$", "Specification");
			newName = Regex.Replace (newName, "Ptr$", "Pointer");
			newName = Regex.Replace (newName, "Ref$", "Reference");
			newName = Regex.Replace (newName, "Proto$", "Prototype");

			newName = Regex.Replace (newName, "^Stmt", "Statement");
			newName = Regex.Replace (newName, "^Decl([^a])", "Declaration$1");
			newName = Regex.Replace (newName, "^Enum([^e])", "Enumeration$1");
			newName = Regex.Replace (newName, "^Parm", "Parameter");
			newName = Regex.Replace (newName, "^Var([^i])", "Variable$1");
			newName = Regex.Replace (newName, "^Struct([^u])", "Structure$1");
			newName = Regex.Replace (newName, "^CXX", "CPlusPlus");
			newName = Regex.Replace (newName, "^GNU", "Gnu");
			newName = Regex.Replace (newName, "^SEH", "WinSeh");
			newName = Regex.Replace (newName, "^ObjC", "ObjectiveC");

			newName = Regex.Replace (newName, "LitteralExpression$", "Litteral");

			_sb.Append ("        ");
			if (newName.StartsWith ("Last") || newName.StartsWith ("First"))
				_sb.Append ("// ");
			_sb.Append (newName);
			_sb.Append (" = ");
			_sb.Append (name);
			_sb.AppendLine (",");
			if (newName.StartsWith ("Last"))
				_sb.AppendLine ();

			return CursorVisitResult.Continue;
		}
	}
}
