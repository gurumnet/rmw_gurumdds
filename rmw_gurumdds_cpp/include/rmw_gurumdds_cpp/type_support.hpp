#ifndef RMW_GURUMDDS__TYPE_SUPPORT_HPP_
#define RMW_GURUMDDS__TYPE_SUPPORT_HPP_

#include <string>

#include "dds_include.hpp"
#include "rosidl_runtime_c/message_type_support_struct.h"
namespace rmw_gurumdds_cpp
{
dds_TypeSupport*
create_type_support_and_register(
  dds_DomainParticipant * participant,
  const rosidl_message_type_support_t * type_support,
  const std::string & type_name,
  const std::string & metastring);
}

#endif  // RMW_GURUMDDS__TYPE_SUPPORT_HPP_
