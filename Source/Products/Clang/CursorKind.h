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

		//FirstDeclaration = CXCursor_FirstDecl,
		UnexposedDeclaration = CXCursor_UnexposedDecl,
		StructureDeclaration = CXCursor_StructDecl,
		UnionDeclaration = CXCursor_UnionDecl,
		ClassDeclaration = CXCursor_ClassDecl,
		EnumerationDeclaration = CXCursor_EnumDecl,
		FieldDeclaration = CXCursor_FieldDecl,
		EnumerationConstantDeclaration = CXCursor_EnumConstantDecl,
		FunctionDeclaration = CXCursor_FunctionDecl,
		VariableDeclaration = CXCursor_VarDecl,
		ParameterDeclaration = CXCursor_ParmDecl,

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
		LinkageSpecifier = CXCursor_LinkageSpec,
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
		CppAccessSpecifier = CXCursor_CXXAccessSpecifier,
		//LastDeclaration = CXCursor_LastDecl,

		//FirstReference = CXCursor_FirstRef,
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
		//LastReference = CXCursor_LastRef,
		
		//FirstInvalid = CXCursor_FirstInvalid,
		InvalidFile = CXCursor_InvalidFile,
		NoDeclarationFound = CXCursor_NoDeclFound,
		NotImplemented = CXCursor_NotImplemented,
		InvalidCode = CXCursor_InvalidCode,
		//LastInvalid = CXCursor_LastInvalid,

		// Expressions - 100
		//FirstExpression = CXCursor_FirstExpr,
		UnexposedExpression = CXCursor_UnexposedExpr,
		DeclarationReferenceExpression = CXCursor_DeclRefExpr,
		MemberReferenceExpression = CXCursor_MemberRefExpr,
		CallExpression = CXCursor_CallExpr,
		ObjectiveCMessageExpression = CXCursor_ObjCMessageExpr,
		BlockExpression = CXCursor_BlockExpr,
		IntegerLiteral = CXCursor_IntegerLiteral,
		FloatingLiteral = CXCursor_FloatingLiteral,
		ImaginaryLiteral= CXCursor_ImaginaryLiteral,
		StringLiteral = CXCursor_StringLiteral,
		CharacterLiteral = CXCursor_CharacterLiteral,
		ParenthesizedExpression = CXCursor_ParenExpr,
		UnaryOperator = CXCursor_UnaryOperator,
		ArraySubscriptExpression = CXCursor_ArraySubscriptExpr,
		BinaryOperator = CXCursor_BinaryOperator,
		CompoundAssignOperator = CXCursor_CompoundAssignOperator,
		ConditionalOperator = CXCursor_ConditionalOperator, // ?: ternary operator
		CStyleCastExpression = CXCursor_CStyleCastExpr,
		CompoundLiteralExpression = CXCursor_CompoundLiteralExpr,
		InitializerListExpression = CXCursor_InitListExpr,
		GnuAddressLabelExpression = CXCursor_AddrLabelExpr, // GNU address (&&label)
		GnuStatementExpression = CXCursor_StmtExpr,			// ({int X=4; X;})
		GenericSelectionExpression = CXCursor_GenericSelectionExpr,
		GnuNullExpression = CXCursor_GNUNullExpr, // GNU __null extension
		CppStaticCastExpression = CXCursor_CXXStaticCastExpr,
		CppDynamicCastExpression = CXCursor_CXXDynamicCastExpr,
		CppReinterpretCastExpression = CXCursor_CXXReinterpretCastExpr,
		CppConstCastExpression = CXCursor_CXXConstCastExpr,
		CppFunctionalCastExpression = CXCursor_CXXFunctionalCastExpr,
		CppTypeidExpression = CXCursor_CXXTypeidExpr,
		CppBooleanLiteral = CXCursor_CXXBoolLiteralExpr,
		CppNullPointerLiteral = CXCursor_CXXNullPtrLiteralExpr,
		CppThisExpression = CXCursor_CXXThisExpr,
		CppThrowExpression = CXCursor_CXXThrowExpr,
		CppNewExpression = CXCursor_CXXNewExpr,
		CppDeleteExpression = CXCursor_CXXDeleteExpr,
		UnaryExpression = CXCursor_UnaryExpr,
		ObjectiveCStringLiteral = CXCursor_ObjCStringLiteral,
		ObjectiveCEncodeExpression = CXCursor_ObjCEncodeExpr,
		ObjectiveCSelectorExpression = CXCursor_ObjCSelectorExpr,
		ObjectiveCProtocolExpression = CXCursor_ObjCProtocolExpr,
		ObjectiveCBridgedCastExpression = CXCursor_ObjCBridgedCastExpr,
		PackExpansionExpression = CXCursor_PackExpansionExpr,
		SizeOfPackExpression = CXCursor_SizeOfPackExpr,
		//LastExpression = CXCursor_LastExpr,

		// Statements
		//FirstStatement = CXCursor_FirstStmt,
		UnexposedStatement = CXCursor_UnexposedStmt, // 200
		LabelStatement = CXCursor_LabelStmt,
		CompoundStatement = CXCursor_CompoundStmt,
		CaseStatement = CXCursor_CaseStmt,
		DefaultStatement = CXCursor_DefaultStmt,
		IfStatement = CXCursor_IfStmt,
		SwitchStatement = CXCursor_SwitchStmt,
		WhileStatement = CXCursor_WhileStmt,
		DoStatement = CXCursor_DoStmt,
		ForStatement = CXCursor_ForStmt,
		GotoStatement = CXCursor_GotoStmt,
		IndirectGotoStatement = CXCursor_IndirectGotoStmt,
		ContinueStatement = CXCursor_ContinueStmt,
		BreakStatement = CXCursor_BreakStmt,
		ReturnStatement = CXCursor_ReturnStmt,
		AssemblyStatement = CXCursor_AsmStmt,
		ObjectiveCAtTryCatchFinallyStatement = CXCursor_ObjCAtTryStmt,
		ObjectiveCAtCatchStatement = CXCursor_ObjCAtCatchStmt,
		ObjectiveCAtFinallyStatement = CXCursor_ObjCAtFinallyStmt,
		ObjectiveCAtThrowStatement = CXCursor_ObjCAtThrowStmt,
		ObjectiveCAtSynchronizedStatement = CXCursor_ObjCAtSynchronizedStmt,
		ObjectiveCAutoreleasePoolStatement = CXCursor_ObjCAutoreleasePoolStmt,
		ObjectiveCForCollectionStatement = CXCursor_ObjCForCollectionStmt,
		CppCatchStatement = CXCursor_CXXCatchStmt,
		CppTryStatement = CXCursor_CXXTryStmt,
		CppForRangeStatement = CXCursor_CXXForRangeStmt,
		WinSehTryStatement = CXCursor_SEHTryStmt,
		WinSehExceptStatement = CXCursor_SEHExceptStmt,
		WinSehFinallyStatement = CXCursor_SEHFinallyStmt,
		NullStatement = CXCursor_NullStmt,
		DeclarationStatement = CXCursor_DeclStmt,
		//LastStatement = CXCursor_LastStmt,

		TranslationUnit = CXCursor_TranslationUnit,

		//FirstAttribute = CXCursor_FirstAttr,
		UnexposedAttribute = CXCursor_UnexposedAttr,
		InterfaceBuilderActionAttribute = CXCursor_IBActionAttr,
		InterfaceBuilderOutletAttribute = CXCursor_IBOutletAttr,
		InterfaceBuilderOutletCollectionAttribute = CXCursor_IBOutletCollectionAttr,
		CppFinalAttribute = CXCursor_CXXFinalAttr,
		CppOverrideAttribute = CXCursor_CXXOverrideAttr,
		AnnotateAttribute = CXCursor_AnnotateAttr,
		AssemblyLabelAttribute = CXCursor_AsmLabelAttr,
		//LastAttribute = CXCursor_LastAttr,

		// preprocessing
		//FirstPreprocessing = CXCursor_FirstPreprocessing,
		PreprocessingDirective = CXCursor_PreprocessingDirective,
		MacroDefinition = CXCursor_MacroDefinition,
		MacroExpansion = CXCursor_MacroExpansion,
		MacroInstantiation = CXCursor_MacroInstantiation,
		InclusionDirective = CXCursor_InclusionDirective,
		//LastPreprocessing = CXCursor_LastPreprocessing,
	};
}
