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
using System.IO;
using System.Linq;
using System.Text;
using Clang;

namespace ClangGenerator
{
    internal class Program
    {
        private static FileInfo _fi;

        private static int _depth;
        private static bool _locked = true;

        private static readonly List<FunctionParser> _functions = new List<FunctionParser>();
        private static readonly List<StructureParser> _structures = new List<StructureParser>();

        private static void Main(string[] arguments)
        {
            if (arguments.Count() != 1)
            {
                Console.WriteLine("Needs one argument: path to Index.h");
            }
            _fi = new FileInfo(arguments[0]);
            if (!_fi.Exists)
            {
                Console.WriteLine("Could not find file '{0}'", _fi.FullName);
            }

            using (var context = new Context())
            {
                Console.WriteLine("Information: {0}", Context.ClangVersion);

                var parameters = new List<string>();
                parameters.Add("-std=c99");

                using (var translationUnit = new TranslationUnit(context, _fi.FullName,
                                                                 TranslationUnitFlags.DetailedPreprocessingRecord,
                                                                 parameters))
                {
                    if (translationUnit.Diagnostics.Count > 0)
                    {
                        foreach (var diagnostic in translationUnit.Diagnostics)
                        {
                            Console.WriteLine("{0}:{1}: {2}", diagnostic.Location.SpellingPosition.File, 
                                diagnostic.Location.SpellingPosition.Line, diagnostic.Spelling);
                        }
                    }
                    else
                    {
                        _depth = 0;
                        _locked = true;
                        new Cursor(translationUnit).VisitChildren(RecursiveCursorVisitor);
                    }
                }
            }

            //StringBuilder sb = new StringBuilder ();
            //foreach (var group in _functions.GroupBy (x => x.FirstParameterType)) {
            //    Console.WriteLine (group.Key);
            //    sb.AppendLine();
            //    sb.Append("class ");
            //    sb.AppendLine(group.Key);
            //    foreach (var func in group) {
            //        func.Write (sb);
            //    }
            //}
            //foreach (var structParser in _structures) {
            //    structParser.Write (sb);
            //}
            //String contents = sb.ToString ();
            //String filename = Path.Combine (fi.DirectoryName, "_methods.h");
            //Console.WriteLine (contents);
            //File.WriteAllText (filename, contents);
        }

        private static CursorVisitResult RecursiveCursorVisitor(Cursor cursor, Cursor parent)
        {
            if (cursor.Location.SpellingPosition.File.Path == _fi.FullName)
            {
                _locked = false;

                DumpCursor(cursor);
                if (cursor.Kind == CursorKind.EnumerationDeclaration)
                {
                    var wrapper = new EnumWrapper(_fi.Directory);
                    wrapper.Parse(cursor);
                }
                else if (cursor.Kind == CursorKind.TypedefDeclaration)
                {
                    var structure = new StructureParser();
                    structure.Parse(cursor);
                    if (structure.IsStructure)
                        _structures.Add(structure);
                }
                else if (cursor.Kind == CursorKind.FunctionDeclaration)
                {
                    var func = new FunctionParser();
                    func.Parse(cursor);
                    //Console.WriteLine (" -> {0,-24} {1}", func.ReturnType, func.Name);
                    //foreach (string p in func.Parameters) {
                    //    var split = p.Split (':');
                    //    Console.WriteLine ("            {0,-24}   {1}", split[0], split[1]);
                    //}
                    _functions.Add(func);
                }
                else
                {
                    _depth++;
                    cursor.VisitChildren(RecursiveCursorVisitor);
                    _depth--;
                }
            }
            else
            {
                if (!_locked)
                {
                    Console.WriteLine("<inside '{0}'>", cursor.Location.SpellingPosition.File.Path);
                    _locked = true;
                }
            }

            return CursorVisitResult.Continue;
        }

        private static void DumpCursor(Cursor cursor)
        {
#if DEBUG
            var sb = new StringBuilder();
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
            Console.WriteLine(sb);
#endif
        }
    }
}