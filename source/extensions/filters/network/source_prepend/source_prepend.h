#pragma once

#include "envoy/extensions/filters/network/source_prepend/v3/source_prepend.pb.h"
#include "envoy/network/filter.h"

#include "source/common/common/logger.h"
#include "source/common/protobuf/utility.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace SourcePrepend {

class SourcePrependFilterConfig {
public:
  SourcePrependFilterConfig(
      const envoy::extensions::filters::network::source_prepend::v3::SourcePrependConfig& config)
      : active_(PROTOBUF_GET_WRAPPED_OR_DEFAULT(config, enable, true)) {}

  bool isActive() const { return active_; }

private:
  const bool active_;
};

using SourcePrependFilterConfigSharedPtr = std::shared_ptr<const SourcePrependFilterConfig>;

class SourcePrependFilter : public Network::ReadFilter, Logger::Loggable<Logger::Id::filter> {
public:
  SourcePrependFilter(const SourcePrependFilterConfigSharedPtr& config) : config_(config) {}

  // Network::ReadFilter
  Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;
  Network::FilterStatus onNewConnection() override { return Network::FilterStatus::Continue; }
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override {
    read_callbacks_ = &callbacks;
  }

private:
  Network::ReadFilterCallbacks* read_callbacks_{};
  const SourcePrependFilterConfigSharedPtr config_;
};

} // namespace SourcePrepend
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
