/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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
#include "modules/localization/msf/local_map/pyramid_map/pyramid_map_node_config.h"

namespace apollo {
namespace localization {
namespace msf {

PyramidMapNodeConfig::PyramidMapNodeConfig() {}

PyramidMapNodeConfig::~PyramidMapNodeConfig() {}

std::shared_ptr<BaseMapNodeConfig> PyramidMapNodeConfig::Clone() {
  std::shared_ptr<PyramidMapNodeConfig> map_node_config(new PyramidMapNodeConfig());
  map_node_config->node_index_ = node_index_;
  map_node_config->map_version_ = map_version_;
  memcpy(map_node_config->body_md5_, body_md5_, sizeof(body_md5_));
  map_node_config->body_size_ = body_size_;
  map_node_config->has_map_version_ = has_map_version_;
  map_node_config->has_body_md5_ = has_body_md5_;

  return std::dynamic_pointer_cast<BaseMapNodeConfig>(map_node_config);
}

}  // namespace msf
}  // namespace localization
}  // namespace apollo
