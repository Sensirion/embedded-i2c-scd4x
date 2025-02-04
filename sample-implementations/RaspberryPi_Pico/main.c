#include "../../scd4x_i2c.h"

#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include <stdio.h>

int main(void) {
    stdio_init_all();

    // Give us a few seconds to start viewing the output if we're plugged into
    // the computer over USB.
    sleep_ms(3000);

    // Setup I2C using GPIO pins 12 & 13.
    const uint desired_clock_hz = 400 * 1000;
    const uint actual_baudrate = i2c_init(i2c_default, desired_clock_hz);
    printf("The I2C baudrate is %u Hz\n", actual_baudrate);
    const uint sda_pin = 12;
    const uint scl_pin = 13;
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    // Initialize driver with i2c address
    scd4x_init(SCD41_I2C_ADDR_62);

    int status;

    // Stop any ongoing measurement.
    status = scd4x_stop_periodic_measurement();
    if (status) {
        printf("Unable to stop measurement. Error: %d\n", status);
        return status;
    }

    // Get serial number.
    uint16_t serial_number[3] = {0};
    status = scd4x_get_serial_number(serial_number, 3);
    if (status) {
        printf("Unable to get sensor serial number. Error: %d\n", status);
        return status;
    }
    printf("Sensor serial number is: 0x%x 0x%x 0x%x\n", (int)serial_number[0],
           (int)serial_number[1], (int)serial_number[2]);

    // Start the readings.
    status = scd4x_start_periodic_measurement();
    if (status) {
        printf("Unable to start periodic measurement. Error %d\n", status);
        return status;
    }

    for (;;) {
        // Wait for the measurement to complete.
        sleep_ms(5000 - 10);
        bool dataReady;
        do {
            sleep_ms(10);
            status = scd4x_get_data_ready_status(&dataReady);
            if (status) {
                printf("Unable to get sensor readiness status. Error %d.\n",
                       status);
                return status;
            }
        } while (!dataReady);

        // Read the measurement data and convert it to common units.
        uint16_t co2Raw;         // ppm
        int32_t temperatureRaw;  // millicelsius
        int32_t humidityRaw;     // millipercent
        status = scd4x_read_measurement(&co2Raw, &temperatureRaw, &humidityRaw);
        if (status) {
            printf("Unable to read measurement data. Error: %d\n", status);
            return status;
        }

        const int co2Ppm = co2Raw;
        const float temperatureCelsius = temperatureRaw / 1000.0f;
        const float temperatureFahrenheit = temperatureCelsius * 1.8f + 32;
        const float humidityPercent = humidityRaw / 1000.0f;

        printf("CO2: %d ppm, Temperature: %.1f C (%.1f F), Humidity: %.1f%%\n",
               co2Ppm, temperatureCelsius, temperatureFahrenheit,
               humidityPercent);
    }
}
