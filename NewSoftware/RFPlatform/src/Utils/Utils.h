#ifndef UTILS_H
#define UTILS_H

class Utils {
    private:
    
    public:
        static float getFormatedAngle(float ang)
        {
            while(ang > 180)
                ang-=360;
            while(ang < -180)
                ang+=360;
            return ang;
        }

        static int limitValue(int value, int minLimit, int maxLimit)
        {
            if(value > maxLimit)
                value = maxLimit;
            if(value < minLimit)
                value = minLimit;
            return value;
        }

        static int mirroredValueLimit(int value, int minLimit, int maxLimit)
        {
            if (value > maxLimit)
                value = maxLimit;
            if (value < -maxLimit)
                value = -maxLimit;
            if (value > 0 && value < minLimit)
                value = minLimit;
            if (value < 0 && value > -minLimit)
                value = -minLimit;
            return value;
        }
};

#endif