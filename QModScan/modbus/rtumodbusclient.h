#ifndef RTUMODBUSCLIENT_H
#define RTUMODBUSCLIENT_H

#include "modbus/basemodbusclient.h"
#include "rtudeviceconfig.h"
#include "QModbusRtuSerialMaster"

class RtuModbusClient : public BaseModbusClient
{
public:
    explicit RtuModbusClient(RtuDeviceConfig* deviceConfig, QObject* pobj = nullptr);
    void updateDeviceConfig(BaseDeviceConfig* deviceConfig) override;
};

#endif // RTUMODBUSCLIENT_H
