// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_SILICON_CREATOR_MANUF_LIB_INDIVIDUALIZE_H_
#define OPENTITAN_SW_DEVICE_SILICON_CREATOR_MANUF_LIB_INDIVIDUALIZE_H_

#include "sw/device/lib/base/status.h"
#include "sw/device/lib/dif/dif_flash_ctrl.h"
#include "sw/device/lib/dif/dif_lc_ctrl.h"
#include "sw/device/lib/dif/dif_otp_ctrl.h"
#include "sw/device/lib/testing/json/provisioning_data.h"

/**
 * Provision the HW_CFG OTP partition.
 *
 * The HW_CFG partition contains:
 * - Unique device identifier (DeviceId), which is a public value used to
 *   identify the device during manufacturing.
 * - Manufacturing state information generated by the manufacturer.
 * - Various digital logic configuration settings.
 *
 * Preconditions:
 * - Device is in DEV, PROD, or PROD_END lifecycle stage.
 * - DeviceId & ManufState are pre-populated in the appropriate flash info page.
 *
 * Note: The test will skip all programming steps and succeed if the HW_CFG
 * parition is already locked. This is to facilitate test re-runs.
 *
 * The caller should reset the device after calling this function and call
 * `manuf_individualize_device_hw_cfg_check()` afterwards to confirm that the
 * OTP partition was successfully locked.
 *
 * @param lc_ctrl Lifecycle controller instance.
 * @param otp_ctrl OTP controller instance.
 * @return OK_STATUS on success.
 */
status_t manuf_individualize_device_hw_cfg(dif_flash_ctrl_state_t *flash_state,
                                           const dif_lc_ctrl_t *lc_ctrl,
                                           const dif_otp_ctrl_t *otp_ctrl);

/**
 * Checks the HW_CFG OTP partition end state.
 *
 * @param otp_ctrl OTP controller interface.
 * @return OK_STATUS if the HW_CFG partition is locked.
 */
status_t manuf_individualize_device_hw_cfg_check(
    const dif_otp_ctrl_t *otp_ctrl);

/**
 * Configures the SECRET0 OTP partition.
 *
 * The SECRET0 partition contains the test unlock and exit tokens.
 *
 * Preconditions:
 * - Device is in TEST_UNLOCKED lifecycle stage.
 *
 * Note: The test will skip all programming steps and succeed if the SECRET0
 * parition is already locked. This is to facilitate test re-runs.
 *
 * The caller should reset the device after calling this function and call
 * `manuf_individualize_device_secret0_check()` afterwards to confirm that the
 * OTP partition was successfully locked.
 *
 * @param lc_ctrl Lifecycle controller instance.
 * @param otp_ctrl OTP controller instance.
 * @param provisioning_data Struct with test unlock/exit tokens to provision.
 * @return OK_STATUS if the HW_CFG partition is locked.
 */
status_t manuf_individualize_device_secret0(
    const dif_lc_ctrl_t *lc_ctrl, const dif_otp_ctrl_t *otp_ctrl,
    const manuf_cp_provisioning_data_t *provisioning_data);

/**
 * Checks the SECRET0 OTP partition end state.
 *
 * @param otp_ctrl OTP controller interface.
 * @return OK_STATUS if the SECRET1 partition is locked.
 */
status_t manuf_individualize_device_secret0_check(
    const dif_otp_ctrl_t *otp_ctrl);

/**
 * Configures the SECRET1 OTP partition.
 *
 * The SECRET1 partition contains the Flash and SRAM scrambling seeds for the
 * device.
 *
 * Preconditions:
 * - Device is in DEV, PROD, or PROD_END lifecycle stage.
 *
 * Note: The test will skip all programming steps and succeed if the SECRET1
 * parition is already locked. This is to facilitate test re-runs.
 *
 * The caller should reset the device after calling this function and call
 * `manuf_individualize_device_secret1_check()` afterwards to confirm that the
 * OTP partition was successfully locked.
 *
 * @param lc_ctrl Lifecycle controller instance.
 * @param otp_ctrl OTP controller instance.
 * @return OK_STATUS if the HW_CFG partition is locked.
 */
status_t manuf_individualize_device_secret1(const dif_lc_ctrl_t *lc_ctrl,
                                            const dif_otp_ctrl_t *otp_ctrl);

/**
 * Checks the SECRET1 OTP partition end state.
 *
 * @param otp_ctrl OTP controller interface.
 * @return OK_STATUS if the SECRET1 partition is locked.
 */
status_t manuf_individualize_device_secret1_check(
    const dif_otp_ctrl_t *otp_ctrl);

#endif  // OPENTITAN_SW_DEVICE_SILICON_CREATOR_MANUF_LIB_INDIVIDUALIZE_H_
