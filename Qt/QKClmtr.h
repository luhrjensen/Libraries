#ifndef QKCLMTR_H
#define QKCLMTR_H

#include <QtGui/QWidget>
#include <portsystem/devices/gendevice.h>
#include "../kclmtr/KClmtr.h"

class QK10V : public QObject {
    Q_OBJECT

public:
    struct QColors {
        int red;
        int green;
        int blue;

        QColors() {}
        QColors(Colors color) {
            red = color.red;
            green = color.green;
            blue = color.blue;
        }
        Colors getNColor() {
            Colors color;

            color.red = red;
            color.green = green;
            color.blue = blue;

            return color;
        }
    };

    QK10V() {
        _k10v = new K10V;
    }
    virtual ~QK10V(void) {
        delete _k10v;
    }
    QK10V(K10V k10v) {
        _k10v = new K10V(k10v);
    }
    Q_PROPERTY(QColors *ColorField READ getColors WRITE setColors)

    K10V getNK10v() {
        return *_k10v;
    }

private:
    K10V *_k10v;
    QColors *getColors() {
        return new QColors(_k10v->getColorField());
    }
    void setColors(QColors *value) {
        _k10v->setColorField(value->getNColor());
    }
};

class QKClmtr;
class SubClass : public KClmtr {
public:
    SubClass(QKClmtr *_QKC) {
        _QKClmtr = _QKC;
    }

    void printMeasure(Measurement m);
    void printFlicker(Flicker f);
    QKClmtr *_QKClmtr;
};
/** @ingroup wrappers
 *  @brief Wraps the Native object to work easly in Qt
 */
class QKClmtr : public GenDevice {
    Q_OBJECT

public:
    QKClmtr() {
        _isOpen = false;
        _kclmtr = new SubClass(this);
    }
    virtual ~QKClmtr(void) {
        delete _kclmtr;
    }
    //Property
    QString getPort() {
        return QString::fromStdString(_kclmtr->getPort());
    }
    void setPort(QString value) {
        _kclmtr->setPort(value.toStdString());
    }
    QString getSN() {
        return QString::fromStdString(_kclmtr->getSN());
    }
    QString getModel() {
        return QString::fromStdString(_kclmtr->getModel());
    }
    bool isPortOpen() {
        if(_isOpen && !_kclmtr->isPortOpen()) {
            emit closed();
        }

        return _kclmtr->isPortOpen();
    }


    void setAimingLights(bool onOff) {
        _kclmtr->setAimingLights(onOff);
    }

    //Property - CalFiles
    QString getCalFileName() {
        return QString::fromStdString(_kclmtr->getCalFileName());
    }
    int getCalFileID() {
        return _kclmtr->getCalFileID();
    }
    void setCalFileID(int calFileID) {
        //will it really change
        if(getCalFileID() != calFileID) {
            _kclmtr->setCalFileID(calFileID);
            emit calfileChanged();
        }
    }
    const matrix getCalMatrix() {
        return _kclmtr->getcalMatrix();
    }
    const matrix getRGBMatrix() {
        return _kclmtr->getRGBMatrix();
    }
    WhiteSpec getWhiteSpec() {
        return _kclmtr->getWhiteSpec();
    }
    void resetWhiteSpec() {
        _kclmtr->resetWhiteSpec();
    }

    void setWhiteSpec(WhiteSpec value) {
        _kclmtr->setWhiteSpec(value);
    }
    QStringList getCalFileList() {
        QStringList CalList;
        const string *calList  = _kclmtr->getCalFileList();

        for(int i = 0; i < 97;  i++) {
            CalList << QString::fromStdString(calList[i]);
        }

        return CalList;
    }
    QK10V *getK10V() {
        return new QK10V(_kclmtr->getVirtualK10());
    }
    void setK10V(QK10V *value) {
        _kclmtr->setVirtualK10(value->getNK10v());
    }


    void setTempCalFile(CorrectedCoefficient matrix, WhiteSpec whiteSpec) {
        _kclmtr->setTempCalFile(matrix, whiteSpec);
    }
    //Property - FFT
    bool getFFT_Cosine() {
        return _kclmtr->getFFT_Cosine();
    }
    void setFFT_Cosine(bool value) {
        _kclmtr->setFFT_Cosine(value);
    }
    bool getFFT_Smoothing() {
        return _kclmtr->getFFT_Smoothing();
    }
    void setFFT_Smoothing(bool value) {
        _kclmtr->setFFT_Smoothing(value);
    }
    bool getFFT_Rolloff() {
        return _kclmtr->getFFT_RoolOff();
    }
    void setFFT_RollOff(bool value) {
        _kclmtr->setFFT_RollOff(value);
    }
    int getFFT_samples() {
        return _kclmtr->getFFT_Samples();
    }
    int setFFT_samples(int value) {
        return _kclmtr->setFFT_Samples(value);
    }


    //XYZ
    bool isMeasuring() {
        return _kclmtr->isMeasuring();
    }
    void startMeasuring() {
        _kclmtr->startMeasuring();
    }
    void stopMeasuring() {
        _kclmtr->stopMeasuring();
    }
    Measurement getNextMeasurement(int n = 1) {
        return Measurement(_kclmtr->getNextMeasurement(n));
    }
    //Setting up to Store CalFiles
    CorrectedCoefficient getCoefficientTestMatrix(wrgb Reference, wrgb Kclmtr) {
        return _kclmtr->getCoefficientTestMatrix(Reference, Kclmtr);
    }
    int deleteCalFile(int CalFileID) {
        return _kclmtr->deleteCalFile(CalFileID);
    }
    //Storing CalFile
    int storeCalFile(int ID, QString Name, wrgb reference, wrgb kclmtr, WhiteSpec whiteSpec) {
        return _kclmtr->storeMatrices(ID, Name.toStdString(), reference, kclmtr, whiteSpec);
    }

    //BlackCal - Cold
    BlackMatrix captureBlackLevel() {
        return _kclmtr->captureBlackLevel();
    }
    BlackMatrix getFlashMatrix() {
        return _kclmtr->getFlashMatrix();
    }

    //BlackCal - Hot
    BlackMatrix getRAMMatrix() {
        return _kclmtr->getRAMMatrix();
    }
    BlackMatrix getCoefficientMatrix() {
        return _kclmtr->getCoefficientMatrix();
    }

    //FFT
    bool isFlickering() {
        return _kclmtr->isFlickering();
    }
    int startFlicker(bool grabConstantly) {
        return _kclmtr->startFlicker(grabConstantly);
    }
    Flicker getNextFlicker() {
        return Flicker(_kclmtr->getNextFlicker());
    }
    void stopFlicker() {
        _kclmtr->stopFlicker();
    }

    //setup/Close
    bool connect() {
        if(_kclmtr->connect()) {
            _isOpen = true;
            emit connected();
            return true;
        } else {
            _isOpen = false;
            return false;
        }
    }
    void closePort(bool resetThePortName) {
        if(isPortOpen()) {
            _kclmtr->closePort(resetThePortName);
            _isOpen = false;
            emit closed();
        }
    }
    bool connect(QString portName) {
        setPort(portName);
        return connect();
    }

    void printMeasure(Measurement measure) {
        emit measured(measure);
    }
    void printFlicker(Flicker flicker) {
        emit flickered(flicker);
    }

    //functions for GenDevice
    DeviceType getType() {
        return typeKClmtr;
    }


signals:
    void closed();
    void connected();
    void calfileChanged();
    /** @brief Sends out measurement
     *  @details You must register Measurement to connect this singal to a slot.
     *  @details Here is an example:
     *  @details Header
     *  @snippet QKClmtrExample.cpp Header_measure
     *   Source
     *  @snippet QKClmtrExample.cpp Source_measure
     */
    void measured(Measurement measure);
    /** @brief Sends out flicker
     *  @details You must register Flicker to connect this singal to a slot.
     *  @details Here is an example:
     *  @details Header
     *  @snippet QKClmtrExample.cpp Header_flicker
     *   Source
     *  @snippet QKClmtrExample.cpp Source_flicker
     */
    void flickered(Flicker flicker);

private:
    bool _isOpen;
    SubClass *_kclmtr;
};

#endif // QKCLMTR_H
