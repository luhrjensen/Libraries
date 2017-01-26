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

#include "..\..\kclmtr\WRGB.h"

namespace KClmtrBase {
	namespace KClmtrWrapper {
		using namespace KClmtrNative;
		public ref class wWRGB {
		public:
			~wWRGB() {
				delete wrgb;
			}
			wWRGB() {
				wrgb = new WRGB();
			}
			wWRGB(const WRGB &WRGB) {
				wrgb = wrgb;
			}
			const WRGB getNative() {
				return *wrgb;
			}
			property cli::array<double, 2>^ v {
				cli::array<double, 2>^ get() {
					cli::array<double, 2>^ values = gcnew cli::array<double, 2>(4, 3);
					for (int i = 0; i < 4; ++i) {
						for (int j = 0; j < 3; ++j) {
							values[i, j] = wrgb->v[i][j];
						}
					}
					return values;
				}
				void set(cli::array<double, 2>^ values) {
					for (int i = 0; i < 4; ++i) {
						for (int j = 0; j < 3; ++j) {
							wrgb->v[i][j] = values[i, j];
						}
					}
				}
			}
		private:
			WRGB *wrgb;
		};
	}
}