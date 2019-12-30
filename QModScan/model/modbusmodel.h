#ifndef MODBUSMODEL_H
#define MODBUSMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include "basedeviceconfig.h"

class ModbusModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ModbusModel(QObject* parent = nullptr);
    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;    
    void UpdateSize(int newSize);    


private:
    QVector<quint16> _data;
    BaseDeviceConfig* _deviceConfig;
};

#endif // MODBUSMODEL_H
