#pragma once

#ifndef TEST_TABLE_H__
#define TEST_TABLE_H__

#include "cbase/table.h"
#include "cbase_test.h"

static inline
char* person_to_key(const Person *obj) {
    return (char *)(obj)->name;
}

static inline
char* character_to_key(const Character *obj) {
    return (char *)(obj)->name;
}

STR_TABLE_DEF(PersonTable, person_table, Person *, person_to_key)

STR_TABLE_DEF(CharacterTable, character_table, Character *, character_to_key)

#endif
