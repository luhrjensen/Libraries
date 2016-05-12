#ifndef QKCLMTR_H
#define QKCLMTR_H

#include <QObject>
#include <QStringList>
#include "../kclmtr/KClmtr.h"

/** @ingroup wrappers
 *  @brief Wraps the Native object to work easly in Qt
 */
class QKClmtr : public QObject, public KClmtr {
    Q_OBJECT

public:
    QKClmtr(QObject *parent = 0) : QObject(parent) {
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
        if(_isOpen && !KClmtr::isPortOpen()) {
            _isOpen = false;
            emit closed();
        }
        return KClmtr::isPortOpen();
    }
    //Property - CalFiles
    QString getCalFileName() {
        return QString::fromStdString(KClmtr::getCalFileName());
    }
    int storeMatrices(int ID, const QString &Name, const wrgb &reference, const wrgb &kclmtr) {
        return KClmtr::storeMatrices(ID, Name.toStdString(), reference, kclmtr);
    }
    void setCalFileID(const int calFileID) {
        //will it really change
        if(getCalFileID() != calFileID) {
            KClmtr::setCalFileID(calFileID);
            emit calfileChanged();
        }
    }
    void setGamutSpec(const gamutSpec &gs) {
        KClmtr::setGamutSpec(gs);
        emit gamutSpecChanged();
    }

    QStringList getCalFileList() {
        QStringList CalList;
        const string *calList  = KClmtr::getCalFileList();
        for(int i = 0; i < 97;  i++) {
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
        string stdModel;
        string stdSN;
        int err = KClmtr::testConnection(portName.toStdString(), stdModel, stdSN);
        model = QString::fromStdString(stdModel);
        SN = QString::fromStdString(stdSN);
        return err;
    }

    void closePort() {
        KClmtr::closePort();
        _isOpen = false;
        emit closed();
    }
    void printMeasure(Measurement measure) {
        emit measured(measure);
    }
    void printFlicker(Flicker flicker) {
        emit flickered(flicker);
    }
    int sendMessageToKColorimeter(const QString &strMsg, int expected, int timeOut_Sec, QString &readString) {
        string stdString;
        int err = KClmtr::sendMessageToKColorimeter(strMsg.toStdString(), expected, timeOut_Sec, stdString);
        readString = QString::fromStdString(stdString);
        return err;
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
