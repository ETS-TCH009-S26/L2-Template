# Guide — chargé(e) de laboratoire

Document interne (enseignant·e et chargé·e·s de labo). **Il n'est pas destiné
aux étudiants** ; supprimez-le ou laissez-le, il ne gêne rien.

---

## 1. Créer un nouveau TP à partir du gabarit

1. Sur GitHub, dans le dépôt gabarit → bouton **« Use this template »** →
   *Create a new repository*.
2. Nommez le dépôt (ex. `TCH009-TP3`), choisissez la visibilité voulue.
3. Dans le nouveau dépôt :
   - remplacez le contenu de `src/` par le squelette de l'énoncé ;
   - remplacez `tests/test_main.c` par les tests de l'exercice ;
   - remplissez la section **`## Énoncé de l'exercice`** du `README.md` ;
   - poussez. La CI valide immédiatement que votre squelette compile.

**Vérification recommandée avant de diffuser :** poussez le squelette tel quel
et confirmez que la CI est verte. Si le squelette laisse des `TODO` qui ne
compilent pas, la CI sera rouge dès le départ — c'est décourageant. Préférez un
squelette qui compile mais échoue aux tests (rouge « utile » : *le code compile,
mais les tests échouent*), ce qui donne un objectif clair à l'étudiant.

---

## 2. Ajouter ou retirer des tests Unity

Aucune modification de `CMakeLists.txt` n'est requise.

- **Ajouter un test** : créez `tests/test_quelquechose.c`. Chaque fichier
  `tests/*.c` devient automatiquement un exécutable *et* un test CTest portant
  le nom du fichier. Chaque fichier doit contenir son propre `main()`,
  `setUp()` et `tearDown()` (voir `tests/test_main.c`).
- **Retirer un test** : supprimez le fichier.
- **Tester des fonctions de l'étudiant** : tous les `src/*.c` *sauf* `main.c`
  sont compilés avec chaque exécutable de test. Il suffit donc de fournir
  `src/fonctions.h` dans l'énoncé et de faire `#include "fonctions.h"` dans le
  test. `main.c` est exclu volontairement pour éviter deux `main()` au lien.

Assertions Unity les plus utiles : `TEST_ASSERT_EQUAL_INT`,
`TEST_ASSERT_EQUAL_DOUBLE`, `TEST_ASSERT_EQUAL_STRING`, `TEST_ASSERT_TRUE`,
`TEST_ASSERT_EQUAL_INT_ARRAY`. Documentation :
<https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md>

> **Piège fréquent :** un test qui appelle `scanf` bloque en CI (aucune entrée
> disponible). Pour tester une lecture au clavier, faites plutôt tester la
> fonction de calcul, séparée de la saisie — c'est de toute façon la bonne
> leçon de conception à transmettre.

---

## 3. Ajuster la sévérité de la CI

Tout est dans `.github/workflows/ci.yml`.

| Vous voulez… | Modification |
|---|---|
| Rendre la mise en forme bloquante | Retirer le `\|\| true` de l'étape *clang-format* |
| Rendre `clang-tidy` bloquant | Retirer le `\|\| true` de l'étape *Analyse statique* |
| Rendre les tests non bloquants (TP exploratoire) | Ajouter `continue-on-error: true` à l'étape *Tests unitaires* |
| Assouplir/durcir l'analyse statique | Modifier la liste `Checks:` dans `.clang-tidy` |
| Traiter les avertissements du compilateur comme des erreurs | Ajouter `-Werror` dans le bloc `add_compile_options` de `CMakeLists.txt` (**déconseillé** pour des débutants) |

Par défaut : **compilation et tests bloquants**, **style informatif seulement**.
Le résumé lisible est écrit dans le *Job Summary* de GitHub Actions (étape
« Résumé »), ce qui évite aux étudiants d'avoir à lire des journaux bruts.

---

## 4. Choix techniques (et pourquoi)

- **CMake 3.21 minimum**, et non 3.20 : c'est la première version qui gère les
  `testPresets` des `CMakePresets.json`. Toutes les versions récentes de CLion
  et de VS Code dépassent largement ce seuil.
- **Aucun générateur imposé dans les presets.** CMake choisit celui de la
  plateforme (Makefiles, Visual Studio, Ninja selon le cas). Imposer Ninja
  aurait cassé le scénario « j'ouvre avec ce que j'ai déjà installé ».
  `CMakeLists.txt` gère MSVC (`/W4 /utf-8`) et GCC/Clang (`-Wall -Wextra`).
- **Sortie unifiée dans `build/bin/`**, y compris pour les générateurs
  multi-configuration, afin que les chemins documentés soient toujours vrais.
- **`file(GLOB … CONFIGURE_DEPENDS)`** plutôt qu'une liste explicite de
  fichiers : un étudiant qui ajoute un `.c` ne doit jamais avoir à toucher au
  `CMakeLists.txt`. Le coût (reconfiguration automatique) est négligeable ici.
- **Unity par `FetchContent`** (tag `v2.6.0`, clone superficiel) : rien à
  installer, rien à *vendorer*. Pour figer une version, changez `GIT_TAG`.
- **Option `TCH009_TESTS`** : porte de sortie pour un poste sans Internet
  (`-DTCH009_TESTS=OFF`).
- **`.idea/` ignoré** : CLion redérive tout de `CMakeLists.txt`,
  `CMakePresets.json` et `.clang-format`. Rien de propriétaire n'est committé.
- **Autocomplétion** : imposée par `.vscode/settings.json` côté VS Code
  (y compris `github.copilot.enable: false`) ; côté CLion, le réglage est global
  à l'IDE et ne peut pas être committé — le `README.md` documente la marche à
  suivre manuelle. Cette limite est assumée, pas contournée.
- **Un exécutable de test par fichier `tests/*.c`** plutôt qu'un seul binaire :
  évite les conflits de `main()` et donne un résultat CTest par fichier.
- **Pas de vérification de nom de branche ni de *linter* global.** Un étudiant
  ne doit jamais voir la CI échouer pour autre chose que son code C.

---

## 5. Vérification du gabarit après modification

```bash
rm -rf build
cmake --preset defaut
cmake --build --preset defaut
ctest --preset defaut
git status --short   # doit être vide : rien de build/ ne doit apparaître
```
