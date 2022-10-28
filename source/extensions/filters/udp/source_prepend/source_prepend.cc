#include "source/extensions/filters/udp/source_prepend/source_prepend.h"

#include <climits>
#include <cstdint>
#include <string>

namespace Envoy {
namespace Extensions {
namespace UdpFilters {
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

Network::FilterStatus SourcePrependFilter::onData(Network::UdpRecvData& data) {
  auto port = data.addresses_.peer_->ip()->port();

  if (!isSystemLittleEndian()) {
    port = swapUint32T(port);
  }

  data.buffer_->prepend(std::string{reinterpret_cast<char*>(&port), 4});

  return Network::FilterStatus::Continue;
}

Network::FilterStatus SourcePrependFilter::onReceiveError(Api::IoError::IoErrorCode) {
  return Network::FilterStatus::Continue;
}

} // namespace SourcePrepend
} // namespace UdpFilters
} // namespace Extensions
} // namespace Envoy
