#ifndef TCPDEVICECONFIG_H
#define TCPDEVICECONFIG_H

#include "basedeviceconfig.h"
#include <QString>
#include <QModbusTcpClient>
#include <QVariant>

class TcpDeviceConfig : public BaseDeviceConfig
{
public:
    TcpDeviceConfig(QObject* pobj = nullptr);
    QString host() const;
    void setHost(const QString& host);

    unsigned int port() const;
    void setPort(unsigned int port);    

private:
    QString _host;
    unsigned int _port;
};

#endif // TCPDEVICECONFIG_H
