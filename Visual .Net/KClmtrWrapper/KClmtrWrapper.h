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
#pragma once

#include "../../kclmtr/KClmtr.h"
#include "MatrixWrapper.h"
#include "MeasurementWrapper.h"
#include "FlickerWrapper.h"
#include "CountsWrapper.h"
#include "WRGBWrapper.h"
#include "BlackMatrixWrapper.h"
#include <vcclr.h>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace KClmtrBase {
	namespace KClmtrWrapper {
		using namespace KClmtrNative;
		using namespace KClmtrWrapper;
		/** @endcond */

		public ref class wCorrectedCoefficient {
		public:
			wCorrectedCoefficient() {
				coeff = new KClmtr::CorrectedCoefficient();
			}
			wCorrectedCoefficient(KClmtr::CorrectedCoefficient c) {
				coeff = new KClmtr::CorrectedCoefficient(c);
			}
			virtual  ~wCorrectedCoefficient() {
				this->!wCorrectedCoefficient();
			}
			property wMatrix<double> ^ColorMatrix {
				wMatrix<double> ^get() {
					return gcnew wMatrix<double>(coeff->colorMatrix);
				}
				void set(wMatrix<double> ^colorMatrix) {
					coeff->colorMatrix = colorMatrix->getNative();
				}
			}
			property wMatrix<double> ^RGBMatrix {
				wMatrix<double> ^get() {
					return gcnew wMatrix<double>(coeff->rgbMatrix);
				}
				void set(wMatrix<double> ^rgbMatrix) {
					coeff->colorMatrix = rgbMatrix->getNative();
				}
			}
			KClmtr::CorrectedCoefficient getNative() {
				return *coeff;
			}
		protected:
			!wCorrectedCoefficient() {
				delete coeff;
			}
		private:
			KClmtr::CorrectedCoefficient *coeff;
		};

		public ref class MeasureEventArgs : public EventArgs {
		public:
			property wMeasurement^ Measurement {
				wMeasurement^ get() {
					return m;
				}
			}
			MeasureEventArgs(wMeasurement ^ _m) {
				m = _m;
			}
		private:
			wMeasurement^ m;
		};
		public ref class FlickerEventArgs : public EventArgs {
		public:
			property wFlicker^ Flicker {
				wFlicker^ get() {
					return f;
				}
			}
			FlickerEventArgs(wFlicker^ _f) {
				f = _f;
			}
		private:
			wFlicker^ f;
		};
		public ref class CountsEventArgs : public EventArgs {
		public:
			property wCounts^ Counts {
				wCounts^ get() {
					return c;
				}
			}
			CountsEventArgs(wCounts^ _c) {
				c = _c;
			}
		private:
			wCounts^ c;
		};

		delegate void DelMeasure(Measurement m);
		delegate void DelFlicker(Flicker f);
		delegate void DelCounts(Counts c);
		typedef void(CALLBACK *CallbackMeasure)(Measurement);
		typedef void(CALLBACK *CallbackFlicker)(Flicker);
		typedef void(CALLBACK *CallbackCounts)(Counts);

		class SubClass : public KClmtr {
		public:
			SubClass(DelMeasure ^_Measure,
				DelFlicker ^_Flicker,
				DelCounts ^_Counts);
			~SubClass() { }
			void printMeasure(Measurement m);
			void printFlicker(Flicker f);
			void printCounts(Counts c);

		private:
			gcroot<DelMeasure^> delegateMeasureCallBack;
			gcroot<DelFlicker^> delegateFlickerCallBack;
			gcroot<DelCounts^> delegateCountsCallBack;
			CallbackMeasure MeasureCallBack;
			CallbackFlicker FlickerCallBack;
			CallbackCounts CountsCallBack;
		};
		/** @ingroup wrappers
		* 	@brief Wraps the Native object to work easly in .Net Framework
		*/
		public ref class KClmtrWrap  {
		public:
			KClmtrWrap() {
				DelMeasure^ callbackMeasure = gcnew DelMeasure(this, &KClmtrWrap::printMeasure);
				DelFlicker^ callbackFlicker = gcnew DelFlicker(this, &KClmtrWrap::printFlicker);
				DelCounts^ callbackCounts = gcnew DelCounts(this, &KClmtrWrap::printCounts);
				_kclmtr = new SubClass(callbackMeasure, callbackFlicker, callbackCounts);
			}
			virtual ~KClmtrWrap() {
				this->!KClmtrWrap();
			}
			//Property

			/// <summary>
			/// Gets or sets the com port's number
			/// </summary>
			/// <value> Com port's number </value>
			property int port {
				int get() {
					string foobar = _kclmtr->getPort();
					return Convert::ToInt16(NativeToDotNet(foobar.substr(3, 1)));
				}
				void set(int value) {
					String^ port = "\\\\.\\COM" + value;
					string foobar = MarshalString(port);
					_kclmtr->setPort(foobar);
				}
			}
			/// <summary>
			/// Gets the Serail Number of the Klein device
			/// </summary>
			property String^ SerialNumber {
				String^ get() {
					return NativeToDotNet(_kclmtr->getSerialNumber());
				}
			}
			/// <summary>
			/// Gets the Model Number of the Klein device
			/// </summary>
			property String^ Model {
				String^ get() {
					return NativeToDotNet(_kclmtr->getModel());
				}
			}
			/// <summary>
			/// Sets the Aiming Lights on or Off
			/// </summary>
			/// <value> ON = true, OFF = False </value>
			property bool AimingLights {
				void set(bool value) {
					_kclmtr->setAimingLights(value);
				}
			}
			/// <summary>
			/// Sets the Range 1-6
			/// </summary>
			/// <value> Ranges from 1 - 6, AutoRange and default = -1  </value>
			property int Range {
				void set(const int range) {
					_kclmtr->setRange(range);
				}
				int get() {
					return _kclmtr->getRange();
				}
			}
			/// <summary>
			/// Returns true if the device is currently hooked up. Returns false if the device is not currently hooked up.
			/// </summary>
			property bool isPortOpen {
				bool get() {
					return _kclmtr->isPortOpen();
				}
			}

			//Property - CalFiles
			/// <summary>
			/// Gets or Set the current Cal File based on it's name
			/// </summary>
			property String^ CalFileName {
				String^ get() {
					return NativeToDotNet(_kclmtr->getCalFileName());
				}
			}
			/// <summary>
			/// Gets or Set the current Cal File based on it's ID
			/// </summary>
			property int CalFileID {
				int get() {
					return _kclmtr->getCalFileID();
				}
				void set(int value) {
					_kclmtr->setCalFileID(value);
				}
			}
			/// <summary>
			/// Gets the current Cal File's calaibration matrix
			/// </summary>
			property wMatrix<double>^ CalMatrix {
				wMatrix<double>^ get() {
					return gcnew wMatrix<double>(_kclmtr->getCalMatrix());
				}
			}
			/// <summary>
			/// Gets the current Cal File's color matrix
			/// </summary>
			property wMatrix<double>^ RGBMatrix {
				wMatrix<double>^ get() {
					return gcnew wMatrix<double>(_kclmtr->getRGBMatrix());
				}
			}
			/// <summary>
			/// Gets or set the current GamutSpec that KClmtr is using to make Measurement
			/// </summary>
			property wGamutSpec^ GamutSpec {
				wGamutSpec^ get() {
					return gcnew wGamutSpec(_kclmtr->getGamutSpec());
				}
				void set(wGamutSpec^ value) {
					_kclmtr->setGamutSpec(value->getNative());
				}
			}
			/// <summary>
			/// Gets the cal files that is on the klein device
			/// </summary>
			property cli::array<System::String ^>^ CalFileList {
				cli::array<System::String ^>^ get() {
					cli::array<System::String ^>^ List = gcnew cli::array<System::String ^>(97);
					const std::string* calFileList = _kclmtr->getCalFileList();
					for (int i = 0; i <= 96; ++i)
						List[i] = NativeToDotNet(calFileList[i]);
					return List;
				}
			}
			/// <summary>
			/// set the temporary cal file spect
			/// </summary>
			void setTempCalFile(wCorrectedCoefficient^ Matrix) {
				_kclmtr->setTempCalFile(Matrix->getNative());
			}

			//Property - FFT
			/// <summary>
			/// Get or Set to use the cosine correction in the flicker output
			/// </summary>
			property bool FFT_Cosine {
				bool get() {
					return _kclmtr->getFFT_Cosine();
				}
				void set(bool value) {
					_kclmtr->setFFT_Cosine(value);
				}
			}
			/// <summary>
			/// Get or Set to use smoothing in the output of flicker. Smooths out the line of flicker
			/// </summary>
			property bool FFT_Smoothing {
				bool get() {
					return _kclmtr->getFFT_Smoothing();
				}
				void set(bool value) {
					_kclmtr->setFFT_Smoothing(value);
				}
			}
			/// <summary>
			/// Get or Set how many samples need for flicker data needs before returning flicker
			/// </summary> 
			/// <value> 256 samples -  1  second, 128 samples - .5  seconds, 64  samples - .25 seconds </value>
			property int FFT_samples {
				int get() {
					return _kclmtr->getFFT_Samples();
				}
				void set(int value) {
					_kclmtr->setFFT_Samples(value);
				}
			}
			/// <summary>
			/// Get or Set JEITA Discount for dB
			/// </summary> 
			/// <value> mode the mode switch to set it too</value>
			property bool FFT_DBJEITA_Discount {
				bool get() {
					return _kclmtr->getFFT_DBJEITA_Discount();
				}
				void set(bool value) {
					_kclmtr->setFFT_DBJEITA_Discount(value);
				}
			}
			/// <summary>
			/// Get or Set JEITA Discount for Percent
			/// </summary> 
			/// <value> mode the mode switch to set it too</value>
			property bool FFT_PercentJEITA_Discount {
				bool get() {
					return _kclmtr->getFFT_PercentJEITA_Discount();
				}
				void set(bool value) {
					_kclmtr->setFFT_PercentJEITA_Discount(value);
				}
			}

			/// <summary>
			/// Get or Set Percent's Calculation for FMA or normalized\n
			/// 		FMA = which will 4 * AC / DC * 100, or Peak to peak
			///	        Normalized = AC / DC * 100
			/// </summary> 
			/// <value> mode the mode switch to set it too</value>
			property PercentMode FFT_PercentMode {
				PercentMode get() {
					return _kclmtr->getFFT_PercentMode();
				}
				void set(PercentMode value) {
					_kclmtr->setFFT_PercentMode(value);
				}
			}
			/// <summary>
			/// Get or Set dB's Calculation for VISA\n
			///			VISA  =  20 * log10(2 * AC / DC) = JEITA + 3.01dB\n
			///			JETIA =  20 * log10(2 ^ (1 / 2) * AC / DC)
			/// </summary> 
			/// <value> mode the mode switch to set it too</value>
			property DecibelMode FFT_DBMode {
				DecibelMode get() {
					return _kclmtr->getFFT_DBMode();
				}
				void set(DecibelMode value) {
					_kclmtr->setFFT_DBMode(value);
				}
			}
			/// <summary>
			/// Returns true if the device is measuring mode. Returns false if it is not in measuring mode.
			/// </summary>
			property bool isFlickering {
				bool get() {
					return _kclmtr->isFlickering();
				}
			}
			/// <summary>
			/// Gets and Set the number of peaks to find when Flickering
			/// </summary>
			property int FFT_numberOfPeaks {
				int get() {
					return _kclmtr->getFFT_numberOfPeaks();
				}
				void set(int value) {
					_kclmtr->setFFT_numberOfPeaks(value);
				}
			}
			//XYZ
			/// <summary>
			/// Gets and Sets the max number of measurements to average over in low light measurments
			/// </summary>
			property int MaxAverageCount {
				int get() {
					return _kclmtr->getMaxAverageCount();
				}
				void set(int value) {
					_kclmtr->setMaxAverageCount(value);
				}
			}
			/// <summary>
			/// Returns true if the device is measuring mode. Returns false if it is not in measuring mode.
			/// </summary>
			property bool isMeasure {
				bool get() {
					return _kclmtr->isMeasuring();
				}
			}
			/// <summary>
			/// Get and Set how fast the device measure
			/// </summary>
			property SpeedMode MeasureSpeedMode {
				SpeedMode get() {
					return _kclmtr->getMeasureSpeedMode();
				}
				void set(SpeedMode value) {
					_kclmtr->setMeasureSpeedMode(value);
				}
			}			
			/// <summary>
			/// Starts the Klein device to measure constantly.
			/// </summary>
			void startMeasuring() {
				_kclmtr->startMeasuring();
			}
			/// <summary>
			/// Stops the Klein device to stop measuring.
			/// </summary>
			void stopMeasuring() {
				_kclmtr->stopMeasuring();
			}
			/// <summary>
			/// Grabs and returns one measurement from the class buffer. Use startMeasering().
			/// </summary>
			/// <param name="m"> the measurement that was in the buffer</param>
			/// <return> to see if the measurement was already grabbed, and it's old data. </return>
			bool getMeasreument([Out] wMeasurement^ %m) {
				Measurement _m;
				bool returnFresh = _kclmtr->getMeasurement(_m);
				m = gcnew wMeasurement(_m);
				return returnFresh;

			}
			/// <summary>
			/// Returns one measurement from the device. Do not need to startMeasuring() to use this method.
			/// <param name="n"> Number of measurment needs average by. Good number is 8 measurement(one second), N less than 1 is auto averages </param>
			/// </summary>
			wMeasurement ^getNextMeasurement(int n) {
				return gcnew wMeasurement(_kclmtr->getNextMeasurement(n));
			}
			//Counts
			/// <summary>
			/// Returns true if the device is measuring mode. Returns false if it is not in measuring mode.
			/// </summary>
			property bool isMeasureCounts {
				bool get() {
					return _kclmtr->isMeasureCounts();
				}
			}
			/// <summary>
			/// Starts the Klein device to measuring counts constantly.
			/// </summary>
			void startMeasureCounts() {
				_kclmtr->startMeasureCounts();
			}
			/// <summary>
			/// Stops the Klein device to stop measuring counts.
			/// </summary>
			void stopMeasureCounts() {
				_kclmtr->stopMeasureCounts();
			}
			/// <summary>
			/// Grabs and returns one measurement of counts from the class buffer. Use startMeasereCounts().
			/// </summary>
			/// <param name="c"> the measurement that was in the buffer</param>
			/// <return> to see if the measurement was already grabbed, and it's old data. </return>
			bool getMeasureCounts([Out] wCounts^ %c) {
				Counts _c;
				bool returnFresh = _kclmtr->getMeasureCounts(_c);
				c = gcnew wCounts(_c);
				return returnFresh;
			}
			/// <summary>
			/// Returns one measurement of counts from the device. Do not need to startMeasuring() to use this method.
			/// </summary>
			wCounts ^getNextMeasureCount() {
				return gcnew wCounts(_kclmtr->getNextMeasureCount());
			}

			//Setting up to Store CalFiles
			/// <summary>
			/// This will create a coefficient matrix from the reference device measurement and the KClmtr measurement. This will not store a calibration file into the Klein Device, but just return the values that would store it. This is good to used with setTempCaliFile()
			/// </summary>
			/// <param name="Reference"> Reference The reference device's measurement </param>
			/// <param name="Kclmtr">  Kclmtr The KClmtr's measurement </param>
			/// <return> The meatrix that would be stored to the KClmtr, but does not </return>
			wCorrectedCoefficient^ getCoefficientTestMatrix(wWRGB^ Reference, wWRGB^ Kclmtr) {
				return gcnew wCorrectedCoefficient(_kclmtr->getCoefficientTestMatrix(Reference->getNative(), Kclmtr->getNative()));
			}
			/// <summary>
			/// Deletes a Calibration file with it's ID.
			/// </summary>
			int deleteCalFile(int CalFileID) {
				return _kclmtr->deleteCalFile(CalFileID);
			}

			//Storing CalFile
			/// <summary>
			/// This will store a Calibration file into the device, based on the reference device's measurement and the KClmtr's measurement
			/// </summary>
			/// <param name="ID"> The location which the Calibration file will be stored </param>
			/// <param name="Name"> The name of the Calibration file </param>
			/// <param name="Reference"> Reference The reference device's measurement </param>
			/// <param name="Kclmtr">  Kclmtr The KClmtr's measurement </param>
			/// <return>int Error code. 0 is Good</return>
			int storeMatrices(int ID, String^ Name, wWRGB^ Reference, wWRGB^ Kclmtr) {
				return _kclmtr->storeMatrices(ID, MarshalString(Name), Reference->getNative(), Kclmtr->getNative());
			}

			/// <summary>
			/// This will store a Calibration file into the device
			/// </summary>
			/// <param name="ID"> The location which the Calibration file will be stored </param>
			/// <param name="Name"> The name of the Calibration file </param>
			/// <param name="correctionMatrix"> correctionMatrix The XYZ 3x3 matrix and The RGB 3x3 matrix, this is obsolete if using chromaSurf or this SDK. Now using GamaSpect </param>
			/// <return>int Error code. 0 is Good</return>
			int storeMatrices(int ID, String^ Name, wCorrectedCoefficient ^correctionMatrix) {
				return _kclmtr->storeMatrices(ID, MarshalString(Name), correctionMatrix->getNative());
			}
			/// <summary>
			/// This will store a Calibration file into the device
			/// </summary>
			/// <param name="ID"> The location which the Calibration file will be stored </param>
			/// <param name="Name"> The name of the Calibration file </param>
			/// <param name="correctedXYZ"> The XYZ 3x3 matrix </param>
			/// <return> int Error code. 0 is Good</return>
			int storeMatrices(int ID, String^ Name, wMatrix<double> ^correctedXYZ) {
				return _kclmtr->storeMatrices(ID, MarshalString(Name), correctedXYZ->getNative());
			}

			//BlackCal - Cold
			/// <summary>
			/// Takes reading of counts, if passes saves to flash/ram
			/// </summary>
			wBlackMatrix^ captureBlackLevel() {
				return gcnew wBlackMatrix(_kclmtr->captureBlackLevel());
			}
			/// <summary>
			/// Reads matrix of saved counts from flash
			/// </summary>
			wBlackMatrix^ getFlashMatrix() {
				return gcnew wBlackMatrix(_kclmtr->getFlashMatrix());
			}

			//BlackCal - Hot
			/// <summary>
			///  Reads matrix of saved counts from RAM
			/// </summary>
			wBlackMatrix^ getRAMMatrix() {
				return gcnew wBlackMatrix(_kclmtr->getRAMMatrix());
			}
			/// <summary>
			/// Reads matrix of black thermal correction coefficents
			/// </summary>
			wBlackMatrix^ getCoefficientMatrix() {
				return gcnew wBlackMatrix(_kclmtr->getCoefficientMatrix());
			}

			//FFT
			/// <summary>
			/// Returns true if the device is in flicker mode. Returns false if the device is not in flicker mode
			/// </summary>
			/// <return> Error string, OK is good </return> 
			int startFlicker() {
				return _kclmtr->startFlicker();
			}
			/// <summary>
			/// Grabs and returns one flicker measurement from the class buffer. Use startFlicker().
			/// </summary>
			/// <param name="f"> the flicker measurement that was in the buffer</param>
			/// <return> to see if the flicker measurement was already grabbed, and it's old data.</return>
			bool getFlicker([Out] wFlicker^ %f) {
				Flicker _f;
				bool returnFresh = _kclmtr->getFlicker(_f);
				f = gcnew wFlicker(_f);
				return returnFresh;
			}
			/// <summary>
			/// Grabs and returns one flicker measurement. Do not use startFlicker(). The speed which this returns is based on the getFFT_Samples()
			/// </summary>
			wFlicker^ getNextFlicker() {
				return gcnew wFlicker(_kclmtr->getNextFlicker());
			}
			/// <summary>
			/// Stops the device from being in flicker mode. This also needs to be if you set the grabConstanly param in startFlicker()
			/// </summary>
			void stopFlicker() {
				_kclmtr->stopFlicker();
			}

			//setup/Close
			/// <summary>
			/// This will open the device
			/// </summary>
			/// <param name="thePort">sets the port name</param>
			/// <return>A user should always have this true. This is used for internal use.</return>
			bool connect(int thePort) {
				port = thePort;
				return _kclmtr->connect();
			}
			/// <summary>
			/// This will open the device to the PortName you have set.
			/// </summary>
			bool connect() {
				return _kclmtr->connect();
			}
			/// <summary>
			/// Closes the port and reset all the propeties of the KClmtr object
			/// </summary>
			void closePort() {
				_kclmtr->closePort();
			}
			/** @endcond */
			/** @brief Sends out measurement
			*  @details You must add the event to the object, and then make sure the thread can touch your threadf
			*  @details Here is an example:
			*  @snippet KClmtrWrapperExample.cpp measure
			*/
			event EventHandler<MeasureEventArgs ^>^ measureEvent;
			/** @brief Sends out flicker
			*  @details You must add the event to the object, and then make sure the thread can touch your thread
			*  @details Here is an example:
			*  @snippet KClmtrWrapperExample.cpp flicker
			*/
			event EventHandler<FlickerEventArgs ^>^ flickerEvent;
			/** @brief Sends out Counts
			*  @details You must add the event to the object, and then make sure the thread can touch your thread
			*  @details Here is an example:
			*  @snippet KClmtrWrapperExample.cpp flicker
			*/
			event EventHandler<CountsEventArgs ^>^ CountsEvent;
			/// <summary>
			/// Test a Port to see if a port is a Klein Device, also returns model and serial number
			/// </summary>
			/// <param name="portNumber"> The portNumber to check</param>
			/// <param name="returnModel"> The Model number of the Device, if it's a Klein Device</param>
			/// <param name="returnSN"> The SerialNumber number of the Device, if it's a Klein Device</param>
			/// <return>Boolean to tell it connected or not</return>
			static bool testConnection(int portNumber, [Out] System::String^% returnModel, [Out] System::String^% returnSN) {
				String^ port = "\\\\.\\COM" + portNumber;
				string nativePort = MarshalString(port);
				
				string model, sn;
				bool test = KClmtr::testConnection(nativePort, model, sn);
				
				returnModel = NativeToDotNet(model);
				returnSN = NativeToDotNet(sn);				
				
				return test;
			}
		protected:
			!KClmtrWrap() {
				delete _kclmtr;
			}			
		private:
			static string MarshalString(String^ s);
			static System::String^ NativeToDotNet(std::string input);
			KClmtr *_kclmtr;

			void printMeasure(Measurement m) {
				wMeasurement^ manMeasurement = gcnew wMeasurement(m);
				measureEvent(this, gcnew MeasureEventArgs(manMeasurement));
			}
			void printFlicker(Flicker f) {
				wFlicker^ manFlicker = gcnew wFlicker(f);
				flickerEvent(this, gcnew FlickerEventArgs(manFlicker));
			}
			void printCounts(Counts c) {
				wCounts^ manCounts = gcnew wCounts(c);
				CountsEvent(this, gcnew CountsEventArgs(manCounts));
			}
		};
	}
}