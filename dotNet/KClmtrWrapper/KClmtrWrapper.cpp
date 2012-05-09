// This is the main DLL file.

#include "stdafx.h"
#include "KClmtrWrapper.h"

string KClmtrWrapper::KClmtrWrap::MarshalString(String^ s){
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	string os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}
System::String^ KClmtrWrapper::KClmtrWrap::NativeToDotNet(std::string input){
	return gcnew String(input.c_str());
}
void KClmtrWrapper::SubClass::printMeasure(Measurement m){
	_kclmtrwrapper->printMeasure(gcnew wMeasurement(m));
}
void KClmtrWrapper::SubClass::printFlick(Flicker f){
	_kclmtrwrapper->printFlick(gcnew wFlicker(f));
}
KClmtrWrapper::SubClass::SubClass(gcroot<KClmtrWrap^> _kcw){
	_kclmtrwrapper = _kcw;
}