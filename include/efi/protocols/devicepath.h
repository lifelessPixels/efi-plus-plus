#pragma once
#include "../basetypes.h"

namespace efi::protocols {

struct device_path {

    enum class node_type : u8 {
        hardware = 0x01,
        acpi = 0x02,
        messaging = 0x03,
        media = 0x04,
        bios_boot_specification = 0x05,
        end_of_path = 0x7f
    };

    enum class end_subtype : u8 {
        entire_path_end = 0xff,
        instance_end = 0x01
    };

    enum class hardware_subtype : u8 {
        pci = 0x01,
        pccard = 0x02,
        memory_mapped = 0x03,
        vendor = 0x04,
        controller = 0x05,
        bmc = 0x06
    };

    enum class acpi_subtype : u8 {
        acpi = 0x01,
        expanded_acpi = 0x02,
        acpi_adr = 0x03,
        nvdimm = 0x04
    };

    enum class messaging_subtype : u8 {
        atapi = 0x01,
        scsi = 0x02,
        fibre_channel = 0x03,
        fibre_channel_ex = 0x15,
        ieee1394 = 0x04,
        usb = 0x05,
        sata = 0x12,
        usb_device_wwid = 0x10,
        device_logical_unit = 0x11,
        usb_device_class = 0x0f,
        i2o = 0x06,
        mac_address = 0x0b,
        ipv4 = 0x0c,
        ipv6 = 0x0d,
        vlan = 0x14,
        infiniband = 0x09,
        uart = 0x0e,
        vendor = 0x0a,
        sas_ex = 0x16,
        iscsi = 0x13,
        nvme_namespace = 0x17,
        uri = 0x18,
        ufs = 0x19,
        sd = 0x1a,
        efi_bluetooth = 0x1b,
        wireless = 0x1c,
        emmc = 0x1d,
        efi_bluetooth_le = 0x1e,
        dns = 0x1f,
        nvdimm_namespace = 0x20,
        rest_service = 0x20 // NOTE: maybe an error in UEFI spec
    };

    enum class media_subtype : u8 {
        hard_drive = 0x01,
        cd_rom = 0x02,
        vendor = 0x03,
        file_path = 0x04,
        media_protocol = 0x05,
        piwg_firmware_file = 0x06,
        piwg_firmware_volume = 0x07,
        relative_offset = 0x08,
        ram_disk = 0x09
    };

    enum class bios_boot_specification_subtype : u8 {
        bios_boot_specification_version_1_01 = 0x01
    };

    u8 type;
    u8 subtype;
    u16 length;

    static constexpr guid protocol_guid = {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
};

struct device_path_utilities {
    usz (*get_device_path_size)(device_path *device_path);
    device_path *(*get_duplicate_device_path)(device_path *device_path);
    device_path *(*append_device_path)(device_path *source1, device_path *source2);
    device_path *(*append_device_node)(device_path *device_path_, device_path *device_node);
    device_path *(*append_device_path_instance)(device_path *device_path_, device_path *device_path_instance);
    device_path *(*get_next_device_path_instance)(device_path **device_path_instance, usz *device_path_instance_size);
    bool *(*is_device_multi_instance)(device_path *device_path);
    device_path *(*create_node)(u8 node_type, u8 node_sub_type, u16 node_length);

    static constexpr guid protocol_guid = {0x0379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4}};
};

struct device_path_to_text {
    c16 *(*convert_device_node_to_text)(device_path *device_node, bool display_only, bool allow_shortcuts);
    c16 *(*convert_device_path_to_text)(device_path *device_path, bool display_only, bool allow_shortcuts);

    static constexpr guid protocol_guid = {0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c}};
};

struct device_path_from_text {
    device_path *(*convert_text_to_device_node)(c16 *text_device_node);
    device_path *(*convert_path_to_device_node)(c16 *text_device_path);

    static constexpr guid protocol_guid = {0x5c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e}};
};
    
} // namespace efi::protocols