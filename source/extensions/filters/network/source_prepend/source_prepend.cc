#include "source/extensions/filters/network/source_prepend/source_prepend.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace SourcePrepend {

namespace {

static inline bool isSystemLittleEndian() {
  const int value{0x01};
  const void* address = static_cast<const void*>(&value);
  const unsigned char* least_significant_address = static_cast<const unsigned char*>(address);
  return (*least_significant_address == 0x01);
}

static inline uint32_t swapUint32T(uint32_t val) {
  return ((((val)&0xff000000) >> 24) | (((val)&0x00ff0000) >> 8) | (((val)&0x0000ff00) << 8) |
          (((val)&0x000000ff) << 24));
}

} // namespace

Network::FilterStatus SourcePrependFilter::onData(Buffer::Instance& buffer, bool /*end_stream*/) {
  if (config_->isActive()) {
    const auto& address = read_callbacks_->connection().connectionInfoProvider().remoteAddress();
    if (address->type() == Network::Address::Type::Ip) {
      auto port = address->ip()->port();
      if (!isSystemLittleEndian()) {
        port = swapUint32T(port);
      }
      buffer.prepend(std::string{reinterpret_cast<char*>(&port), 4});
    } else {
      uint32_t port = 0;
      buffer.prepend(std::string{reinterpret_cast<char*>(&port), 4});
    }
  }
  return Network::FilterStatus::Continue;
}

} // namespace SourcePrepend
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy