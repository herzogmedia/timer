////////////////////////////////////////////////////////////////////////////////
#include "eventreader.hpp"
#include "sectionreader.hpp"
#include "error.hpp"

#include <QDate>
#include <QFile>

////////////////////////////////////////////////////////////////////////////////
static inline QDate to_date(const QString& string)
{
    return QDate::fromString(string, "MMM d yyyy");
}

////////////////////////////////////////////////////////////////////////////////
static inline QString value(const QXmlStreamAttributes& attrs, const QString& name)
{
    return attrs.value(name).toString();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Event EventReader::read(const QString& filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)) throw XmlError(file.errorString());

    Event event = EventReader::read(&file);
    if(file.error()) throw XmlError(file.errorString());

    return event;
}

////////////////////////////////////////////////////////////////////////////////
Event EventReader::read(QIODevice* device)
{
    QXmlStreamReader reader(device);

    Event event = EventReader::read(reader);
    if(reader.error()) throw XmlError(reader.errorString());

    return event;
}

////////////////////////////////////////////////////////////////////////////////
Event EventReader::read(QXmlStreamReader& reader)
{
    ////////////////////
    // Event format:
    //   <event name="foo">
    //     <section name="bar" duration="x:xx:xx"/>
    //     ...
    //   </event>

    ////////////////////
    // fast forward until opening tag
    if(reader.tokenType() != QXmlStreamReader::StartElement)
        reader.readNextStartElement();

    ////////////////////
    // check opening tag
    if(reader.tokenType() != QXmlStreamReader::StartElement
    || reader.name() != "event")
    throw XmlError("Expecting event start element");

    ////////////////////
    // get event name
    Event event;
    auto attrs = reader.attributes();

    if(!attrs.hasAttribute("name")) throw XmlError("Missing name attribute");
    event.set_name(value(attrs, "name"));

    if(!attrs.hasAttribute("date")) throw XmlError("Missing date attribute");
    event.set_date(to_date(value(attrs, "date")));

    ////////////////////
    // read sections
    while(reader.readNextStartElement())
        event.insert(SectionReader::read(reader));

    ////////////////////
    // check closing tag
    reader.readElementText();

    if(reader.tokenType() != QXmlStreamReader::EndElement
    || reader.name() != "event")
    throw XmlError("Expecting event end element");

    return event;
}
