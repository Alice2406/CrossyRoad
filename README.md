# The Only Road

**The Only Road** est une réinterprétation sombre et oppressante du genre infinite runner. Ce projet s'approprie les mécaniques fondamentales de Crossy Road pour les plonger dans un univers horrifique où la seule issue est d'avancer, malgré l'angoisse qui s'intensifie à chaque pas.

## Le Concept
L'objectif de ce projet était de déconstruire un classique du jeu mobile pour transformer radicalement l'expérience utilisateur à travers deux axes majeurs :

1. **Reskin Total** : Transition d'une esthétique "Voxel/Pop" colorée vers une direction artistique Horreur sombre.

2. **Mécaniques de bonus** : Intégration d'un système de bonus stratégiques pour influencer la survie.

##  Une Immersion Horrifique
Dans **The Only Road**, l'environnement n'est pas un simple décor, c'est une menace constante :

1. **Visuels** : Une palette de couleurs désaturées.

2. **Obstacles** : Les véhicules cèdent leur place à des boules à pic (fléau), le train est remplacé par des scies et les arbres/rocher sont remplacés par des arbres morts et des tombes.

3. **Perspective** : La gestion de la caméra, plus proche du sol et du personnage, renforce le sentiment de vulnérabilité et d'oppression.

##  Nouvelles Mécaniques : Les Bonus
Pour compenser une difficulté accrue et ajouter une couche tactique, des bonus apparaissent aléatoirement sur la route :

1. **Invisibilité** : Rend le personnage immatériel, lui permettant de traverser les obstacles et les ennemis sans subir de dégâts pendant quelques secondes.

2. **Vie Supplémentaire** : Octroie une seconde chance en permettant de résister à une collision, quel que soit l'obstacle rencontré.

## Spécifications Techniques

###  Moteur Isométrique
Le jeu utilise une projection isométrique personnalisée.

### Systèmes implémentés
* **Génération Procédurale :** Les obstacles apparaissent dynamiquement autour du joueur.
* **Gestionnaire de Scènes :** Transition fluide entre le menu, la sélection de personnages, le jeu et l'écran de fin.
* **Shaders:** Système de **Vignette** (TriangleFan) pour créer une ambiance de brouillard sombre qui suit le joueur.
* **Physique & Collisions :** Gestion des collisions par AABB adaptée à l'isométrie.

##  Commandes
| Touche | Action |
| :--- | :--- |
| **Flèches directionnelles** | Se déplacer (Haut / Bas / Gauche / Droite) |
| **Échap** | Mettre le jeu en pause |

##  Installation avec Microsoft Visual Studio

1. **Ouvrir le projet :** Lancez Visual Studio et ouvrez le fichier `.sln` ou le dossier du projet.
2. **Fichiers DLL :** Assurez-vous que les fichiers `.dll` de SFML se trouvent dans le même dossier que l'exécutable final (`Debug` ou `Release`).
3. **Compilation :** Appuyez sur **F5** pour compiler et lancer le jeu.
 
##  Fiche Technique

**Langage** : C++ (CPP)

**Architecture** : SFML 3.0.2

**Audio** : Sound design immersif utilisant des ressources libres de droits.

##  Crédits & Assets
* **Moteur Graphique :** [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library).
* **Musique de fond :** *Down the Rabbit Hole* par **Myuu** (Libre de droits).
* **Polices :** *Thunder.ttf*.
* **Code, Design & Gestion du projet :** DEHEDIN Anthony, GOUACHE Pierre, JANGOTCHIAN Clovis, BELASKRI Hania, KHIAT Sofyan et NIEZGODZKI Alice
