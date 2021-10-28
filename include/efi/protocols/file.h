#pragma once
#include "../basetypes.h"

namespace efi {

struct file_info {
    u64 size;
    u64 file_size;
    u64 physical_size;
    time create_time;
    time last_access_time;
    time modification_time;
    u64 attribute;
    c16 filename[];

    static constexpr guid info_guid = {0x09576e92, 0x6d3f, 0x11d2, {0x8e39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
};

struct file_system_info {
    u64 size;
    bool read_only;
    u64 volume_size;
    u64 free_space;
    u32 block_size;
    c16 volume_label[];

    static constexpr guid info_guid = {0x09576e93, 0x6d3f, 0x11d2, {0x8e39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
};

struct file_system_volume_label {
    c16 volume_label[];

    static constexpr guid info_guid = {0xdb47d7d3, 0xfe81, 0x11d3, {0x9a35, 0x00, 0x90, 0x27, 0x3f, 0xC1, 0x4d}};
};

namespace protocols {

struct file {

    enum class mode : u64 {
        create = 0x00,
        read = 0x01,
        write = 0x02
    };

    enum class attribute : u64 {
        read_only = 0x01,
        hidden = 0x02,
        system = 0x04,
        reserved = 0x08,
        directory = 0x10,
        archive = 0x20,
        valid_attribute = 0x37
    };

    struct io_token {
        event event;
        status status;
        usz buffer_size;
        void *buffer;
    };

    u64 revision;
    status (*open)(file *proto, file **new_handle, c16 *file_name, u64 open_mode, u64 attributes);
    status (*close)(file *proto);
    status (*delete_)(file *proto);
    status (*read)(file *proto, usz *buffer_size, void *buffer);
    status (*write)(file *proto, usz *buffer_size, void *buffer);
    status (*get_position)(file *proto, u64 *position);
    status (*set_position)(file *proto, u64 position);
    status (*get_info)(file *proto, guid *info_type, usz *buffer_size, void *buffer);
    status (*set_info)(file *proto, guid *info_type, usz buffer_size, void *buffer);
    status (*flush)(file *proto);
    status (*open_ex)(file *proto, file **new_handle, c16 *file_name, u64 open_mode, u64 attributes, io_token *token);
    status (*read_ex)(file *proto, io_token *token);
    status (*write_ex)(file *proto, io_token *token);
    status (*flush_ex)(file *proto, io_token *token);
};

struct simple_file_system {
    u64 revision;
    status (*open_volume)(simple_file_system *proto, file **root);

    static constexpr guid protocol_guid = {0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
};

} // namespace protocols
} // namespace efi