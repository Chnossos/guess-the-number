Vivoka - Évaluation C++/Qt
==========================

Jeu du Plus ou Moins, en réseau.

## Consigne

Réalisez 2 programmes console, client et serveur, à l'aide du [framework Qt][1]. Le serveur attend un ou plusieurs clients et une fois connectés, choisi un nombre aléatoire pour chacun que ce dernier doit ensuite trouver.

- Les deux programmes doivent résider dans le même dépôt Git mais chacun disposer de son dossier
- Les deux programmes doivent pouvoir être build à la suite en une seule commande
- Le type de socket à utiliser est WebSocket non-sécurisée ([`QWebSocket`][2])
- Les données réseau doivent transiter au format [`JSON`][3]
- Seule la [programmation évènementielle][4] est autorisée (l'utilisation de thread/fork/...est **INTERDITE**)
- Toutes les erreurs doivent être gérées gracieusement
- Aucun autre framework ou librairie n'est autorisé

## Client

### Options de démarrage (toutes sont optionnelles)

| Option        | Type   | Défaut      | Description                                          |
| ------------- | :----: | :---------: | ---------------------------------------------------- |
| `-h` `--host` | String | `localhost` | Host name du serveur à contacter                     |
| `-p` `--port` | Nombre | `4242`      | Port sur lequel se connecter                         |
| `-a` `--auto` |        |             | Trouve le nombre aléatoire à la place de l'humain    |
| `-n` `--name` |        |             | Identité du client (désactivée si `--auto` utilisée) |

## Serveur

### Options de démarrage (toutes sont optionnelles)

| Option          | Type   | Défaut   | Description                                              |
| --------------- | :----: | :------: | -------------------------------------------------------- |
| `-p` `--port`   | Nombre | `4242`   | Port sur lequel attendre les clients                     |
| `-l` `--limit`  | Nombre |          | Limite de tentatives par partie                          |
| `-b` `--bounds` | String | `1,100`  | Bornes de l'interval (entiers _signés_, X et Y _inclus_) |

- À chaque tentative du client, le serveur indique si le nombre a trouver est supérieur ou inférieur au nombre tenté, ou si une erreur s'est produite.

- Si le client dépasse le nombre de tentatives possibles, la partie s'arrête et le serveur indique quel était le nombre à trouver.

- Le serveur doit garder un historique des parties jouées par les humains, même une fois relancé :
    + Nom du joueur
    + Date de début de partie
    + Date de fin de partie
    + Nombre de tentatives
    + Statut de la partie (gagnée, perdue, abandonnée)

- Le serveur doit transmettre en fin de partie les 5 meilleurs scores du joueur s'il est humain et non anonyme.

## Critères d'évalution

Seront évalués les critères suivants :

- Capacité du serveur à gérer plusieurs clients en parallèle
- Gestion des différentes erreurs classiques (serveur introuvable, connexion perdue, format invalide, ...)
- Propreté, lisibilité et cohérence du code et de son style
- Qualité du design de l'architecture du code
- Capacité à proposer à l'utilisateur final une expérience agréable

[1]: https://doc.qt.io/qt-5/reference-overview.html
[2]: https://doc.qt.io/qt-5/qwebsocket.html
[3]: https://doc.qt.io/qt-5/json.html
[4]: https://doc.qt.io/qt-5/signalsandslots.html
