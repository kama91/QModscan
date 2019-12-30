#ifndef BASEDEVICECONFIG_H
#define BASEDEVICECONFIG_H
#include <QString>
#include <QObject>
#include <QModbusClient>

class BaseDeviceConfig : public QObject
{
Q_OBJECT
public:
    explicit BaseDeviceConfig(QObject* pobj = nullptr);
    QString title() const;
    void setTitle(const QString &title);

    int pointAddress() const;
    void setPointAddress(int pointAddress);

    quint16 length() const;
    void setLength(quint16 length);

    unsigned int slave() const;
    void setSlave(unsigned int slave);

    int scanRate() const;
    void setScanRate(int scanRate);    

private:
    QString _title;
    int _scanRate;
    int _pointAddress;
    quint16 _length;
    unsigned int _slave; //todo rename this
};

#endif // BASEDEVICECONFIG_H
