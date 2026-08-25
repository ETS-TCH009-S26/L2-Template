/*
 * TCH009 - Exemple de test unitaire avec Unity
 *
 * Ce fichier montre le patron à suivre. Chaque fichier .c placé dans tests/
 * devient automatiquement un exécutable de test, lancé par CTest.
 *
 * Les fonctions que vous écrivez dans src/ (autres que main.c) sont
 * compilées avec les tests : ajoutez simplement #include "mon_fichier.h".
 */

#include "unity.h"

// Appelée avant chaque test. Laissez vide si vous n'en avez pas besoin.
void setUp(void) {}

// Appelée après chaque test.
void tearDown(void) {}

// Exemple de fonction à tester (normalement, elle serait dans src/).
static int addition(int a, int b) {
    return a + b;
}

static void test_addition_de_deux_entiers(void) {
    TEST_ASSERT_EQUAL_INT(4, addition(2, 2));
    TEST_ASSERT_EQUAL_INT(0, addition(-3, 3));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition_de_deux_entiers);
    return UNITY_END();
}
