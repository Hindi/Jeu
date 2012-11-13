Le level design se prépare par vague qui sont séparée par des timers. Le schéma global sera le suivant :

timer x
.
.
.
.
.
END

Le timer au début de chaque vague permet de séparer les vagues. La valeur x est à décider.
Le mot clé "END" permet de prévenir que la vague d'ennemis est terminée (ne sera pas forcemment précisé au joueurs, je sais pas encore)

La fin du niveau est précisée par le mot clé "OVER".

Le mot clé "spawn" précise que la ligne concerne une créatio, d'ennemi. Exemple :

spawn ship down 200 500

ship : le type d'ennemis
down : le type de déplacement qu'il va effectuer
200 500 : le vecteur position où il va apparaitre (origine placée en haut à gauche de l'écran)

le mot clé boss précède le nom du boss à spawn.

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
- spawnMove (déplacement aléatoire)
- roundtrip (aller-retour)