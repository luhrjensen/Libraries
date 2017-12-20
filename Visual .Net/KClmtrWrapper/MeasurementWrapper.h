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
#include "../../kclmtr/Measurement.h"
#include "MatrixWrapper.h"

namespace KClmtrBase {
	namespace KClmtrWrapper {
		using namespace KClmtrNative;
		public ref struct wGamutSpec {
		public:
			virtual ~wGamutSpec() {
				this->!wGamutSpec();
			}
			wGamutSpec() {
				gs = new GamutSpec();
			}
			wGamutSpec(const GamutSpec &_gs) {
				gs = new GamutSpec(_gs);
			}
			wGamutSpec(double redX, double redY,
				double greenX, double greenY,
				double blueX, double blueY,
				double whiteX, double whiteY, double whiteBigY) {
				gs = new GamutSpec(redX, redY,
					greenX, greenY,
					blueX, blueY,
					whiteX, whiteY, whiteBigY);
			}

			static wGamutSpec^ fromCode(GamutCode code) {
				return fromCode(code, 100);
			}
			static wGamutSpec^ fromCode(GamutCode code, double whiteBigY) {
				wGamutSpec^ wgs = gcnew wGamutSpec();
				GamutSpec g = GamutSpec::fromCode(code, whiteBigY);
				wgs->gs = new GamutSpec(g);
				return wgs;
			}
			GamutCode getCodeSpec() {
				return gs->getCodeSpec();
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
			wMatrixDouble^ getRGBtoXYZ() {
				return gcnew wMatrixDouble(gs->getRGBtoXYZ());
			}
			wMatrixDouble^ getXYZtoRGB() {
				return gcnew wMatrixDouble(gs->getXYZtoRGB());
			}

			const GamutSpec getNative() {
				return *gs;
			}
		protected:
			!wGamutSpec() {
				delete gs;
			}
		private:
			GamutSpec *gs;
		};

		public ref class wMeasurement {
		public:
			property double CIE1931_x {
				double get() {
					return m->getCIE1931_x();
				}
			}
			property double CIE1931_y {
				double get() {
					return m->getCIE1931_y();
				}
			}
			property double BigX {
				double get() {
					return m->getBigX();
				}
			}
			property double BigY {
				double get() {
					return m->getBigY();
				}
			}
			property double BigZ {
				double get() {
					return m->getBigZ();
				}
			}
			property double BigXRaw {
				double get() {
					return m->getBigXRaw();
				}
			}
			property double BigYRaw {
				double get() {
					return m->getBigYRaw();
				}
			}
			property double BigZRaw {
				double get() {
					return m->getBigZRaw();
				}
			}
			property double RGB_Red {
				double get() {
					return m->getRGB_Red();
				}
			}
			property double RGB_Green {
				double get() {
					return m->getRGB_Green();
				}
			}
			property double RGB_Blue {
				double get() {
					return m->getRGB_Blue();
				}
			}
			property double CIE1974_u {
				double get() {
					return m->getCIE1974_u();
				}
			}
			property double CIE1974_v {
				double get() {
					return m->getCIE1974_v();
				}
			}
			property double Wavelength_nm {
				double get() {
					return m->getWavelength_nm();
				}
			}
			property double Wavelength_duv {
				double get() {
					return m->getWavelength_duv();
				}
			}
			property double Lab_L {
				double get() {
					return m->getLab_L();
				}
			}
			property double Lab_a {
				double get() {
					return m->getLab_a();
				}
			}
			property double LAB_b {
				double get() {
					return m->getLab_b();
				}
			}
			property double LCh_C {
				double get() {
					return m->getLCh_C();
				}
			}
			property double LCh_h {
				double get() {
					return m->getLCh_h();
				}
			}
			property double hue {
				double get() {
					return m->getHSV_hue();
				}
			}
			property double saturation {
				double get() {
					return m->getHSV_saturation();
				}
			}
			property double value {
				double get() {
					return m->getHSV_value();
				}
			}
			property MeasurementRange RedRange {
				MeasurementRange get() {
					return m->getRedRange();
				}
			}
			property MeasurementRange GreenRange {
				MeasurementRange get() {
					return m->getGreenRange();
				}
			}
			property MeasurementRange BlueRange {
				MeasurementRange get() {
					return m->getBlueRange();
				}
			}
			property double ColorTemputure_K {
				double get() {
					return m->getColorTemputure_K();
				}
			}
			property double ColorTemputure_duv {
				double get() {
					return m->getColorTemputure_duv();
				}
			}
			property unsigned int errorcode {
				unsigned int get() {
					return m->getErrorCode();
				}
			}

			property int Averagingby {
				int get() {
					return m->getAveragingby();
				}
			}
			property double MinX {
				double get() {
					return m->getMinX();
				}
			}
			property double MaxX {
				double get() {
					return m->getMaxX();
				}
			}
			property double MinY {
				double get() {
					return m->getMinY();
				}
			}
			property double MaxY {
				double get() {
					return m->getMaxY();
				}
			}
			property double MinZ {
				double get() {
					return m->getMinZ();
				}
			}
			property double MaxZ {
				double get() {
					return m->getMaxZ();
				}
			}
			property wGamutSpec^ GamutSpec {
				wGamutSpec^ get() {
					return gcnew wGamutSpec(m->getGamutSpec());
				}
				void set(wGamutSpec ^gs) {
					m->setGamutSpec(gs->getNative());
				}
			}
			virtual ~wMeasurement() {
				this->!wMeasurement();
			}
			wMeasurement() {
				m = new Measurement();
			}
			wMeasurement(const Measurement &measurement) {
				m = new Measurement(measurement);
			}
			wMeasurement(const wMeasurement %_m) {
				m = new Measurement(*(_m.m));
			};
			wMeasurement% operator=(const wMeasurement %m) {
				wMeasurement::wMeasurement(m);
				return *this;
			};

			static wMeasurement^ fromXYZ(double X, double Y, double Z) {
				return fromXYZ(X, Y, Z, wGamutSpec::fromCode(GamutCode::defaultGamut));
			}
			static wMeasurement^ fromxyY(double x, double y, double Y) {
				return fromxyY(x, y, Y, wGamutSpec::fromCode(GamutCode::defaultGamut));
			}
			static wMeasurement^ fromuvprimeY(double u, double v, double Y) {
				return fromuvprimeY(u, v, Y, wGamutSpec::fromCode(GamutCode::defaultGamut));
			}
			static wMeasurement^ fromTempduvY(double _temp, double _tempduv, double Y) {
				return fromTempduvY(_temp, _tempduv, Y, wGamutSpec::fromCode(GamutCode::defaultGamut));
			}
			static wMeasurement^ fromnmduvY(double _nm, double _nmduv, double Y) {
				return fromnmduvY(_nm, _nmduv, Y, wGamutSpec::fromCode(GamutCode::defaultGamut));
			}
			static wMeasurement^ fromRGB(double red, double green, double blue) {
				return fromRGB(red, green, blue, wGamutSpec::fromCode(GamutCode::defaultGamut));
			}
			static wMeasurement^ fromXYZ(double X, double Y, double Z, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromXYZ(X, Y, Z, gs->getNative()));
			}
			static wMeasurement^ fromxyY(double x, double y, double Y, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromxyY(x, y, Y, gs->getNative()));
			}
			static wMeasurement^ fromuvprimeY(double u, double v, double Y, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromuvprimeY(u, v, Y, gs->getNative()));
			}
			static wMeasurement^ fromTempduvY(double _temp, double _tempduv, double Y, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromTempduvY(_temp, _tempduv, Y, gs->getNative()));
			}
			static wMeasurement^ fromnmduvY(double _nm, double _nmduv, double Y, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromnmduvY(_nm, _nmduv, Y, gs->getNative()));
			}
			static wMeasurement^ fromRGB(double r, double g, double b, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromRGB(r, g, b, gs->getNative()));
			}
			static wMeasurement^ fromHSV(double hue, double saturation, double value, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromHSV(hue, saturation, value, gs->getNative()));
			}
			static wMeasurement^ fromLab(double L, double a, double b, wGamutSpec^ gs) {
				return gcnew wMeasurement(Measurement::fromLab(L, a, b, gs->getNative()));
			}

			double deltaE1976(wMeasurement^ spec) {
				return m->deltaE1976(spec->getNative());
			}
			double deltaE1994(wMeasurement^ spec) {
				return  m->deltaE1994(spec->getNative());
			}
			double deltaE2000(wMeasurement^ spec) {
				return m->deltaE2000(spec->getNative());
			}

			static double toNits(double FootLamberts) {
				return Measurement::toNits(FootLamberts);
			}
			static double toFootLamberts(double nits) {
				return Measurement::toFootLamberts(nits);
			}

			const Measurement getNative() {
				return *m;
			}
		protected:
			!wMeasurement() {
				delete m;
			}
		private:
			Measurement *m;
		};
	}
}