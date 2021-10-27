#pragma once

// definitions outside of UEFI scope
using u64 = unsigned long long;
using u32 = unsigned int;
using u16 = unsigned short;
using u8  = unsigned char;
using i64 = signed long long;
using i32 = signed int;
using i16 = signed short;
using i8  = signed char;
using usz = u64;
using isz = i64;
using c8 = char;
using c16 = wchar_t;

// definitions tightly coupled with UEFI
namespace efi {

using status = usz;
using handle = void *;
using event = void *;
using lba = u64;
using tpl = usz;
using physical_address = u64;
using virtual_address = u64;

struct guid {
    u32 data1;
    u16 data2;
    u16 data3;
    u8  data4[8];
};

struct time {
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 second;
    u8 padding1;
    u32 nanosecond;
    i16 time_zone;
    u8 daylight;
    u8 padding2;
};

using event_notify = void (*)(event event, void *context);

enum class timer_delay {
    timer_cancel,
    timer_periodic,
    timer_relative
};

enum class allocate_type {
    allocate_any_pages,
    allocate_max_address,
    allocate_address,
    max_allocate_type
};

enum class memory_type {
    reserved,
    loader_code,
    loader_data,
    boot_services_code,
    boot_services_data,
    runtime_services_code,
    runtime_serviced_data,
    conventional,
    unusable,
    acpi_reclaim,
    acpi_nvs,
    memory_mapped_io,
    memory_mapped_io_port_space,
    pal_code,
    persistent,
    max_memory_type
};

struct memory_descriptor {
    u32 type;
    physical_address physical_start;
    virtual_address virtual_start;
    u64 number_of_pages;
    u64 attribute;
};

enum class interface_type {
    native_interface
};

enum class locate_search_type {
    all_handles,
    by_register_notify,
    by_protocol
};

struct open_protocol_information_entry {
    handle agent_handle;
    handle controller_handle;
    u32 attributes;
    u32 open_count;
};

} // namespace efi

