Le level design se pr�pare par vague qui sont s�par�e par des timers. Le sch�ma global sera le suivant :

timer x
.
.
.
.
.
END

Le timer au d�but de chaque vague permet de s�parer les vagues. La valeur x est � d�cider.
Le mot cl� "END" permet de pr�venir que la vague d'ennemis est termin�e (ne sera pas forcemment pr�cis� au joueurs, je sais pas encore)

La fin du niveau est pr�cis�e par le mot cl� "OVER".

Le mot cl� "spawn" pr�cise que la ligne concerne une cr�atio, d'ennemi. Exemple :

spawn ship down 200 500

ship : le type d'ennemis
down : le type de d�placement qu'il va effectuer
200 500 : le vecteur position o� il va apparaitre (origine plac�e en haut � gauche de l'�cran)

le mot cl� boss pr�c�de le nom du boss � spawn.

types d'ennemis possibles :
- ship
- flyingSaucer
- spawner

boss :
- lilith

type de mouvements possibles :
- up
- down
- left
- right
- don'tmove (sans espace entre les deux mots)
- spawnMove (d�placement al�atoire)
- roundtrip (aller-retour)