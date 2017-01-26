/*
KClmtr Object to communicate with Klein K-10/8/1

Copyright (c) 2017 Klein Instruments Inc.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

// This is the main DLL file.

#include "KClmtrWrapper.h"

using namespace KClmtrBase::KClmtrNative;
using namespace KClmtrBase::KClmtrWrapper;

string KClmtrWrap::MarshalString(String^ s) {
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	string os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}
System::String^ KClmtrWrap::NativeToDotNet(std::string input){
	return gcnew String(input.c_str());
}
void SubClass::printMeasure(Measurement m){ 
	MeasureCallBack(m);
}
void SubClass::printFlicker(Flicker f){
	FlickerCallBack(f);
}
void SubClass::printCounts(Counts c){
	CountsCallBack(c);
}
SubClass::SubClass(DelMeasure ^_Measure, DelFlicker ^_Flicker, DelCounts ^_Counts) {
	delegateMeasureCallBack = _Measure;
	delegateFlickerCallBack = _Flicker;
	delegateCountsCallBack = _Counts;
	MeasureCallBack = (CallbackMeasure)Marshal::GetFunctionPointerForDelegate(_Measure).ToPointer();
	FlickerCallBack = (CallbackFlicker)Marshal::GetFunctionPointerForDelegate(_Flicker).ToPointer();
	CountsCallBack = (CallbackCounts)Marshal::GetFunctionPointerForDelegate(_Counts).ToPointer();
}