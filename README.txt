listGames.txt :
Contiendra les donn�es g�n�r�es par les parties.
Seules 10 parties seront gard�es dans le cache. On ecrira la 11�me partie
sur la 1�re, la 12�me sur la 2�me etc de mani�re cyclique.
Il y aura un reset possible avec demande de confirmation.

En gros : listGames = list of saved (avec des donn�es en moins i.e. filtrage)

n�partie,  nameWinner : gains, nameLooser : gains, timeGame


saved.txt :
Contiendra les donn�es g�n�r�es par UNE partie.
n�partie, nameJoueur1, nameJoueur2, gain1, gain2, board_config, timeGame, currentPlayer

Les joueurs pourront donc quitter une partie en cours, puis la reprendre � l'�tat 
sauvegard� dans ce fichier. Reset possible.
