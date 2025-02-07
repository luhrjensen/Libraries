#ifndef QKCLMTR_H
#define QKCLMTR_H

#include <QObject>
#include <QStringList>
#include "../kclmtr/KClmtr.h"

using namespace KClmtrBase;
using namespace KClmtrNative;
/**
 *  @brief Wraps the Native object to work easly in Qt
 */
class QKClmtr : public QObject, public KClmtr {
    Q_OBJECT

public:
    QKClmtr(QObject *parent = 0) : QObject(parent), KClmtr() {
        _isOpen = false;
    }

    //Property
    QString getPort() {
        return QString::fromStdString(KClmtr::getPort());
    }
    void setPort(const QString &value) {
        KClmtr::setPort(value.toStdString());
    }
    QString getSerialNumber() {
        return QString::fromStdString(KClmtr::getSerialNumber());
    }
    QString getModel() {
        return QString::fromStdString(KClmtr::getModel());
    }
    bool isPortOpen() {
        bool isOpen = KClmtr::isPortOpen();
        if(_isOpen && !isOpen) {
            _isOpen = false;
            emit closed();
        }
        return isOpen;
    }
    //Property - CalFiles
    QString getCalFileName() {
        return QString::fromStdString(KClmtr::getCalFileName());
    }
    int storeMatrices(int ID, const QString &Name, const WRGB &reference, const WRGB &kclmtr) {
        return KClmtr::storeMatrices(ID, Name.toStdString(), reference, kclmtr);
    }
    int storeMatrices(int ID, const QString &Name, const CorrectedCoefficient &CorrectionMatrix) {
        return KClmtr::storeMatrices(ID, Name.toStdString(), CorrectionMatrix);
    }
    int deleteCalFile(const int calFileID) {
        int oldID = getCalFileID();
        int returnVaule = KClmtr::deleteCalFile(calFileID);
        if(oldID == calFileID) {
            emit calfileChanged();
        }
        return returnVaule;
    }

    void setCalFileID(const int calFileID) {
        //will it really change
        if(getCalFileID() != calFileID) {
            KClmtr::setCalFileID(calFileID);
            emit calfileChanged();
        }
    }
    void setGamutSpec(const GamutSpec &gs) {
        KClmtr::setGamutSpec(gs);
        emit gamutSpecChanged();
    }

    QStringList getCalFileList() {
        QStringList CalList;
        std::vector<std::string> calList  = KClmtr::getCalFileList();
        for(size_t i = 0; i < calList.size();  i++) {
            CalList << QString::fromStdString(calList[i]);
        }
        return CalList;
    }
    //setup/Close
    bool connect(const QString &portName) {
        setPort(portName);
        return connect();
    }
    bool connect() {
        if(KClmtr::connect()) {
            _isOpen = true;
            emit connected();
            return true;
        } else {
            _isOpen = false;
            return false;
        }
    }
    static bool testConnection(const QString &portName, QString &model, QString &SN) {
        std::string stdModel;
        std::string stdSN;
        bool connected = KClmtr::testConnection(portName.toStdString(), stdModel, stdSN);
        model = QString::fromStdString(stdModel);
        SN = QString::fromStdString(stdSN);
        return connected;
    }

    void closePort() {
        if(_isOpen) {
            KClmtr::closePort();
            _isOpen = false;
            emit closed();
        }
    }
    void printMeasure(Measurement measure) {
        emit measured(measure);
    }
    void printFlicker(Flicker flicker) {
        emit flickered(flicker);
    }
    int sendMessageToKColorimeter(const std::string &strMsg, int expected, int timeOut_Sec, std::string &readString) {
        return KClmtr::sendMessageToKColorimeter(strMsg, expected, timeOut_Sec, readString);
    }

private:
    bool _isOpen;

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
