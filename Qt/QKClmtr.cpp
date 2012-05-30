#include "QKClmtr.h"

void SubClass::printMeasure(Measurement m)
{
    _QKClmtr->printMeasure(QMeasurement(m));
}
void SubClass::printFlicker(Flicker f)
{
    _QKClmtr->printFlicker(QFlicker(f));
}
/*
void SubClass3D::printMeasure(Measurement left, Measurement right)
{
    _QKClmtr3D->printMeasure(QMeasurement(left), QMeasurement(right));
}
void SubClass3D::printFlicker(Flicker left, Flicker right)
{
    _QKClmtr3D->printFlicker(QFlicker(left), QFlicker(right));
}
*/
