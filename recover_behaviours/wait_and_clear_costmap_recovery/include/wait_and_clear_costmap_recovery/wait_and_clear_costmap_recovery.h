/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2009, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Author: Eitan Marder-Eppstein
*********************************************************************/
#ifndef WAIT_AND_CLEAR_COSTMAP_RECOVERY_H_
#define WAIT_AND_CLEAR_COSTMAP_RECOVERY_H_
#include <nav_core/recovery_behavior.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <tf/transform_listener.h>
#include <ros/ros.h>
#include <costmap_2d/costmap_layer.h>
#include <std_srvs/Trigger.h>


namespace wait_and_clear_costmap_recovery{
  /**
   * @class WaitAndClearCostmapRecovery
   * @brief A recovery behavior that wait for specified time and reverts the navigation stack's costmaps to the static map outside of a user-specified region.
   */
  class WaitAndClearCostmapRecovery : public nav_core::RecoveryBehavior {
    public:
      /**
       * @brief  Constructor, make sure to call initialize in addition to actually initialize the object
       * @param  
       * @return 
       */
      WaitAndClearCostmapRecovery();

      /**
       * @brief  Initialization function for the ClearCostmapRecovery recovery behavior
       * @param tf A pointer to a transform listener
       * @param global_costmap A pointer to the global_costmap used by the navigation stack 
       * @param local_costmap A pointer to the local_costmap used by the navigation stack 
       */
      void initialize(std::string name, tf2_ros::Buffer* tf,
          costmap_2d::Costmap2DROS* global_costmap, costmap_2d::Costmap2DROS* local_costmap);

      /**
       * @brief  Run the ClearCostmapRecovery recovery behavior. Wait and Reverts the
       * costmap to the static map outside of a user-specified window and
       * clears unknown space around the robot.
       */
      void runBehavior();

    private:
      void clear(costmap_2d::Costmap2DROS* costmap);
      void clearMap(boost::shared_ptr<costmap_2d::CostmapLayer> costmap, double pose_x, double pose_y);
      bool checkForObstacle(costmap_2d::Costmap2DROS* costmap);
      bool checkForObstacles(boost::shared_ptr<costmap_2d::CostmapLayer> costmap, double pose_x, double pose_y);
      bool runBehavior(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);

      ros::ServiceServer runBehaviorService;
      costmap_2d::Costmap2DROS* global_costmap_, *local_costmap_;
      std::string name_;
      tf2_ros::Buffer* tf_;
      bool initialized_;
      double reset_distance_;
      double wait_time_;
      double check_distance_;
      std::set<std::string> clearable_layers_; ///< Layer names which will be cleared.
  };
};
#endif  
