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

unsigned char utf8_bytes[12] = {
    0xE8, 0xA6, 0x8B, 0xE3, 0x81, 0xAC, 0xE3, 0x81, 0x8C, 0xE8, 0x8A, 0xB1
};

unsigned char utf16_bytes[10] = {
    0xFF, 0xFE,
    0x8B, 0x89,
    0x6C, 0x30,
    0x4C, 0x30,
    0xB1, 0x82
};

unsigned char utf32_bytes[20] = {
    0xFF, 0xFE, 0x00, 0x00,
    0x8B, 0x89, 0x00, 0x00,
    0x6C, 0x30, 0x00, 0x00,
    0x4C, 0x30, 0x00, 0x00,
    0xB1, 0x82, 0x00, 0x00,
};

unsigned char shiftjis_bytes[8] = {
    0x8C, 0xA9, 0x82, 0xCA, 0x82, 0xAA, 0x89, 0xD4
};

#include <stdio.h>

void test_charset(void **state) {
    Buffer out;
    Slice s;
    String sout;
    SSlice ss;
    Status status;

    (void)state;

    status_clear(&status);

    assert_true(buffer_init_alloc(&out, 1, &status));
    assert_true(string_init(&sout, " ", &status));

    buffer_clear(&out);
    s.data = (char *)utf8_bytes;
    s.len = sizeof(utf8_bytes);
    assert_true(charset_convert(&s, "utf-8", "utf-16", &out, &status));
    assert_int_equal(out.len, sizeof(utf16_bytes));
    assert_memory_equal(out.data, utf16_bytes, out.len);

    string_clear(&sout);
    assert_true(buffer_slice(&out, 0, out.len, &s, &status));
    assert_true(charset_convert_to_string(&s, "utf-16", &sout, &status));
    assert_int_equal(sout.byte_len, strlen(utf8_phrase));
    assert_memory_equal(sout.data, utf8_phrase, sout.byte_len);

    buffer_clear(&out);
    assert_true(string_slice(&sout, 0, sout.byte_len, &ss, &status));
    assert_true(charset_convert_from_string(&ss, "utf-16", &out, &status));
    assert_int_equal(out.len, sizeof(utf16_bytes));
    assert_memory_equal(out.data, utf16_bytes, out.len);

    buffer_clear(&out);
    s.data = (char *)utf8_bytes;
    s.len = sizeof(utf8_bytes);
    assert_true(charset_convert(&s, "utf-8", "utf-32", &out, &status));
    assert_int_equal(out.len, sizeof(utf32_bytes));
    assert_memory_equal(out.data, utf32_bytes, out.len);

    string_clear(&sout);
    assert_true(buffer_slice(&out, 0, out.len, &s, &status));
    assert_true(charset_convert_to_string(&s, "utf-32", &sout, &status));
    assert_int_equal(sout.byte_len, strlen(utf8_phrase));
    assert_memory_equal(sout.data, utf8_phrase, sout.byte_len);

    buffer_clear(&out);
    assert_true(string_slice(&sout, 0, sout.byte_len, &ss, &status));
    assert_true(charset_convert_from_string(&ss, "utf-32", &out, &status));
    assert_int_equal(out.len, sizeof(utf32_bytes));
    assert_memory_equal(out.data, utf32_bytes, out.len);

    buffer_clear(&out);
    s.data = (char *)shiftjis_bytes;
    s.len = sizeof(shiftjis_bytes);
    assert_true(charset_convert(&s, "shift-jis", "utf-8", &out, &status));
    assert_int_equal(out.len, sizeof(utf8_bytes));
    assert_memory_equal(out.data, utf8_bytes, out.len);

    string_clear(&sout);
    assert_true(buffer_slice(&out, 0, out.len, &s, &status));
    assert_true(charset_convert_to_string(&s, "utf-8", &sout, &status));
    assert_int_equal(sout.byte_len, strlen(utf8_phrase));
    assert_memory_equal(sout.data, utf8_phrase, sout.byte_len);

    buffer_clear(&out);
    assert_true(string_slice(&sout, 0, sout.byte_len, &ss, &status));
    assert_true(charset_convert_from_string(&ss, "shift-jis", &out, &status));
    assert_int_equal(out.len, sizeof(shiftjis_bytes));
    assert_memory_equal(out.data, shiftjis_bytes, out.len);

    buffer_clear(&out);
    s.data = (char *)shiftjis_bytes;
    s.len = sizeof(shiftjis_bytes);
    assert_true(charset_convert(&s, "shift-jis", "utf-16", &out, &status));
    assert_int_equal(out.len, sizeof(utf16_bytes));
    assert_memory_equal(out.data, utf16_bytes, out.len);

    string_clear(&sout);
    assert_true(buffer_slice(&out, 0, out.len, &s, &status));
    assert_true(charset_convert_to_string(&s, "utf-16", &sout, &status));
    assert_int_equal(sout.byte_len, strlen(utf8_phrase));
    assert_memory_equal(sout.data, utf8_phrase, sout.byte_len);

    buffer_clear(&out);
    assert_true(string_slice(&sout, 0, sout.byte_len, &ss, &status));
    assert_true(charset_convert_from_string(&ss, "shift-jis", &out, &status));
    assert_int_equal(out.len, sizeof(shiftjis_bytes));
    assert_memory_equal(out.data, shiftjis_bytes, out.len);

    buffer_clear(&out);
    s.data = (char *)shiftjis_bytes;
    s.len = sizeof(shiftjis_bytes);
    assert_true(charset_convert(&s, "shift-jis", "utf-32", &out, &status));
    assert_int_equal(out.len, sizeof(utf32_bytes));
    assert_memory_equal(out.data, utf32_bytes, out.len);

    string_clear(&sout);
    assert_true(buffer_slice(&out, 0, out.len, &s, &status));
    assert_true(charset_convert_to_string(&s, "utf-32", &sout, &status));
    assert_int_equal(sout.byte_len, strlen(utf8_phrase));
    assert_memory_equal(sout.data, utf8_phrase, sout.byte_len);

    buffer_clear(&out);
    assert_true(string_slice(&sout, 0, sout.byte_len, &ss, &status));
    assert_true(charset_convert_from_string(&ss, "shift-jis", &out, &status));
    assert_int_equal(out.len, sizeof(shiftjis_bytes));
    assert_memory_equal(out.data, shiftjis_bytes, out.len);
}

/* vi: set et ts=4 sw=4: */
