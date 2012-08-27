#ifndef QKCLMTR_H
#define QKCLMTR_H

#include <QtGui/QWidget>
#include "../kclmtr/KClmtr.h"

struct QMeasurement {
public:
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
    double nmduv;           //The duv' in the nmdu'v'Y
    //double L;               //The L in L*A*B*
    //double A;               //The A in L*A*B*
    //double B;               //The B in L*A*B*
    QString redrange;       //The range which the KClmtr is in red
    QString greenrange;     //The range which the KClmtr is in green
    QString bluerange;      //The range which the KClmtr is in blue
    int range;              //The range which the KClmtr is in overall
    double temp;            //The temperature in K
    double tempduv;         //The distance off the curve
    int errorcode;          //The error code whenever you are getting data
    int averagingby;        //How many measurements we are averaging by

    QMeasurement() {}
    QMeasurement(int X, int Y, int Z) {
        Measurement m;
        m.bigx = X;
        m.bigy = Y;
        m.bigz = Z;
        m.computeDerivativeData();
        copy(m);
    }
    QMeasurement(Measurement m) {
        copy(m);
    }
private:
    void copy(Measurement measurement) {
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
        nmduv = measurement.nmduv;
        //L = measurement.L;
        //A = measurement.A;
        //B = measurement.B;
        redrange = QString::fromStdString(measurement.redrange);
        greenrange = QString::fromStdString(measurement.greenrange);
        bluerange = QString::fromStdString(measurement.bluerange);
        range = measurement.range;
        temp = measurement.temp;
        tempduv = measurement.tempduv;
        errorcode = measurement.errorcode;
        averagingby = measurement.averagingby;
    }
};
struct Qwrgb {
public:
    //white, red, green, blue
    //x, y, z
    double v[4][3];

    Qwrgb() {}
    Qwrgb(wrgb WRGB) {
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 3; ++j) {
                v[i][j] = WRGB.v[i][j];
            }
    }
    wrgb getNwrgb() {
        wrgb WRGB;

        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 3; ++j) {
                WRGB.v[i][j] = v[i][j];
            }

        return WRGB;
    }
};
struct QBlackMatrix {
public:
    double range[6][3];
    double Therm;
    int errorcode;
    QString errorstring;

    QBlackMatrix() {}
    QBlackMatrix(BlackMatrix black) {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 6; ++j) {
                range[j][i] = black.range[j][i];
            }
        }
        Therm = black.Therm;
        errorcode = black.errorcode;
    }

};
struct QCorrectedCoefficient {
public:
    double colorMatrix[3][3];
    double rgbMatrix[3][3];

    QCorrectedCoefficient() {}
    QCorrectedCoefficient(CorrectedCoefficient corrected) {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                colorMatrix[i][j] = corrected.colorMatrix[i][j];
                rgbMatrix[i][j] = corrected.rgbMatrix[i][j];
            }
        }
    }

    CorrectedCoefficient getNCorrectedCoefficient() {
        CorrectedCoefficient corrected;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                corrected.colorMatrix[i][j] = colorMatrix[i][j];
                corrected.rgbMatrix[i][j] = rgbMatrix[i][j];
            }
        }
        return corrected;
    }
};
struct QFlicker {
public:
    QMeasurement xyz;
    double peakfrequency[3][3];
    double flickerDB[101];
    double flickerPercent[101];
    int errorcode;

    QFlicker() {}
    QFlicker(Flicker flicker) {
        xyz = QMeasurement(flicker.xyz);
        //peakfrequencyDB = new double[3][2];
        //peakfrequencyPercent = new double[3][2];
        //FlickerDB = new double[101];
        //FlickerPercent = new double[101];

        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                peakfrequency[i][j] = flicker.peakfrequency[i][j];
            }
        }
        for(int i = 0; i < 101; ++i) {
            flickerDB[i] = flicker.flickerDB[i];
            flickerPercent[i] = flicker.flickerPercent[i];
        }
        errorcode = flicker.errorcode;
    }
    ~QFlicker() {
        //delete xyz;
    }
};
struct Qwhitespect {
public:
    double x;
    double y;
    double z;
    double xy;
    double l;

    Qwhitespect() {}
    Qwhitespect(whitespect White) {
        x = White.x;
        y = White.y;
        z = White.z;
        xy = White.xy;
        l = White.l;
    }
    whitespect getNwhitespect() {
        whitespect White;

        White.x = x;
        White.y = y;
        White.z = z;
        White.xy = xy;
        White.l = l;

        return White;
    }
};

class QK10V : public QWidget {
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
    Q_PROPERTY(QColors* ColorField READ getColors WRITE setColors)

    K10V getNK10v() {
        return *_k10v;
    }

private:
    K10V * _k10v;
    QColors* getColors() {
        return new QColors(_k10v->getColorField());
    }
    void setColors(QColors* value) {
        _k10v->setColorField(value->getNColor());
    }
};

class QKClmtr;
class GenDevice : public QObject {
    Q_OBJECT
public:
    enum GenType {
        genTypeKClmtr,
        genTypeCS2000,
        genTypePR650,
        genTypeBM7
    };

    virtual QString getModel() = 0;
    virtual QString getSN() = 0;
    virtual QString getPort() = 0;
    virtual QMeasurement getNextMeasurement() = 0;
    virtual GenType getType() = 0;
    virtual bool isPortOpen() = 0;
    virtual void closePort(bool) = 0;
    virtual bool connect(QString* portName) = 0;

signals:
    void closed();
};

class GenClmtr : public GenDevice {
    Q_OBJECT

public:
    virtual QString getModel() = 0;
    virtual QString getSN() = 0;
    virtual QString getPort() = 0;
    virtual QMeasurement getNextMeasurement() = 0;
    virtual GenType getType() = 0;
    virtual bool isPortOpen() = 0;
    virtual void closePort(bool) = 0;
    virtual bool connect(QString* portName) = 0;

    virtual Qwhitespect* getWhiteSpect() = 0;

    //CalFiles
    virtual QStringList getCalFileList() = 0;
    virtual int deleteCalFile(int CalFileID) = 0;
    virtual int getCalFileID() = 0;
    virtual void setCalFileID(int) = 0;
    virtual QString getCalFileName() = 0;
    virtual int storeCalFile(int ID, QString Name, Qwrgb* Reference, Qwrgb* Kclmtr, Qwhitespect* whitespect) = 0;

    //BlackCal
    virtual QBlackMatrix* captureBlackLevel() = 0;
    virtual QBlackMatrix* recallCoefficientMatrix() = 0;
    virtual QBlackMatrix* recallRAMMatrix() = 0;
    virtual QBlackMatrix* recallFlashMatrix() = 0;
};

class SubClass : public KClmtr {
public:
    SubClass(QKClmtr* _QKC) {
        _QKClmtr = _QKC;
    }

    void printMeasure(Measurement m);
    void printFlicker(Flicker f);
    QKClmtr* _QKClmtr;
};
/** @ingroup wrappers
 *  @brief Wraps the Native object to work easly in Qt
 */
class QKClmtr : public GenClmtr {
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
    Qwhitespect* getWhiteSpect() {
        return new Qwhitespect(_kclmtr->getWhiteSpect());
    }
    void resetWhiteSpect() {
        _kclmtr->resetWhiteSpect();
    }

    void setWhiteSpect(Qwhitespect* value) {
        _kclmtr->setWhiteSpect(value->getNwhitespect());
    }
    QStringList getCalFileList() {
        QStringList CalList;
        const string* calList  = _kclmtr->getCalFileList();

        for(int i = 0; i < 97;  i++) {
            CalList << QString::fromStdString(calList[i]);
        }

        return CalList;
    }
    QK10V* getK10V() {
        return new QK10V(_kclmtr->getVirtualK10());
    }
    void setK10V(QK10V* value) {
        _kclmtr->setVirtualK10(value->getNK10v());
    }


    void setTempCalFile(QCorrectedCoefficient* Matrix, Qwhitespect* whiteSpect) {
        _kclmtr->setTempCalFile(Matrix->getNCorrectedCoefficient(), whiteSpect->getNwhitespect());
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
    bool getFFT_samples() {
        return _kclmtr->getFFT_Samples();
    }
    void setFFT_samples(int value) {
        _kclmtr->setFFT_Samples(value);
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
    QMeasurement getNextMeasurement() {
        return QMeasurement(_kclmtr->getNextMeasurement());
    }
    QMeasurement getNextMeasurement(int n = 1) {
        return QMeasurement(_kclmtr->getNextMeasurement(n));
    }
    //Setting up to Store CalFiles
    QCorrectedCoefficient* getCoefficientTestMatrix(Qwrgb* Reference, Qwrgb* Kclmtr) {
        return new QCorrectedCoefficient(_kclmtr->getCoefficientTestMatrix(Reference->getNwrgb(), Kclmtr->getNwrgb()));
    }
    int deleteCalFile(int CalFileID) {
        return _kclmtr->deleteCalFile(CalFileID);
    }
    //Storing CalFile
    int storeCalFile(int ID, QString Name, Qwrgb* Reference, Qwrgb* Kclmtr, Qwhitespect* whitespect) {
        return _kclmtr->storeMatrices(ID, Name.toStdString(), Reference->getNwrgb(), Kclmtr->getNwrgb(), whitespect->getNwhitespect());
    }

    //BlackCal - Cold
    QBlackMatrix* captureBlackLevel() {
        return new QBlackMatrix(_kclmtr->captureBlackLevel());
    }
    QBlackMatrix* recallFlashMatrix() {
        return new QBlackMatrix(_kclmtr->recallFlashMatrix());
    }

    //BlackCal - Hot
    QBlackMatrix* recallRAMMatrix() {
        return new QBlackMatrix(_kclmtr->recallRAMMatrix());
    }
    QBlackMatrix* recallCoefficientMatrix() {
        return new QBlackMatrix(_kclmtr->recallCoefficientMatrix());
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
        _kclmtr->closePort(resetThePortName);
        _isOpen = false;
        emit closed();
    }
    bool connect(QString *portName) {
        setPort(portName[0]);
        return connect();
    }

    void printMeasure(QMeasurement measure) {
        emit measured(measure);
    }
    void printFlicker(QFlicker flicker) {
        emit flickered(flicker);
    }

    //functions for GenDevice
    GenType getType() {
        return genTypeKClmtr;
    }


signals:
    void connected();
    void calfileChanged();
    /** @brief Sends out measurement
     *  @details You must Registring QMeasurement connect this singal to a slot.
     *  @details Here is an example:
     *  @details Header
     *  @snippet QKClmtrExample.cpp Header_measure
     *   Source
     *  @snippet QKClmtrExample.cpp Source_measure
     */
    void measured(QMeasurement measure);
    /** @brief Sends out flicker
     *  @details You must Registring QFlicker connect this singal to a slot.
     *  @details Here is an example:
     *  @details Header
     *  @snippet QKClmtrExample.cpp Header_flicker
     *   Source
     *  @snippet QKClmtrExample.cpp Source_flicker
     */
    void flickered(QFlicker flicker);

private:
    bool _isOpen;
    SubClass *_kclmtr;
};

#endif // QKCLMTR_H
