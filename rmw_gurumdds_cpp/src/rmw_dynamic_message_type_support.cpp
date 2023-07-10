// Copyright 2019 GurumNetworks, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rmw_gurumdds_cpp/rmw_dynamic_message_type_support.hpp"

#include "rcutils/allocator.h"
#include "rcutils/env.h"
#include "rcutils/filesystem.h"
#include "rcutils/format_string.h"

extern "C"
{
rmw_ret_t 
rmw_serialization_support_init(
    const char* serialization_lib_name,
    rcutils_allocator_t* allocator,
    rosidl_dynamic_typesupport_serialization_support_t
    *serialization_support)
    {
        static_cast<void>(serialization_lib_name);
        static_cast<void>(allocator);
        static_cast<void>(serialization_support);

        RMW_SET_ERROR_MSG("rmw_serialization_support_init: unimplemented");
        return RMW_RET_UNSUPPORTED;
    }

rmw_ret_t rmw_take_dynamic_message(
        const rmw_subscription_t * subscription,
        rosidl_dynamic_typesupport_dynamic_data_t * dynamic_message,
        bool* taken,
        rmw_subscription_allocation_t * allocation)
    {
        static_cast<void>(subscription);
        static_cast<void>(dynamic_message);
        static_cast<void>(taken);
        static_cast<void>(allocation);

        RMW_SET_ERROR_MSG("rmw_take_dynamic_message: unimplemented");
        return RMW_RET_UNSUPPORTED;
    }

rmw_ret_t rmw_take_dynamic_message_with_info(
  const rmw_subscription_t * subscription,
  rosidl_dynamic_typesupport_dynamic_data_t * dynamic_message,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation)
{
  static_cast<void>(subscription);
  static_cast<void>(dynamic_message);
  static_cast<void>(taken);
  static_cast<void>(message_info);
  static_cast<void>(allocation);

  RMW_SET_ERROR_MSG("rmw_take_dynamic_message_with_info: unimplemented");
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_get_serialization_support(
  const char * serialization_lib_name,
  rosidl_dynamic_typesupport_serialization_support_t ** serialization_support)
{
  static_cast<void>(serialization_lib_name);
  static_cast<void>(serialization_support);

  RMW_SET_ERROR_MSG("rmw_get_serialization_support: unimplemented");
  return RMW_RET_UNSUPPORTED;
}
}







