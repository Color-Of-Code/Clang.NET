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

#pragma once

#include "Index.h"

namespace Clang {

	public enum class TypeKind {

		Invalid = CXType_Invalid,

		Unexposed = CXType_Unexposed,

		Void = CXType_Void,
		Bool = CXType_Bool,
		Char_U = CXType_Char_U,
		UChar = CXType_UChar,
		Char16 = CXType_Char16,
		Char32 = CXType_Char32,
		UShort = CXType_UShort,
		UInt = CXType_UInt,
		ULong = CXType_ULong,
		ULongLong = CXType_ULongLong,
		UInt128 = CXType_UInt128,
		Char_S = CXType_Char_S,
		SChar = CXType_SChar,
		WChar = CXType_WChar,
		Short = CXType_Short,
		Int = CXType_Int,
		Long = CXType_Long,
		LongLong = CXType_LongLong,
		Int128 = CXType_Int128,
		Float = CXType_Float,
		Double = CXType_Double,
		LongDouble = CXType_LongDouble,
		NullPointer = CXType_NullPtr,
		Overload = CXType_Overload,
		Dependent = CXType_Dependent,
		ObjectiveCId = CXType_ObjCId,
		ObjectiveCClass = CXType_ObjCClass,
		ObjectiveCSel = CXType_ObjCSel,
		//CXType_FirstBuiltin = CXType_Void,
		//CXType_LastBuiltin  = CXType_ObjCSel,

		Complex = CXType_Complex,
		Pointer = CXType_Pointer,
		BlockPointer = CXType_BlockPointer,
		LValueReference = CXType_LValueReference,
		RValueReference = CXType_RValueReference,
		Record = CXType_Record,
		Enum = CXType_Enum,
		Typedef = CXType_Typedef,
		ObjectiveCInterface = CXType_ObjCInterface,
		ObjectiveCObjectPointer = CXType_ObjCObjectPointer,
		FunctionNoPrototype = CXType_FunctionNoProto,
		FunctionPrototype = CXType_FunctionProto,
		ConstantArray = CXType_ConstantArray
	};
}
