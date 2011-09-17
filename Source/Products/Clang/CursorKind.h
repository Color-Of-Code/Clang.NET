// Copyright (c) 2011 Josh Petrie
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
	public enum class CursorKind {
		UnexposedDeclaration = CXCursor_UnexposedDecl,
		StructDeclaration = CXCursor_StructDecl,
		UnionDeclaration = CXCursor_UnionDecl,
		ClassDeclaration = CXCursor_ClassDecl,
		EnumDeclaration = CXCursor_EnumDecl,
		FieldDeclaration = CXCursor_FieldDecl,
		EnumerationConstantDeclaration = CXCursor_EnumConstantDecl,
		FunctionDeclaration = CXCursor_FunctionDecl,
		VariableDeclaration = CXCursor_VarDecl,
		ParmeterDeclaration = CXCursor_ParmDecl,
		ObjectiveCInterfaceDeclaration = CXCursor_ObjCInterfaceDecl,
		ObjectiveCCategoryDeclaration = CXCursor_ObjCCategoryDecl,
		ObjectiveCProtocolDeclaration = CXCursor_ObjCProtocolDecl,
		ObjectiveCPropertyDeclaration = CXCursor_ObjCPropertyDecl,
		ObjectiveCInstanceVariableDeclaration = CXCursor_ObjCIvarDecl,
		ObjectiveCInstanceMethodDeclaration = CXCursor_ObjCInstanceMethodDecl,
		ObjectiveCClassMethodDeclaration = CXCursor_ObjCClassMethodDecl,
		ObjectiveCImplementationDeclaration = CXCursor_ObjCImplementationDecl,
		ObjectiveCCategoryImplementationDeclaration = CXCursor_ObjCCategoryImplDecl,
		TypedefDeclaration = CXCursor_TypedefDecl,
		CppMethod = CXCursor_CXXMethod,
		Namespace = CXCursor_Namespace,
		LinkageSpec = CXCursor_LinkageSpec,
		Constructor = CXCursor_Constructor,
		Destructor = CXCursor_Destructor,
		ConversionFunction = CXCursor_ConversionFunction,
		TemplateTypeParameter = CXCursor_TemplateTypeParameter,
		NonTypeTemplateParameter = CXCursor_NonTypeTemplateParameter,
		TemplateTemplateParameter = CXCursor_TemplateTemplateParameter,
		FunctionTemplate = CXCursor_FunctionTemplate,
		ClassTemplate = CXCursor_ClassTemplate,
		ClassTemplatePartialSpecialization = CXCursor_ClassTemplatePartialSpecialization,
		NamespaceAlias = CXCursor_NamespaceAlias,
		UsingDirective = CXCursor_UsingDirective,
		UsingDeclaration = CXCursor_UsingDeclaration,
		TypeAliasDeclaration = CXCursor_TypeAliasDecl,
		ObjectiveCSynthesizeDeclaration = CXCursor_ObjCSynthesizeDecl,
		ObjectiveCDynamicDeclaration = CXCursor_ObjCDynamicDecl,
		FirstDeclaration = CXCursor_FirstDecl,
		LastDeclaration = CXCursor_LastDecl,
		FirstReference = CXCursor_FirstRef,
		ObjectiveCSuperClassReference = CXCursor_ObjCSuperClassRef,
		ObjectiveCProtocolRefference = CXCursor_ObjCProtocolRef,
		ObjectiveCClassReference = CXCursor_ObjCClassRef,
		TypeReference = CXCursor_TypeRef,
		CppBaseSpecifier = CXCursor_CXXBaseSpecifier,
		TemplateReference = CXCursor_TemplateRef,
		NamespaceReference = CXCursor_NamespaceRef,
		MemberReference = CXCursor_MemberRef,
		LabelReference = CXCursor_LabelRef,
		OverloadedDeclReference = CXCursor_OverloadedDeclRef,
		LastReference = CXCursor_LastRef,
		FirstInvalid = CXCursor_FirstInvalid,
		InvalidFile = CXCursor_InvalidFile,
		NoDeclarationFound = CXCursor_NoDeclFound,
		NotImplemented = CXCursor_NotImplemented,
		InvalidCode = CXCursor_InvalidCode,
		LastInvalid = CXCursor_LastInvalid,
		FirstExpression = CXCursor_FirstExpr,
		UnexposedExpression = CXCursor_UnexposedExpr,
		DeclarationReferenceExpression = CXCursor_DeclRefExpr,
		MemberReferenceExpression = CXCursor_MemberRefExpr,
		CallExpression = CXCursor_CallExpr,
		ObjectiveCMessageExpression = CXCursor_ObjCMessageExpr,
		BlockExpression = CXCursor_BlockExpr,
		LastExpression = CXCursor_LastExpr,
		FirstStatement = CXCursor_FirstStmt,
		UnexposedStatement = CXCursor_UnexposedStmt,
		LabelStatement = CXCursor_LabelStmt,
		LastStatement = CXCursor_LastStmt,
		TranslationUnit = CXCursor_TranslationUnit,
		FirstAttribute = CXCursor_FirstAttr,
		UnexposedAttribute = CXCursor_UnexposedAttr,
		InterfaceBuilderActionAttribute = CXCursor_IBActionAttr,
		InterfaceBuilderOutletAttribute = CXCursor_IBOutletAttr,
		InterfaceBuilderOutletCollectionAttribute = CXCursor_IBOutletCollectionAttr,
		LastAttribute = CXCursor_LastAttr,
		PreprocessingDirective = CXCursor_PreprocessingDirective,
		MacroDefinition = CXCursor_MacroDefinition,
		MacroExpansion = CXCursor_MacroExpansion,
		MacroInstantiation = CXCursor_MacroInstantiation,
		InclusionDirective = CXCursor_InclusionDirective,
		FirstPreprocessing = CXCursor_FirstPreprocessing,
		LastPreprocessing = CXCursor_LastPreprocessing,
	};
}
