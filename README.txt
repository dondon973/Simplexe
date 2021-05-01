Auteur : Dondon973
Licence GNU libre
Simplexe V 1.0

Le projet Simplexe est d'automatiser un programme linéaire en implémentant l'algorithme du simplexe.
 Cet algorithme est un des outils de la recherche opérationnel aide à résoudre certains problème d'optimisaton.
		
	Pour la premier version , mon programme automatise seulement la résolution des problèmes de maximum.L’utilisateur rentre les informations associée au problème que l’on va modéliser ,tel que le nombres variables ,le nombre de  contraintes, leurs coefficient dans la fonction objectif et etc. Ensuite il résout le problème en suivant l’algorithme du simplexe et à chaque étape de la résolution on affiche le tableau de du programme linéaire. De plus les contraintes saisi par l’utilisateur devront être des limites maximum ,sinon il faut entrer les opposée des coefficients des variables pour les limites minimum . 
	Dans le répertoire, vous trouverez le fichier source main.c qui exécute le programme linéaire. Il y a le fichier source simplexe.c qui contient les définitions des fonctions qui est associée a chaque étapes de l’algorithme. Et le fichier header qui contient les définitions des types et structures ainsi que les prototypes des fonctions .  Vous trouverez aussi README qui explique comment compiler le programme avec le Makefile. Pour le future ,je souhaite implémentez de telle façon a ce qu’il résout pour des fonction à minimiser ou maximiser et peut importe les contraintes (minimum ou maximum)
	
Pour compiler le programme linéaire entrez sur un terminal ou console ou invité de commande :
	make exec
	Pour le lancer : 
	./exec
Lancez ces commandes dans un invité de commande situé dans le repertoire.Et suivez les instructions du programme.
La version 1.0 ne traite que les problèmes de maximisation. La prochaine version traitera les fonctions à minimiser.
 les inéquations du problème doivent etre des inégalités supérieur ,sinon les ocefficient rentrer par l'utililsateur doivent etre de signe opposée.
