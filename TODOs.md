Serveur
[] Envoyer état du jeu régulièrement (RFC)

Client

Commun

[x] Parsing commandes binaires
[] Setup connexion client/serveur
    [] Partie 3.5 sujet
[] Generation de map
[] Verifier le maximum de commandes
[] Boucle de jeu
    [] Socket bloquants ! partie 5 sujet
        -> permettrait de mesurer le temps ?
        -> se renseigner sur cette merde (select, poll, epoll ?)
            Ne pas etre bloqué dans l'attente d'un message
    [] Hypothèse 1 : itérer sur tous les joueurs et vérifier les messages reçus à leur sujet ???
    [] Hypothèse 2 : Partir de la socket pour déterminer le temps d'envoi ?
[] Temps de jeu -> se baser sur l'heure absolue std::chrono
[] lib commune pour l'envoi de messages
[] Setup QT
[] IHM 
    [] Connexion server
    [] Faire des trucs stylés
[] IA 
    [] Faire des trucs stylés
[] BONUUUS ?
    [] Voir ce qu'on peut faire avec QT

Questions :
Besoin d'envoyer plus d'infos au serveur ?
Bien se renseigner sur les socket et comment les intégrer à la boucle de jeu

Contraintes :
Délai pour accepter une connexion client. 1/t par exemple
    -> Protection côté client
Essayer de ne pas rester bloqué dans une communcation avec un client



Boucle de jeu :
while (1)
    Check les message de chaque joueur + check socket (queue de messages avec un timestamp ?)
    si le joueur a une action en cours et sa duree est terminée
        envoyer un message de fin d'action
        passer a l'action suivante
    sinon depiler message suivant 
    
