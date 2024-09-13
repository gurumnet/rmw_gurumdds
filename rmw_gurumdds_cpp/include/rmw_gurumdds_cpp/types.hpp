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

#ifndef RMW_GURUMDDS_CPP__TYPES_HPP_
#define RMW_GURUMDDS_CPP__TYPES_HPP_

#include <atomic>
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "rmw/ret_types.h"

#include "rmw_gurumdds_cpp/dds_include.hpp"
#include "rmw_gurumdds_cpp/visibility_control.h"

void on_participant_changed(
  const dds_DomainParticipant * a_participant,
  const dds_ParticipantBuiltinTopicData * data,
  dds_InstanceHandle_t handle);

void on_publication_changed(
  const dds_DomainParticipant * a_participant,
  const dds_PublicationBuiltinTopicData * data,
  dds_InstanceHandle_t handle);

void on_subscription_changed(
  const dds_DomainParticipant * a_participant,
  const dds_SubscriptionBuiltinTopicData * data,
  dds_InstanceHandle_t handle);

typedef struct _GurumddsWaitSetInfo
{
  dds_WaitSet * wait_set;
  dds_ConditionSeq * active_conditions;
  dds_ConditionSeq * attached_conditions;
} GurumddsWaitSetInfo;

typedef struct
{
  std::mutex mutex;
  rmw_event_callback_t callback {nullptr};
  const void * user_data {nullptr};
  // TODO: Consier putting this into GurumddsEventInfo
  // rmw_event_callback_t event_callback[RMW_EVENT_INVALID] = {nullptr};
  // const void * event_data[RMW_EVENT_INVALID] = {nullptr};
  // size_t event_unread_count[RMW_EVENT_INVALID] = {0};
} event_callback_data_t;

typedef struct _GurumddsEventInfo
{
  virtual ~_GurumddsEventInfo() = default;

  virtual rmw_ret_t get_status(rmw_event_type_t event_type, void * event) = 0;

  virtual dds_StatusCondition * get_status_condition() = 0;

  virtual dds_GuardCondition * get_guard_condition(rmw_event_type_t event_type) = 0;

  virtual bool is_status_changed(rmw_event_type_t event_type) = 0;

  virtual bool has_callback(rmw_event_type_t event_type) = 0;

  virtual rmw_ret_t set_on_new_event_callback(
    rmw_event_type_t event_type,
    const void * user_data,
    rmw_event_callback_t callback) = 0;

  virtual void update_inconsistent_topic(
    int32_t total_count,
    int32_t total_count_change
    ) = 0;

} GurumddsEventInfo;

typedef struct _GurumddsPublisherInfo : GurumddsEventInfo
{
  const rosidl_message_type_support_t * rosidl_message_typesupport;
  const char * implementation_identifier;
  rmw_context_impl_t * ctx;
  int64_t sequence_number;

  rmw_gid_t publisher_gid;
  dds_DataWriter * topic_writer;
  std::mutex mutex_event;
  rmw_event_callback_t on_new_event_cb[RMW_EVENT_INVALID] = { };
  const void * user_data_cb[RMW_EVENT_INVALID] = { };
  dds_GuardCondition* event_guard_cond[RMW_EVENT_INVALID] = { };
  dds_StatusMask mask = 0;
  bool inconsistent_topic_changed = false;
  dds_InconsistentTopicStatus inconsistent_topic_status = { };
  bool offered_deadline_missed_changed = false;
  dds_OfferedDeadlineMissedStatus offered_deadline_missed_status = { };
  bool offered_incompatible_qos_changed = false;
  dds_OfferedIncompatibleQosStatus offered_incompatible_qos_status = { };
  bool liveliness_lost_changed = false;
  dds_LivelinessLostStatus liveliness_lost_status = { };
  bool publication_matched_changed = false;
  dds_PublicationMatchedStatus publication_matched_status = { };
  dds_DataWriterListener topic_listener = { };

  rmw_ret_t get_status(rmw_event_type_t event_type, void * event) override;

  dds_StatusCondition * get_status_condition() override;

  dds_GuardCondition * get_guard_condition(rmw_event_type_t event_type) override;

  bool is_status_changed(rmw_event_type_t event_type) override;

  bool has_callback(rmw_event_type_t event_type) override;

  bool has_callback_unsafe(rmw_event_type_t event_type) const;

  rmw_ret_t set_on_new_event_callback(
    rmw_event_type_t event_type,
    const void * user_data,
    rmw_event_callback_t callback) override;

  void update_inconsistent_topic(
    int32_t total_count,
    int32_t total_count_change) override;

  void on_offered_deadline_missed(const dds_OfferedDeadlineMissedStatus & status);

  void on_offered_incompatible_qos(const dds_OfferedIncompatibleQosStatus & status);

  void on_liveliness_lost(const dds_LivelinessLostStatus & status);

  void on_publication_matched(const dds_PublicationMatchedStatus & status);
} GurumddsPublisherInfo;

typedef struct _GurumddsPublisherGID
{
  uint8_t publication_handle[16];
} GurumddsPublisherGID;

typedef struct _GurumddsSubscriberInfo : GurumddsEventInfo
{
  const rosidl_message_type_support_t * rosidl_message_typesupport;
  const char * implementation_identifier;
  rmw_context_impl_t * ctx;
  std::mutex mutex_event;
  rmw_event_callback_t on_new_event_cb[RMW_EVENT_INVALID] = { };
  const void * user_data_cb[RMW_EVENT_INVALID] = { };
  dds_GuardCondition* event_guard_cond[RMW_EVENT_INVALID] = { };
  dds_StatusMask mask = 0;
  bool requested_deadline_missed_changed = false;
  dds_RequestedDeadlineMissedStatus requested_deadline_missed_status = { };
  bool requested_incompatible_qos_changed = false;
  dds_RequestedIncompatibleQosStatus requested_incompatible_qos_status = { };
  bool inconsistent_topic_changed = false;
  dds_InconsistentTopicStatus inconsistent_topic_status = { };
  bool liveliness_changed = false;
  dds_LivelinessChangedStatus liveliness_changed_status = { };
  bool subscription_matched_changed = false;
  dds_SubscriptionMatchedStatus subscription_matched_status = { };
  bool sample_lost_changed = false;
  dds_SampleLostStatus sample_lost_status = { };

  rmw_gid_t subscriber_gid;
  dds_DataReader * topic_reader;
  dds_ReadCondition * read_condition;

  dds_DataReaderListener topic_listener;
  dds_DataSeq * data_seq;
  dds_SampleInfoSeq * info_seq;
  dds_UnsignedLongSeq * raw_data_sizes;
  event_callback_data_t event_callback_data;

  rmw_ret_t get_status(rmw_event_type_t event_type, void * event) override;

  dds_StatusCondition * get_status_condition() override;

  dds_GuardCondition * get_guard_condition(rmw_event_type_t event_type) override;

  bool is_status_changed(rmw_event_type_t event_type) override;

  bool has_callback(rmw_event_type_t event_type) override;

  bool has_callback_unsafe(rmw_event_type_t event_type) const;

  rmw_ret_t set_on_new_event_callback(
    rmw_event_type_t event_type,
    const void * user_data,
    rmw_event_callback_t callback) override;

  void update_inconsistent_topic(
    int32_t total_count,
    int32_t total_count_change) override;

  void on_requested_deadline_missed(const dds_RequestedDeadlineMissedStatus& status);

  void on_requested_incompatible_qos(const dds_RequestedIncompatibleQosStatus& status);

  void on_liveliness_changed(const dds_LivelinessChangedStatus& status);

  void on_subscription_matched(const dds_SubscriptionMatchedStatus& status);

  void on_sample_lost(const dds_SampleLostStatus& status);

  size_t count_unread();
} GurumddsSubscriberInfo;

typedef struct _GurumddsClientInfo
{
  const rosidl_service_type_support_t * service_typesupport;
  const char * implementation_identifier;
  rmw_context_impl_t * ctx;
  int64_t sequence_number;
  uint8_t writer_guid[16];

  rmw_gid_t publisher_gid;
  rmw_gid_t subscriber_gid;
  dds_DataWriter * request_writer;
  dds_DataReader * response_reader;
  dds_ReadCondition * read_condition;

  dds_DataReaderListener response_listener;
  dds_DataSeq * data_seq;
  dds_SampleInfoSeq * info_seq;
  dds_UnsignedLongSeq * raw_data_sizes;
  event_callback_data_t event_callback_data;

  size_t count_unread();
} GurumddsClientInfo;

typedef struct _GurumddsServiceInfo
{
  const rosidl_service_type_support_t * service_typesupport;
  const char * implementation_identifier;
  rmw_context_impl_t * ctx;

  rmw_gid_t publisher_gid;
  rmw_gid_t subscriber_gid;
  dds_DataWriter * response_writer;
  dds_DataReader * request_reader;
  dds_ReadCondition * read_condition;

  dds_DataReaderListener request_listener;
  dds_DataSeq * data_seq;
  dds_SampleInfoSeq * info_seq;
  dds_UnsignedLongSeq * raw_data_sizes;
  event_callback_data_t event_callback_data;

  size_t count_unread();
} GurumddsServiceInfo;

class GurumddsTopicEventListener {
public:
  static rmw_ret_t associate_listener(dds_Topic* topic);

  static rmw_ret_t disassociate_Listener(dds_Topic* topic);

  static void add_event(dds_Topic* topic, GurumddsEventInfo* event_info);

  static void remove_event(dds_Topic* topic, GurumddsEventInfo* event_info);

  void on_inconsistent_topic(const dds_InconsistentTopicStatus& status);

private:
  static void on_inconsistent_topic(const dds_Topic* the_topic, const dds_InconsistentTopicStatus* status);

private:
  static std::map<dds_Topic*, GurumddsTopicEventListener*> table_;
  static std::mutex mutex_table_;

  std::recursive_mutex mutex_;
  std::vector<GurumddsEventInfo*> event_list_;
};

#endif  // RMW_GURUMDDS_CPP__TYPES_HPP_
