#ifndef QKCLMTR_H
#define QKCLMTR_H

#include <QObject>
#include <QStringList>
#include "../kclmtr/KClmtr.h"

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
class QKClmtr : public QObject {
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
    QString getPort() const {
        return QString::fromStdString(_kclmtr->getPort());
    }
    void setPort(const QString &value) {
        _kclmtr->setPort(value.toStdString());
    }
    QString getSerialNumber() const {
        return QString::fromStdString(_kclmtr->getSerialNumber());
    }
    QString getModel() const {
        return QString::fromStdString(_kclmtr->getModel());
    }
    bool isPortOpen() const {
        if(_isOpen && !_kclmtr->isPortOpen()) {
            emit closed();
        }

        return _kclmtr->isPortOpen();
    }


    void setAimingLights(const bool onOff) const {
        _kclmtr->setAimingLights(onOff);
    }

    //Property - CalFiles
    QString getCalFileName() const {
        return QString::fromStdString(_kclmtr->getCalFileName());
    }
    int getCalFileID() const {
        return _kclmtr->getCalFileID();
    }
    void setCalFileID(const int calFileID) {
        //will it really change
        if(getCalFileID() != calFileID) {
            _kclmtr->setCalFileID(calFileID);
            emit calfileChanged();
        }
    }
    matrix getCalMatrix() const {
        return _kclmtr->getCalMatrix();
    }
    matrix getRGBMatrix() const {
        return _kclmtr->getRGBMatrix();
    }
    WhiteSpec getWhiteSpec() const {
        return _kclmtr->getWhiteSpec();
    }
    void resetWhiteSpec() {
        _kclmtr->resetWhiteSpec();
    }

    void setWhiteSpec(const WhiteSpec &value) {
        _kclmtr->setWhiteSpec(value);
    }
    QStringList getCalFileList() const {
        QStringList CalList;
        const string *calList  = _kclmtr->getCalFileList();

        for(int i = 0; i < 97;  i++) {
            CalList << QString::fromStdString(calList[i]);
        }

        return CalList;
    }

    void setTempCalFile(const CorrectedCoefficient &matrix, const WhiteSpec &whiteSpec) {
        _kclmtr->setTempCalFile(matrix, whiteSpec);
    }
    //Property - FFT
    bool getFFT_Cosine() const {
        return _kclmtr->getFFT_Cosine();
    }
    void setFFT_Cosine(const bool value) {
        _kclmtr->setFFT_Cosine(value);
    }
    bool getFFT_Smoothing() const {
        return _kclmtr->getFFT_Smoothing();
    }
    void setFFT_Smoothing(const bool value) {
        _kclmtr->setFFT_Smoothing(value);
    }
    bool getFFT_Rolloff() const {
        return _kclmtr->getFFT_RollOff();
    }
    void setFFT_RollOff(const bool value) {
        _kclmtr->setFFT_RollOff(value);
    }
    int getFFT_Samples() const {
        return _kclmtr->getFFT_Samples();
    }
    int setFFT_Samples(int value) const {
        return _kclmtr->setFFT_Samples(value);
    }


    //XYZ
    bool isMeasuring() const {
        return _kclmtr->isMeasuring();
    }
    void startMeasuring() const {
        _kclmtr->startMeasuring();
    }
    void stopMeasuring() const {
        _kclmtr->stopMeasuring();
    }
    AvgMeasurement getNextMeasurement(const int n = 1) {
        return _kclmtr->getNextMeasurement(n);
    }
    //Setting up to Store CalFiles
    CorrectedCoefficient getCoefficientTestMatrix(const wrgb &Reference, const wrgb &Kclmtr) {
        return _kclmtr->getCoefficientTestMatrix(Reference, Kclmtr);
    }
    int deleteCalFile(int CalFileID) {
        return _kclmtr->deleteCalFile(CalFileID);
    }
    //Storing CalFile
    int storeCalFile(const int ID, const QString &Name, const wrgb &reference, const wrgb &kclmtr, const WhiteSpec &whiteSpec) const {
        return _kclmtr->storeMatrices(ID, Name.toStdString(), reference, kclmtr, whiteSpec);
    }

    //BlackCal - Cold
    BlackMatrix captureBlackLevel() const {
        return _kclmtr->captureBlackLevel();
    }
    BlackMatrix getFlashMatrix() const {
        return _kclmtr->getFlashMatrix();
    }

    //BlackCal - Hot
    BlackMatrix getRAMMatrix() const {
        return _kclmtr->getRAMMatrix();
    }
    BlackMatrix getCoefficientMatrix() const {
        return _kclmtr->getCoefficientMatrix();
    }

    //FFT
    bool isFlickering() const {
        return _kclmtr->isFlickering();
    }
    int startFlicker(bool grabConstantly) const {
        return _kclmtr->startFlicker(grabConstantly);
    }
    Flicker getNextFlicker() const {
        return Flicker(_kclmtr->getNextFlicker());
    }
    void stopFlicker() {
        _kclmtr->stopFlicker();
    }

    //setup/Close
    bool connect(const QString &portName) const {
        setPort(portName);
        return connect();
    }
    bool connect() const {
        if(_kclmtr->connect()) {
            _isOpen = true;
            emit connected();
            return true;
        } else {
            _isOpen = false;
            return false;
        }
    }
    void closePort() {
        if(isPortOpen()) {
            _kclmtr->closePort();
            _isOpen = false;
            emit closed();
        }
    }

    void printMeasure(const Measurement &measure) {
        emit measured(measure);
    }
    void printFlicker(const Flicker &flicker) {
        emit flickered(flicker);
    }


private:
    bool _isOpen;
    SubClass *_kclmtr;

signals:
    void closed();
    void connected();
    void measured(const Measurement&);
    void flickered(const Flicker&);
    void calfileChanged();
};

#endif // QKCLMTR_H
