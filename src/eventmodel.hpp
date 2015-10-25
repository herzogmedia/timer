////////////////////////////////////////////////////////////////////////////////
#ifndef EVENTMODEL_HPP
#define EVENTMODEL_HPP

#include "event.hpp"

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QVariant>

////////////////////////////////////////////////////////////////////////////////
class EventModel : public QAbstractTableModel
{
public:
    explicit EventModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    ////////////////////
    void clear();
    void open(QString filename);
    void save();
    void save_as(QString filename);

    ////////////////////
    static EventModel* get_model();

private:
    Event _event;
    QString _filename;
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENTMODEL_HPP
