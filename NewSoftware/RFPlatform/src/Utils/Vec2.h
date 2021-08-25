#pragma once

#include <math.h>

#define	PI		3.141592654
#define	DEG(rad)	(rad*180.0/PI)
#define	RAD(deg)	(deg*PI/180.0)

class Vec2
{
public:
    float x, y;

    Vec2()
    {
        x = 0;
        y = 0;
    }

    Vec2(float angle, float speed)
    {
        x = speed * sin(RAD(angle));
		y = speed * cos(RAD(angle));
    }

    void setTo(Vec2 v)
    {
        x = v.x;
        y = v.y;
    }

    void sub(Vec2 v)
    {
        x -= v.x;
        y -= v.y;
    }

    void mult(Vec2 v)
    {
        x *= v.x;
        y *= v.y;
    }

    void add(Vec2 v)
    {
        x += v.x;
        y += v.y;
    }

    float getAngle() {
		return DEG(atan2(x , y));
	}

	float getSpeed() {
	    return sqrt((x * x) + (y * y));
	}

    void clear()
    {
        x = 0;
        y = 0;
    }
};
