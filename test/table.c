#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

static size_t key_to_hash(const void *key, size_t seed) {
    return hash64(key, strlen((const char *)key), seed);
}

static void* person_to_key(const void *obj) {
    return (void *)((Person *)obj)->name;
}

static void* character_to_key(const void *obj) {
    return (void *)((Character *)obj)->name;
}

static bool key_equal(const void *key1, const void *key2) {
    return strcmp((const char *)key1, (const char *)key2) == 0;
}

void test_table(void **state) {
    Table table;
    Table table2;
    Status status;

    (void)state;

    status_init(&status);

    assert_true(table_init(
        &table, key_to_hash, person_to_key, key_equal, 0, &status
    ));

    assert_int_equal(table.buckets.len, 16);
    assert_int_equal(table.buckets.alloc, 16);
    assert_int_equal(table.bucket_bit, 4);
    assert_int_equal(table.bucket_max, 16);
    assert_int_equal(table.bucket_mask, 15);
    assert_int_equal(table.len, 0);

    assert_true(table_init(
        &table2, key_to_hash, person_to_key, key_equal, 0, &status
    ));

    assert_int_equal(table2.buckets.len, 16);
    assert_int_equal(table2.buckets.alloc, 16);
    assert_int_equal(table2.bucket_bit, 4);
    assert_int_equal(table2.bucket_max, 16);
    assert_int_equal(table2.bucket_mask, 15);
    assert_int_equal(table2.len, 0);

    Person john;
    Person lyndon;
    Person james;
    Person william;
    Person barack;
    Person *person;

    john.name = "John";
    john.age = 43;

    lyndon.name = "Lyndon";
    lyndon.age = 55;

    james.name = "James";
    james.age = 53;

    william.name = "William";
    william.age = 47;

    barack.name = "Barack";
    barack.age = 46;

    assert_true(table_insert(&table, &john, &status));
    assert_true(table_insert(&table, &lyndon, &status));
    assert_true(table_insert(&table, &james, &status));
    assert_true(table_insert(&table, &william, &status));
    assert_true(table_insert(&table, &barack, &status));
    assert_int_equal(table.len, 5);

    assert_true(table_insert(&table, &barack, &status));
    assert_int_equal(table.len, 6);

    if (!table_lookup(&table, "John", (void **)&person, &status)) {
        printf("Error [%s - %d, %s:%d] %s\n",
            status.domain,
            status.code,
            status.file,
            status.line,
            status.message
        );
    }
    assert_true(table_lookup(&table, "John", (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(table_lookup(&table, "Lyndon", (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(table_lookup(&table, "James", (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(table_lookup(&table, "William", (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(table_lookup(&table, "Barack", (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(table_remove(&table, "William", (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);
    assert_int_equal(table.len, 5);

    assert_true(table_remove(&table, "Barack", (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);
    assert_int_equal(table.len, 4);

    assert_true(table_remove(&table, "Barack", (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);
    assert_int_equal(table.len, 3);

    table_free(&table);
    assert_ptr_equal(table.buckets.elements, NULL);
    assert_int_equal(table.buckets.len, 0);
    assert_int_equal(table.buckets.alloc, 0);
    assert_int_equal(table.bucket_bit, 0);
    assert_int_equal(table.bucket_max, 0);
    assert_int_equal(table.bucket_mask, 0);
    assert_int_equal(table.len, 0);

    assert_true(table_init(
        &table, key_to_hash, character_to_key, key_equal, 0, &status
    ));

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

    assert_true(table_insert(&table, (void **)&banon, &status));
    assert_true(table_insert(&table, (void **)&celes, &status));
    assert_true(table_insert(&table, (void **)&cyan, &status));
    assert_true(table_insert(&table, (void **)&edgar, &status));
    assert_true(table_insert(&table, (void **)&gau, &status));
    assert_true(table_insert(&table, (void **)&ghost, &status));
    assert_true(table_insert(&table, (void **)&gogo, &status));
    assert_true(table_insert(&table, (void **)&leo, &status));
    assert_true(table_insert(&table, (void **)&locke, &status));
    assert_true(table_insert(&table, (void **)&mog, &status));
    assert_true(table_insert(&table, (void **)&relm, &status));
    assert_true(table_insert(&table, (void **)&sabin, &status));
    assert_true(table_insert(&table, (void **)&setzer, &status));
    assert_true(table_insert(&table, (void **)&shadow, &status));
    assert_int_equal(table.len, 14);

    assert_true(table_insert(&table, (void **)&strago, &status));

    assert_int_equal(table.len, 15);
    assert_int_equal(table.bucket_bit, 5);
    assert_int_equal(table.bucket_max, 32);
    assert_int_equal(table.bucket_mask, 0x1F);

    assert_true(table_copy(&table2, &table, &status));

    assert_int_equal(table2.len, 15);
    assert_int_equal(table2.bucket_bit, 5);
    assert_int_equal(table2.bucket_max, 32);
    assert_int_equal(table2.bucket_mask, 0x1F);

    assert_true(table_insert(&table, (void **)&terra, &status));
    assert_true(table_insert(&table, (void **)&umaro, &status));
    assert_true(table_insert(&table, (void **)&umaro, &status));
    assert_true(table_insert(&table, (void **)&umaro, &status));
    assert_int_equal(table.len, 19);

    size_t i;
    size_t count = 0;

    cha = NULL;

    while (table_iterate(&table, &i, (void **)&cha)) {
        count++;
    }

    cha = NULL;

    assert_int_equal(count, table.len);

    assert_true(table_remove(&table, (void *)umaro.name, NULL, &status));
    assert_int_equal(table.len, 18);

    assert_true(table_remove(&table, (void *)umaro.name, NULL, &status));
    assert_int_equal(table.len, 17);

    assert_true(table_remove(&table, (void *)gogo.name, NULL, &status));
    assert_true(table_remove(&table, (void *)leo.name, NULL, &status));
    assert_true(table_remove(&table, (void *)locke.name, NULL, &status));
    assert_true(table_remove(&table, (void *)mog.name, NULL, &status));
    assert_true(table_remove(&table, (void *)relm.name, NULL, &status));
    assert_true(table_remove(&table, (void *)sabin.name, NULL, &status));
    assert_true(table_remove(&table, (void *)setzer.name, NULL, &status));
    assert_true(table_remove(&table, (void *)shadow.name, NULL, &status));
    assert_true(table_remove(&table, (void *)strago.name, NULL, &status));
    assert_true(table_remove(&table, (void *)terra.name, NULL, &status));

    assert_int_equal(table.len, 7);

    assert_true(table_remove(&table, (void *)umaro.name, NULL, &status));

    assert_int_equal(table.len, 6);
    assert_int_equal(table.bucket_bit, 4);
    assert_int_equal(table.bucket_max, 16);
    assert_int_equal(table.bucket_mask, 0xF);

    assert_false(table_remove(&table, (void *)strago.name, NULL, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.message, "search term not found");

    status_clear(&status);

    assert_true(table_remove(
        &table, (void *)banon.name, (void **)&cha, &status
    ));

    assert_non_null(cha);
    assert_string_equal(cha->name, "Banon");
    assert_string_equal(cha->job, "Oracle");

    assert_true(table_remove(&table, (void *)celes.name, NULL, &status));
    assert_true(table_remove(&table, (void *)cyan.name, NULL, &status));
    assert_true(table_remove(&table, (void *)edgar.name, NULL, &status));
    assert_true(table_remove(&table, (void *)gau.name, NULL, &status));
    assert_true(table_remove(&table, (void *)ghost.name, NULL, &status));

    table_free(&table);

    assert_null(table.key_to_hash);
    assert_null(table.obj_to_key);
    assert_null(table.key_equal);
    assert_int_equal(table.seed, 0);
    assert_int_equal(table.bucket_bit, 0);
    assert_int_equal(table.bucket_max, 0);
    assert_int_equal(table.bucket_mask, 0);
    assert_int_equal(table.len, 0);
}

/* vi: set et ts=4 sw=4: */
