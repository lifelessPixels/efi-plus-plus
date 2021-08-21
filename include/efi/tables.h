#pragma once
#include "basetypes.h"
#include "protocols/devicepath.h"
#include "protocols/simpletextoutput.h"

// UEFI defined tables
namespace efi {

struct table_header {
    u64 signature;
    u32 revision;
    u32 header_size;
    u32 crc32;
    u32 reserved;
};

// boot services

struct boot_services {
    table_header header;

    tpl (*raise_tpl)(tpl new_tpl);
    void (*restore_tpl)(tpl old_tpl);

    status (*allocate_pages)(allocate_type type, memory_type memory_type, usz pages, physical_address *memory);
    status (*free_pages)(physical_address memory, usz pages);
    status (*get_memory_map)(usz *memory_map_size, memory_descriptor *memory_map, usz *map_key, usz *descriptor_size, u32 *descriptor_version);
    status (*allocate_pool)(memory_type pool_type, usz size, void **buffer);
    status (*free_pool)(void *buffer);

    status (*create_event)(u32 type, tpl notfiy_tpl, event_notify notify_function, void *notify_context, event *event);
    status (*set_timer)(event event, timer_delay type, u64 trigger_time);
    status (*wait_for_event)(usz number_of_events, event event, usz *index);
    status (*signal_event)(event event);
    status (*close_event)(event event);
    status (*check_event)(event event);
    
    status (*install_protocol_interface)(handle *handle, guid *protocol, interface_type interface_type, void *interface);
    status (*reinstall_protocol_interface)(handle *handle, guid *protocol, void *old_interface, void *new_interface);
    status (*uninstall_protocol_interface)(handle *handle, guid *protocol, void *interface);
    status (*handle_protocol)(handle handle, guid *protocol, void **interface);
    void *reserved;
    status (*register_protocol_notify)(guid *protocol, event event, void *registration);
    status (*locate_handle)(locate_search_type search_type, guid *protocol, void *search_key, usz *buffer_size, handle *buffer);
    status (*locate_device_path)(guid *protocol, protocols::device_path_protocol **device_path, handle *device);
    status (*install_configuration_table)(guid *guid, void *table);

    status (*load_image)(bool boot_policy, handle parent_image_handle, protocols::device_path_protocol **device_path, void *source_buffer, usz source_size, handle *image_handle);
    status (*start_image)(handle image_handle, usz *exit_data_size, c16 **exit_data);
    status (*exit)(handle image_handle, status exit_status, usz exit_data_size, c16 exit_data);
    status (*unload_image)(handle image_handle);
    status (*exit_boot_services)(handle image_handle, usz map_key);

    status (*get_next_monotonic_count)(u64 *count);
    status (*stall)(usz microseconds);
    status (*set_watchdog_timer)(usz timeout, u64 watchdog_code, usz data_size, c16 *watchdog_data);

    status (*connect_controller)(handle controller_handle, handle *driver_image_handle, protocols::device_path_protocol *remaining_device_path, bool recursive); 
    status (*disconnect_controller)(handle controller_handle, handle driver_image_handle, handle child_handle);

    status (*open_protocol)(handle open_handle, guid *protocol, void **interface, handle agent_handle, handle controller_handle, u32 attributes);
    status (*close_protocol)(handle close_handle, guid *protocol, handle agent_handle, handle controller_handle);
    status (*open_protocol_information)(handle handle, guid *protocol, open_protocol_information_entry **entry_buffer, usz *entry_count);
    
    status (*protocols_per_handle)(handle handle, guid ***protocol_buffer, usz *protocol_buffer_count);
    status (*locate_handle_buffer)(locate_search_type search_type, guid *protocol, void *search_key, usz *number_of_handles, handle **buffer);
    status (*locate_protocol)(guid *protocol, void *registration, void **interface);
    status (*install_multiple_protocol_interfaces)(handle *handle, ...);
    status (*uninstall_multiple_protocol_interfaces)(handle handle, ...);

    status (*calculate_crc32)(void *data, usz data_size, u32 *crc32);

    status (*copy_memory)(void *destination, void *source, usz length);
    status (*set_memory)(void *buffer, usz size, u8 value);
    status (*create_event_ex)(u32 type, tpl notify_tpl, event_notify notify_function, void *notify_context, guid *event_group, event *event);
};

// TODO: change void pointers to correct types as they are created
struct system_table {
    table_header header;
    c16 *firmware_vendor;
    u32 firmware_revision;
    handle console_in_handle;
    void *console_in;
    handle console_out_handle;
    protocols::simple_text_output *console_out;
    handle standard_error_handle;
    void *standard_error;
    void *runtime_services;
    boot_services *boot_services;
    usz number_of_table_entries;
    void *configuration_table;
};

} // namespace efi