# CPU Load Logger Kernel Module

This kernel module logs the CPU load every `N` seconds, where `N` is configurable via the `interval` parameter. The CPU load is fetched from the kernel's `avenrun` array, which holds load averages over 1, 5, and 15 minutes. The module utilizes a timer to log the CPU load at regular intervals and can be customized based on the specified `interval`.

## Features
- Logs CPU load every configurable interval.
- The interval is adjustable by setting the `interval` module parameter.
- The load is logged using the 1-minute load average from the kernel's `avenrun` array.
- The module logs the CPU load in a human-readable format.

## Prerequisites
- **Linux Kernel**: This module is designed for use in the Linux kernel.
- **Kernel Development Tools**: Ensure that the necessary tools for building kernel modules are installed on your system (e.g., `make`, `gcc`, `kernel-headers`).

## Installation
1. **Clone or Download the Code**:
   - Clone this repository or download the `cpu_load_logger.c` file to your system.

2. **Build the Module**:
   - Create a `Makefile` for building the kernel module, or use the following basic Makefile:

     ```
     obj-m += cpu_load_logger.o
     all:
         make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
     clean:
         make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
     ```

   - Run `make` to compile the kernel module.

3. **Load the Module**:
   - Once the module is compiled, load it into the kernel using:

     ```
     sudo insmod cpu_load_logger.ko interval=10
     ```

     This command loads the module with an interval of 10 seconds (default value).

4. **Check the Logs**:
   - The module logs the CPU load every `N` seconds using `dmesg`. To see the output, run:

     ```
     dmesg | grep "CPU Load Logger"
     ```

5. **Unload the Module**:
   - To remove the module from the kernel, run:

     ```
     sudo rmmod cpu_load_logger
     ```

## Module Parameters
- **interval**: Defines the time interval (in seconds) between each log entry. The default value is `10` seconds.

## How It Works
1. The module sets up a timer that invokes a callback function (`log_cpu_load`) at regular intervals.
2. The `log_cpu_load` function retrieves the 1-minute load average from the `avenrun[0]` value.
3. The load average is then split into integer and fractional parts, and the CPU load is logged using `pr_info`.
4. The timer is re-armed after every callback to log the load continuously.


## Exit Code
- **0**: Successful initialization of the module.
- **1**: Error in initialization (not expected under normal circumstances).

## License
This kernel module is released under the **GPL-2.0 License**.

## Author
- **Vladyslav Yavorskyi**

## Notes
- The module works on Linux systems with a kernel version that supports the `avenrun` array and timer functions.
- The module is primarily intended for monitoring system load in development or testing environments.
- Ensure you have appropriate permissions to load/unload kernel modules and access `dmesg` output.

## Troubleshooting
- If the module doesn't seem to work as expected, ensure that the `interval` parameter is set correctly and that you are checking the logs with `dmesg`.

