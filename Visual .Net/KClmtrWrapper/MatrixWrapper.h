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
#include "../../kclmtr/matrix.h"

#define MAKE_MATRIX(NAME, TYPE) \
public ref class NAME { \
	public: \
		NAME() { \
			matrix = new KClmtrBase::KClmtrNative::Matrix<TYPE>(); \
		} \
		NAME(const KClmtrBase::KClmtrNative::Matrix<TYPE> &v) { \
			matrix = new KClmtrBase::KClmtrNative::Matrix<TYPE>(v); \
		} \
		NAME(unsigned int row, unsigned int col) { \
			matrix = new KClmtrBase::KClmtrNative::Matrix<TYPE>(row, col); \
		} \
		virtual ~NAME() { \
			this->!NAME(); \
		} \
		property unsigned int Row { \
			unsigned  int get() { \
				return matrix->getRow(); \
			} \
		} \
		property unsigned int Column { \
			unsigned  int get() { \
				return matrix->getColumn(); \
			} \
		} \
		property cli::array<TYPE, 2>^ v { \
			cli::array<TYPE, 2>^ get() { \
				cli::array<TYPE, 2>^ values = gcnew cli::array<TYPE, 2>(matrix->getRow(), matrix->getColumn()); \
				for (unsigned int i = 0; i < matrix->getRow(); ++i) { \
					for (unsigned int j = 0; j < matrix->getColumn(); ++j) { \
						values[i, j] = matrix->v[i][j]; \
					} \
				} \
				return values; \
			} \
			void set(cli::array<TYPE, 2>^ values) { \
				matrix->initializeV(matrix->getRow(), matrix->getColumn()); \
				for (unsigned int i = 0; i < matrix->getRow(); ++i) { \
					for (unsigned int j = 0; j < matrix->getColumn(); ++j) { \
						matrix->v[i][j] = values[i, j]; \
					} \
				} \
			} \
		} \
		property TYPE default[int, int] { \
			TYPE get(int x, int y) { \
				return matrix->v[x][y]; \
			} \
			void set(int x, int y, TYPE value) { \
				matrix->v[x][y] = value; \
			} \
		} \
		void initializeV(unsigned int row, unsigned int columns) { \
			matrix->initializeV(row, columns); \
		} \
		const KClmtrBase::KClmtrNative::Matrix<TYPE> getNative() { \
			return *matrix; \
		} \
	protected: \
		!NAME() { \
			delete matrix; \
		} \
	private: \
		KClmtrBase::KClmtrNative::Matrix<TYPE> *matrix; \
	};

namespace KClmtrBase {
	namespace KClmtrWrapper {
		MAKE_MATRIX(wMatrixDouble, double)
		MAKE_MATRIX(wMatrixFloat, float)
		MAKE_MATRIX(wMatrixInt, int)
	}
}