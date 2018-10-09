/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "modules/planning/proto/pad_msg.pb.h"

#include "modules/planning/common/frame.h"
#include "modules/planning/planner/navi_planner_dispatcher.h"
#include "modules/planning/planner/planner_dispatcher.h"
#include "modules/planning/planning_base.h"

/**
 * @namespace apollo::planning
 * @brief apollo::planning
 */
namespace apollo {
namespace planning {

/**
 * @class planning
 *
 * @brief Planning module main class. It processes GPS and IMU as input,
 * to generate planning info.
 */
class NaviPlanning : public PlanningBase {
 public:
  NaviPlanning() {
    planner_dispatcher_ = std::make_unique<NaviPlannerDispatcher>();
  }
  virtual ~NaviPlanning();

  /**
   * @brief Planning algorithm name.
   */
  std::string Name() const override;

  /**
   * @brief module initialization function
   * @return initialization status
   */
  apollo::common::Status Init() override;

  /**
   * @brief main logic of the planning module, runs periodically triggered by
   * timer.
   */
  void RunOnce(const LocalView& local_view,
               ADCTrajectory* const trajectory_pb) override;


  apollo::common::Status Plan(
      const double current_time_stamp,
      const std::vector<common::TrajectoryPoint>& stitching_trajectory,
      ADCTrajectory* const trajectory) override;

 private:
  common::Status InitFrame(const uint32_t sequence_num,
                           const common::TrajectoryPoint& planning_start_point,
                           const double start_time,
                           const common::VehicleState& vehicle_state);

  bool CheckPlanningConfig();

  /**
   * @brief receiving planning pad message
   */
  void OnPad(const PadMessage& pad);

  /**
   * @brief make driving decisions by received planning pad msg
   */
  void ProcessPadMsg(DrivingAction drvie_action);

  /**
   * @brief get the lane Id of the lane in which the vehicle is located
   */
  std::string GetCurrentLaneId();

  /**
   * @brief get the left neighbors lane info of the lane which the vehicle is
   *located
   * @lane_info_group output left neighors info which sorted from near to
   *far
   */
  void GetLeftNeighborLanesInfo(
      std::vector<std::pair<std::string, double>>* const lane_info_group);

  /**
   * @brief get the right neighbors lane of the lane which the vehicle is
   * located
   * @lane_info_group output right neighors info which sorted from near to
   *far
   */
  void GetRightNeighborLanesInfo(
      std::vector<std::pair<std::string, double>>* const lane_info_group);

  void ExportReferenceLineDebug(planning_internal::Debug* debug);

  class VehicleConfig {
   public:
    double x_ = 0.0;
    double y_ = 0.0;
    double theta_ = 0.0;
    bool is_valid_ = false;
  };
  VehicleConfig last_vehicle_config_;

  VehicleConfig ComputeVehicleConfigFromLocalization(
      const localization::LocalizationEstimate& localization) const;

  std::string target_lane_id_;
  DrivingAction driving_action_;
  bool is_received_pad_msg_ = false;

  std::unique_ptr<Frame> frame_;

  std::unique_ptr<ReferenceLineProvider> reference_line_provider_;

  std::unique_ptr<PlannerDispatcher> planner_dispatcher_;
};

}  // namespace planning
}  // namespace apollo
