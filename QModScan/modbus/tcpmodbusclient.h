#ifndef TCPMODBUSCLIENT_H
#define TCPMODBUSCLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include "modbus/basemodbusclient.h"
#include "tcpdeviceconfig.h"

class TcpModbusClient: public BaseModbusClient
{
    Q_OBJECT
public:
    explicit TcpModbusClient(TcpDeviceConfig* deviceConfig, QObject* parent = nullptr);
    void updateDeviceConfig(BaseDeviceConfig* deviceConfig) override;
};

#endif // TCPMODBUSCLIENT_H
