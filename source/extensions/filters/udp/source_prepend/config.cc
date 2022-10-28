#include <string>

#include "envoy/extensions/filters/udp/source_prepend/v3/source_prepend.pb.h"
#include "envoy/extensions/filters/udp/source_prepend/v3/source_prepend.pb.validate.h"
#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"

#include "source/extensions/filters/udp/source_prepend/source_prepend.h"

namespace Envoy {
namespace Extensions {
namespace UdpFilters {
namespace SourcePrepend {

/**
 * Config registration for the TLS inspector filter. @see NamedNetworkFilterConfigFactory.
 */
class SourcePrependConfigFactory
    : public Server::Configuration::NamedUdpListenerFilterConfigFactory {
public:
  // NamedUdpListenerFilterConfigFactory
  Network::UdpListenerFilterFactoryCb
  createFilterFactoryFromProto(const Protobuf::Message& config,
                               Server::Configuration::ListenerFactoryContext& context) override {
    auto shared_config = std::make_shared<SourcePrependFilterConfig>(
        context,
        MessageUtil::downcastAndValidate<
            const envoy::extensions::filters::udp::source_prepend::v3::SourcePrependConfig&>(
            config, context.messageValidationVisitor()));
    return [shared_config](Network::UdpListenerFilterManager& filter_manager,
                           Network::UdpReadFilterCallbacks& callbacks) -> void {
      filter_manager.addReadFilter(std::make_unique<SourcePrependFilter>(callbacks, shared_config));
    };
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return std::make_unique<
        envoy::extensions::filters::udp::source_prepend::v3::SourcePrependConfig>();
  }

  std::string name() const override { return "envoy.filters.udp.source_prepend"; }
};

static Registry::RegisterFactory<SourcePrependConfigFactory,
                                 Server::Configuration::NamedUdpListenerFilterConfigFactory>
    register_;

} // namespace SourcePrepend
} // namespace UdpFilters
} // namespace Extensions
} // namespace Envoy
