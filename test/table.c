#include <setjmp.h>
#include <stdio.h>

#include "cbase/table.h"
#include "cbase_test.h"
#include "./table.h"

#include <cmocka.h>

void test_table(void **state) {
    PersonTable person_table;
    PersonTable person_table2;

    CharacterTable character_table;
    CharacterTable character_table2;

    Person john = {"John", 43};
    Person lyndon = {"Lyndon", 55};
    Person james = {"James", 53};
    Person william = {"William", 47};
    Person barack = {"Barack", 46};
    Person *person = NULL;

    (void)state;

    assert_int_equal(person_table_init(&person_table, 0), 0);

    assert_int_equal(person_table.buckets.len, 16);
    assert_int_equal(person_table.buckets.alloc, 16);
    assert_int_equal(person_table.bucket_bit, 4);
    assert_int_equal(person_table.bucket_max, 16);
    assert_int_equal(person_table.bucket_mask, 15);
    assert_int_equal(person_table.len, 0);

    assert_int_equal(person_table_init(&person_table2, 0), 0);

    assert_int_equal(person_table2.buckets.len, 16);
    assert_int_equal(person_table2.buckets.alloc, 16);
    assert_int_equal(person_table2.bucket_bit, 4);
    assert_int_equal(person_table2.bucket_max, 16);
    assert_int_equal(person_table2.bucket_mask, 15);
    assert_int_equal(person_table2.len, 0);

    assert_int_equal(person_table_insert(&person_table, &john), 0);
    assert_int_equal(person_table_insert(&person_table, &lyndon), 0);
    assert_int_equal(person_table_insert(&person_table, &james), 0);
    assert_int_equal(person_table_insert(&person_table, &william), 0);
    assert_int_equal(person_table_insert(&person_table, &barack), 0);
    assert_int_equal(person_table.len, 5);

    assert_int_equal(person_table_insert(&person_table, &barack), 0);
    assert_int_equal(person_table.len, 6);

    assert_int_equal(person_table_lookup(&person_table, "John", &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_table_lookup(&person_table, "Lyndon", &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_table_lookup(&person_table, "James", &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(
        person_table_lookup(&person_table, "William", &person),
        0
    );
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_table_lookup(&person_table, "Barack", &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_table_pop(&person_table, "William", &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);
    assert_int_equal(person_table.len, 5);

    assert_int_equal(person_table_pop(&person_table, "Barack", &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);
    assert_int_equal(person_table.len, 4);

    assert_int_equal(person_table_pop(&person_table, "Barack", &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);
    assert_int_equal(person_table.len, 3);

    person_table_free(&person_table);
    assert_ptr_equal(person_table.buckets.data, NULL);
    assert_int_equal(person_table.buckets.len, 0);
    assert_int_equal(person_table.buckets.alloc, 0);
    assert_int_equal(person_table.bucket_bit, 0);
    assert_int_equal(person_table.bucket_max, 0);
    assert_int_equal(person_table.bucket_mask, 0);
    assert_int_equal(person_table.len, 0);

    assert_int_equal(character_table_init(&character_table, 0), 0);

    Character banon = {"Banon", "Oracle"};
    Character celes = {"Celes Chere", "Rune Knight"};
    Character cyan = {"Cyan Garamonde", "Samurai"};
    Character edgar = {"Edgar Figaro", "Machinist"};
    Character gau = {"Gau", "Feral Youth"};
    Character ghost = {"Ghost", "Ghost"};
    Character gogo = {"Gogo", "Mime"};
    Character leo = {"Leo Cristophe", "General"};
    Character locke = {"Locke Cole", "Adventurer"};
    Character mog = {"Mog", "Moogle"};
    Character relm = {"Relm Arrowny", "Pictomancer"};
    Character sabin = {"Sabin Figaro", "Monk"};
    Character setzer = {"Setzer Gabbiani", "Gambler"};
    Character shadow = {"Shadow", "Assassin"};
    Character strago = {"Strago Magus", "Blue Mage"};
    Character terra = {"Terra Branford", "Magitek Elite"};
    Character umaro = {"Umaro", "Berserker"};
    Character *cha = NULL;

    assert_int_equal(character_table_insert(&character_table, &banon), 0);
    assert_int_equal(character_table_insert(&character_table, &celes), 0);
    assert_int_equal(character_table_insert(&character_table, &cyan), 0);
    assert_int_equal(character_table_insert(&character_table, &edgar), 0);
    assert_int_equal(character_table_insert(&character_table, &gau), 0);
    assert_int_equal(character_table_insert(&character_table, &ghost), 0);
    assert_int_equal(character_table_insert(&character_table, &gogo), 0);
    assert_int_equal(character_table_insert(&character_table, &leo), 0);
    assert_int_equal(character_table_insert(&character_table, &locke), 0);
    assert_int_equal(character_table_insert(&character_table, &mog), 0);
    assert_int_equal(character_table_insert(&character_table, &relm), 0);
    assert_int_equal(character_table_insert(&character_table, &sabin), 0);
    assert_int_equal(character_table_insert(&character_table, &setzer), 0);
    assert_int_equal(character_table_insert(&character_table, &shadow), 0);
    assert_int_equal(character_table.len, 14);

    assert_int_equal(character_table_insert(&character_table, &strago), 0);

    assert_int_equal(character_table.len, 15);
    assert_int_equal(character_table.bucket_bit, 5);
    assert_int_equal(character_table.bucket_max, 32);
    assert_int_equal(character_table.bucket_mask, 0x1F);

    assert_int_equal(character_table_init(&character_table2, 0), 0);

    assert_int_equal(
        character_table_copy(&character_table2, &character_table),
        0
    );

    assert_int_equal(character_table2.len, 15);
    assert_int_equal(character_table2.bucket_bit, 5);
    assert_int_equal(character_table2.bucket_max, 32);
    assert_int_equal(character_table2.bucket_mask, 0x1F);

    assert_int_equal(character_table_insert(&character_table, &terra), 0);
    assert_int_equal(character_table_insert(&character_table, &umaro), 0);
    assert_int_equal(character_table_insert(&character_table, &umaro), 0);
    assert_int_equal(character_table_insert(&character_table, &umaro), 0);
    assert_int_equal(character_table.len, 19);

    size_t i;
    size_t count = 0;

    cha = NULL;

    while (character_table_iterate(&character_table, &i, &cha)) {
        count++;
    }

    cha = NULL;

    assert_int_equal(count, character_table.len);

    assert_int_equal(character_table_remove(&character_table, umaro.name), 0);
    assert_int_equal(character_table.len, 18);

    assert_int_equal(character_table_remove(&character_table, umaro.name), 0);
    assert_int_equal(character_table.len, 17);

    assert_int_equal(character_table_remove(&character_table, gogo.name), 0);
    assert_int_equal(character_table_remove(&character_table, leo.name), 0);
    assert_int_equal(character_table_remove(&character_table, locke.name), 0);
    assert_int_equal(character_table_remove(&character_table, mog.name), 0);
    assert_int_equal(character_table_remove(&character_table, relm.name), 0);
    assert_int_equal(character_table_remove(&character_table, sabin.name), 0);
    assert_int_equal(character_table_remove(&character_table, setzer.name), 0);
    assert_int_equal(character_table_remove(&character_table, shadow.name), 0);
    assert_int_equal(character_table_remove(&character_table, strago.name), 0);
    assert_int_equal(character_table_remove(&character_table, terra.name), 0);

    assert_int_equal(character_table.len, 7);

    assert_int_equal(character_table_remove(&character_table, umaro.name), 0);

    assert_int_equal(character_table.len, 6);
    assert_int_equal(character_table.bucket_bit, 4);
    assert_int_equal(character_table.bucket_max, 16);
    assert_int_equal(character_table.bucket_mask, 0xF);

    assert_int_equal(
        character_table_remove(&character_table, strago.name),
        CBASE_ERROR_NOT_FOUND
    );

    assert_int_equal(
        character_table_pop(&character_table, banon.name, &cha),
        0
    );

    assert_non_null(cha);
    assert_string_equal(cha->name, "Banon");
    assert_string_equal(cha->job, "Oracle");

    assert_int_equal(character_table_remove(&character_table, celes.name), 0);
    assert_int_equal(character_table_remove(&character_table, cyan.name), 0);
    assert_int_equal(character_table_remove(&character_table, edgar.name), 0);
    assert_int_equal(character_table_remove(&character_table, gau.name), 0);
    assert_int_equal(character_table_remove(&character_table, ghost.name), 0);

    character_table_free(&character_table);

    assert_int_equal(character_table.seed, 0);
    assert_int_equal(character_table.bucket_bit, 0);
    assert_int_equal(character_table.bucket_max, 0);
    assert_int_equal(character_table.bucket_mask, 0);
    assert_int_equal(character_table.len, 0);
}

/* vi: set et ts=4 sw=4: */
