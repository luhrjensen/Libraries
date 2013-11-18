// KClmtrWrapper.h
#include "../../kclmtr/KClmtr.h"
#include <vcclr.h>
#pragma once

using namespace System;

namespace KClmtrWrapper {

	ref class KClmtrWrap;

	public enum class wMeasureErrorCodes {
		NONE                    = 0x00000000,
		//Serial Port
		NOT_OPEN                = 0x00000001,
		TIMED_OUT               = 0x00000002,
		LOST_CONNECTION         = 0x00000004,

		//Measurement
		BAD_VALUES              = 0x00000008,
		CONVERTED_NM            = 0x00000010,
		KELVINS                 = 0x00000020,
		AIMING_LIGHTS           = 0x00000040,
		AVERAGING_LOW_LIGHT     = 0x00000080,

		//Ranges
		BOTTOM_UNDER_RANGE      = 0x00000100,
		TOP_OVER_RANGE          = 0x00000200,
		OVER_HIGH_RANGE         = 0x00000400,

		//Black Cals
		BLACK_ZERO              = 0x00000800,
		BLACK_OVERDRIVE         = 0x00001000,
		BLACK_EXCESSIVE         = 0x00002000,
		BLACK_PARSING_ROM       = 0x00004000,
		BLACK_STORING_ROM       = 0x00008000,

		//CalFiles
		CAL_WHITE_RGB           = 0x00010000,
		CAL_STORING             = 0x00020000,
		CAL_CONVERT_BINARY      = 0x00040000,

		//FFT
		FFT_BAD_STRING          = 0x00080000,
		FFT_RANGE_CAL           = 0x00100000,
		FFT_NO_XYZ              = 0x00200000,
		FFT_NO_RANGE            = 0x00400000,
		FFT_INSUFFICIENT_DATA   = 0x00800000,
		FFT_PREVIOUS_RANGE      = 0x01000000,
		FFT_NOT_SUPPORTED       = 0x02000000,
		FFT_BAD_SAMPLES         = 0x04000000,

		//Miscellaneous
		wFIRMWARE               = 0x08000000
	};


	/** @cond */
	class SubClass : public KClmtr {

	public:
		SubClass(gcroot<KClmtrWrap^> _kcw);
		void printMeasure(Measurement m);
		void printFlicker(Flicker f);
		gcroot<KClmtrWrap^>  _kclmtrwrapper;
	};
	/** @endcond */
	public ref struct wMatrix {
		int row;
		int column;
		array<double, 2>^ v;

		wMatrix() {
			row = 0;
			column = 0;
		}
		~wMatrix() {
			deleteV();
		}
		void  initializeV(int _row, int _column) {
			deleteV();
			row = _row;
			column = _column;
			v = gcnew array<double, 2>(row,column);

			clear();
		}
		void clear() {
			for(int i = 0; i < row; ++i) {
				for(int j = 0; j < column; ++j) {
					v[i,j] = 0;
				}
			}
		}

		static wMatrix^ fromNative(const matrix &other) {
			wMatrix^ m = gcnew wMatrix();
			m->initializeV(other.row, other.column);

			for(int i = 0; i < m->row; ++i) {
				for(int j = 0; j < m->column; ++j) {
					m->v[i,j] = other.v[i][j];
				}
			}
			
			return m;
		}

	private:
		void deleteV() {
			delete v;

			column = 0;
			row = 0;
		}
	};
	public ref struct wGamutSpec {
		enum class wGamutCode {
			NTSC,
			EBU,
			REC709,
			SMPTE,
			DCIP3,
			USER_DEFINE,
			defaultGamut = REC709
		};
		~wGamutSpec() {
			delete gs;
		}
		wGamutSpec() {
			gs = new gamutSpec();
		}
		wGamutSpec(gamutSpec _gs) {
			gs = new gamutSpec(_gs);
		}
		wGamutSpec(double redX, double redY,
				   double greenX, double greenY,
				   double blueX, double blueY,
				   double whiteX, double whiteY, double whiteBigY) {
					  gs = new gamutSpec(redX, redY,
										greenX, greenY,
										blueX, blueY,
										whiteX, whiteY, whiteBigY);
		}

		static wGamutSpec^ fromCode(wGamutCode code){
			return fromCode(code, 100);
		}
		static wGamutSpec^ fromCode(wGamutCode code, double whiteBigY){
			wGamutSpec^ wgs = gcnew wGamutSpec();
			gamutSpec g = gamutSpec::fromCode(static_cast<gamutSpec::gamutCode>(code), whiteBigY);
			wgs->gs = new gamutSpec(g);
			return wgs;
		}

		wGamutSpec::wGamutCode getCodeSpec() {
			return static_cast<wGamutSpec::wGamutCode>(gs->getCodeSpec());
		}

		void setRed(double x, double y) {
			gs->setRed(x, y);
		}
		void setGreen(double x, double y) {
			gs->setGreen(x, y);
		}
		void setBlue(double x, double y) {
			gs->setBlue(x, y);
		}
		void setWhite(double x, double y, double bigY) {
			gs->setWhite(x, y, bigY);
		}

		void getWhite(double &x, double &y, double &bigY) {
			gs->getWhite(x, y, bigY);
		}
		void getRed(double &x, double &y, double &bigY) {
			gs->getRed(x, y, bigY);
		}
		void getGreen(double &x, double &y, double &bigY) {
			gs->getGreen(x, y, bigY);
		}
		void getBlue(double &x, double &y, double &bigY) {
			gs->getBlue(x, y, bigY);
		}

		wMatrix^ getRGBtoXYZ() {
			return wMatrix::fromNative(gs->getRGBtoXYZ());
		}
		wMatrix^ getXYZtoRGB()  {
			return wMatrix::fromNative(gs->getXYZtoRGB());
		}

		gamutSpec getNative() {
			return *gs;
		}
	private:
		gamutSpec *gs;
	};
	public ref struct wMeasurement {
		enum class MeasurmentRange {
			range1 = 1,
			range2 = range1 + 1,
			range3 = range2 + 1,
			range4 = range3 + 1,
			range5 = range4 + 1,
			range6 = range5 + 1,

			range1B = range1,
			range1T = range2,
			range2B = range3,
			range2T = range4,
			range3B = range5,
			range3T = range6,
		};

		double x;
		double y;
		double bigx;
		double bigy;
		double bigz;
		double bigxraw;
		double bigyraw;
		double bigzraw;
		double red;
		double green;
		double blue;
		double u;
		double v;
		double nm;
		double nmduv;
		double L;
		double a;
		double b;
		double C;
		double h;
		double hue;
		double saturation;
		double value;
		MeasurmentRange redrange;
		MeasurmentRange greenrange;
		MeasurmentRange bluerange;
		double temp;
		double tempduv;
		int errorcode;
		int averagingby;

		wMeasurement(){
			convertNativeToManage(Measurement());
		}

		wMeasurement(Measurement measurement) {
			convertNativeToManage(measurement);
		}

		static wMeasurement^ fromXYZ(double X, double Y, double Z){
			return fromXYZ(X, Y, Z, wGamutSpec::fromCode(wGamutSpec::wGamutCode::defaultGamut));
		}
		static wMeasurement^ fromxyY(double x, double y, double Y){
			return fromxyY(x, y, Y, wGamutSpec::fromCode(wGamutSpec::wGamutCode::defaultGamut));
		}
		static wMeasurement^ fromuvprimeY(double u, double v, double Y){
			return fromuvprimeY(u, v, Y, wGamutSpec::fromCode(wGamutSpec::wGamutCode::defaultGamut));
		}
		static wMeasurement^ fromTempduvY(double _temp, double _tempduv, double Y){
			return fromTempduvY(_temp, _tempduv, Y, wGamutSpec::fromCode(wGamutSpec::wGamutCode::defaultGamut));
		}
		static wMeasurement^ fromnmduvY(double _nm, double _nmduv, double Y){
			return fromnmduvY(_nm, _nmduv, Y, wGamutSpec::fromCode(wGamutSpec::wGamutCode::defaultGamut));
		}
		static wMeasurement^ fromRGB(double red, double green, double blue){
			return fromRGB(red, green, blue, wGamutSpec::fromCode(wGamutSpec::wGamutCode::defaultGamut));
		}

		static wMeasurement^ fromXYZ(double X, double Y, double Z, wGamutSpec^ gs){
			return gcnew wMeasurement(Measurement::fromXYZ(X, Y, Z, gs->getNative()));
		}
		static wMeasurement^ fromxyY(double x, double y, double Y, wGamutSpec^ gs){
			return gcnew wMeasurement(Measurement::fromxyY(x, y, Y, gs->getNative()));
		}
		static wMeasurement^ fromuvprimeY(double u, double v, double Y, wGamutSpec^ gs){
			return gcnew wMeasurement(Measurement::fromuvprimeY(u, v, Y, gs->getNative()));
		}
		static wMeasurement^ fromTempduvY(double _temp, double _tempduv, double Y, wGamutSpec^ gs){
			return gcnew wMeasurement(Measurement::fromTempduvY(_temp, _tempduv, Y, gs->getNative()));
		}
		static wMeasurement^ fromnmduvY(double _nm, double _nmduv, double Y, wGamutSpec^ gs){
			return gcnew wMeasurement(Measurement::fromnmduvY(_nm, _nmduv, Y, gs->getNative()));
		}
		static wMeasurement^ fromRGB(double r, double g, double b, wGamutSpec^ gs){
			return gcnew wMeasurement(Measurement::fromRGB(r, g, b, gs->getNative()));
		}
		static wMeasurement^ fromHSV(double hue, double saturation, double value, wGamutSpec^ gs) {
			return gcnew wMeasurement(Measurement::fromHSV(hue, saturation, value, gs->getNative()));
		}
		
		double deltaE1976(wMeasurement^ spec) {
			return getNative().deltaE1976(spec->getNative());
		}
		double deltaE1994(wMeasurement^ spec) {
			return getNative().deltaE1994(spec->getNative());
		}
		double deltaE2000(wMeasurement^ spec) {
			return getNative().deltaE2000(spec->getNative());
		}

		void setGamutSpec(wGamutSpec^ gs) {
			Measurement m = Measurement::fromXYZ(bigx, bigy, bigz, gs->getNative());
			convertNativeToManage(m);
		}
		wGamutSpec^ getGamutSpec() {
			return gs;
		}

		static double toNits(double FootLamberts) {
			return Measurement::toNits(FootLamberts);
		}
		static double toFootLamberts(double nits) {
			return Measurement::toFootLamberts(nits);
		}
		
		Measurement getNative() {
			Measurement m;
			m.x = x;
			m.y = y;
			m.bigx = bigx;
			m.bigy = bigy;
			m.bigz = bigz;
			m.bigxraw = bigxraw;
			m.bigyraw = bigyraw;
			m.bigzraw = bigzraw;
			m.red = red;
			m.green = green;
			m.blue = blue;
			m.u = u;
			m.v = v;
			m.nm = nm;
			m.nmduv = nmduv;
			m.L = L;
			m.a = a;
			m.b = b;
			m.C = C;
			m.h = h;
			m.hue = hue;
			m.saturation = saturation;
			m.value = value;
			m.redrange = static_cast<Measurement::MeasurmentRange>(redrange);
			m.greenrange = static_cast<Measurement::MeasurmentRange>(greenrange);
			m.bluerange = static_cast<Measurement::MeasurmentRange>(bluerange);
			m.temp = temp;
			m.tempduv = tempduv;
			m.errorcode = errorcode;
			m.averagingby = averagingby;
			m.setGamutSpec(gs->getNative());
			return m;
		}
	protected:
		void convertNativeToManage(Measurement measurement) {
			x = measurement.x;
			y = measurement.y;
			bigx = measurement.bigx;
			bigy = measurement.bigy;
			bigz = measurement.bigz;
			bigxraw = measurement.bigxraw;
			bigyraw = measurement.bigyraw;
			bigzraw = measurement.bigzraw;
			red = measurement.red;
			green = measurement.green;
			blue = measurement.blue;
			u = measurement.u;
			v = measurement.v;
			nm = measurement.nm;
			nmduv = measurement.nmduv;
			L = measurement.L;
			a = measurement.a;
			b = measurement.b;
			C = measurement.C;
			h = measurement.h;
			hue = measurement.hue;
			saturation = measurement.saturation;
			value = measurement.value;
			redrange = (MeasurmentRange)measurement.redrange;
			greenrange = (MeasurmentRange)measurement.greenrange;
			bluerange = (MeasurmentRange)measurement.bluerange;
			temp = measurement.temp;
			tempduv = measurement.tempduv;
			errorcode = measurement.errorcode;
			averagingby = measurement.averagingby;
			
			gs = gcnew wGamutSpec(measurement.getGamutSpec());
		}
		wGamutSpec^ gs;
		
	};

	public ref struct wAvgMeasurement : public wMeasurement{
		double minX;
		double minY;
		double minZ;
		double maxX;
		double maxY;
		double maxZ;

		wAvgMeasurement() {
			wMeasurement();

			minX = bigx;
			maxX = bigx;
			minY = bigy;
			maxY = bigy;
			minZ = bigz;
			maxZ = bigz;
		};
		wAvgMeasurement(wMeasurement m) {
		    x = m.x;
			y = m.y;
			bigx = m.bigx;
			bigy = m.bigy;
			bigz = m.bigz;
			bigxraw = m.bigxraw;
			bigyraw = m.bigyraw;
			bigzraw = m.bigzraw;
			red = m.red;
			green = m.green;
			blue = m.blue;
			u = m.u;
			v = m.v;
			nm = m.nm;
			nmduv = m.nmduv;
			L = m.L;
			a = m.a;
			b = m.b;
			C = m.C;
			h = m.h;
			hue = m.hue;
			saturation = m.saturation;
			value = m.saturation;
			redrange = m.redrange;
			greenrange = m.greenrange;
			bluerange = m.bluerange;
			temp = m.temp;
			tempduv = m.tempduv;
			errorcode = m.errorcode;
			averagingby = m.averagingby;
		
			gs = m.getGamutSpec();

			minX = bigx;
			maxX = bigx;
			minY = bigy;
			maxY = bigy;
			minZ = bigz;
			maxZ = bigz;
		};

		wAvgMeasurement(AvgMeasurement m) {
			convertNativeToManage(m);
		};

	protected:
		void convertNativeToManage(AvgMeasurement m) {
			minX = m.minX;
			maxX = m.maxX;
			minY = m.minY;
			maxY = m.maxY;
			minZ = m.minZ;
			maxZ = m.maxZ;
			
			wMeasurement::convertNativeToManage(m);
		}
	};
	public ref struct wwrgb {
		//white, red, green, blue
		//x, y, z
		//The z from when the screen was blue
		array<double, 2>^ v;

		wwrgb(){
			v = gcnew array<double, 2>(4, 3);
		}
		wwrgb(wrgb WRGB){
			v = gcnew array<double, 2>(4, 3);
			for(int i=0; i<4; ++i){
				for(int j=0; j<3; ++j){
					v[i, j] = WRGB.v[i][j];
				}
			}
		}
		wrgb getNative(){
			wrgb WRGB;
			for(int i=0; i<4; ++i){
				for(int j=0; j<3; ++j){
					WRGB.v[i][j] = v[i, j];
				}
			}
			return WRGB;
		}
	};

	public ref struct wBlackMatrix {
		array<array<double>^>^ range;
		double therm;
		int errorcode;            //The error code whenever you are getting data


		wBlackMatrix() {
			convertNativeToManage(BlackMatrix());
		}

		wBlackMatrix(BlackMatrix black){
			convertNativeToManage(black);
		}

	private:
		void convertNativeToManage(BlackMatrix black){
			for(int i = 0; i < 6; ++i){
				range[i][0] = black.range[i][0];
				range[i][1] = black.range[i][1];
				range[i][2] = black.range[i][2];
			}
			therm = black.therm;
			errorcode = black.errorcode;
		}
	};

	public ref struct wCorrectedCoefficient {
		static array<double, 2>^ colorMatrix = gcnew array<double, 2>(3, 3);
		static array<double, 2>^ rgbMatrix = gcnew array<double, 2>(3, 3);
		wCorrectedCoefficient(){}
		wCorrectedCoefficient(CorrectedCoefficient corrected){
			for(int i = 0; i < 3; i++){
				for(int x = 0; x < 3; x++){
					colorMatrix[i, x] = corrected.colorMatrix[i][x];
					rgbMatrix[i, x] = corrected.rgbMatrix[i][x];
				}
			}
		}
		CorrectedCoefficient getNCorrectedCoefficient(){
			CorrectedCoefficient corrected;
			for(int i = 0; i < 3; i++){
				for(int x = 0; x < 3; x++){
					corrected.colorMatrix[i][x] = colorMatrix[i, x];
					corrected.rgbMatrix[i][x] = rgbMatrix[i, x];
				}
			}
			return corrected;
		}
	};

	public ref struct wFlicker {
		wMeasurement ^xyz;					//The measurement from XYZ
		wMatrix ^peakfrequency;		//The top 3 frequency of DB
		wMatrix ^flickerDB;			//The DB from 1hz to 100hz
		wMatrix ^flickerPercent;		//The Percent from 1hz to 100hz
		int errorcode;						//The error code whenever you are getting data

		wFlicker(){}
		wFlicker(Flicker flicker){
			xyz = gcnew wMeasurement(flicker.xyz);
			peakfrequency = wMatrix::fromNative(flicker.peakfrequency);
			flickerDB = wMatrix::fromNative(flicker.flickerDB);	
			flickerPercent = wMatrix::fromNative(flicker.flickerPercent);
			errorcode = flicker.errorcode;
		}
	};

	/** @ingroup wrappers
	* 	@brief Wraps the Native object to work easly in .Net Framework
	*/
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
		/** @cond */
		/// <summary>
		/// Gets or sets the com port's number
		/// </summary>
		/// <value> Com port's number </value>
		property int port{
			int get(){
				string foobar = _kclmtr->getPort();
				return Convert::ToInt16(NativeToDotNet(foobar.substr(3, 1)));
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
		property String^ SerialNumber{
			String^ get(){
				return NativeToDotNet(_kclmtr->getSerialNumber());
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
		property wMatrix^ CalMatrix {
			wMatrix^ get(){
				return wMatrix::fromNative(_kclmtr->getCalMatrix());
			}
		}
		/// <summary>
		/// Gets the current Cal File's color matrix
		/// </summary>
		property wMatrix^ RGBMatrix {
			wMatrix^ get(){
				return wMatrix::fromNative(_kclmtr->getRGBMatrix());
			}
		}
		/// <summary>
		/// Gets or set the current GamutSpec that KClmtr is using to make Measurement
		/// </summary>
		property wGamutSpec^ GamutSpec {
			wGamutSpec^ get(){
				return gcnew wGamutSpec(_kclmtr->getGamutSpec());
			}
			void set(wGamutSpec^ value){
				_kclmtr->setGamutSpec(value->getNative());
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
		void setTempCalFile(wCorrectedCoefficient^ Matrix){
			_kclmtr->setTempCalFile(Matrix->getNCorrectedCoefficient());
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
				return _kclmtr->getFFT_RollOff();
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
		/// <param name="n"> Number of measurment needs average by. Good number is 8 measurement(one second)</param>
		/// </summary>
		wAvgMeasurement ^getNextMeasurement(int n){
			return gcnew wAvgMeasurement(_kclmtr->getNextMeasurement(n));
		}

		//Setting up to Store CalFiles
		/// <summary>
		/// This will create a coefficient matrix from the reference device measurement and the KClmtr measurement. This will not store a calibration file into the Klein Device, but just return the values that would store it. This is good to used with setTempCaliFile()
		/// </summary>
		/// <param name="Reference"> Reference The reference device's measurement </param>
		/// <param name="Kclmtr">  Kclmtr The KClmtr's measurement </param>
		/// <return> The meatrix that would be stored to the KClmtr, but does not </return>
		wCorrectedCoefficient^ getCoefficientTestMatrix(wwrgb^ Reference, wwrgb^ Kclmtr){
			return gcnew wCorrectedCoefficient(_kclmtr->getCoefficientTestMatrix(Reference->getNative(), Kclmtr->getNative()));
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
		int storeMatrices(int ID, String^ Name, wwrgb^ Reference, wwrgb^ Kclmtr){
			return _kclmtr->storeMatrices(ID, MarshalString(Name), Reference->getNative(), Kclmtr->getNative());
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
		wBlackMatrix^ getFlashMatrix(){
			return gcnew wBlackMatrix(_kclmtr->getFlashMatrix());
		}

		//BlackCal - Hot
		/// <summary>
		///  Reads matrix of saved counts from RAM
		/// </summary>
		wBlackMatrix^ getRAMMatrix(){
			return gcnew wBlackMatrix(_kclmtr->getRAMMatrix());
		}
		/// <summary>
		/// Reads matrix of black thermal correction coefficents
		/// </summary>
		wBlackMatrix^ getCoefficientMatrix(){
			return gcnew wBlackMatrix(_kclmtr->getCoefficientMatrix());
		}

		//FFT
		/// <summary>
		/// Returns true if the device is in flicker mode. Returns false if the device is not in flicker mode
		/// </summary>
		/// <param name="grabConstantly"> If you are planning to use getNextFlicker() set this to be false. If you want it to return flicker has soon has it grabs one, set it to be true </param>
		/// <return> Error string, OK is good </return> 
		int StartFlicker(bool grabConstantly){
			return _kclmtr->startFlicker(grabConstantly);
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
		void closePort(){
			_kclmtr->closePort();
		}

		delegate System::Void MeasureEventHandler(wMeasurement^);
		delegate System::Void FlickerEventHandler(wFlicker^);
		/** @endcond */
		/** @brief Sends out measurement
		*  @details You must add the event to the object, and then make sure the thread can touch your threadf
		*  @details Here is an example: 
		*  @details Header
		*  @snippet KClmtrWrapperExample.cpp measure
		*   Source
		*  @snippet KClmtrWrapperExample.cpp measure
		*/
		event MeasureEventHandler^ measureEvent;
		/** @brief Sends out flicker
		*  @details You must add the event to the object, and then make sure the thread can touch your thread
		*  @details Here is an example: 
		*  @details Header
		*  @snippet KClmtrWrapperExample.cpp flicker
		*   Source
		*  @snippet KClmtrWrapperExample.cpp flicker
		*/
		event FlickerEventHandler^ flickerEvent;
		void printMeasure(wMeasurement^ m){
			while(backgroundWorkerMeasure->IsBusy);
			backgroundWorkerMeasure->RunWorkerAsync(m);
		}
		void printFlicker(wFlicker^ f){
			flickerEvent(f);
		}

	private:
		System::Void backgroundWorkerMeasure_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			measureEvent((KClmtrWrapper::wMeasurement^) e->Argument);
		}
		System::Void backgroundWorkerFlicker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
			flickerEvent((KClmtrWrapper::wFlicker^) e->Argument);
		}

		System::ComponentModel::BackgroundWorker^ backgroundWorkerMeasure;
		System::ComponentModel::BackgroundWorker^ backgroundWorkerFlicker;
		string MarshalString(String^ s);
		System::String^ NativeToDotNet(std::string input);
		KClmtr *_kclmtr;
	};
}