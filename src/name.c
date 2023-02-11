#include "usb_names.h"

#define MIDI_NAME {'S','t','o','m','p','y'}
#define MIDI_NAME_LEN 6

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};
