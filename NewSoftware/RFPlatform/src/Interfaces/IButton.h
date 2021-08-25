#pragma once

class Button;
class IButton
{
public:
    virtual void OnButtonClicked(Button *button) = 0;
};
