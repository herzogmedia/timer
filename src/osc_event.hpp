////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_EVENT_HPP
#define OSC_EVENT_HPP

////////////////////////////////////////////////////////////////////////////////
#include "osc_listener.hpp"

#include <QObject>
#include <QString>

////////////////////////////////////////////////////////////////////////////////
namespace Osc
{

////////////////////////////////////////////////////////////////////////////////
class Event : public QObject
{
    Q_OBJECT

public:
    ////////////////////
    enum Status { Started, Stopped, Reset };

    ////////////////////
    explicit Event(QObject* parent = nullptr);

signals:
    ////////////////////
    void status_changed(Status);

private:
    ////////////////////
    void proc_message(const QString& addr, const QList<QVariant>& args);

    const QString _addr_status;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif // OSC_EVENT_HPP