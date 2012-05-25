// KClmtrWrapper.h
#include "../../kclmtr/KClmtr.h"
#include <vcclr.h>
#pragma once

using namespace System;

namespace KClmtrWrapper {
	ref class KClmtrWrap;

	class SubClass : public KClmtr {

	public:
		SubClass(gcroot<KClmtrWrap^> _kcw);
		void printMeasure(Measurement m);
		void printFlick(Flicker f);
		gcroot<KClmtrWrap^>  _kclmtrwrapper;
	};

	public ref struct wMeasurement {
		double x;               //The x in the xyl
		double y;               //The y in the xyl
		double l;               //The l in the xyl
		double bigx;            //The x in the xyz
		double bigy;            //The y in the xyz
		double bigz;            //The z in the xyz
		double bigxraw;         //The xraw in the xyz
		double bigyraw;         //The yraw in the xyz
		double bigzraw;         //The zraw in the xyz
		double r;               //The r in the rgb
		double g;               //The g in the rgb
		double b;               //The b in the rgb
		double u;               //The u' in the u'v'y
		double v;               //The v' in the u'v'y
		double nm;              //The nm in the nmdu'v'Y
		double du;              //The duv' in the nmdu'v'Y
		//double L;               //The L in L*A*B*
		//double A;               //The A in L*A*B*
		//double B;               //The B in L*A*B*
		String^ redrange;		//The range which the KClmtr is in red
		String^ greenrange;		//The range which the KClmtr is in green
		String^ bluerange;		//The range which the KClmtr is in blue
		int range;              //The range which the KClmtr is in overall
		double temp;            //The temperature in K
		double duv;             //The distance off the curve
		int errorcode;          //The error code whenever you are getting data
		String^ errorstring;	//The string
		int averagingby;        //How many measurements we are averaging by
		bool readyflag;         //Ready or not to grab it

		wMeasurement(){}
		wMeasurement(Measurement measurement) {
			x = measurement.x;
			y = measurement.y;
			l = measurement.l;
			bigx = measurement.bigx;
			bigy = measurement.bigy;
			bigz = measurement.bigz;
			bigxraw = measurement.bigxraw;
			bigyraw = measurement.bigyraw;
			bigzraw = measurement.bigzraw;
			r = measurement.r;
			g = measurement.g;
			b = measurement.b;
			u = measurement.u;
			v = measurement.v;
			nm = measurement.nm;
			du = measurement.du;
			//L = measurement.L;
			//A = measurement.A;
			//B = measurement.B;
			redrange = gcnew String(measurement.redrange.c_str());
			greenrange = gcnew String(measurement.greenrange.c_str());
			bluerange = gcnew String(measurement.bluerange.c_str());
			range = measurement.range;
			duv = measurement.duv;
			errorcode = measurement.errorcode;
			errorstring = gcnew String(measurement.errorstring.c_str());
			averagingby = measurement.averagingby;
			readyflag = measurement.readyflag;
		}
	};

	public ref struct wwrgb {
		//white, red, green, blue
		//x, y, z
		//The z from when the screen was blue
		array<double,2>^ v;

		wwrgb(){
			v = gcnew array<double, 2>(4, 3);
		}
		wwrgb(wrgb WRGB){
			v = gcnew array<double, 2>(4, 3);
			for(int i=0; i<4; ++i){
				for(int j=0; j<3; ++j){
					v[i,j] = WRGB.v[i][j];
				}
			}
		}
		wrgb getNwrgb(){
			wrgb WRGB;
			for(int i=0; i<4; ++i){
				for(int j=0; j<3; ++j){
					WRGB.v[i][j] = v[i,j];
				}
			}
			return WRGB;
		}
	};

	public ref struct wBlackMatrix {
		array<double>^ range1;
		array<double>^ range2;
		array<double>^ range3;
		array<double>^ range4;
		array<double>^ range5;
		array<double>^ range6;
		double Therm;
		int errorcode;            //The error code whenever you are getting data
		String^ errorstring;      //The string

		wBlackMatrix(){}
		wBlackMatrix(BlackMatrix black){
			for(int i = 0; i < 3; i++){
				range1[i] = black.range1[i];
				range2[i] = black.range2[i];
				range3[i] = black.range3[i];
				range4[i] = black.range4[i];
				range5[i] = black.range5[i];
				range6[i] = black.range6[i];
			}
			Therm = black.Therm;
			errorcode = black.errorcode;
			errorstring = gcnew String(black.errorstring.c_str());
		}
	};

	public ref struct wCorrectedCoefficient {
		static array<double,2>^ colorMatrix = gcnew array<double,2>(3,3);
		static array<double,2>^ rgbMatrix = gcnew array<double,2>(3,3);
		wCorrectedCoefficient(){}
		wCorrectedCoefficient(CorrectedCoefficient corrected){
			for(int i = 0; i < 3; i++){
				for(int x = 0; x < 3; x++){
					colorMatrix[i,x] = corrected.colorMatrix[i][x];
					rgbMatrix[i,x] = corrected.rgbMatrix[i][x];
				}
			}
		}
		CorrectedCoefficient getNCorrectedCoefficient(){
			CorrectedCoefficient corrected;
			for(int i = 0; i < 3; i++){
				for(int x = 0; x < 3; x++){
					corrected.colorMatrix[i][x] = colorMatrix[i,x];
					corrected.rgbMatrix[i][x] = rgbMatrix[i,x];
				}
			}
			return corrected;
		}
	};

	public ref struct wFlicker {
		wMeasurement ^xyz;					//The measurement from XYZ
		array<double,2> ^peakfrequency;		//The top 3 frequency of DB
		array<double> ^flickerDB;			//The DB from 1hz to 100hz
		array<double> ^flickerPercent;		//The Percent from 1hz to 100hz
		int errorcode;						//The error code whenever you are getting data
		String^ errorstring;				//The string
		bool readyflag;					    //Ready or not to grab it

		wFlicker(){}
		wFlicker(Flicker flicker){
			xyz = gcnew wMeasurement(flicker.xyz);
			peakfrequency = gcnew array<double, 2>(3, 3);
			flickerDB = gcnew array<double>(101);	
			flickerPercent = gcnew array<double>(101);
			for(int i = 0; i < 3; i++){
				for(int x = 0; x < 3; x++){
					peakfrequency[i,x] = flicker.peakfrequency[i][x];
				}
			}
			for(int i = 0; i < 101; i++){
				flickerDB[i] =  flicker.flickerDB[i];
				flickerPercent[i] = flicker.flickerPercent[i];
			}
			errorcode = flicker.errorcode;
			errorstring = gcnew String(flicker.errorstring.c_str());
			readyflag = flicker.readyflag;
		}
	};

	public ref struct wwhitespect {
		double x;                //The X to the Whitespect modifier
		double y;                //The y to the Whitespect modifier
		double z;                //The z to the Whitespect modifier
		double xy;               //The allowed variance of xy
		double l;                //The allowed variance of Y
		wwhitespect(){}
		wwhitespect(whitespect White){
			x = White.x;
			y = White.y;
			z = White.z;
			xy = White.xy;
			l = White.l;
		}
		whitespect getNwhitespect(){
			whitespect White;

			White.x = x;
			White.y = y;
			White.z = z;
			White.xy = xy;
			White.l = l;

			return White;
		}
	};

	public ref class K10VWrap {
	public:
		ref struct wColors{
			int red;
			int green;
			int blue;

			wColors(){}
			wColors(Colors color){
				red = color.red;
				green = color.green;
				blue = color.blue;
			}
			Colors getNColor(){
				Colors color;

				color.red = red;
				color.green = green;
				color.blue = blue;

				return color;
			}
		};

		K10VWrap(){
			_k10v = new K10V;
		}
		virtual ~K10VWrap(void){
			delete _k10v;
		}
		K10VWrap(K10V k10v){
			_k10v = new K10V(k10v);
		}

		property wColors^ ColorField{
			wColors^ get(){
				return gcnew wColors(_k10v->getColorField());
			}
			void set(wColors^ value){
				_k10v->setColorField(value->getNColor());
			}
		}

		K10V getNK10V(){
			return *_k10v;
		}

	private:
		K10V *_k10v;
	};

	public ref class KClmtrWrap {
	public:
		KClmtrWrap(){
			_kclmtr = new SubClass(this);

			this->backgroundWorkerMeasure = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerFlicker = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorkerMeasure->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &KClmtrWrap::backgroundWorkerMeasure_DoWork);
			this->backgroundWorkerFlicker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &KClmtrWrap::backgroundWorkerFlicker_DoWork);
		}
		virtual ~KClmtrWrap(void){
			delete _kclmtr;
		}

		//Property
		/// <summary>
		/// Gets or sets the com port's number
		/// </summary>
		/// <value> Com port's number </value>
		property int port{
			int get(){
				string foobar = _kclmtr->getPort();
				return Convert::ToInt16(NativeToDotNet(foobar.substr(3,1)));
			}
			void set(int value){
				String^ port = "\\\\.\\COM" + value;
				string foobar = MarshalString(port);
				_kclmtr->setPort(foobar);
			}
		}
		/// <summary>
		/// Gets the Serail Number of the Klein device
		/// </summary>
		property String^ SN{
			String^ get(){
				return NativeToDotNet(_kclmtr->getSN());
			}
		}
		/// <summary>
		/// Gets the Model Number of the Klein device
		/// </summary>
		property String^ Model{
			String^ get(){
				return NativeToDotNet(_kclmtr->getModel());
			}
		}
		/// <summary>
		/// Sets the Aiming Lights on or Off
		/// </summary>
		/// <value> ON = true, OFF = False </value>
		property bool AimingLights{
			void set(bool value){
				_kclmtr->setAimingLights(value);
			}
		}
		/// <summary>
		/// Returns true if the device is currently hooked up. Returns false if the device is not currently hooked up.
		/// </summary>
		property bool isPortOpen{
			bool get(){
				return _kclmtr->isPortOpen();
			}
		}

		//Property - CalFiles
		/// <summary>
		/// Gets or Set the current Cal File based on it's name
		/// </summary>
		property String^ CalFileName{
			String^ get(){
				return NativeToDotNet(_kclmtr->getCalFileName());
			}
			void set(String^ value){
				_kclmtr->setCalFileName(MarshalString(value));
			}
		}
		/// <summary>
		/// Gets or Set the current Cal File based on it's ID
		/// </summary>
		property int CalFileID{
			int get(){
				return _kclmtr->getCalFileID();
			}
			void set(int value){
				_kclmtr->setCalFileID(value);
			}
		}
		/// <summary>
		/// Gets the current Cal File's calaibration matrix
		/// </summary>
		property array<double,2>^ CalMatrix{
			array<double,2>^ get(){
				array<double,2>^ matrix = gcnew array<double,2>(3,3);
				for (int i = 0; i < 3; i++){
					for(int x = 0; x < 3; x++){
						matrix[i, x] = _kclmtr->getcalMatrix().v[i][x];
					}
				}
				return matrix;
			}
		}
		/// <summary>
		/// Gets the current Cal File's color matrix
		/// </summary>
		property array<double,2>^ RGBMatrix{
			array<double,2>^ get(){
				array<double,2>^ matrix = gcnew array<double,2>(3,3);
				for (int i = 0; i < 3; i++){
					for(int x = 0; x < 3; x++){
						matrix[i, x] = _kclmtr->getRGBMatrix().v[i][x];
					}
				}
				return matrix;
			}
		}
		/// <summary>
		/// Gets or set the current Cal File's white spect
		/// </summary>
		property wwhitespect^ WhiteSpect{
			wwhitespect^ get(){
				return gcnew wwhitespect(_kclmtr->getWhiteSpect());
			}
			void set(wwhitespect^ value){
				_kclmtr->setWhiteSpect(value->getNwhitespect());
			}
		}
		/// <summary>
		/// Gets the cal files that is on the klein device
		/// </summary>
		property array<System::String ^>^ CalFileList{
			array<System::String ^>^ get(){
				array<System::String ^>^ List = gcnew array<System::String ^>(97);
				const std::string* calFileList = _kclmtr->getCalFileList();
				for(int i = 0; i <= 96; ++i)
					List[i] = NativeToDotNet(calFileList[i]);
				return List;
			}
		}
		/// <summary>
		/// set the temporary cal file spect
		/// </summary>
		void setTempCalFile(wCorrectedCoefficient^ Matrix, wwhitespect^ whiteSpect){
			_kclmtr->setTempCalFile(Matrix->getNCorrectedCoefficient(), whiteSpect->getNwhitespect());
		}

		//Property - FFT
		/// <summary>
		/// Get or Set to use the cosine correction in the flicker output
		/// </summary>
		property bool FFT_Cosine{
			bool get(){
				return _kclmtr->getFFT_Cosine();
			}
			void set(bool value){
				_kclmtr->setFFT_Cosine(value);
			}
		}
		/// <summary>
		/// Get or Set to use smoothing in the output of flicker. Smooths out the line of flicker
		/// </summary>
		property bool FFT_Smoothing{
			bool get(){
				return _kclmtr->getFFT_Smoothing();
			}
			void set(bool value){
				_kclmtr->setFFT_Smoothing(value);
			}
		}
		/// <summary>
		/// Get or Set the use of the EIAJ Roll off in the flicker output
		/// </summary>
		property bool FFT_RollOff{
			bool get(){
				return _kclmtr->getFFT_RoolOff();
			}
			void set(bool value){
				_kclmtr->setFFT_RollOff(value);
			}
		}
		/// <summary>
		/// Get or Set how many samples need for flicker data needs before returning flicker
		/// </summary> 
		/// <value> 256 samples -  1  second, 128 samples - .5  seconds, 64  samples - .25 seconds </value>
		property int FFT_samples{
			int get(){
				return _kclmtr->getFFT_Samples();
			}
			void set(int value){
				_kclmtr->setFFT_Samples(value);
			}
		}
		/// <summary>
		/// Get or Set the Virtual K10 object, K10V, to the KClmtr to be used during measurements
		/// </summary>
		property K10VWrap^ VirtualK10{
			K10VWrap^ get(){
				return gcnew K10VWrap(_kclmtr->getVirtualK10());
			}
			void set(K10VWrap^ value){
				_kclmtr->setVirtualK10(value->getNK10V());
			}
		}

		//XYZ
		/// <summary>
		/// Returns true if the device is measuring mode. Returns false if it is not in measuring mode.
		/// </summary>
		property bool isMeasure{
			bool get(){
				return _kclmtr->isMeasuring();
			}
		}
		/// <summary>
		/// Starts the Klein device to measure constantly.
		/// </summary>
		void startMeasuring(){
			_kclmtr->startMeasuring();
		}
		/// <summary>
		/// Stops the Klein device to stop measuring.
		/// </summary>
		void stopMeasuring(){
			_kclmtr->stopMeasuring();
		}
		/// <summary>
		/// Returns one measurement from the device. Do not need to startMeasuring() to use this method.
		/// </summary>
		wMeasurement ^getNextMeasurement(){
			return gcnew wMeasurement(_kclmtr->getNextMeasurement());
		}

		//Setting up to Store CalFiles
		/// <summary>
		/// This will create a coefficient matrix from the reference device measurement and the KClmtr measurement. This will not store a calibration file into the Klein Device, but just return the values that would store it. This is good to used with setTempCaliFile()
		/// </summary>
		/// <param name="Reference"> Reference The reference device's measurement </param>
		/// <param name="Kclmtr">  Kclmtr The KClmtr's measurement </param>
		/// <return> The meatrix that would be stored to the KClmtr, but does not </return>
		wCorrectedCoefficient^ getCoefficientTestMatrix(wwrgb^ Reference, wwrgb^ Kclmtr){
			return gcnew wCorrectedCoefficient(_kclmtr->getCoefficientTestMatrix(Reference->getNwrgb(), Kclmtr->getNwrgb()));
		}
		/// <summary>
		/// Deletes a Calibration file with it's ID.
		/// </summary>
		int deleteCalFile(int CalFileID){
			return _kclmtr->deleteCalFile(CalFileID);
		}

		//Storing CalFile
		/// <summary>
		/// This will store a Calibration file into the device, based on the reference device's measurement and the KClmtr's measurement
		/// </summary>
		/// <param name="ID"> The location which the Calibration file will be stored </param>
		/// <param name"name"> e The name of the Calibration file </param>
		/// <param name="Reference"> Reference The reference device's measurement </param>
		/// <param name="Kclmtr">  Kclmtr The KClmtr's measurement </param>
		/// <param name="whitespect> The white spect to be stored for the Calibration file </param>
		/// <return>int Error code. 0 is Good</return>
		int storeMatrices(int ID, String^ Name, wwrgb^ Reference, wwrgb^ Kclmtr, wwhitespect^ whitespect){
			return _kclmtr->storeMatrices(ID, MarshalString(Name), Reference->getNwrgb(), Kclmtr->getNwrgb(), whitespect->getNwhitespect());
		}

		//BlackCal - Cold
		/// <summary>
		/// Takes reading of counts, if passes saves to flash/ram
		/// </summary>
		wBlackMatrix^ captureBlackLevel(){
			return gcnew wBlackMatrix(_kclmtr->captureBlackLevel());
		}
		/// <summary>
		/// Reads matrix of saved counts from flash
		/// </summary>
		wBlackMatrix^ recallFlashMatrix(){
			return gcnew wBlackMatrix(_kclmtr->recallFlashMatrix());
		}

		//BlackCal - Hot
		/// <summary>
		///  Reads matrix of saved counts from RAM
		/// </summary>
		wBlackMatrix^ recallRAMMatrix(){
			return gcnew wBlackMatrix(_kclmtr->recallRAMMatrix());
		}
		/// <summary>
		/// Reads matrix of black thermal correction coefficents
		/// </summary>
		wBlackMatrix^ recallCoefficientMatrix(){
			return gcnew wBlackMatrix(_kclmtr->recallCoefficientMatrix());
		}

		//FFT
		/// <summary>
		/// Returns true if the device is in flicker mode. Returns false if the device is not in flicker mode
		/// </summary>
		/// <param name="grabConstantly"> If you are planning to use getNextFlicker() set this to be false. If you want it to return flicker has soon has it grabs one, set it to be true </param>
		/// <return> Error string, OK is good </return> 
		String^ StartFlicker(bool grabConstantly){
			return NativeToDotNet(_kclmtr->startFlicker(grabConstantly));
		}
		/// <summary>
		/// Grabs and returns one flicker measurement. The speed which this returns is based on the getFFT_Samples()
		/// </summary>
		wFlicker^ getNextFlicker(){
			return gcnew wFlicker(_kclmtr->getNextFlicker());
		}
		/// <summary>
		/// Stops the device from being in flicker mode. This also needs to be if you set the grabConstanly param in startFlicker()
		/// </summary>
		void StopFlicker(){
			_kclmtr->stopFlicker();
		}

		//setup/Close
		/// <summary>
		/// This will open the device
		/// </summary>
		/// <param name="theport">sets the port name</param>
		/// <return>A user should always have this true. This is used for internal use.</return>
		bool connect(int thePort){
			port = thePort;
			return _kclmtr->connect();
		}
		/// <summary>
		/// This will open the device to the PortName you have set.
		/// </summary>
		bool connect(){
			return _kclmtr->connect();
		}
		/// <summary>
		/// Closes the port and reset all the propeties of the KClmtr object
		/// </summary>
		void closePort(bool resetThePortName){
			_kclmtr->closePort(resetThePortName);
		}

		delegate System::Void MeasureEventHandler(wMeasurement^);
		delegate System::Void FlickerEventHandler(wFlicker^);
		event MeasureEventHandler^ measureEvent;
		event FlickerEventHandler^ flickerEvent;
		void printMeasure(wMeasurement^ m){
			while(backgroundWorkerMeasure->IsBusy);
			backgroundWorkerMeasure->RunWorkerAsync(m);
		}
		void printFlicker(wFlicker^ f){
			flickerEvent(f);
		}

	private:
		System::Void backgroundWorkerMeasure_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			measureEvent((KClmtrWrapper::wMeasurement^) e->Argument);
		}
		System::Void backgroundWorkerFlicker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			flickerEvent((KClmtrWrapper::wFlicker^) e->Argument);
		}

		System::ComponentModel::BackgroundWorker^ backgroundWorkerMeasure;
		System::ComponentModel::BackgroundWorker^ backgroundWorkerFlicker;
		string MarshalString(String^ s);
		System::String^ NativeToDotNet(std::string input);
		KClmtr *_kclmtr;
	};
}