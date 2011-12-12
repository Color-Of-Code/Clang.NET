using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Clang;

namespace ClangGenerator {

	class StructureParser {
		public StructureParser ()
		{
		}

		public String Name { get; private set; }
		public Boolean IsStructure { get; private set; }
		public List<String> Fields { get; private set; }

		private Cursor _cursor;

		public void Parse (Cursor cursor)
		{
			Name = cursor.Name;
			_cursor = cursor;
			Fields = new List<string> ();
			cursor.VisitChildren (RecusiveVisitor);
		}

		private CursorVisitResult RecusiveVisitor (Cursor cursor, Cursor parent)
		{
			if (_cursor.Hash == parent.Hash)
				IsStructure = cursor.Type.Kind == TypeKind.Record;
			if (cursor.Kind == CursorKind.FieldDeclaration) {
				if (cursor.Type.Kind == TypeKind.ConstantArray) {
					String field = String.Format ("{0} ({1}[{2}])", cursor.Name, cursor.Type.ElementType.Kind, cursor.Type.ElementCount);
					Fields.Add (field);
				} else {
					String field = String.Format ("{0} ({1})", cursor.Name, cursor.Type.Kind);
					Fields.Add (field);
				}
			}
			return CursorVisitResult.Recurse;
		}
	}
}
