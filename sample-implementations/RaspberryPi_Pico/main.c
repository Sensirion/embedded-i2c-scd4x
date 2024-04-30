

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "scd4x_i2c.h"
#include <stdio.h>

/// I2C address
static int addr = 0x62;

// I2C Pins
static uint sda_pin = 16;
static uint scl_pin = 17;

// This is the main entry for your c application. U
// is
int main() {

    stdio_init_all();

    // Setup I2c using pins 16 & 17
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    // This variable will hold the return status of the function calls.
    // You can separate each function call result into their own variable or re
    // - use this.

    int status = 0;

    // Stop any readings if occuring
    status = scd4x_stop_periodic_measurement();

    // Perform self test
    uint16_t* selfTest = 0;
    scd4x_perform_self_test(selfTest);

    // Get Serial number 3 parts
    uint16_t one;
    uint16_t two;
    uint16_t three;

    scd4x_get_serial_number(&one, &two, &three);

    // Start the readings.
    status1 = scd4x_start_periodic_measurement();

    while (1) {

        // Check if data is ready to read
        bool dataReady;
        while (dataReady == false) {

            status1 = scd4x_get_data_ready_flag(&dataReady);
        }

        // Get the ticks. The scd4x_read_measurement function is giving
        // incorrect data due to the arthimetic
        uint16_t co2;
        uint16_t temp;
        uint16_t humidity;
        status1 = scd4x_read_measurement_ticks(&co2, &temp, &humidity);

        // Arithemtic to change raw data into information
        int tempInCelsius = -45 + 175 * temp / 65536;
        int tempInFarenheit = tempInCelsius * 1.8 + 32;
        int humidityPercent = 100 * humidity / 65536;

        // Print results to terminal (output)
        printf("C:%d,T:%d,H:%d", co2, tempInFarenheit, humidityPercent);

        // Sleep for 5 seconds.
        sleep_ms(5000);
    }
}
