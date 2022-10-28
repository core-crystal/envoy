load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

envoy_extension_package()

envoy_cc_library(
    name = "source_prepend_lib",
    srcs = ["source_prepend.cc"],
    hdrs = ["source_prepend.h"],
    deps = [
        "//envoy/network:filter_interface",
        "//envoy/network:listener_interface",
        "//envoy/server:factory_context_interface",
        "//envoy/upstream:cluster_manager_interface",
        "@envoy_api//envoy/extensions/filters/udp/source_prepend/v3:pkg_cc_proto",
    ],
)

envoy_cc_extension(
    name = "config",
    srcs = ["config.cc"],
    deps = [
        "//envoy/registry",
        "//envoy/server:filter_config_interface",
        "//source/extensions/filters/udp/source_prepend:source_prepend_lib",
        "@envoy_api//envoy/extensions/filters/udp/source_prepend/v3:pkg_cc_proto",
    ],
)
