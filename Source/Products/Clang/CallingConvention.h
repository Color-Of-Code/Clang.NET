// File auto-generated using ClangGenerator - clang version 3.4 (181997).
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

    public enum class CallingConvention    {
        Default = CXCallingConv_Default,
        C = CXCallingConv_C,
        X86StdCall = CXCallingConv_X86StdCall,
        X86FastCall = CXCallingConv_X86FastCall,
        X86ThisCall = CXCallingConv_X86ThisCall,
        X86Pascal = CXCallingConv_X86Pascal,
        AAPCS = CXCallingConv_AAPCS,
        AAPCS_VFP = CXCallingConv_AAPCS_VFP,
        PnaclCall = CXCallingConv_PnaclCall,
        IntelOclBicc = CXCallingConv_IntelOclBicc,
        Invalid = CXCallingConv_Invalid,
        Unexposed = CXCallingConv_Unexposed,
    };

}

