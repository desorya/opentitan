# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load("//rules:const.bzl", "CONST", "hex")
load("//rules:manifest.bzl", "manifest")
load("//rules/opentitan:defs.bzl", "opentitan_binary")
load("//rules:signing.bzl", "offline_presigning_artifacts", "offline_signature_attach")
load("@rules_pkg//pkg:tar.bzl", "pkg_tar")
load(
    "//sw/device/silicon_creator/rom_ext:defs.bzl",
    "ROM_EXT_VERSION",
)

package(default_visibility = ["//visibility:public"])

# In order to prevent the linker from prematurely discarding symbols, we
# need to give the CRT library last.
LINK_ORDER = [
    "$(location //sw/device/silicon_creator/rom_ext)",
    "$(location //sw/device/lib/crt)",
]

manifest(d = {
    "name": "manifest_prodc",
    "address_translation": hex(CONST.HARDENED_FALSE),
    "identifier": hex(CONST.ROM_EXT),
    "manuf_state_creator": hex(CONST.MANUF_STATE.PRODC),
    "version_major": ROM_EXT_VERSION.MAJOR,
    "version_minor": ROM_EXT_VERSION.MINOR,
    "security_version": ROM_EXT_VERSION.SECURITY,
    "visibility": ["//visibility:public"],
})

# To test that the fake-signed ProdC ROM_EXT can boot, you need a bitstream
# with the OTP word CREATOR_SW_CCFG_MANUF_STATE set to `PRODC` (as above
# in the manifest definition).  You can manually create such a bitstream with:
#
# bazel build //hw/bitstream/universal:splice --//hw/bitstream/universal:env=//hw/top_earlgrey:fpga_cw310_sival
opentitan_binary(
    name = "rom_ext_fake_prod_signed_slot_a",
    ecdsa_key = {"//sw/device/silicon_creator/rom/keys/fake/ecdsa:prod_key_0_ecdsa_p256": "prod_key_0"},
    exec_env = [
        "//hw/top_earlgrey:silicon_creator",
        "//hw/top_earlgrey:fpga_cw310",
        "//hw/top_earlgrey:sim_dv_base",
        "//hw/top_earlgrey:sim_verilator_base",
    ],
    linker_script = "//sw/device/silicon_creator/rom_ext:ld_slot_a",
    linkopts = LINK_ORDER,
    manifest = ":manifest_prodc",
    deps = [
        "//sw/device/lib/crt",
        "//sw/device/silicon_creator/lib:manifest_def",
        "//sw/device/silicon_creator/rom_ext",
        "//sw/device/silicon_creator/rom_ext/prodc/keys",
    ],
)

opentitan_binary(
    name = "rom_ext_fake_prod_signed_slot_b",
    ecdsa_key = {"//sw/device/silicon_creator/rom/keys/fake/ecdsa:prod_key_0_ecdsa_p256": "prod_key_0"},
    exec_env = [
        "//hw/top_earlgrey:silicon_creator",
        "//hw/top_earlgrey:fpga_cw310",
        "//hw/top_earlgrey:sim_dv_base",
        "//hw/top_earlgrey:sim_verilator_base",
    ],
    linker_script = "//sw/device/silicon_creator/rom_ext:ld_slot_b",
    linkopts = LINK_ORDER,
    manifest = ":manifest_prodc",
    deps = [
        "//sw/device/lib/crt",
        "//sw/device/silicon_creator/lib:manifest_def",
        "//sw/device/silicon_creator/rom_ext",
        "//sw/device/silicon_creator/rom_ext/prodc/keys",
    ],
)

opentitan_binary(
    name = "rom_ext_real_prod_signed_slot_a",
    exec_env = [
        "//hw/top_earlgrey:silicon_creator",
        "//hw/top_earlgrey:fpga_cw310",
    ],
    linker_script = "//sw/device/silicon_creator/rom_ext:ld_slot_a",
    linkopts = LINK_ORDER,
    deps = [
        "//sw/device/lib/crt",
        "//sw/device/silicon_creator/lib:manifest_def",
        "//sw/device/silicon_creator/rom_ext",
        "//sw/device/silicon_creator/rom_ext/prodc/keys",
    ],
)

opentitan_binary(
    name = "rom_ext_real_prod_signed_slot_b",
    exec_env = [
        "//hw/top_earlgrey:silicon_creator",
        "//hw/top_earlgrey:fpga_cw310",
    ],
    linker_script = "//sw/device/silicon_creator/rom_ext:ld_slot_b",
    linkopts = LINK_ORDER,
    deps = [
        "//sw/device/lib/crt",
        "//sw/device/silicon_creator/lib:manifest_def",
        "//sw/device/silicon_creator/rom_ext",
        "//sw/device/silicon_creator/rom_ext/prodc/keys",
    ],
)

offline_presigning_artifacts(
    name = "presigning",
    testonly = True,
    srcs = [
        ":rom_ext_real_prod_signed_slot_a",
        ":rom_ext_real_prod_signed_slot_b",
    ],
    manifest = ":manifest_prodc",
    rsa_key = {
        "//sw/device/silicon_creator/rom/keys/real/rsa:keyset": "earlgrey_a0_prod_0",
    },
    tags = ["manual"],
)

pkg_tar(
    name = "digests",
    testonly = True,
    srcs = [":presigning"],
    mode = "0644",
    tags = ["manual"],
)

offline_signature_attach(
    name = "signed",
    testonly = True,
    srcs = [
        ":presigning",
    ],
    rsa_signatures = [
        "//sw/device/silicon_creator/rom_ext/prodc/signatures:rsa_signatures",
    ],
    tags = ["manual"],
)
