#ifndef PARADOXSHOOTER_H_
#define PARADOXSHOOTER_H_

#include "WPILib.h"


class ParadoxShooter
{
public:
        ParadoxShooter(UINT32 motor1, UINT32 tilt1, UINT32 encoa1, UINT32 encob1, UINT32 encoa2, UINT32 encob2, UINT32 limitr, UINT32 limitl);
        virtual ~ParadoxShooter() {}
        
        void Shoot(bool on);
        void FindTarget(bool stop);
        
protected:
        
       Victor *Shoot1;
       Victor   *Tilt;
       Encoder *ENCO1;
       Encoder *ENCO2;
       DigitalInput *LimitR;
       DigitalInput *LimitL;
        
private:
        DISALLOW_COPY_AND_ASSIGN(ParadoxShooter);
};

#endif
