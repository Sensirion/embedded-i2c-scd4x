# Getting started

To get the embedded driver for your Sensirion Sensor working there are now
only a few steps missing. These steps are needed since our driver is made
in a way that it is possible to run it on different hardware platforms.
So we need to adjust two files according to your platform.
The first one is `sensirion_i2c_hal.c`.
This file contains the implementation of the sensor communication
(how to send requests to it). Therefore, how this is done depends on your
hardware platform. For this reason we can't provide just one version of this
code. The default version of this file is an unimplemented template, where you
can implement it yourself. For some common platforms we provide an
implementation in the `sample-implementations` folder.
If you are using for example a Linux based platform like Raspberry Pi
you can just replace the unimplemented HAL template with the provided
implementation in `sample-implementations/linux_user_space/` by replacing
the template with the actual implementation:

```
cp sample-implementations/linux_user_space/sensirion_i2c_hal.c ./
```

If you are on a different platform just use one of the other sample
implementations or implement `sensirion_i2c_hal.c` yourself.
The second file is `sensirion_config.h`.
If you are on a Linux based platform you can skip this part since
everything is already correctly setup for you.
Otherwise you need to check if the libraries `<stdint.h>` and
`<stdlib.h>` are provided by your toolchain, compiler or are available
on your system. If you have no idea on how to do that you can skip this
step for now and come back when you get errors including these names when
trying to compile your driver.
The features we use out of those libraries is standard integer sizes
from `<stdint.h>` and `NULL` from `<stdlib.h>`. If they are not available
you need to specify the following integer types yourself:
* `int64_t` = signed 64bit integer
* `uint64_t` = unsigned 64bit integer
* `int32_t` = signed 32bit integer
* `uint32_t` = unsigned 32bit integer
* `int16_t` = signed 16bit integer
* `uint16_t` = unsigned 16bit integer
* `int8_t` = signed 8bit integer
* `uint8_t` = unsigned 8bit integer

In addition to that you will need to specify `NULL`.
For both we have a commented template where just need to fill in
your system specific values.
Now we are ready to compile and run the example usage for your sensor.
This is again specific to your platform. Since this step can vary quite
a lot we here just explain how to do it on Linux based platforms. In
general you now just need to take all the `.c` and `.h` files directly in
this folder pass them to your favorite C compiler and run the resulting
binary. For Linux systems this is done by following these steps:

1. Open up a terminal.
2. Navigate the directory where this README is located.
3. Run `make`, this compiles all the code here to one binary.
4. Run `./[SENSORNAME]_example_usage`, where you replace `[SENSORNAME]`
   with your sensors name. This will run your newly compiled binary.
5. Now you should see the first measurement values appear in your terminal.
   As a next step you can adjust the example usage file or write your own
   main function to use the sensor.

We hope this tutorial was helpful and you are now able to use the embedded drivers
to communicate with your Sensirion sensor.

# Background

## Files

### sensirion\_i2c.[ch]

In these files you can find the implementation of the I2C protocol used by Sensirion
sensors. The functions in these files are used by the embedded driver to build the
correct frame out of data to be sent to the sensor or receive a frame of data from
the sensor and convert is back to data readable by your machine. The functions in
here calculate and check CRCs, reorder bytes for different byte orders and build the
correct formatted frame for your sensor.

### sensirion\_i2c\_hal.[ch]

In these files you can find the implementation of the hardware abstraction layer used
by Sensirion I2C embedded drivers. This part of the code is specific to the underlying
hardware platform, therefore multiple implementations exist. We also provide an
unimplemented template for the user to implement.
In the `sample-implementations/` folder we provide implementations for the most common
platforms.

### sensirion\_config.h

In this file we keep all the included libraries for our drivers and global defines.
Next to `sensirion_i2c_hal.c` *it's the only file you should need to edit to get your
driver working.*

### sensirion\_common.[ch]

In these files you can find some helper functions used by Sensirion embedded drivers.
It mostly contains byte order conversions for different variable types. These functions
are also used by the UART embedded drivers therefore they are keep in their own file.
