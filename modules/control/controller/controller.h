/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
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

/**
 * @file
 * @brief Defines the Controller base class.
 */

#pragma once

#include <cmath>
#include <string>

#include "modules/control/proto/control_cmd.pb.h"
#include "modules/control/proto/control_conf.pb.h"
#include "modules/localization/proto/localization.pb.h"
#include "modules/planning/proto/planning.pb.h"

#include "modules/common/status/status.h"

/**
 * @namespace apollo::control
 * @brief apollo::control
 */
namespace apollo {
namespace control {

/**
 * @class Controller
 *
 * @brief base class for all controllers.
 */
class Controller {
 public:
  /**
   * @brief constructor
   */
  Controller() = default;

  /**
   * @brief destructor
   */
  virtual ~Controller() = default;

  /**
   * @brief initialize Controller
   * @param control_conf control configurations
   * @return Status initialization status
   */
  virtual common::Status Init(const ControlConf *control_conf) = 0;

  /**
   * @brief compute control command based on current vehicle status
   *        and target trajectory
   * @param localization vehicle location
   * @param chassis vehicle status e.g., speed, acceleration
   * @param trajectory trajectory generated by planning
   * @param cmd control command
   * @return Status computation status
   */
  virtual common::Status ComputeControlCommand(
      const localization::LocalizationEstimate *localization,
      const canbus::Chassis *chassis, const planning::ADCTrajectory *trajectory,
      control::ControlCommand *cmd) = 0;

  /**
   * @brief reset Controller
   * @return Status reset status
   */
  virtual common::Status Reset() = 0;

  /**
   * @brief controller name
   * @return string controller name in string
   */
  virtual std::string Name() const = 0;

  /**
   * @brief stop controller
   */
  virtual void Stop() = 0;
};

}  // namespace control
}  // namespace apollo
