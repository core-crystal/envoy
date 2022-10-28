#pragma once

#include "envoy/extensions/filters/udp/source_prepend/v3/source_prepend.pb.h"
#include "envoy/network/filter.h"
#include "envoy/server/factory_context.h"
#include "envoy/upstream/cluster_manager.h"

#include "source/common/protobuf/utility.h"

namespace Envoy {
namespace Extensions {
namespace UdpFilters {
namespace SourcePrepend {

class SourcePrependFilterConfig {
public:
  SourcePrependFilterConfig(
      Server::Configuration::ListenerFactoryContext& /*context*/,
      const envoy::extensions::filters::udp::source_prepend::v3::SourcePrependConfig& config)
      : active_(PROTOBUF_GET_WRAPPED_OR_DEFAULT(config, enable, true)) {}

  bool isActive() const { return active_; }

private:
  const bool active_;
};

using SourcePrependFilterConfigSharedPtr = std::shared_ptr<const SourcePrependFilterConfig>;

class SourcePrependFilter : public Network::UdpListenerReadFilter,
                            Logger::Loggable<Logger::Id::filter> {
public:
  SourcePrependFilter(Network::UdpReadFilterCallbacks& callbacks,
                      const SourcePrependFilterConfigSharedPtr& config)
      : Network::UdpListenerReadFilter(callbacks), config_(config) {}

  // Network::UdpListenerReadFilter
  Network::FilterStatus onData(Network::UdpRecvData& data) override;
  Network::FilterStatus onReceiveError(Api::IoError::IoErrorCode error_code) override;

private:
  const SourcePrependFilterConfigSharedPtr config_;
};

} // namespace SourcePrepend
} // namespace UdpFilters
} // namespace Extensions
} // namespace Envoy
