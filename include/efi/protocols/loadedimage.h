#pragma once
#include "../basetypes.h"
#include "../tables.h"

namespace efi::protocols {

struct loaded_image {
    u32 revision;
    handle parent_handle;
    system_table *system_table;
    handle device_handle;
    device_path_protocol *file_path;
    void *reserved;
    u32 load_options_size;
    void *load_options;
    void *image_base;
    u64 image_size;
    memory_type image_code_type;
    memory_type image_data_type;
    status (*unload)(handle image_handle);

    static constexpr guid protocol_guid = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
};

struct loaded_image_path : device_path_protocol {
    static constexpr guid protocol_guid = {0xbc62157e, 0x3e33, 0x4fec, {0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf}};
};

} // namespace efi::protocols