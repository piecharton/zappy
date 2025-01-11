# Zappy
Make a fun game

Architecture :

    - Choisir :
        - les langages
        - les libs / framework

    - Github Actions :
        - compilation 
        - tests unitaires (GTest ?)
        - tests fonctionnels


Conception :
Diagrammes de sequences avec plantuml ?

Serveur - cpp

Features
- [P1] Boucle de jeu serveur ??
    - ecouter les messages
    - calculer l'etat du jeu
    - envoyer le resultat aux clients

- Generation de Map
- Connexion Client

Contraintes :
- Socket non bloquant
- 1 Process et 1 thread


<u>Client - TBD</u>
- Commandes
- Connexion Serveur

GUI - TBD

[Questions]
Protocole TCP a recoder ?-> A priori non, c'est juste un parametre (SOCK_STREAM a donner a la socket)


Algo IA