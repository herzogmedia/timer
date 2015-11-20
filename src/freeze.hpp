////////////////////////////////////////////////////////////////////////////////
#ifndef FREEZE_HPP
#define FREEZE_HPP

////////////////////////////////////////////////////////////////////////////////
class FreezingWidget
{
public:
    ////////////////////
    class Freeze
    {
    public:
        explicit Freeze(FreezingWidget* widget) : _widget(widget) { _widget->_frozen = true; }
        ~Freeze() { _widget->_frozen = false; }

    private:
        FreezingWidget* _widget;
    };

protected:
    bool _frozen = false;
};

////////////////////////////////////////////////////////////////////////////////
#endif // FREEZE_HPP

