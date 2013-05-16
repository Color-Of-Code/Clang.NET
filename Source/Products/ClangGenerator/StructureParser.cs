using System;
using System.Collections.Generic;
using System.Text;
using Clang;

namespace ClangGenerator
{
    internal class StructureParser
    {
        private Cursor _cursor;
        public String Name { get; private set; }
        public Boolean IsStructure { get; private set; }
        public List<String> Fields { get; private set; }

        public void Write(StringBuilder sb)
        {
            sb.AppendFormat("private: {0}", Name);
            sb.AppendLine(" {");
            foreach (string p in Fields)
                sb.AppendLine(p);
            sb.AppendLine("}");
            sb.AppendLine();
        }

        public void Parse(Cursor cursor)
        {
            Name = cursor.Name;
            _cursor = cursor;
            Fields = new List<string>();
            cursor.VisitChildren(RecusiveVisitor);
        }

        private CursorVisitResult RecusiveVisitor(Cursor cursor, Cursor parent)
        {
            if (_cursor.Equals(parent))
                IsStructure = cursor.Type.Kind == TypeKind.Record;
            if (cursor.Kind == CursorKind.FieldDeclaration)
            {
                if (cursor.Type.Kind == TypeKind.ConstantArray)
                {
                    String field = String.Format("    {1} {0}[{2}];", cursor.Name, cursor.Type.ElementType.Kind,
                                                 cursor.Type.ElementCount);
                    Fields.Add(field);
                }
                else
                {
                    String field = String.Format("    {1} {0};", cursor.Name, cursor.Type.Kind);
                    Fields.Add(field);
                }
            }
            return CursorVisitResult.Recurse;
        }
    }
}