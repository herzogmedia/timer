////////////////////////////////////////////////////////////////////////////////
#ifndef EVENTWRITER_HPP
#define EVENTWRITER_HPP

#include "event.hpp"
#include <QXmlStreamWriter>

////////////////////////////////////////////////////////////////////////////////
class EventWriter
{
public:
    static void write(QXmlStreamWriter&, const Event&);
};

////////////////////////////////////////////////////////////////////////////////
#endif // EVENTWRITER_HPP
