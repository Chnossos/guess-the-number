Vivoka - Évaluation C++/Qt
==========================

Jeu du Plus ou Moins, en réseau.

Réalisez 2 programmes console, client et serveur, à l'aide du framework Qt. Le serveur attend un client et une fois connecté, choisi un nombre aléatoire que le client doit ensuite trouver.

- Les deux programmes doivent résider dans le même dépôt Git mais chacun disposer de son dossier
- Le type de socket à utiliser est WebSocket (`QWebSocket`)
- Les données réseau doivent transiter au format JSON
- Seule la programmation évènementielle est autorisée (l'utilisation de thread/fork/...est **INTERDITE**)
- Toutes les erreurs doivent être gérées gracieusement

## Client

- Options de démarrage :
    + -h --host (optionnelle): IP du serveur à contacter [défaut: 127.0.0.1]
    + -p --port (optionnelle): port sur lequel se connecter [défault: 4242]
    + -a --auto (optionnelle): trouve le nombre aléatoire à la place de l'humain
    + -n --name (optionnelle): identité du client (incompatible avec `--auto`)

## Serveur

- Options de démarrage :
    + -p --port   (optionnelle): port sur lequel attendre les clients [défaut: 4242]
    + -b --bounds (optionnelle): bornes de l'interval au format X,Y (entiers uniquement, X et Y inclus) [défaut: 1,100]
    + -l --limit  (optionnelle): limite de tentatives par partie

- À chaque tentative valide mais infructueuse du client, le serveur indique si le nombre a trouver est supérieur ou inférieur au nombre tenté

- Le serveur doit garder un historique des parties jouées par les humains, même une fois relancé :
    + nom du joueur
    + date de début de partie
    + date de fin de partie
    + nombre de tentatives
    + statut de la partie (gagnée, perdue, abandonnée)

- Le serveur doit transmettre en fin de partie les 5 meilleurs scores du joueur s'il est humain et non anonyme.
