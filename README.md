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

- A microcontroller (e.g., STM32, ESP32, nRF52,rpi-pico(RP2040/RP2350), etc.)
- SPI driver for your target MCU

### Integration

1. **Clone this repository**:
    ```bash
    git clone https://github.com/pdlsurya/sdFat32.git
    ```

2. **Add to your project**:
   - Include the `fat32.h` and corresponding `.c` files in your build system.
   - Include the `sd_platform.h` and corresponding `.c` file for selected platform.

3. **Initialize and use the driver**:
    ```c
    #include "fat32.h"
    if (fat32Init()) {
        file myFile = fileOpen("/", "example.txt", FILE_MODE_READ);
        if (fileIsValid(&myFile)) {
            uint8_t byte = fileReadByte(&myFile);
            // Process byte...
            fileClose(&myFile);
        }
    }
    ```

### File System Functions

| Function | Description |
|----------|-------------|
| `fat32Init()` | Initializes the FAT32 file system |
| `fileOpen(path, filename,accessMode)` | Opens a file for reading or writing |
| `fileReadByte(pFile)` | Reads a single byte from a file |
| `fileWrite(pFile, data)` | Writes a string to a file |
| `fileDelete(path, filename)` | Deletes a file |
| `fileGetNext(pFile)` | Iterates to the next file in a directory |
| `fileGetName(pFile)` | Returns the full name of a file (including extension) |
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
[GitHub](https://github.com/<your-username>)

---

Contributions, suggestions, and issues are welcome!
