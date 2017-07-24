#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

const char *utf8_phrase = "見ぬが花";

unsigned char codepoints[16] = {
    0x8B, 0x89, 0x00, 0x00,
    0x6C, 0x30, 0x00, 0x00,
    0x4C, 0x30, 0x00, 0x00,
    0xB1, 0x82, 0x00, 0x00,
};

unsigned char utf8_bytes[13] = {
    0xE8, 0xA6, 0x8B, 0xE3,
    0x81, 0xAC, 0xE3, 0x81,
    0x8C, 0xE8, 0x8A, 0xB1,
    0x00
};

unsigned char utf16le_bytes[10] = {
    0x8B, 0x89,
    0x6C, 0x30,
    0x4C, 0x30,
    0xB1, 0x82,
    0x00, 0x00,
};

unsigned char utf16be_bytes[10] = {
    0x89, 0x8B,
    0x30, 0x6C,
    0x30, 0x4C,
    0x82, 0xB1,
    0x00, 0x00
};

unsigned char utf32le_bytes[20] = {
    0x8B, 0x89, 0x00, 0x00, 
    0x6C, 0x30, 0x00, 0x00, 
    0x4C, 0x30, 0x00, 0x00, 
    0xB1, 0x82, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

unsigned char utf32be_bytes[20] = {
    0x00, 0x00, 0x89, 0x8B,
    0x00, 0x00, 0x30, 0x6C,
    0x00, 0x00, 0x30, 0x4C,
    0x00, 0x00, 0x82, 0xB1,
    0x00, 0x00, 0x00, 0x00
};

unsigned char shiftjis_bytes[9] = {
    0x8C, 0xA9, 0x82, 0xCA, 0x82, 0xAA, 0x89, 0xD4, 0x00
};

typedef struct EncodingInfoStruct {
    const char *name;
    unsigned char *data;
    size_t len;
} EncodingInfo;

EncodingInfo encoding_info[6] = {
    { "utf-8",     &utf8_bytes[0],     sizeof(utf8_bytes)     },
    { "utf-16le",  &utf16le_bytes[0],  sizeof(utf16le_bytes)  },
    { "utf-16be",  &utf16be_bytes[0],  sizeof(utf16be_bytes)  },
    { "utf-32le",  &utf32le_bytes[0],  sizeof(utf32le_bytes)  },
    { "utf-32be",  &utf32be_bytes[0],  sizeof(utf32be_bytes)  },
    { "shift-jis", &shiftjis_bytes[0], sizeof(shiftjis_bytes) },
};

void test_charset(void **state) {
    Slice inslice;
    Slice outslice;
    Buffer out;
    String sout;
    Status status;

    (void)state;

    status_clear(&status);

    assert_true(buffer_init_alloc(&out, 64, &status));
    assert_true(string_init(&sout, " ", &status));
    assert_true(string_ensure_capacity(&sout, 64, &status));

    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 6; j++) {
            EncodingInfo *from_encoding = &encoding_info[i];
            EncodingInfo *to_encoding = &encoding_info[j];

            if (j == i) {
                continue;
            }

            buffer_clear(&out);
            inslice.data = (char *)from_encoding->data;
            inslice.len = from_encoding->len;
            outslice.data = out.data;
            outslice.len = out.alloc;
            assert_true(charset_convert(&inslice, from_encoding->name,
                                                  to_encoding->name,
                                                  &outslice,
                                                  &status));
            out.len = (outslice.data - out.data);
            assert_int_equal(out.len, to_encoding->len);
            assert_memory_equal(out.data, to_encoding->data, out.len);

            string_clear(&sout);
            assert_true(string_assign_buffer(&sout, &out, to_encoding->name,
                                                          &status));
            assert_int_equal(sout.byte_len, strlen(utf8_phrase) + 1);
            assert_memory_equal(sout.data, utf8_phrase, sout.byte_len);

            buffer_clear(&out);
            assert_true(string_encode(&sout, from_encoding->name, &out,
                                                                  &status));
            assert_int_equal(out.len, from_encoding->len);
            assert_memory_equal(out.data, from_encoding->data, out.len);
        }
    }
}

/* vi: set et ts=4 sw=4: */
