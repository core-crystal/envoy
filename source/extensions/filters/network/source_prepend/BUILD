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
        "//envoy/buffer:buffer_interface",
        "//envoy/network:connection_interface",
        "//envoy/network:filter_interface",
        "//envoy/server:factory_context_interface",
        "//envoy/upstream:cluster_manager_interface",
        "//source/common/common:minimal_logger_lib",
        "@envoy_api//envoy/extensions/filters/network/source_prepend/v3:pkg_cc_proto",
    ],
)

envoy_cc_extension(
    name = "config",
    srcs = ["config.cc"],
    deps = [
        ":source_prepend_lib",
        "//envoy/registry",
        "//envoy/server:filter_config_interface",
        "//source/extensions/filters/network:well_known_names",
        "//source/extensions/filters/network/common:factory_base_lib",
        "@envoy_api//envoy/extensions/filters/network/source_prepend/v3:pkg_cc_proto",
    ],
)
