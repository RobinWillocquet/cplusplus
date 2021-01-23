# Morse
### *Par Robin Willocquet*

Voici mon repository pour le projet sur le Morse.

## L'encodage/décodage texte

### `morse.cpp`

C'est le premier fichier créé. Il contient la map de conversion morse-français, et les fonctions pour décoder une lettre, puis un mot, puis une ligne entière : idem pour encoder.
Il contient aussi la fonction pareil, utilisée dans `testmorse.cpp` pour savoir si deux chaînes de caractère sont identiques (sensible à la casse...)

### `morse.h`

Son header associé.

### `testmorse.cpp`

Un fichier avec de nombreux tests pour tester les diverses fonctions de `morse.cpp`. Ainsi, le message sur la saucisse de Morteau sera protégé !

### `morsetot.cpp`

Un ancien fichier qui regroupait les tests, les fonctions.


## La partie audio

***Note*** : *La librairie d'Adam Stark ne m'a servi qu'à comprendre plus aisément le format .wav, le reste reste de moi uniquement.*

### `AudioFile.h`

Une librairie pour comprendre le format .wav.

### `audiolib.cpp`

Le fichier créé pour générer et lire des fichiers .wav de morse. Des fonctions pour ajouter des silences et des bips morses de durées souhaitées y sont, ainsi qu'une fonction pour écrire le fichier audio à partir de son tableau de samples (discret).
Il y a aussi des fonctions pour décoder un fichier audio en bips et silences.
S'y trouvent aussi une fonction pour transformer une ligne morse de texte en audio, et un fichier audio en ligne morse de texte.

### `audiolib.h`

Le header associé.

### `testaudio.cpp`

Un petit fichier de tests, avec création de SOS, encodage et décodage de lignes de texte morse.

## Le programme final

### `progmorse.cpp`

C'est le programme avec interface. L'utilisateur peut choisir entre 8 options différentes, choisir la durée et la note de ses bips audios, choisir où stocker ses fichiers décodés...
Le fichier `saucisse.txt` par exemple est traduit temporairement en `saucissetemp.txt` avant de devenir `saucisse.wav`. Ce dernier est ensuite retransformé en texte, c'est `saucissenew.txt`.

## Makefile

Un *makefile* est présent pour aider à la compilation, et au nettoyage du dossier. 




Bonne découverte à vous !


Robin Willocquet

1ère année Ingénieur Civil | Mines ParisTech