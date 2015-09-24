// This is the main DLL file.

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
	MeasureCallBack(m);
}
void KClmtrWrapper::SubClass::printFlicker(Flicker f){
	FlickerCallBack(f);
}
KClmtrWrapper::SubClass::SubClass(DelMeasure ^_Measure, DelFlicker ^_Flicker) {
	delegateMeasureCallBack = _Measure;
	delegateFlickerCallBack = _Flicker;
	MeasureCallBack = (CallbackMeasure)Marshal::GetFunctionPointerForDelegate(_Measure).ToPointer();
	FlickerCallBack = (CallbackFlicker)Marshal::GetFunctionPointerForDelegate(_Flicker).ToPointer();
}