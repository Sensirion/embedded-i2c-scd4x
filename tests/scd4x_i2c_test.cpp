/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * Generator:     sensirion-driver-generator 1.1.2
 * Product:       scd4x
 * Model-Version: 2.0
 */

#include "scd4x_i2c.h"
#include "sensirion_common.h"
#include "sensirion_i2c.h"
#include "sensirion_i2c_hal.h"
#include "sensirion_test_setup.h"
#include <inttypes.h>
#include <stdio.h>

#define sensirion_hal_sleep_us sensirion_i2c_hal_sleep_usec

void print_ushort_array(uint16_t* array, uint16_t len) {
    uint16_t i = 0;
    printf("0x");
    for (; i < len; i++) {
        printf("%04x", array[i]);
    }
}

TEST_GROUP (SCD4X_Tests) {
    void setup() {
        scd4x_init(0x62);
    }
};

TEST (SCD4X_Tests, test_set_temperature_offset_raw1) {
    int16_t local_error = 0;
    local_error = scd4x_set_temperature_offset_raw(1498);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_temperature_offset_raw");
}

TEST (SCD4X_Tests, test_get_temperature_offset_raw1) {
    int16_t local_error = 0;
    uint16_t offset_temperature = 0;
    local_error = scd4x_get_temperature_offset_raw(&offset_temperature);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_temperature_offset_raw");
    printf("offset_temperature: %u\n", offset_temperature);
}

TEST (SCD4X_Tests, test_set_sensor_altitude1) {
    int16_t local_error = 0;
    local_error = scd4x_set_sensor_altitude(0);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_sensor_altitude");
}

TEST (SCD4X_Tests, test_get_sensor_altitude1) {
    int16_t local_error = 0;
    uint16_t sensor_altitude = 0;
    local_error = scd4x_get_sensor_altitude(&sensor_altitude);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_sensor_altitude");
    printf("sensor_altitude: %u\n", sensor_altitude);
}

TEST (SCD4X_Tests, test_get_serial_number1) {
    int16_t local_error = 0;
    uint16_t serial_number[3] = {0};
    local_error = scd4x_get_serial_number(serial_number, 3);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_serial_number");
    printf("serial_number: ");
    print_ushort_array(serial_number, 3);
    printf("\n");
}

TEST (SCD4X_Tests, test_perform_forced_recalibration1) {
    int16_t local_error = 0;
    uint16_t frc_correction = 0;
    local_error = scd4x_perform_forced_recalibration(400, &frc_correction);
    CHECK_EQUAL_ZERO_TEXT(local_error, "perform_forced_recalibration");
    printf("frc_correction: %u\n", frc_correction);
}

TEST (SCD4X_Tests, test_set_automatic_self_calibration_enabled1) {
    int16_t local_error = 0;
    local_error = scd4x_set_automatic_self_calibration_enabled(1);
    CHECK_EQUAL_ZERO_TEXT(local_error,
                          "set_automatic_self_calibration_enabled");
}

TEST (SCD4X_Tests, test_get_automatic_self_calibration_enabled1) {
    int16_t local_error = 0;
    uint16_t asc_enabled = 0;
    local_error = scd4x_get_automatic_self_calibration_enabled(&asc_enabled);
    CHECK_EQUAL_ZERO_TEXT(local_error,
                          "get_automatic_self_calibration_enabled");
    printf("asc_enabled: %u\n", asc_enabled);
}

TEST (SCD4X_Tests, test_set_automatic_self_calibration_target1) {
    int16_t local_error = 0;
    local_error = scd4x_set_automatic_self_calibration_target(400);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_automatic_self_calibration_target");
}

TEST (SCD4X_Tests, test_get_automatic_self_calibration_target1) {
    int16_t local_error = 0;
    uint16_t asc_target = 0;
    local_error = scd4x_get_automatic_self_calibration_target(&asc_target);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_automatic_self_calibration_target");
    printf("asc_target: %u\n", asc_target);
}

TEST (SCD4X_Tests, test_persist_settings1) {
    int16_t local_error = 0;
    local_error = scd4x_persist_settings();
    CHECK_EQUAL_ZERO_TEXT(local_error, "persist_settings");
}

TEST (SCD4X_Tests, test_perform_self_test1) {
    int16_t local_error = 0;
    uint16_t sensor_status = 0;
    local_error = scd4x_perform_self_test(&sensor_status);
    CHECK_EQUAL_ZERO_TEXT(local_error, "perform_self_test");
    printf("sensor_status: %u\n", sensor_status);
}

TEST (SCD4X_Tests, test_perform_factory_reset1) {
    int16_t local_error = 0;
    local_error = scd4x_perform_factory_reset();
    CHECK_EQUAL_ZERO_TEXT(local_error, "perform_factory_reset");
}

TEST (SCD4X_Tests, test_reinit1) {
    int16_t local_error = 0;
    local_error = scd4x_reinit();
    CHECK_EQUAL_ZERO_TEXT(local_error, "reinit");
}

TEST (SCD4X_Tests, test_get_sensor_variant_raw1) {
    int16_t local_error = 0;
    uint16_t sensor_variant = 0;
    local_error = scd4x_get_sensor_variant_raw(&sensor_variant);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_sensor_variant_raw");
    printf("sensor_variant: %u\n", sensor_variant);
}

TEST (SCD4X_Tests, test_get_sensor_variant1) {
    int16_t local_error = 0;
    scd4x_sensor_variant a_sensor_variant = SCD4X_SENSOR_VARIANT_UNKNOWN;
    local_error = scd4x_get_sensor_variant(&a_sensor_variant);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_sensor_variant");
    printf("a_sensor_variant: %i\n", a_sensor_variant);
}

TEST (SCD4X_Tests, test_set_automatic_self_calibration_initial_period1) {
    int16_t local_error = 0;
    local_error = scd4x_set_automatic_self_calibration_initial_period(44);
    CHECK_EQUAL_ZERO_TEXT(local_error,
                          "set_automatic_self_calibration_initial_period");
}

TEST (SCD4X_Tests, test_get_automatic_self_calibration_initial_period1) {
    int16_t local_error = 0;
    uint16_t asc_initial_period = 0;
    local_error = scd4x_get_automatic_self_calibration_initial_period(
        &asc_initial_period);
    CHECK_EQUAL_ZERO_TEXT(local_error,
                          "get_automatic_self_calibration_initial_period");
    printf("asc_initial_period: %u\n", asc_initial_period);
}

TEST (SCD4X_Tests, test_set_automatic_self_calibration_standard_period1) {
    int16_t local_error = 0;
    local_error = scd4x_set_automatic_self_calibration_standard_period(156);
    CHECK_EQUAL_ZERO_TEXT(local_error,
                          "set_automatic_self_calibration_standard_period");
}

TEST (SCD4X_Tests, test_get_automatic_self_calibration_standard_period1) {
    int16_t local_error = 0;
    uint16_t asc_standard_period = 0;
    local_error = scd4x_get_automatic_self_calibration_standard_period(
        &asc_standard_period);
    CHECK_EQUAL_ZERO_TEXT(local_error,
                          "get_automatic_self_calibration_standard_period");
    printf("asc_standard_period: %u\n", asc_standard_period);
}

TEST (SCD4X_Tests, test_measure_single_shot_rht_only1) {
    int16_t local_error = 0;
    local_error = scd4x_measure_single_shot_rht_only();
    CHECK_EQUAL_ZERO_TEXT(local_error, "measure_single_shot_rht_only");
    local_error = scd4x_read_measurement_raw(&co2_concentration, &temperature,
                                             &relative_humidity);
    CHECK_EQUAL_ZERO_TEXT(local_error, "read_measurement_raw");
    printf("co2_concentration: %u ", co2_concentration);
    printf("temperature: %u ", temperature);
    printf("relative_humidity: %u\n", relative_humidity);
}

TEST (SCD4X_Tests, test_measure_single_shot1) {
    int16_t local_error = 0;
    local_error = scd4x_measure_single_shot();
    CHECK_EQUAL_ZERO_TEXT(local_error, "measure_single_shot");
    local_error = scd4x_read_measurement_raw(&co2_concentration, &temperature,
                                             &relative_humidity);
    CHECK_EQUAL_ZERO_TEXT(local_error, "read_measurement_raw");
    printf("co2_concentration: %u ", co2_concentration);
    printf("temperature: %u ", temperature);
    printf("relative_humidity: %u\n", relative_humidity);
}

TEST (SCD4X_Tests, test_start_periodic_measurement1) {
    int16_t local_error = 0;
    uint16_t co2_concentration = 0;
    uint16_t temperature = 0;
    uint16_t relative_humidity = 0;
    uint32_t a_ambient_pressure = 0;
    uint16_t ambient_pressure = 0;
    bool arg_0 = false;
    uint16_t data_ready_status = 0;
    local_error = scd4x_start_periodic_measurement();
    CHECK_EQUAL_ZERO_TEXT(local_error, "start_periodic_measurement");
    // wait for measurement
    sensirion_hal_sleep_us(5000000);
    local_error = scd4x_get_data_ready_status(&arg_0);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_data_ready_status");
    printf("arg_0: %d\n", arg_0);
    local_error = scd4x_get_data_ready_status_raw(&data_ready_status);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_data_ready_status_raw");
    printf("data_ready_status: %u\n", data_ready_status);
    local_error = scd4x_read_measurement_raw(&co2_concentration, &temperature,
                                             &relative_humidity);
    CHECK_EQUAL_ZERO_TEXT(local_error, "read_measurement_raw");
    printf("co2_concentration: %u ", co2_concentration);
    printf("temperature: %u ", temperature);
    printf("relative_humidity: %u\n", relative_humidity);
    local_error = scd4x_set_ambient_pressure(101300);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_ambient_pressure");
    local_error = scd4x_get_ambient_pressure(&a_ambient_pressure);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_ambient_pressure");
    printf("a_ambient_pressure: %u\n", a_ambient_pressure);
    local_error = scd4x_set_ambient_pressure_raw(1013);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_ambient_pressure_raw");
    local_error = scd4x_get_ambient_pressure_raw(&ambient_pressure);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_ambient_pressure_raw");
    printf("ambient_pressure: %u\n", ambient_pressure);
    local_error = scd4x_stop_periodic_measurement();
    CHECK_EQUAL_ZERO_TEXT(local_error, "stop_periodic_measurement");
}

TEST (SCD4X_Tests, test_start_low_power_periodic_measurement1) {
    int16_t local_error = 0;
    uint16_t co2_concentration = 0;
    uint16_t temperature = 0;
    uint16_t relative_humidity = 0;
    uint32_t a_ambient_pressure = 0;
    uint16_t ambient_pressure = 0;
    bool arg_0 = false;
    uint16_t data_ready_status = 0;
    local_error = scd4x_start_low_power_periodic_measurement();
    CHECK_EQUAL_ZERO_TEXT(local_error, "start_low_power_periodic_measurement");
    local_error = scd4x_read_measurement_raw(&co2_concentration, &temperature,
                                             &relative_humidity);
    // as we do not wait the read measurement command returns with nack/error
    CHECK_EQUAL_TEXT(local_error, 1, "read_measurement_raw");
    local_error = scd4x_set_ambient_pressure(101300);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_ambient_pressure");
    local_error = scd4x_get_ambient_pressure(&a_ambient_pressure);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_ambient_pressure");
    printf("a_ambient_pressure: %u\n", a_ambient_pressure);
    local_error = scd4x_set_ambient_pressure_raw(1013);
    CHECK_EQUAL_ZERO_TEXT(local_error, "set_ambient_pressure_raw");
    local_error = scd4x_get_ambient_pressure_raw(&ambient_pressure);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_ambient_pressure_raw");
    printf("ambient_pressure: %u\n", ambient_pressure);
    local_error = scd4x_get_data_ready_status(&arg_0);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_data_ready_status");
    printf("arg_0: %d\n", arg_0);
    local_error = scd4x_get_data_ready_status_raw(&data_ready_status);
    CHECK_EQUAL_ZERO_TEXT(local_error, "get_data_ready_status_raw");
    printf("data_ready_status: %u\n", data_ready_status);
    local_error = scd4x_stop_periodic_measurement();
    CHECK_EQUAL_ZERO_TEXT(local_error, "stop_periodic_measurement");
}
