#pragma once
#include "../basetypes.h"

namespace efi::protocols {

struct simple_text_output {
    status (*reset)(simple_text_output *proto, bool extended_verification);
    status (*output_string)(simple_text_output *proto, const c16 *string);
    status (*test_string)(simple_text_output *proto, const c16 *string);
    status (*query_mode)(simple_text_output *proto, usz mode_number, usz *columns, usz *rows);
    status (*set_mode)(simple_text_output *proto, usz mode_number);
    status (*set_attribute)(simple_text_output *proto, usz attribute);
    status (*clear_screen)(simple_text_output *proto);
    status (*set_cursor_position)(simple_text_output *proto, usz column, usz row);
    status (*enable_cursor)(simple_text_output *proto, bool visible);

    static constexpr guid protocol_guid = {0x387477c2, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
};

} // namespace efi::protocols