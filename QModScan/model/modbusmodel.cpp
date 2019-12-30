#include "modbusmodel.h"

ModbusModel::ModbusModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    //_data.fill(0, 10);
}

int ModbusModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

int ModbusModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return _data.size();
}

QVariant ModbusModel::data(const QModelIndex& index, int) const
{    
    if (!index.isValid())
        return QVariant();
    if (index.column() >= _data.size())
        return QVariant();
    return _data[index.column()];
}

bool ModbusModel::setData(const QModelIndex& index, const QVariant& value, int)
{
    if (!index.isValid())
        return true;
    if (index.column() >= _data.size())
        return true;
    _data[index.column()] = value.toUInt();
    return true;
}

void ModbusModel::UpdateSize(int newSize)
{
    beginResetModel();
    _data.resize(newSize);
    endResetModel();
}
