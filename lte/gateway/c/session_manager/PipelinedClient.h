/**
 * Copyright 2020 The Magma Authors.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <mutex>
#include <unordered_map>

#include <lte/protos/policydb.pb.h>
#include <lte/protos/pipelined.grpc.pb.h>
#include <lte/protos/pipelined.pb.h>
#include <lte/protos/subscriberdb.pb.h>

#include "GRPCReceiver.h"
#include "SessionState.h"

#define M5G_MIN_TEID (UINT32_MAX / 2)

using grpc::Status;

namespace magma {
using namespace lte;
using std::experimental::optional;

/**
 * PipelinedClient is the base class for managing rules and their activations.
 * The class is intended on interfacing with the data pipeline to enforce rules.
 */
class PipelinedClient {
 public:
  virtual ~PipelinedClient() = default;

  /**
   * Activates all rules for provided SessionInfos
   * @param infos - list of SessionInfos to setup flows for
   */
  virtual void setup_cwf(
      const std::vector<SessionState::SessionInfo>& infos,
      const std::vector<SubscriberQuotaUpdate>& quota_updates,
      const std::vector<std::string> ue_mac_addrs,
      const std::vector<std::string> msisdns,
      const std::vector<std::string> apn_mac_addrs,
      const std::vector<std::string> apn_names,
      const std::vector<std::uint64_t> pdp_start_times,
      const std::uint64_t& epoch,
      std::function<void(Status status, SetupFlowsResult)> callback) = 0;

  /**
   * Activates all rules for provided SessionInfos
   * @param infos - list of SessionInfos to setup flows for
   */
  virtual void setup_lte(
      const std::vector<SessionState::SessionInfo>& infos,
      const std::uint64_t& epoch,
      std::function<void(Status status, SetupFlowsResult)> callback) = 0;

  /**
   * Deactivate all flows for the specified rules plus any drop default rule
   * added by pipelined
   * @param imsi - UE to delete flows for
   * @param rule_ids - rules to deactivate
   */
  virtual void deactivate_flows_for_rules_for_termination(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const RequestOriginType_OriginType origin_type) = 0;

  /**
   * Deactivate all flows for the specified rules
   * @param imsi - UE to delete flows for
   * @param rule_ids - rules to deactivate
   */
  virtual void deactivate_flows_for_rules(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const RulesToProcess to_process,
      const RequestOriginType_OriginType origin_type) = 0;

  /**
   * Activate all rules for the specified rules, using a normal vector
   */
  virtual void activate_flows_for_rules(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const std::string& msisdn, const optional<AggregatedMaximumBitrate>& ambr,
      const RulesToProcess to_process,
      std::function<void(Status status, ActivateFlowsResult)> callback) = 0;

  /**
   * Send the MAC address of UE and the subscriberID
   * for pipelined to add a flow for the subscriber by matching the MAC
   */
  virtual void add_ue_mac_flow(
      const SubscriberID& sid, const std::string& ue_mac_addr,
      const std::string& msisdn, const std::string& ap_mac_addr,
      const std::string& ap_name,
      std::function<void(Status status, FlowResponse)> callback) = 0;

  /**
   * Update the IPFIX export rule in pipeliend
   */
  virtual void update_ipfix_flow(
      const SubscriberID& sid, const std::string& ue_mac_addr,
      const std::string& msisdn, const std::string& ap_mac_addr,
      const std::string& ap_name, const uint64_t& pdp_start_time) = 0;

  /**
   * Send the MAC address of UE and the subscriberID
   * for pipelined to delete a flow for the subscriber by matching the MAC
   */
  virtual void delete_ue_mac_flow(
      const SubscriberID& sid, const std::string& ue_mac_addr) = 0;

  /**
   * Propagate whether a subscriber has quota / no quota / or terminated
   */
  virtual void update_subscriber_quota_state(
      const std::vector<SubscriberQuotaUpdate>& updates) = 0;

  /**
   * Activate the GY final action policy
   */
  virtual void add_gy_final_action_flow(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const std::string& msisdn, const RulesToProcess to_process) = 0;

  /**
   * Set up a Session of type SetMessage to be sent to UPF
   */
  virtual void set_upf_session(
      const SessionState::SessionInfo info,
      std::function<void(Status status, UPFSessionContextState)> callback) = 0;

  virtual uint32_t get_next_teid()    = 0;
  virtual uint32_t get_current_teid() = 0;
};

/**
 * AsyncPipelinedClient implements PipelinedClient but sends calls
 * asynchronously to pipelined.
 */
class AsyncPipelinedClient : public GRPCReceiver, public PipelinedClient {
 public:
  AsyncPipelinedClient();

  AsyncPipelinedClient(std::shared_ptr<grpc::Channel> pipelined_channel);

  /**
   * Activates all rules for provided SessionInfos
   * @param infos - list of SessionInfos to setup flows for
   * @return true if the operation was successful
   */
  void setup_cwf(
      const std::vector<SessionState::SessionInfo>& infos,
      const std::vector<SubscriberQuotaUpdate>& quota_updates,
      const std::vector<std::string> ue_mac_addrs,
      const std::vector<std::string> msisdns,
      const std::vector<std::string> apn_mac_addrs,
      const std::vector<std::string> apn_names,
      const std::vector<std::uint64_t> pdp_start_times,
      const std::uint64_t& epoch,
      std::function<void(Status status, SetupFlowsResult)> callback);

  /**
   * Activates all rules for provided SessionInfos
   * @param infos - list of SessionInfos to setup flows for
   */
  void setup_lte(
      const std::vector<SessionState::SessionInfo>& infos,
      const std::uint64_t& epoch,
      std::function<void(Status status, SetupFlowsResult)> callback);

  /**
   * Deactivate all flows related to a specific charging key plus any default
   * rule installed by pipelined. Used for session termination.
   * @param imsi - UE to delete flows for
   * @param charging_key - key to deactivate
   */
  void deactivate_flows_for_rules_for_termination(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const RequestOriginType_OriginType origin_type);

  /**
   * Deactivate all flows related to a specific charging key
   * @param imsi - UE to delete flows for
   * @param charging_key - key to deactivate
   */
  void deactivate_flows_for_rules(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const RulesToProcess to_process,
      const RequestOriginType_OriginType origin_type);

  /**
   * Deactivate all flows included on the request
   * @param request
   */
  void deactivate_flows(DeactivateFlowsRequest& request);

  /**
   * Activate all rules for the specified rules, using a normal vector
   */
  void activate_flows_for_rules(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const std::string& msisdn, const optional<AggregatedMaximumBitrate>& ambr,
      const RulesToProcess to_process,
      std::function<void(Status status, ActivateFlowsResult)> callback);

  /**
   * Send the MAC address of UE and the subscriberID
   * for pipelined to add a flow for the subscriber by matching the MAC
   */
  void add_ue_mac_flow(
      const SubscriberID& sid, const std::string& ue_mac_addr,
      const std::string& msisdn, const std::string& ap_mac_addr,
      const std::string& ap_name,
      std::function<void(Status status, FlowResponse)> callback);

  /**
   * Update the IPFIX export rule in pipeliend
   */
  void update_ipfix_flow(
      const SubscriberID& sid, const std::string& ue_mac_addr,
      const std::string& msisdn, const std::string& ap_mac_addr,
      const std::string& ap_name, const uint64_t& pdp_start_time);

  /**
   * Propagate whether a subscriber has quota / no quota / or terminated
   */
  void update_subscriber_quota_state(
      const std::vector<SubscriberQuotaUpdate>& updates);

  void delete_ue_mac_flow(
      const SubscriberID& sid, const std::string& ue_mac_addr);

  void add_gy_final_action_flow(
      const std::string& imsi, const std::string& ip_addr,
      const std::string& ipv6_addr, const Teids teids,
      const std::string& msisdn, const RulesToProcess to_process);

  void set_upf_session(
      const SessionState::SessionInfo info,
      std::function<void(Status status, UPFSessionContextState)> callback);

  void handle_add_ue_mac_callback(
      const magma::UEMacFlowRequest req, const int retries, Status status,
      FlowResponse resp);

  uint32_t get_next_teid();
  uint32_t get_current_teid();

 private:
  static const uint32_t RESPONSE_TIMEOUT = 6;  // seconds
  std::unique_ptr<Pipelined::Stub> stub_;
  uint32_t teid;

 private:
  void setup_default_controllers_rpc(
      const SetupDefaultRequest& request,
      std::function<void(Status, SetupFlowsResult)> callback);

  void setup_policy_rpc(
      const SetupPolicyRequest& request,
      std::function<void(Status, SetupFlowsResult)> callback);

  void setup_ue_mac_rpc(
      const SetupUEMacRequest& request,
      std::function<void(Status, SetupFlowsResult)> callback);

  void deactivate_flows_rpc(
      const DeactivateFlowsRequest& request,
      std::function<void(Status, DeactivateFlowsResult)> callback);

  void activate_flows_rpc(
      const ActivateFlowsRequest& request,
      std::function<void(Status, ActivateFlowsResult)> callback);

  void add_ue_mac_flow_rpc(
      const UEMacFlowRequest& request,
      std::function<void(Status, FlowResponse)> callback);

  void update_ipfix_flow_rpc(
      const UEMacFlowRequest& request,
      std::function<void(Status, FlowResponse)> callback);

  void update_subscriber_quota_state_rpc(
      const UpdateSubscriberQuotaStateRequest& request,
      std::function<void(Status, FlowResponse)> callback);

  void delete_ue_mac_flow_rpc(
      const UEMacFlowRequest& request,
      std::function<void(Status, FlowResponse)> callback);

  void set_upf_session_rpc(
      const SessionSet& request,
      std::function<void(Status, UPFSessionContextState)> callback);
};

}  // namespace magma
