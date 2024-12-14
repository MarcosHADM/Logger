# LOGGER

A lightweight and efficient logging library designed for microcontrollers such as Arduino, ESP32, and similar devices. Logger simplifies debugging and monitoring by providing structured log output, tailored specifically for embedded systems.
<br><br>
Compatible with [PlatformIO](https://platformio.org/), this library is easy to integrate and optimized for resource-constrained devices.

## Table of Contents

-   [Features](#features)
-   [Limitations](#installation)
-   [Usage](#usage)
    -   [Basic Example](#basic-example)
    -   [Supported Log Levels](#supported-log-levels)
    -   [Logger Configuration](#logger-configuration)
-   [Project Roadmap](#project-roadmap)
-   [Contributing](#contributing)
    -   [Contributor Graph](#contributor-graph)
-   [License](#license)
-   [Author](#author)

## Features

-   **Log Levels**: Supports five essential levels: `Debug`, `Info`, `Warn`, `Error`, and `Critical`.
-   **PlatformIO Compatible**: Seamlessly integrates into PlatformIO-based projects.
-   **Low Resource Usage**: Designed for minimal memory and CPU overhead.

## Limitations

-   **No Custom Log Levels**: Only supports pre-defined levels (`Debug`, `Info`, `Warn`, `Error`, `Critical`).
-   **No Persistent Storage**: Logs are currently not saved to non-volatile memory or external storage.
-   **Not Extensible**: The library does not support plugins or additional features at this time.

## Installation

Clone or download the repository and integrate it with your PlatformIO project:

1. Copy the `Logger` library folder into your project's `lib` directory.
2. Include the library in your code.

## Usage

### Basic Example

```cpp
#include <Arduino.h>
#include <Logger.h>

Logger logger(Debug, "[{time}] {level} [{file}.{function}.{lineno}] {message}"); // Create a logger instance with log level Info

void setup()
{
    Serial.begin(115200);

    Serial.println("\n");
    LOG(Debug, "This is a debug message");
    LOG(Info, "This is the number %d: %d", 3, 3);
    LOG(Warning, "Countdown: %d, %d, %d", 3, 2, 1);
    LOG(Error, "Error encountered: %s", "Value invalid");
    LOG(Critical, "This is a critical message");
}
```

### Supported Log Levels

The library supports the following log levels:

1. **Debug**: Detailed information for debugging.
2. **Info**: General system information.
3. **Warn**: Warnings for potential issues.
4. **Error**: Errors requiring immediate attention.
5. **Critical**: Severe issues affecting system stability.

### Logger Configuration

Customize the logger when initializing:

```cpp
Logger logger({Log Level}, {Log Format}); // Enable timestamps in the Serial output
```

**Configuration Options**:

-   **Log Level**: Set the minimum log level to display (e.g., `Debug`, `Info`, `Warn`, `Error`, `Critical`).
-   **Log Format**: Define the format for log messages, including placeholders for timestamp, log level, file, function, line number, and message.

## Project Roadmap

-   [ ] **`Persistent Logs`**: Add support for saving logs to SD cards or EEPROM.
-   [ ] **`Multi-Interface Support`**: Enable logging over UART, I2C, or SPI.

## Contributing

Contributions are welcome! Here's how you can help:

-   **📋 [Contribute to the Project](./CONTRIBUTING.md)**: Review the contribution guidelines and consider submitting a pull request.
-   **🐛 [Report Issues](https://github.com/MarcosHelbert/Logger/issues)**: Submit bugs found or log feature requests for the project.
-   **💡 [Submit Pull Requests](https://github.com/MarcosHelbert/Logger/pulls)**: Review open PRs, and submit your own PRs.

### Contributor Graph

<p align="center">
   <a href="https://github.com/MarcosHelbert/Logger/graphs/contributors">
      <img src="https://contrib.rocks/image?repo=MarcosHelbert/Logger">
   </a>
</p>

## License

This project is protected under the MIT License. For more details, refer to the [LICENSE](./LICENSE.md) file.

## Author

Developed by [Marcos Helbert](https://github.com/MarcosHelbert).

Feel free to open issues or share suggestions for improving the library!
