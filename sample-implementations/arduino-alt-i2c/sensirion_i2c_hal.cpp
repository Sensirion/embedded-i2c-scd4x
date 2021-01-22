/*
 * Copyright (c) 2019, Sensirion AG
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

#include "sensirion_i2c_hal.h"
#include "sensirion_common.h"
#include "sensirion_config.h"

// needed for delay() routine
#include "i2c_master_lib.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize all hard- and software components that are needed for the I2C
 * communication. After this function has been called, the functions
 * i2c_read() and i2c_write() must succeed.
 */
void sensirion_i2c_hal_init(void) {
    I2c.begin();
}

/**
 * Release all resources initialized by sensirion_i2c_hal_init().
 */
void sensirion_i2c_hal_free(void) {
}

int8_t sensirion_i2c_hal_read(uint8_t address, uint8_t* data, uint16_t count) {
    return I2c.read(address, count, data);
}

int8_t sensirion_i2c_hal_write(uint8_t address, const uint8_t* data,
                               uint16_t count) {
    // the API doesn't forsee calls without register, so we'll use the first
    // byte as "register", and pass the rest as data argument
    if (count == 0) {
        return 0;
    }
    return I2c.write(address, data[0], data + 1, count - 1);
}

/**
 * Sleep for a given number of microseconds. The function should delay the
 * execution for at least the given time, but may also sleep longer.
 *
 * @param useconds the sleep time in microseconds
 */
void sensirion_i2c_hal_sleep_usec(uint32_t useconds) {
    delay((useconds / 1000) + 1);
}

#ifdef __cplusplus
}  // extern "C"
#endif
