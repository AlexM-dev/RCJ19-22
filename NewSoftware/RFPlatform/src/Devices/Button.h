#pragma once

#include "../Defines.h"
#include "../Interfaces/IButton.h"

enum ButtonState {
    NOTHING, 
    CLICK,
    LONG_CLICK
};

class Button
{
private:
    uint8_t pin;
    int pressedTimes, id;
    bool pressed;
    IButton *interface;
    ButtonState state;

    void setState(ButtonState s)
    {
        state = s;
        if(interface != nullptr)
            interface->OnButtonClicked(this);
    }
    
public:
    Button(uint8_t p, int buttonID, IButton *iButton)
    {
        pin = p;
        pressedTimes = 0;
        id = buttonID;
        pressed = false;
        interface = iButton;
    }

    void update()
    {
        if(digitalRead(pin) == HIGH && !pressed)
        {
            pressed = true;
            pressedTimes = 0;
            state = NOTHING;
        } else if(digitalRead(pin) == HIGH && pressed)
        {
            pressedTimes++;
            state = NOTHING;
        } else if (digitalRead(pin) == LOW && pressed)
        {
            if(pressedTimes < (BUTTON_LONG_CLICK_DELAY / BUTTON_REFRESH_RATE))
                setState(CLICK);
            else
                setState(LONG_CLICK);
            pressed = false;
        }
    }

    ButtonState getState()
    {
        return state;
    }

    int getID()
    {
        return id;
    }
};