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

#include "MatrixWrapper.h"
#include "..\..\kclmtr\Counts.h"

namespace KClmtrBase {
	namespace KClmtrWrapper {
		using namespace KClmtrBase::KClmtrNative;
		public ref struct wCounts {
			property int Th1 {
				int get() {
					return counts->getTh1();
				}
			}
			property int Th2 {
				int get() {
					return counts->getTh2();
				}
			}
			property int Therm {
				int get() {
					return counts->getTherm();
				}
			}
			property MeasurementRange RedRange {
				MeasurementRange get() {
					return counts->getRedRange();
				}
			}
			property MeasurementRange GreenRange {
				MeasurementRange get() {
					return counts->getGreenRange();
				}
			}
			property MeasurementRange BlueRange {
				MeasurementRange get() {
					return counts->getBlueRange();
				}
			}
			property wMatrix<int> ^TheCounts {
				wMatrix<int> ^get() {
					return gcnew wMatrix<int>(counts->getTheCounts());
				}
			}
			property unsigned int ErrorCode {
				unsigned int get() {
					return counts->getErrorCode();
				}
			}

			wCounts() {
				counts = new Counts();
			}

			wCounts(const Counts &other) {
				counts = new Counts(other);
			}
			virtual  ~wCounts() {
				this->!wCounts();
			}
			const Counts getNative() {
				return *counts;
			}
		protected:
			!wCounts() {
				delete counts;
			}
		private:
			Counts *counts;
		};
	}
}