#ifndef ANGLEUTILS_H
#define ANGLEUTILS_H

class AngleUtils {
    private:
    
    public:
        static int getFormatedAngle(int ang){
            while(ang > 180)
                ang-=360;
            while(ang < -180)
                ang+=360;
            return ang;
        }
};

#endif