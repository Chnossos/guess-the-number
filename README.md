Vivoka - Évaluation C++/Qt
==========================

Jeu du Plus ou Moins, en réseau.

Réalisez 2 programmes console, client et serveur, à l'aide du [framework Qt][1]. Le serveur attend un ou plusieurs clients et une fois connectés, choisi un nombre aléatoire que le client doit ensuite trouver.

- Les deux programmes doivent résider dans le même dépôt Git mais chacun disposer de son dossier
- Le type de socket à utiliser est WebSocket non-sécurisée ([`QWebSocket`][2])
- Les données réseau doivent transiter au format [`JSON`][3]
- Seule la [programmation évènementielle][4] est autorisée (l'utilisation de thread/fork/...est **INTERDITE**)
- Toutes les erreurs doivent être gérées gracieusement

## Client

- Options de démarrage (toutes sont **optionnelles**) :
    + `-h` `--host` : host name du serveur à contacter [défaut: `127.0.0.1`]
    + `-p` `--port` : port sur lequel se connecter [défault: `4242`]
    + `-a` `--auto` : trouve le nombre aléatoire à la place de l'humain
    + `-n` `--name` : identité du client (désactivée si `--auto` utilisée)

## Serveur

- Options de démarrage :
    + `-p` `--port`   : port sur lequel attendre les clients [défaut: 4242]
    + `-b` `--bounds` : bornes de l'interval au format X,Y (entiers uniquement, X et Y inclus) [défaut: 1,100]
    + `-l` `--limit`  : limite de tentatives par partie

- À chaque tentative valide mais infructueuse du client, le serveur indique si le nombre a trouver est supérieur ou inférieur au nombre tenté.

- Si le client dépasse le nombre de tentatives possibles, la partie s'arrête et le serveur indique quel était le nombre à trouver.

- Le serveur doit garder un historique des parties jouées par les humains, même une fois relancé :
    + nom du joueur
    + date de début de partie
    + date de fin de partie
    + nombre de tentatives
    + statut de la partie (gagnée, perdue, abandonnée)

- Le serveur doit transmettre en fin de partie les 5 meilleurs scores du joueur s'il est humain et non anonyme.

[1]: https://doc.qt.io/qt-5/reference-overview.html
[2]: https://doc.qt.io/qt-5/qwebsocket.html
[3]: https://doc.qt.io/qt-5/json.html
[4]: https://doc.qt.io/qt-5/signalsandslots.html
