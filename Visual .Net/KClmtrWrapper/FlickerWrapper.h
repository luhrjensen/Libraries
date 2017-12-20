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
#include "..\..\kclmtr\Flicker.h"
#include "MatrixWrapper.h"

namespace KClmtrBase {
	namespace KClmtrWrapper {
		using namespace KClmtrBase;
		public ref class wFlickerSetting {
		public:
			ref class wRange {
			public:
				property int start {
					int get() {
						return r->start;
					}
					void set(int v) {
						r->start = v;
					}
				}
				property int end {
					int get() {
						return r->end;
					}
					void set(int v) {
						r->end = v;
					}
				}
				int numbers() {
					return r->numbers();
				}
				wRange() {
					r = new FlickerSetting::Range();
				}
				wRange(int _start, int _end) {
					r = new FlickerSetting::Range(_start, _end);
				}
				wRange(const FlickerSetting::Range &range) {
					r = new FlickerSetting::Range(range);
				}
				~wRange() {
					this->!wRange();
				}

				const FlickerSetting::Range getNative() {
					return *r;
				}
			protected:
				!wRange() {
					delete r;
				}
			private:
				FlickerSetting::Range *r;
			};
			ref class wRangeCorrecionArray {
			public:
				property wRange ^rangeOfHz {
					wRange ^get() {
						return gcnew wRange(cArray->rangeOfHz);
					}
					void set(wRange ^v) {
						cArray->rangeOfHz = v->getNative();
					}
				}
				property CorrectionMode mode {
					CorrectionMode get() {
						return cArray->mode;
					}
					void set(CorrectionMode v) {
						cArray->mode = v;
					}
				}
				property cli::array<double> ^array {
					cli::array<double> ^get() {
						cli::array<double> ^values = gcnew cli::array<double>(cArray->array.size());
						for (int i = 0; i < (int)cArray->array.size(); ++i) {
							values[i] = cArray->array[i];
						}
						return values;
					}
					void set(cli::array<double> ^values) {
						cArray->array = std::vector<double>();
						cArray->array.resize(values->Length);
						for (int i = 0; i < values->Length; ++i) {
							cArray->array[i] = values[i];
						}
					}
				}

				wRangeCorrecionArray() {
					cArray = new FlickerSetting::RangeCorrecionArray();
				}
				wRangeCorrecionArray(const FlickerSetting::RangeCorrecionArray &cArr) {
					cArray = new FlickerSetting::RangeCorrecionArray(cArr);
				}
				~wRangeCorrecionArray() {
					this->!wRangeCorrecionArray();
				}
			protected:
				!wRangeCorrecionArray() {
					delete cArray;
				}
			private:
				FlickerSetting::RangeCorrecionArray *cArray;
			};

			int samples; 							/**< Must be a power of 2 between 64 and 2048 */
			int speed; 								/**< How many samples per 1 second */
			int numberOfPeaks;						/**< How many peaks to find */
			bool cosine;							/**< Cosine correction, should be on */
			bool smoothing; 						/**< Averaging, should be on */
			bool JETIADiscount_DB;					/**< JEITA Discount to be applied to dB. It's a human eye responds to the frequency */
			bool JEITADiscount_Percent;				/**< JEITA Discount to be applied to percent. It's a human eye reponds to the frequency */
			DecibelMode decibel; 	/**< The mode of DB */
			PercentMode percent;	/**< The mode of the percent */
			//Correction Matrix
			cli::array<wRangeCorrecionArray ^> ^corrections; /**< The corrections to be used */

			wFlickerSetting() {
				settings = new FlickerSetting();
			}
			wFlickerSetting(const FlickerSetting &s) {
				settings = new FlickerSetting(s);
			}
			~wFlickerSetting() {
				this->!wFlickerSetting();
			}
		protected:
			!wFlickerSetting() {
				delete settings;
			}
		private:
			FlickerSetting *settings;
		};

		public ref class wFlicker {
		public:
			property double BigY {
				double get() {
					return f->getBigY();
				}
			}
			property MeasurementRange Range {
				MeasurementRange get() {
					return f->getRange();
				}
			}
			property wMatrixDouble ^PeakFrequencyPercent {
				wMatrixDouble ^get() {
					return gcnew wMatrixDouble(f->getPeakFrequencyPercent());
				}
			}
			property wMatrixDouble ^PeakFrequencyDB {
				wMatrixDouble ^get() {
					return gcnew wMatrixDouble(f->getPeakFrequencyDB());
				}
			}
			property wMatrixDouble ^FlickerDB {
				wMatrixDouble ^get() {
					return gcnew wMatrixDouble(f->getFlickerDB());
				}
			}
			property wMatrixDouble ^FlickerPercent {
				wMatrixDouble ^get() {
					return gcnew wMatrixDouble(f->getFlickerPercent());
				}
			}
			property wMatrixDouble^Counts {
				wMatrixDouble^get() {
					return gcnew wMatrixDouble(f->getCounts());
				}
			}
			property wMatrixDouble ^Nits {
				wMatrixDouble ^get() {
					return gcnew wMatrixDouble(f->getNits());
				}
			}
			property wMatrixDouble ^Amplitude {
				wMatrixDouble^get() {
					return gcnew wMatrixDouble(f->getAmplitude());
				}
			}
			property unsigned int ErrorCode {
				unsigned int get() {
					return f->getErrorCode();
				}
			}
			property wFlickerSetting ^FlickerSetting {
				wFlickerSetting ^get() {
					return gcnew wFlickerSetting(f->getSettings());
				}
			}

			wFlicker() {
				f = new Flicker();
			}
			wFlicker(const Flicker &flicker) {
				f = new Flicker(flicker);
			}
			virtual  ~wFlicker() {
				this->!wFlicker();
			}
		protected:
			!wFlicker() {
				delete f;
			}
		private:
			Flicker *f;
		};
	}
}