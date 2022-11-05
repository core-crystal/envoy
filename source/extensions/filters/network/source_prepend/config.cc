#include "envoy/extensions/filters/network/source_prepend/v3/source_prepend.pb.h"
#include "envoy/extensions/filters/network/source_prepend/v3/source_prepend.pb.validate.h"
#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"

#include "source/extensions/filters/network/common/factory_base.h"
#include "source/extensions/filters/network/source_prepend/source_prepend.h"
#include "source/extensions/filters/network/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace SourcePrepend {

/**
 * Config registration for the echo filter. @see NamedNetworkFilterConfigFactory.
 */
class SourcePrependConfigFactory
    : public Common::FactoryBase<
          envoy::extensions::filters::network::source_prepend::v3::SourcePrependConfig> {
public:
  SourcePrependConfigFactory() : FactoryBase(NetworkFilterNames::get().SourcePrepend) {}

private:
  Network::FilterFactoryCb createFilterFactoryFromProtoTyped(
      const envoy::extensions::filters::network::source_prepend::v3::SourcePrependConfig& message,
      Server::Configuration::FactoryContext& ctxt) override {
    auto shared_config = std::make_shared<SourcePrependFilterConfig>(
        MessageUtil::downcastAndValidate<
            const envoy::extensions::filters::network::source_prepend::v3::SourcePrependConfig&>(
            message, ctxt.messageValidationVisitor()));

    return [shared_config](Network::FilterManager& filter_manager) -> void {
      filter_manager.addReadFilter(std::make_unique<SourcePrependFilter>(shared_config));
    };
  }
};

/**
 * Static registration for the echo filter. @see RegisterFactory.
 */
REGISTER_FACTORY(SourcePrependConfigFactory,
                 Server::Configuration::NamedNetworkFilterConfigFactory);

} // namespace SourcePrepend
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
