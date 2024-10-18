# Maze Game

## English

**Maze Game** is a console application developed in C that allows players to navigate through a maze generated from a text file. The application keeps track of player information and scores using a MySQL database.

### Key Features

- **Maze Generation**: The maze is generated from a text file, making it easy to create and modify different maze layouts.
- **Score Tracking**: The application retains the player's score and other relevant information without a login system.
- **User-Friendly Interface**: Navigate through the maze using keyboard controls.

### Database Structure

The application utilizes the following MySQL database tables:

- **jeu**: Stores game information.
  - **ID_JEU**: Unique identifier for each game.
  - **NOM_DU_JEU**: Name of the game.

- **joueur**: Stores player information.
  - **ID_JOUEUR**: Unique identifier for each player.
  - **NOM_DU_JOUEUR**: Name of the player (must be unique).

- **partie**: Stores game session information.
  - **ID_PARTIE**: Unique identifier for each game session.
  - **SCORE**: Score achieved by the player.
  - **ID_JEU**: References the game being played.
  - **ID_JOUEUR**: References the player participating in the session.

### Project Status

This project is currently in development and may require further enhancements for a better user experience and additional features.

### Technologies Used

- **Programming Language**: C
- **Database**: MySQL

### Future Improvements

- Implement additional features like multiple maze levels.
- Enhance the scoring system with achievements or milestones.
- Improve the user interface and add more detailed instructions.

### Credits

Project developed by **Alexis Zarzycki** in 2023.

---

## Français

**Jeu de Labyrinthe** est une application console développée en C qui permet aux joueurs de naviguer à travers un labyrinthe généré à partir d'un fichier texte. L'application conserve les informations du joueur et les scores à l'aide d'une base de données MySQL.

### Fonctionnalités principales

- **Génération de labyrinthe** : Le labyrinthe est généré à partir d'un fichier texte, ce qui facilite la création et la modification de différents agencements de labyrinthes.
- **Suivi des scores** : L'application conserve le score du joueur et d'autres informations pertinentes sans système de connexion.
- **Interface conviviale** : Naviguez à travers le labyrinthe en utilisant les commandes du clavier.

### Structure de la base de données

L'application utilise les tables de base de données MySQL suivantes :

- **jeu** : Stocke les informations sur le jeu.
  - **ID_JEU** : Identifiant unique pour chaque jeu.
  - **NOM_DU_JEU** : Nom du jeu.

- **joueur** : Stocke les informations sur les joueurs.
  - **ID_JOUEUR** : Identifiant unique pour chaque joueur.
  - **NOM_DU_JOUEUR** : Nom du joueur (doit être unique).

- **partie** : Stocke les informations sur les sessions de jeu.
  - **ID_PARTIE** : Identifiant unique pour chaque session de jeu.
  - **SCORE** : Score réalisé par le joueur.
  - **ID_JEU** : Référence au jeu joué.
  - **ID_JOUEUR** : Référence au joueur participant à la session.

### État du projet

Ce projet est en développement et peut nécessiter des améliorations supplémentaires pour une meilleure expérience utilisateur et des fonctionnalités additionnelles.

### Technologies utilisées

- **Langage de programmation** : C
- **Base de données** : MySQL

### Améliorations futures

- Mettre en œuvre des fonctionnalités supplémentaires comme plusieurs niveaux de labyrinthe.
- Améliorer le système de score avec des réalisations ou des jalons.
- Améliorer l'interface utilisateur et ajouter des instructions plus détaillées.

### Crédits

Projet développé par **Alexis Zarzycki** en 2023.
