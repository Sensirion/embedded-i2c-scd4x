/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * Generator:     sensirion-driver-generator 1.1.2
 * Product:       scd4x
 * Model-Version: 2.0
 */
/*
 * Copyright (c) 2025, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "scd4x_i2c.h"
#include "sensirion_common.h"
#include "sensirion_i2c.h"
#include "sensirion_i2c_hal.h"

#define sensirion_hal_sleep_us sensirion_i2c_hal_sleep_usec

#define ROUND(x) ((int32_t)((x) + 0.5))

static uint8_t communication_buffer[9] = {0};

static uint8_t _i2c_address;

void scd4x_init(uint8_t i2c_address) {
    _i2c_address = i2c_address;
}

uint16_t scd4x_signal_co2_concentration(uint16_t raw_co2_concentration) {
    uint16_t co2_concentration = 0;
    co2_concentration = raw_co2_concentration;
    return co2_concentration;
}

uint32_t scd4x_signal_ambient_pressure(uint16_t raw_ambient_pressure) {
    uint32_t ambient_pressure = 0;
    ambient_pressure = (uint32_t)raw_ambient_pressure * 100;
    return ambient_pressure;
}

int16_t scd4x_set_ambient_pressure(uint32_t ambient_pressure) {
    int16_t local_error = 0;
    uint16_t raw_ambient_pressure = (uint16_t)ROUND(ambient_pressure / 100.0);
    local_error = scd4x_set_ambient_pressure_raw(raw_ambient_pressure);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t scd4x_get_ambient_pressure(uint32_t* a_ambient_pressure) {
    uint16_t raw_ambient_pressure = 0;
    int16_t local_error = 0;
    local_error = scd4x_get_ambient_pressure_raw(&raw_ambient_pressure);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *a_ambient_pressure = scd4x_signal_ambient_pressure(raw_ambient_pressure);

    return local_error;
}

int16_t scd4x_get_data_ready_status(bool* arg_0) {
    uint16_t data_ready_status = 0;
    int16_t local_error = 0;
    local_error = scd4x_get_data_ready_status_raw(&data_ready_status);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *arg_0 = (data_ready_status & 2047) != 0;
    ;
    return local_error;
}

int16_t scd4x_get_sensor_variant(scd4x_sensor_variant* a_sensor_variant) {
    uint16_t raw_sensor_variant = 0;
    int16_t local_error = 0;
    local_error = scd4x_get_sensor_variant_raw(&raw_sensor_variant);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    uint16_t variant = (uint16_t)(raw_sensor_variant & 4);
    if (variant == 0) {
        *a_sensor_variant = SCD4X_SENSOR_VARIANT_SCD40;
        ;
        return local_error;
    } else if (variant == 1) {
        *a_sensor_variant = SCD4X_SENSOR_VARIANT_SCD41;
        ;
        return local_error;
    }
    *a_sensor_variant = SCD4X_SENSOR_VARIANT_UNKNOWN;
    ;
    return local_error;
}

int16_t scd4x_start_periodic_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x21b1);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t scd4x_read_measurement_raw(uint16_t* co2_concentration,
                                   uint16_t* temperature,
                                   uint16_t* relative_humidity) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xec05);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 6);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *co2_concentration = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    *temperature = sensirion_common_bytes_to_uint16_t(&buffer_ptr[2]);
    *relative_humidity = sensirion_common_bytes_to_uint16_t(&buffer_ptr[4]);
    return local_error;
}

int16_t scd4x_stop_periodic_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3f86);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(500 * 1000);
    return local_error;
}

int16_t scd4x_set_temperature_offset_raw(uint16_t offset_temperature) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x241d);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, offset_temperature);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_temperature_offset_raw(uint16_t* offset_temperature) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2318);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *offset_temperature = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_set_sensor_altitude(uint16_t sensor_altitude) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2427);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, sensor_altitude);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_sensor_altitude(uint16_t* sensor_altitude) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2322);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *sensor_altitude = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_set_ambient_pressure_raw(uint16_t ambient_pressure) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe000);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, ambient_pressure);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_ambient_pressure_raw(uint16_t* ambient_pressure) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe000);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *ambient_pressure = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_perform_forced_recalibration(uint16_t target_co2_concentration,
                                           uint16_t* frc_correction) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x362f);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, target_co2_concentration);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(400 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *frc_correction = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_set_automatic_self_calibration_enabled(uint16_t asc_enabled) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2416);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, asc_enabled);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_automatic_self_calibration_enabled(uint16_t* asc_enabled) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2313);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *asc_enabled = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_set_automatic_self_calibration_target(uint16_t asc_target) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x243a);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, asc_target);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_automatic_self_calibration_target(uint16_t* asc_target) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x233f);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *asc_target = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_start_low_power_periodic_measurement() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x21ac);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    return local_error;
}

int16_t scd4x_get_data_ready_status_raw(uint16_t* data_ready_status) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0xe4b8);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *data_ready_status = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_persist_settings() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3615);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(800 * 1000);
    return local_error;
}

int16_t scd4x_get_serial_number(uint16_t* serial_number,
                                uint16_t serial_number_size) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3682);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 6);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_common_copy_bytes(&buffer_ptr[0], (uint8_t*)serial_number,
                                (serial_number_size * 2));
    return local_error;
}

int16_t scd4x_perform_self_test(uint16_t* sensor_status) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3639);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(10000 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *sensor_status = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_perform_factory_reset() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3632);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1200 * 1000);
    return local_error;
}

int16_t scd4x_reinit() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x3646);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(30 * 1000);
    return local_error;
}

int16_t scd4x_get_sensor_variant_raw(uint16_t* sensor_variant) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x202f);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *sensor_variant = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_measure_single_shot() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x219d);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(5000 * 1000);
    return local_error;
}

int16_t scd4x_measure_single_shot_rht_only() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2196);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(50 * 1000);
    return local_error;
}

int16_t scd4x_power_down() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x36e0);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_wake_up() {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x36f6);
    sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    sensirion_i2c_hal_sleep_usec(30 * 1000);
    return local_error;
}

int16_t scd4x_set_automatic_self_calibration_initial_period(
    uint16_t asc_initial_period) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2445);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, asc_initial_period);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_automatic_self_calibration_initial_period(
    uint16_t* asc_initial_period) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x2340);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *asc_initial_period = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t scd4x_set_automatic_self_calibration_standard_period(
    uint16_t asc_standard_period) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x244e);
    local_offset = sensirion_i2c_add_uint16_t_to_buffer(
        buffer_ptr, local_offset, asc_standard_period);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    return local_error;
}

int16_t scd4x_get_automatic_self_calibration_standard_period(
    uint16_t* asc_standard_period) {
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    uint16_t local_offset = 0;
    local_offset =
        sensirion_i2c_add_command16_to_buffer(buffer_ptr, local_offset, 0x234b);
    local_error =
        sensirion_i2c_write_data(_i2c_address, buffer_ptr, local_offset);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    sensirion_i2c_hal_sleep_usec(1 * 1000);
    local_error = sensirion_i2c_read_data_inplace(_i2c_address, buffer_ptr, 2);
    if (local_error != NO_ERROR) {
        return local_error;
    }
    *asc_standard_period = sensirion_common_bytes_to_uint16_t(&buffer_ptr[0]);
    return local_error;
}
