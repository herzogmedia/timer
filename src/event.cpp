////////////////////////////////////////////////////////////////////////////////
#include "event.hpp"

////////////////////////////////////////////////////////////////////////////////
Event::Event(QString name, QDate date)
{
    set_name(std::move(name));
    set_date(std::move(date));
    reset();
}

////////////////////////////////////////////////////////////////////////////////
const Duration Event::duration() const
{
    Duration duration { 0 };

    for(const auto& section : _sections) duration += section.duration();
    return duration;
}

////////////////////////////////////////////////////////////////////////////////
void Event::reset()
{
    _current = none;
    for(auto& section : _sections) section.reset();
}

////////////////////////////////////////////////////////////////////////////////
void Event::next()
{
    if(current() < size())
    {
        _sections.at(current()).end();
        if(++_current < size()) _sections.at(current()).start();
    }
}

////////////////////////////////////////////////////////////////////////////////
const Duration Event::overage() const
{
    Duration overage { 0 };

    for(const auto& section : _sections) overage += section.overage();
    return overage;
}
