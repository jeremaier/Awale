listGames.txt :
Contiendra les données générées par les parties.
Seules 10 parties seront gardées dans le cache. On ecrira la 11ème partie
sur la 1ère, la 12ème sur la 2ème etc de manière cyclique.
Il y aura un reset possible avec demande de confirmation.

En gros : listGames = list of saved (avec des données en moins i.e. filtrage)

n°partie,  nameWinner : gains, nameLooser : gains, timeGame


saved.txt :
Contiendra les données générées par UNE partie.
n°partie, nameJoueur1, nameJoueur2, gain1, gain2, board_config, timeGame, currentPlayer

Les joueurs pourront donc quitter une partie en cours, puis la reprendre à l'état 
sauvegardé dans ce fichier. Reset possible.
