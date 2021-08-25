#pragma once

#include "../Interfaces/IButton.h"
#include "../Defines.h"
#include "Button.h"

class ButtonsController
{
private:
    Button *buttons[ BUTTONS_COUNT ];
    unsigned long long prev;
public:
    ButtonsController(IButton *iButton)
    {
        buttons[ BUTTON1_ID ] = new Button( A10, BUTTON1_ID, iButton );

        prev = millis();
    }
    ~ButtonsController()
    {
        for(int i = 0; i < BUTTONS_COUNT; ++i)
            delete buttons[i];
    }

    void update()
    {
        if(millis() - prev >= BUTTON_REFRESH_RATE)
        {   
            for(int i = 0; i < BUTTONS_COUNT; ++i)
                if(buttons[i] != nullptr)
                    buttons[i]->update();
            prev = millis();
        }
    }
};
