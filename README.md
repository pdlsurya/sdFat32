# sdFat32

A lightweight FAT32 driver for microcontrollers interfacing with SD cards over SPI. This library is designed to run on bare-metal systems with minimal dependencies, enabling file system access for embedded platforms.

## Features

- FAT32 support for SD cards via SPI
- Read/write/delete file operations
- Directory listing and recursive traversal
- Long File Name (LFN) support
- Directory creation and deletion
- Clean and modular structure for portability

## Getting Started

### Prerequisites

- A microcontroller (Currently supported platform:`Arduino`, `STM32`, `ESP32`, `nRF52`,`rpi-pico(RP2040/RP2350)`)
- SPI driver for your target MCU

> ESP32 support uses the custom [`esp32-riscv-bare-metal-sdk`](https://github.com/pdlsurya/esp32-riscv-bare-metal-sdk) platform layer and is intended for ESP32 RISC-V targets such as ESP32-C6 and ESP32-P4.

### Integration

1. **Clone this repository**:
    ```bash
    git clone https://github.com/pdlsurya/sdFat32.git
    ```

2. **Add to your project**:

- ***Add the src/ folder***:
  Include the src/ folder of the SdFat32 library into your project. This contains the core source files required to use the library.
- ***Add your platform/ folder***:
Include the folder that matches your platform (e.g., `platform/rpi-pico/`, `platform/stm32/`, `platform/esp32/`, etc.) along with the source file inside it. This contains platform-specific implementations needed for SdFat32 to work properly on your hardware.

3. **Initialize and use the driver**:

 ```c
    #include "sdFat32.h"

    uint8_t data[8];
   
    if (sdFat32Init()) {
        file myFile = fileOpen("/", "example.txt", FA_READ);
        if (fileIsValid(&myFile)) {
            fileRead(&myFile,data,8);
            // Process data...
            fileClose(&myFile);
        }
    }

```

### File System Functions

| Function | Description |
|----------|-------------|
| `sdFat32Init()` | Initializes the FAT32 file system |
| `fileOpen(path, filename, accessMode)` | Opens a file with corresponding access mode|
| `fileRead(pFile, data, len)` | Reads from a file |
| `fileWrite(pFile, data, len)` | Writes to a file|
| `fileDelete(path, filename)` | Deletes a file |
| `fileGetNext(pDir)` | Iterates to the next file in a directory |
| `fileGetName(pFile)` | Returns the full name of a file (including extension) |
|  `fileIsValid(pFile)` | Checks if a filed is valid |
| `createDirectory(path, dirName)` | Creates a new subdirectory |
| `listDirectory(path)` | Lists contents of a directory |
| `listDirectoryRecursive(pFolder, tab)` | Recursively lists directory contents |


### Notes

- Long File Name entries are supported and parsed correctly.
- All structures map closely to FAT32 specification (e.g., directory entries, FSInfo).
- The library supports directory navigation and file searching within clusters.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Surya Poudel**  
[GitHub](https://github.com/pdlsurya)

---

Contributions, suggestions, and issues are welcome!
