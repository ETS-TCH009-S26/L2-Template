# TCH009 — Gabarit de projet en C

Gabarit de départ pour les travaux pratiques et le Devoir de session du cours
**TCH009 — Informatique** (ÉTS). Il fonctionne de la même façon dans **CLion**
et dans **VS Code**, sur Windows, macOS et Linux.

---

## Pourquoi utiliser ce gabarit ? (facultatif)

**Ce gabarit est une commodité, pas une obligation.** Si vous avez déjà votre
propre façon de travailler et qu'elle vous convient, gardez-la : ce qui est
évalué, c'est votre code, pas votre outillage.

Cela dit, il vous évite quelques irritants :

- **Ça compile pareil pour tout le monde.** Vous, votre coéquipier et le
  correcteur obtenez exactement le même résultat — fini le « chez moi ça marche ».
- **Les tests sont déjà branchés.** Vous pouvez vérifier vous-même que votre
  programme donne les bonnes réponses, avant la remise.
- **Rien à configurer.** Vous ouvrez le dossier, vous appuyez sur un bouton, ça
  compile. Aucun réglage de compilateur à comprendre.
- **Vérification automatique à chaque `git push`.** GitHub vous dit en clair si
  votre code compile et si les tests passent.

---

## Démarrage rapide — en local (sans Docker)

C'est le chemin normal. Il vous faut simplement **CLion** *ou* **VS Code**.

### Avec CLion (recommandé par l'enseignant)

CLion contient déjà tout le nécessaire (compilateur, CMake, débogueur).

1. `File` → `Open…` et choisissez **le dossier du projet** (pas un fichier).
2. CLion détecte `CMakeLists.txt` et `CMakePresets.json` et se configure seul.
   Attendez la fin du chargement (barre de progression en bas).
3. En haut à droite, choisissez la cible **`programme`**, puis :
   - ▶️ **Run** (`Maj+F10`) pour exécuter ;
   - 🐞 **Debug** (`Maj+F9`) pour déboguer pas à pas.
4. Pour lancer les tests : choisissez la cible **`test_main`** et exécutez-la,
   ou clic droit sur le projet → `Run 'All CTest Tests'`.

### Avec VS Code

Prérequis : un compilateur C et CMake installés
(Windows : [MSYS2/MinGW](https://www.msys2.org/) ou Visual Studio Build Tools ;
macOS : `xcode-select --install` ; Linux : `sudo apt install build-essential cmake`).

1. `Fichier` → `Ouvrir le dossier…` et choisissez le dossier du projet.
2. VS Code propose d'installer les extensions recommandées → **acceptez**.
3. Si on vous demande de choisir une configuration CMake, prenez **`defaut`**.
4. Ensuite :
   - **Compiler** : `Ctrl+Maj+B`
   - **Exécuter** : `Ctrl+Maj+P` → `Tasks: Run Task` → **Exécuter**
   - **Tester** : `Ctrl+Maj+P` → `Tasks: Run Task` → **Tester**
   - **Déboguer** : `F5`

### En ligne de commande (si vous préférez)

```bash
cmake --preset defaut        # préparer
cmake --build --preset defaut # compiler
./build/bin/programme         # exécuter (Windows : build\bin\programme.exe)
ctest --preset defaut         # tester
```

> **Note :** la première configuration télécharge la bibliothèque de tests
> Unity depuis Internet. Sans connexion, utilisez
> `cmake --preset defaut -DTCH009_TESTS=OFF` : le programme compilera, mais
> sans les tests.

---

## Démarrage en conteneur (optionnel)

Utile si vous voulez un environnement identique à celui de la correction, ou si
vous n'arrivez pas à installer un compilateur sur votre machine. **Ce n'est pas
nécessaire** pour faire le travail.

Prérequis : [Docker Desktop](https://www.docker.com/products/docker-desktop/) installé et démarré.

- **VS Code** : installez l'extension *Dev Containers*, ouvrez le dossier, puis
  `Ctrl+Maj+P` → **Dev Containers: Reopen in Container**. Attendez la
  construction (quelques minutes la première fois). Ensuite, tout fonctionne
  exactement comme en local.
- **CLion** (2024.1 ou plus récent) : ouvrez le fichier
  `.devcontainer/devcontainer.json`, puis cliquez sur l'icône de conteneur dans
  la marge → **Create Dev Container**.

---

## Désactiver l'autocomplétion

L'enseignant travaille **sans autocomplétion** : le but est d'apprendre la
syntaxe du C plutôt que de la faire deviner par l'éditeur.

### VS Code — déjà fait ✅

C'est configuré dans `.vscode/settings.json`, qui fait partie du projet. Vous
n'avez rien à faire. Les **erreurs de compilation** restent affichées : seules
les suggestions automatiques sont coupées.

### CLion — à faire manuellement ⚠️

**Limite technique honnête :** dans CLion, ce réglage est *global à
l'application*, pas propre au projet. Aucun fichier du dépôt ne peut le forcer :
vous devez le faire vous-même, une seule fois.

1. `File` → `Settings…` (Windows/Linux) ou `CLion` → `Settings…` (macOS) —
   raccourci `Ctrl+Alt+S`.
2. Allez dans **`Editor` → `General` → `Code Completion`**.
3. Décochez :
   - **`Show suggestions as you type`** (le réglage principal) ;
   - **`Show parameter name hints`** ;
   - **`Full Line completion`** / **`Machine Learning-Assisted Completion`**,
     si ces options sont présentes dans votre version.
4. Allez ensuite dans **`Editor` → `Inlay Hints`** et décochez
   **`Show inlay hints`** pour retirer les annotations affichées dans le code.
5. `Apply` → `OK`.

Le raccourci `Ctrl+Espace` continue de fonctionner si vous voulez une suggestion
volontairement — c'est l'automatisme qu'on retire, pas l'outil.

---

## Ça ne compile pas, que faire ?

Avant de paniquer : **lisez la première erreur**, pas la dernière. Une seule
faute en produit souvent une dizaine.

| Message typique | Cause fréquente | Solution |
|---|---|---|
| `expected ';' before …` | Point-virgule manquant | Regardez la **ligne précédant** celle indiquée. |
| `undefined reference to 'printf'` / `implicit declaration of function` | `#include` oublié | Ajoutez `#include <stdio.h>` (ou l'en-tête approprié) en haut du fichier. |
| `undefined reference to 'ma_fonction'` | Fonction déclarée mais jamais écrite, ou fichier `.c` placé ailleurs que dans `src/` | Écrivez la fonction et vérifiez que le fichier est bien dans `src/`. |
| `'x' undeclared` | Variable utilisée avant d'être déclarée, ou faute de frappe dans son nom | Déclarez-la (`int x;`) ou corrigez l'orthographe. |
| L'IDE ne trouve aucune cible à exécuter | Le projet n'a pas fini de se configurer | CLion : `Tools` → `CMake` → `Reset Cache and Reload Project`. VS Code : `Ctrl+Maj+P` → `CMake: Configure`. |

**Solution universelle** quand rien ne va plus : supprimez le dossier `build/`
et recompilez. Rien d'important ne s'y trouve — il est entièrement régénéré.

---

## Où écrire mon code ?

```
src/main.c       ← votre programme (point de départ : la fonction main)
src/*.c, *.h     ← vos autres fonctions, si l'exercice le demande
tests/test_*.c   ← les tests (ajoutés par l'enseignant, ou par vous)
```

Tout fichier ajouté dans `src/` ou `tests/` est **détecté automatiquement** :
vous n'avez jamais à modifier `CMakeLists.txt`.

---

## Énoncé de l'exercice

<!-- À REMPLIR à chaque nouveau TP ou pour le Devoir de session. -->

*(À compléter par la personne chargée de laboratoire.)*

---

## Remise

1. `git add .`
2. `git commit -m "Description de ce que vous avez fait"`
3. `git push`
4. Onglet **Actions** sur GitHub : vérifiez la pastille verte ✅. En cas
   d'échec, cliquez dessus pour lire le résumé, qui explique ce qui a cassé.

Le style de code (mise en forme, suggestions de `clang-tidy`) **ne fait jamais
échouer** la vérification : seuls un code qui ne compile pas ou des tests qui
échouent la font échouer.

---

## Mention

Matériel pédagogique à usage interne — cours TCH009, École de technologie
supérieure. Aucune licence d'utilisation publique n'est accordée.
