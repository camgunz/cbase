#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

const char *utf8_phrase = "見ぬが花";

char codepoints[16] = {
    0x8B, 0x89, 0x00, 0x00,
    0x6C, 0x30, 0x00, 0x00,
    0x4C, 0x30, 0x00, 0x00,
    0xB1, 0x82, 0x00, 0x00,
};

char utf8_bytes[12] = {
    0xE8, 0xA6, 0x8B, 0xE3, 0x81, 0xAC, 0xE3, 0x81, 0x8C, 0xE8, 0x8A, 0xB1
};

char utf16_bytes[10] = {
    0xFF, 0xFE,
    0x8B, 0x89,
    0x6C, 0x30,
    0x4C, 0x30,
    0xB1, 0x82
};

char utf32_bytes[20] = {
    0xFF, 0xFE, 0x00, 0x00,
    0x8B, 0x89, 0x00, 0x00,
    0x6C, 0x30, 0x00, 0x00,
    0x4C, 0x30, 0x00, 0x00,
    0xB1, 0x82, 0x00, 0x00,
};

char shiftjis_bytes[8] = {
    0x8C, 0xA9, 0x82, 0xCA, 0x82, 0xAA, 0x89, 0xD4
};

#include <stdio.h>

void test_charset(void **state) {
    Slice ss;
    Status status;
    Buffer out;

    (void)state;

    status_clear(&status);

    assert_true(buffer_init_alloc(&out, 1, &status));

    ss.data = utf8_bytes;
    ss.len = sizeof(utf8_bytes);

    buffer_clear(&out);
    assert_true(charset_convert(&ss, "utf-8", "utf-16", &out, &status));
    assert_int_equal(out.len, sizeof(utf16_bytes));
    assert_memory_equal(out.data, utf16_bytes, sizeof(utf16_bytes));

    buffer_clear(&out);
    assert_true(charset_convert(&ss, "utf-8", "utf-32", &out, &status));
    assert_int_equal(out.len, sizeof(utf32_bytes));
    assert_memory_equal(out.data, utf32_bytes, sizeof(utf32_bytes));

    buffer_clear(&out);
    assert_true(charset_convert(&ss, "utf-8", "shift-jis", &out, &status));
    assert_int_equal(out.len, sizeof(shiftjis_bytes));
    assert_memory_equal(out.data, shiftjis_bytes, sizeof(shiftjis_bytes));

    ss.data = shiftjis_bytes;
    ss.len = sizeof(shiftjis_bytes);

    buffer_clear(&out);
    assert_true(charset_convert(&ss, "shift-jis", "utf-16", &out, &status));
    assert_int_equal(out.len, sizeof(utf16_bytes));
    assert_memory_equal(out.data, utf16_bytes, sizeof(utf16_bytes));

    buffer_clear(&out);
    assert_true(charset_convert(&ss, "shift-jis", "utf-32", &out, &status));
    assert_int_equal(out.len, sizeof(utf32_bytes));
    assert_memory_equal(out.data, utf32_bytes, sizeof(utf32_bytes));

    buffer_clear(&out);
    assert_true(charset_convert(&ss, "shift-jis", "utf-8", &out, &status));
    assert_int_equal(out.len, sizeof(utf8_bytes));
    assert_memory_equal(out.data, utf8_bytes, sizeof(utf8_bytes));
}

/* vi: set et ts=4 sw=4: */
