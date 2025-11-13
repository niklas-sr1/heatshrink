# Using Heatshrink as an ESP-IDF Component

This document describes how to use heatshrink as an ESP-IDF component.

## Installation

### Method 1: Using ESP Component Manager (Recommended)

Once published to the ESP Component Registry, you can add heatshrink to your project:

```bash
idf.py add-dependency "heatshrink"
```

### Method 2: Manual Installation

Copy this entire heatshrink directory into your project's `components` folder:

```
my_project/
├── components/
│   └── heatshrink/
│       ├── CMakeLists.txt
│       ├── Kconfig
│       ├── heatshrink_encoder.h
│       ├── heatshrink_encoder.c
│       ├── heatshrink_decoder.h
│       ├── heatshrink_decoder.c
│       ├── heatshrink_common.h
│       └── heatshrink_config.h
├── main/
└── CMakeLists.txt
```

## Configuration

Heatshrink provides several configuration options through ESP-IDF's menuconfig system:

```bash
idf.py menuconfig
```

Navigate to `Component config` → `Heatshrink Configuration` to configure:

### Dynamic vs Static Allocation

- **Use dynamic memory allocation** (default: enabled)
  - When enabled: Use `heatshrink_encoder_alloc()` and `heatshrink_decoder_alloc()` functions
  - When disabled: Use static allocation with compile-time configuration

### Static Configuration (when dynamic allocation is disabled)

- **Static window size (bits)**: 4-15, default 8
  - Window size = 2^N bytes
  - Larger values compress better but use more memory
  
- **Static lookahead size (bits)**: 3-14, default 4
  - Lookahead size = 2^N bytes
  - Must be less than window_bits
  
- **Static input buffer size (bytes)**: 1-65535, default 32
  - Decoder input buffer size

### Performance Options

- **Use index for faster compression** (default: enabled)
  - Enables faster compression at the cost of additional memory (2^(window_size+1) bytes)
  
- **Enable debugging logs** (default: disabled)
  - Enable only for development/troubleshooting

## Usage in Your Code

### Include Headers

```c
#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"
```

### Dynamic Allocation Example

```c
// Create encoder
heatshrink_encoder *hse = heatshrink_encoder_alloc(8, 4);
if (!hse) {
    // Handle allocation error
}

// Use encoder...
heatshrink_encoder_sink(hse, input_buf, size, &input_size);
heatshrink_encoder_poll(hse, output_buf, out_size, &output_size);
heatshrink_encoder_finish(hse);

// Free encoder
heatshrink_encoder_free(hse);
```

### Static Allocation Example

Configure via menuconfig:
- Disable "Use dynamic memory allocation"
- Set window bits, lookahead bits, and input buffer size

```c
// Declare static encoder/decoder
static heatshrink_encoder hse;

// Initialize
heatshrink_encoder_reset(&hse);

// Use encoder...
heatshrink_encoder_sink(&hse, input_buf, size, &input_size);
heatshrink_encoder_poll(&hse, output_buf, out_size, &output_size);
heatshrink_encoder_finish(&hse);
```

## Component Dependencies

Add heatshrink as a requirement in your component's CMakeLists.txt:

```cmake
idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES heatshrink
)
```

## Memory Considerations

Memory usage depends on configuration:

### Dynamic Allocation
- Encoder: ~50-300 bytes + window buffer (2^window_bits bytes)
- With index: + 2^(window_bits+1) bytes
- Decoder: ~50-100 bytes + window buffer + input buffer

### Static Allocation
- Memory allocated at compile time
- Use when exact memory usage must be known
- Good for resource-constrained applications

## Further Information

See the main [README.md](README.md) for detailed API documentation and usage examples.
