// Copyright 2022 GurumNetworks, Inc.
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

#include <rcutils/allocator.h>

#include "rcutils/allocator.h"
#include "rcutils/env.h"
#include "rcutils/filesystem.h"
#include "rcutils/format_string.h"
#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/rmw.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rmw_gurumdds_cpp/dds_include.hpp"
#include "rmw_gurumdds_cpp/event_converter.hpp"
#include "rmw_gurumdds_cpp/types.hpp"
#include "rmw_gurumdds_cpp/dds_include.hpp"


#ifndef RMW_GURUMDDS_CPP__DYNAMIC_MESSAGE_TYPE_SUPPORT_HPP_
#define RMW_GURUMDDS_CPP__DYNAMIC_MESSAGE_TYPE_SUPPORT_HPP_

extern "C"
{
rmw_ret_t 
rmw_serialization_support_init(
    const char* serialization_lib_name,
    rcutils_allocator_t* allocator,
    rosidl_dynamic_typesupport_serialization_support_t
    *serialization_support);



rmw_ret_t rmw_take_dynamic_message(
        const rmw_subscription_t * subscription,
        rosidl_dynamic_typesupport_dynamic_data_t * dynamic_message,
        bool* taken,
        rmw_subscription_allocation_t * allocation);

rmw_ret_t rmw_take_dynamic_message_with_info(
  const rmw_subscription_t * subscription,
  rosidl_dynamic_typesupport_dynamic_data_t * dynamic_message,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation);


rmw_ret_t rmw_get_serialization_support(
  const char * serialization_lib_name,
  rosidl_dynamic_typesupport_serialization_support_t ** serialization_support);

}

#endif  // RMW_GURUMDDS_CPP__DYNAMIC_MESSAGE_TYPE_SUPPORT_HPP_
