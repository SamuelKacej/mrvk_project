//
// Created by matejko on 18.3.2019.
//

#ifndef PROJECT_MRVKCONTROLLBUTTONS_H
#define PROJECT_MRVKCONTROLLBUTTONS_H

#include <ros/ros.h>
#include <exception>

namespace mrvk_gui {
    class MrvkControllButtons {
    public:
        MrvkControllButtons();
        void setCentralStop();
        void resetCentralStop();
        void blockMovement();
        void unblockMovement();
        void autoComputeGPS();

    private:
        ros::ServiceClient setCentralStopServiceClient;
        ros::ServiceClient resetCentralStopServiceClient;
        ros::ServiceClient blockMovementServiceClient;
        ros::ServiceClient unblockMovementServiceClient;
        ros::ServiceClient autoComputeGPSServiceClient;
    };
}

#endif //PROJECT_MRVKCONTROLLBUTTONS_H
