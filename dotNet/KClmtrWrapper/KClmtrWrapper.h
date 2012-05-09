// KClmtrWrapper.h
#include "../../kclmtr/KClmtr.h"
#include <vcclr.h>
#pragma once

using namespace System;


namespace KClmtrWrapper {
	ref class KClmtrWrap;

	class SubClass : public KClmtr
	{
	public:
		SubClass(gcroot<KClmtrWrap^> _kcw);
		//~foobar();
		void printMeasure(Measurement m);
		void printFlick(Flicker f);
		gcroot<KClmtrWrap^>  _kclmtrwrapper;
	};

	public ref struct wMeasurement
	{
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

		wMeasurement(){};
		wMeasurement(Measurement measurement)
		{
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
		};
	};
	public ref struct wwrgb
	{
		//white, red, green, blue
		//x, y, z
		array<double,2>^ v;         //The z from when the screen was blue

		wwrgb() 
		{
			v = gcnew array<double, 2>(4, 3);
		};
		wwrgb(wrgb WRGB)
		{
			v = gcnew array<double, 2>(4, 3);
			for(int i=0; i<4; ++i)
				for(int j=0; j<3; ++j)
					v[i,j] = WRGB.v[i][j];
		};
		wrgb getNwrgb()
		{
			wrgb WRGB;
	        
			for(int i=0; i<4; ++i)
				for(int j=0; j<3; ++j)
					WRGB.v[i][j] = v[i,j];

			return WRGB;
		};
	};
	public ref struct wBlackMatrix
	{
		array<double>^ range1;// = gcnew array<double>(3);         //The Matrix at range one (R,G,B)
		array<double>^ range2;// = gcnew array<double>(3);         //The Matrix at range two (R,G,B)
		array<double>^ range3;// = gcnew array<double>(3);         //The Matrix at range three (R,G,B)
		array<double>^ range4;// = gcnew array<double>(3);         //The Matrix at range four (R,G,B)
		array<double>^ range5;// = gcnew array<double>(3);         //The Matrix at range five (R,G,B)
		array<double>^ range6;// = gcnew array<double>(3);         //The Matrix at range six (R,G,B)
		double Therm;
		int errorcode;            //The error code whenever you are getting data
		String^ errorstring;      //The string

		wBlackMatrix(){};
		wBlackMatrix(BlackMatrix black)
		{
			for(int i = 0; i < 3; i++)
			{
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
	public ref struct wCorrectedCoefficient
	{
		static array<double,2>^ colorMatrix = gcnew array<double,2>(3,3);
		static array<double,2>^ rgbMatrix = gcnew array<double,2>(3,3);
		wCorrectedCoefficient(){};
		wCorrectedCoefficient(CorrectedCoefficient corrected)
		{
			for(int i = 0; i < 3; i++)
			{
				for(int x = 0; x < 3; x++)
				{
					colorMatrix[i,x] = corrected.colorMatrix[i][x];
					rgbMatrix[i,x] = corrected.rgbMatrix[i][x];
				}
			}
		};

		CorrectedCoefficient getNCorrectedCoefficient()
		{
			CorrectedCoefficient corrected;
			for(int i = 0; i < 3; i++)
			{
				for(int x = 0; x < 3; x++)
				{
					corrected.colorMatrix[i][x] = colorMatrix[i,x];
					corrected.rgbMatrix[i][x] = rgbMatrix[i,x];
				}
			}
			return corrected;
		};
	};
	public ref struct wFlicker
	{
		wMeasurement ^xyz;					//The measurement from XYZ
		array<double,2> ^peakfrequency; //= gcnew array<double, 2>(3, 2);        //The top 3 frequency of DB
		array<double> ^flickerDB;// = gcnew array<double>(101);					//The DB from 1hz to 100hz
		array<double> ^flickerPercent;// = gcnew array<double>(101);			//The Percent from 1hz to 100hz
		int errorcode;						//The error code whenever you are getting data
		String^ errorstring;				//The string
		bool readyflag;					    //Ready or not to grab it

		wFlicker(){};
		wFlicker(Flicker flicker)
		{
			xyz = gcnew wMeasurement(flicker.xyz);
			peakfrequency = gcnew array<double, 2>(3, 3);
			flickerDB = gcnew array<double>(101);	
			flickerPercent = gcnew array<double>(101);
			for(int i = 0; i < 3; i++)
			{
				for(int x = 0; x < 3; x++)
				{
					peakfrequency[i,x] = flicker.peakfrequency[i][x];
				}
			}
			for(int i = 0; i < 101; i++)
			{
				flickerDB[i] =  flicker.flickerDB[i];
				flickerPercent[i] = flicker.flickerPercent[i];
			}
			errorcode = flicker.errorcode;
			errorstring = gcnew String(flicker.errorstring.c_str());
			readyflag = flicker.readyflag;
		};
	};
	public ref struct wwhitespect
	{
		double x;                //The X to the Whitespect modifier
		double y;                //The y to the Whitespect modifier
		double z;                //The z to the Whitespect modifier
		double xy;               //The allowed variance of xy
		double l;                //The allowed variance of Y
		wwhitespect(){};
		wwhitespect(whitespect White)
		{
			x = White.x;
			y = White.y;
			z = White.z;
			xy = White.xy;
			l = White.l;
		};
		whitespect getNwhitespect()
		{
			whitespect White;

			White.x = x;
			White.y = y;
			White.z = z;
			White.xy = xy;
			White.l = l;

			return White;
		};
	};
	
	public ref class K10VWrap
	{
	public:
		ref struct wColors
		{
			int red;
			int green;
			int blue;

			wColors(){};
			wColors(Colors color)
			{
				red = color.red;
				green = color.green;
				blue = color.blue;
			};
			Colors getNColor()
			{
				Colors color;

				color.red = red;
				color.green = green;
				color.blue = blue;

				return color;
			};
		};

		K10VWrap() { _k10v = new K10V; };
		virtual ~K10VWrap(void) { delete _k10v; };
		K10VWrap(K10V k10v)
		{
			_k10v = new K10V(k10v);
		};


		property wColors^ ColorField
		{
			wColors^ get()
			{
				return gcnew wColors(_k10v->getColorField());
			};
			void set(wColors^ value)
			{
				_k10v->setColorField(value->getNColor());
			};
		};

		K10V getNK10V()
		{
			return *_k10v;
		};
	private:
		K10V *_k10v;
	};
	public ref class KClmtrWrap
	{
	public:
		KClmtrWrap() { _kclmtr = new SubClass(this); };
		virtual ~KClmtrWrap(void) { delete _kclmtr; };
		//Property
		property int port
		{
			int get()
			{
				string foobar = _kclmtr->getPort();
				return Convert::ToInt16(NativeToDotNet(foobar.substr(3,1)));
			}
			void set(int value)
			{
				String^ port = "\\\\.\\COM" + value;
				string foobar = MarshalString(port);
				_kclmtr->setPort(foobar);
			}
		};

		property String^ SN
		{
			String^ get()
			{
				return NativeToDotNet(_kclmtr->getSN());
			};
		};
		property String^ Model
		{
			String^ get()
			{
				return NativeToDotNet(_kclmtr->getModel());
			};
		};
		property bool AimingLights
		{
			void set(bool value)
			{
				_kclmtr->setAimingLights(value);
			};
		};

		property bool isPortOpen
		{
			bool get()
			{
				return _kclmtr->isPortOpen();
			};
		};
		//Property - CalFiles
		property String^ CalFileName
		{
			String^ get()
			{
				return NativeToDotNet(_kclmtr->getCalFileName());
			};
			void set(String^ value)
			{
				_kclmtr->setCalFileName(MarshalString(value));
			};
		};

		property int CalFileID
		{
			int get()
			{
				return _kclmtr->getCalFileID();
			};
			void set(int value)
			{
				_kclmtr->setCalFileID(value);
			}
		};
		property array<double,2>^ CalMatrix
		{
			array<double,2>^ get()
			{
				array<double,2>^ matrix = gcnew array<double,2>(3,3);
				for (int i = 0; i < 3; i++)
					for(int x = 0; x < 3; x++)
						matrix[i, x] = _kclmtr->getcalMatrix()[i][x];

				return matrix;
			};
		};
		property array<double,2>^ RGBMatrix
		{
			array<double,2>^ get()
			{
				array<double,2>^ matrix = gcnew array<double,2>(3,3);
				for (int i = 0; i < 3; i++)
					for(int x = 0; x < 3; x++)
						matrix[i, x] = _kclmtr->getRGBMatrix()[i][x];
				return matrix;
			};
		};
		property wwhitespect^ WhiteSpect
		{
			wwhitespect^ get()
			{
				return gcnew wwhitespect(_kclmtr->getWhiteSpect());
			};
			void set(wwhitespect^ value)
			{
				_kclmtr->setWhiteSpect(value->getNwhitespect());
				
			};
		};
		property String^ CalFileList
		{
			String^ get()
			{
				return NativeToDotNet(_kclmtr->getCalFileList());
			};
		};
		void setTempCalFile(wCorrectedCoefficient^ Matrix, wwhitespect^ whiteSpect)
		{
			_kclmtr->setTempCalFile(Matrix->getNCorrectedCoefficient(), whiteSpect->getNwhitespect());
		};
		//Property - FFT
		property bool FFT_Cosine
		{
			bool get()
			{
				return _kclmtr->getFFT_Cosine();
			};
			void set(bool value)
			{
				_kclmtr->setFFT_Cosine(value);
			};
		};
		property bool FFT_Smoothing
		{
			bool get()
			{
				return _kclmtr->getFFT_Smoothing();
			};
			void set(bool value)
			{
				_kclmtr->setFFT_Smoothing(value);
			};
		};
		property bool FFT_RollOff
		{
			bool get()
			{
				return _kclmtr->getFFT_RoolOff();
			};
			void set(bool value)
			{
				_kclmtr->setFFT_RollOff(value);
			};
		};
		property int FFT_samples
		{
			int get()
			{
				return _kclmtr->getFFT_Samples();
			};
			void set(int value)
			{
				_kclmtr->setFFT_Samples(value);
			};
		}
		property K10VWrap^ VirtualK10
		{
			K10VWrap^ get()
			{
				return gcnew K10VWrap(_kclmtr->getVirtualK10());
			};
			void set(K10VWrap^ value)
			{
				_kclmtr->setVirtualK10(value->getNK10V());
			};
		};

		//XYZ
		property bool isMeasure
		{
			bool get()
			{
				return _kclmtr->isMeasuring();
			};
		};
		void startMeasuring()
		{
			_kclmtr->startMeasuring();
		}
		void stopMeasuring()
		{
			_kclmtr->stopMeasuring();
		}
		wMeasurement ^getNextMeasurement()
		{
			return gcnew wMeasurement(_kclmtr->getNextMeasurement());
		};
		//Setting up to Store CalFiles
		wCorrectedCoefficient^ getCoefficientTestMatrix(wwrgb^ Reference, wwrgb^ Kclmtr)
		{
			return gcnew wCorrectedCoefficient(_kclmtr->getCoefficientTestMatrix(Reference->getNwrgb(), Kclmtr->getNwrgb()));
		};
		int deleteCalFile(int CalFileID)
		{
			return _kclmtr->deleteCalFile(CalFileID);
		};
		//Storing CalFile
		int storeMatrices(int ID, String^ Name, wwrgb^ Reference, wwrgb^ Kclmtr, wwhitespect^ whitespect)
		{
			return _kclmtr->storeMatrices(ID, MarshalString(Name), Reference->getNwrgb(), Kclmtr->getNwrgb(), whitespect->getNwhitespect());
		};

		//BlackCal - Cold
		wBlackMatrix^ captureBlackLevel()
		{
			return gcnew wBlackMatrix(_kclmtr->captureBlackLevel());
		};
		wBlackMatrix^ recallFlashMatrix()
		{
			return gcnew wBlackMatrix(_kclmtr->recallFlashMatrix());
		};
		
		//BlackCal - Hot
		wBlackMatrix^ recallRAMMatrix()
		{
			return gcnew wBlackMatrix(_kclmtr->recallRAMMatrix());
		};
		wBlackMatrix^ recallCoefficientMatrix()
		{
			return gcnew wBlackMatrix(_kclmtr->recallCoefficientMatrix());
		};
		
		//FFT
		String^ StartFlicker(bool grabConstantly)
		{
			return NativeToDotNet(_kclmtr->startFlicker(grabConstantly));
		};
		wFlicker^ getNextFlicker()
		{
			return gcnew wFlicker(_kclmtr->getNextFlicker());
		};
		void StopFlicker()
		{
			_kclmtr->stopFlicker();
		}

		//setup/Close
		bool connect(int thePort)
		{
			port = thePort;
			return _kclmtr->connect();
		};
		bool connect()
		{
			return _kclmtr->connect();
		};
		void closePort(bool resetThePortName)
		{
			_kclmtr->closePort(resetThePortName);
		};

		delegate System::Void MeasureEventHandler(wMeasurement^);
		delegate System::Void FlickEventHandler(wFlicker^);
		event MeasureEventHandler^ measureEvent;
		event FlickEventHandler^ flickEvent;
		void printMeasure(wMeasurement^ m){
			measureEvent(m);
		};
		void printFlick(wFlicker^ f){
			flickEvent(f);
		};

	private:
		string MarshalString ( String ^ s);
		System::String^ NativeToDotNet( std::string input );
		KClmtr *_kclmtr;
	};
}