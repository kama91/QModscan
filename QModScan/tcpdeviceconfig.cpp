#include "tcpdeviceconfig.h"

TcpDeviceConfig::TcpDeviceConfig(QObject* pobj): BaseDeviceConfig (pobj)
{

}

QString TcpDeviceConfig::host() const
{
    return _host;
}

void TcpDeviceConfig::setHost(const QString &host)
{
    _host = host;
}

unsigned int TcpDeviceConfig::port() const
{
    return _port;
}

void TcpDeviceConfig::setPort(unsigned int port)
{
    _port = port;
}
