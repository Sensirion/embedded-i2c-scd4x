# CHANGELOG

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased] 


## [1.0.1] - 2025-2-1

- add convenience method to read out measurements again

## [1.0.0] - 2025-1-30

### Added

- All commands according to data sheet


### Changed

Note that there are breaking changes compared to 0.1.0
- You need to call scd4x_init(SCD41_I2C_ADDR_62); befor sending any command to set the I2c address of the sensor
- all methods that have been named xxxTicks are now named xxxRaw
- getDataReadyFlag has been renamed to getDataReadyStatus
- data type for parameter count in HAL implementation has been changed from uint16_t to uint8_t 
- scd4x_set_ambient_pressure takes now a uint32_t in Pa and scd4x_set_ambient_pressure_raw takes a uint16_t in hPa
- scd4x_get_ambient_pressure returns now a uint32_t in Pa and scd4x_get_ambient_pressure_raw returns a uint16_t in hPa
- scd4x_get_automatic_self_calibration/scd4x_set_automatic_self_calibration has been renamed to scd4x_get_automatic_self_calibration_enabled/scd4x_set_automatic_self_calibration_enabled
- signature of scd4x_get_serial_number has changed
- removed read_measurement convenience method - see bugfix 1.0.1 where it is added again


## [0.1.0] - 2021-2-1

### Added

- Initial version
- Check latest 0.x.x version for changelog prior to version 1.0.0

[Unreleased]: https://github.com/Sensirion/embedded-i2c-scd4x/compare/1.0.0...HEAD
[1.0.0]: https://github.com/Sensirion/embedded-i2c-scd4x/compare/0.1.0...1.0.0
[0.1.0]: https://github.com/Sensirion/embedded-i2c-scd4x/releases/tag/0.1.0