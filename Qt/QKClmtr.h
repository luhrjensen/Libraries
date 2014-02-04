#ifndef QKCLMTR_H
#define QKCLMTR_H

#include <QObject>
#include <QStringList>
#include "../kclmtr/KClmtr.h"

class QKClmtr;
/** @cond */
class SubClass : public KClmtr {
public:
    SubClass(QKClmtr *_QKC) {
        _QKClmtr = _QKC;
    }

    void printMeasure(Measurement m);
    void printFlicker(Flicker f);
    QKClmtr *_QKClmtr;
};
/** @endcond */
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
    QString getPort() {
        return QString::fromStdString(_kclmtr->getPort());
    }
    void setPort(const QString &value) {
        _kclmtr->setPort(value.toStdString());
    }
    QString getSerialNumber() {
        return QString::fromStdString(_kclmtr->getSerialNumber());
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


    void setAimingLights(const bool onOff) {
        _kclmtr->setAimingLights(onOff);
    }

    //Property - CalFiles
    QString getCalFileName() {
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
    matrix getCalMatrix() {
        return _kclmtr->getCalMatrix();
    }
    matrix getRGBMatrix() {
        return _kclmtr->getRGBMatrix();
    }
    gamutSpec getGamutSpec() {
        return _kclmtr->getGamutSpec();
    }
    void setGamutSpec(const gamutSpec &gs) {
        _kclmtr->setGamutSpec(gs);
        emit gamutSpecChanged();
    }

    QStringList getCalFileList() {
        QStringList CalList;
        const string *calList  = _kclmtr->getCalFileList();

        for(int i = 0; i < 97;  i++) {
            CalList << QString::fromStdString(calList[i]);
        }

        return CalList;
    }

    void setTempCalFile(const CorrectedCoefficient &matrix/*, const WhiteSpec &whiteSpec*/) {
        _kclmtr->setTempCalFile(matrix/*, whiteSpec*/);
    }
    //Property - FFT
    bool getFFT_Cosine() {
        return _kclmtr->getFFT_Cosine();
    }
    void setFFT_Cosine(const bool value) {
        _kclmtr->setFFT_Cosine(value);
    }
    bool getFFT_Smoothing() {
        return _kclmtr->getFFT_Smoothing();
    }
    void setFFT_Smoothing(const bool value) {
        _kclmtr->setFFT_Smoothing(value);
    }
    int getFFT_Samples() {
        return _kclmtr->getFFT_Samples();
    }
    int setFFT_Samples(int value) {
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
    int storeCalFile(int ID, const QString &Name, const wrgb &reference, const wrgb &kclmtr) {
        return _kclmtr->storeMatrices(ID, Name.toStdString(), reference, kclmtr);
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
    bool connect(const QString &portName) {
        setPort(portName);
        return connect();
    }
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
    /** @brief Sends out Measure
     *  @details You must setup the target where the flicker needs to go to.
     *  @details Here is an example:
     *  @details Header
     *  @snippet QKclmtrExample.cpp Header_flicker
     *   Source
     *  @snippet QKclmtrExample.cpp Source_flicker
     */
    void measured(const Measurement &);
    /** @brief Sends out flicker
     *  @details You must setup the target where the flicker needs to go to.
     *  @details Here is an example:
     *  @details Header
     *  @snippet QKclmtrExample.cpp Header_flicker
     *   Source
     *  @snippet QKclmtrExample.cpp Source_flicker
     */
    void flickered(const Flicker &);
    void calfileChanged();
    void gamutSpecChanged();
};

#endif // QKCLMTR_H
