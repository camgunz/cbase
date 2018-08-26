#include <setjmp.h>
#include <stdio.h>

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
    Buffer in;
    Buffer out;
    String sout;
    Status status;

    (void)state;

    status_clear(&status);

    assert_true(buffer_init_alloc(&in, 64, &status));
    assert_true(buffer_init_alloc(&out, 64, &status));
    assert_true(string_init_alloc(&sout, 64, &status));

    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 6; j++) {
            size_t len = 0;
            EncodingInfo *from_encoding = &encoding_info[i];
            EncodingInfo *to_encoding = &encoding_info[j];

            if (j == i) {
                continue;
            }

            puts(from_encoding->name);
            puts(to_encoding->name);

            buffer_clear(&in);
            buffer_clear(&out);
            assert_true(buffer_assign_data(
                &in,
                (const char *)from_encoding->data,
                from_encoding->len,
                &status
            ));

            len = out.array.alloc;

            assert_true(charset_convert_data(
                in.array.elements,
                in.array.len,
                from_encoding->name,
                to_encoding->name,
                out.array.elements,
                &len,
                &status
            ));

            assert_int_equal(len, to_encoding->len);

            out.array.len = len;

            assert_memory_equal(
                out.array.elements, to_encoding->data, out.array.len
            );

            string_clear(&sout);
            assert_true(string_assign_buffer(
                &sout, &out, to_encoding->name, &status
            ));

            // assert_int_equal(sout.buffer.array.len, strlen(utf8_phrase) + 1);
            assert_memory_equal(
                sout.buffer.array.elements, utf8_phrase, sout.buffer.array.len
            );

            buffer_clear(&out);
            assert_true(string_encode(
                &sout, from_encoding->name, &out, &status
            ));
            assert_int_equal(out.array.len, from_encoding->len);
            assert_memory_equal(
                out.array.elements, from_encoding->data, out.array.len
            );
        }
    }
}

/* vi: set et ts=4 sw=4: */
