#pragma once

#include <WillowVox/events/Event.h>
#include <WillowVox/input/Key.h>

namespace WillowVox
{
    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(Key key) 
            : Event(Type::KeyPress), m_key(key) {}

        std::string ToString() const override { return "KeyPressEvent"; }
    
        Key m_key;
    };
}