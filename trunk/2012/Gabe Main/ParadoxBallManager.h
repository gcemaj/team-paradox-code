#ifndef PARADOXSBALLMANAGER_H_
#define PARADOXBALLMANAGER_H_

#include "WPILib.h"


class ParadoxBallManager
{
public:
        ParadoxBallManager(UINT32 store, UINT32 feedball);
        virtual ~ParadoxBallManager() {}
        
        void Storage(bool storage);
        void FeedToShoot(bool feed, bool rev);
        
protected:
       Relay 	 	 *Sucker;
       Relay		  *Spine;
       CANJaguar	   *Feed; 
       
private:
        DISALLOW_COPY_AND_ASSIGN(ParadoxBallManager);
};

#endif