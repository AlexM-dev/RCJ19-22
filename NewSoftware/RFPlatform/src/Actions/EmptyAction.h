#pragma once

#include "BaseAction.h"

class EmptyAction : public BaseAction
{
private:	

public:
	EmptyAction(ActionsController* cont) : BaseAction(cont)
	{

	};

	void onUpdate() override 
	{

	}

	void onStart() override 
	{

	}

	void onStop() override 
	{

	}

	void OnTimerEnd(Timer *timer)
	{
        
	}
};
