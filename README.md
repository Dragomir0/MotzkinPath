# MotzkinPath

En combinatoire, un *chemin de Motzkin* est un chemin de longueur `n` qu'on peut tracer sur une grille et qui respecte les contraintes suivantes:

* Seulement 3 déplacements sont permis: en direction *nord-est* `(1,1)`, en
  direction *est* `(1,0)` et en direction *sud-est* `(1,-1)`;
* Le chemin doit commencer au point `(0,0)`;
* Le chemin doit terminer au point `(n,0)`;
* Le chemin ne peut jamais passer sous le segment qui relie les points `(0,0)`
  et `(n,0)`.

Par exemple, l'ensemble de tous les chemins de Motzkin de longueur `4` est
illustré ci-bas (tiré de la [page de Wikipedia sur les nombres de
Motzkin](https://en.wikipedia.org/wiki/Motzkin_number)):

![Les 9 chemins de Motzkin de longueur
4](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/Motzkin4.svg/1280px-Motzkin4.svg.png)

Le programme peut etre invoqué à l'aide de la syntaxe suivante

```sh
$ ./motzkin LETTRES
```

où `LETTRES` est une suite de lettres choisies parmi l'ensemble `{u,d,r}` et
devra produire sur `stdout` un fichier SVG représentant le mot de Motzkin dont
les déplacements sont interprétés comme suit:

* `u` (*up*): déplacement en direction *nord-est*;
* `d` (*down*): déplacement en direction *sud-est*;
* `r` (*right*): déplacement en direction *est*.

## Exemples de fonctionnement

```sh
$ ./motzkin urudd > urudd.svg
```

![Le chemin de Motzkin `urudd`](./urudd.svg)

```sh
$  ./motzkin uuuuuuuuuddurrruuuurddrrrdddddduuddddddr > test.svg
```

![Le chemin de Motzkin `uuuuuuuuuddurrruuuurddrrrdddddduuddddddr`](./test.svg)

* Si le programme n'a pas d'argument fourni, le programme affiche sur
  `stderr` le message `"error: wrong number of arguments"`, affiche le manuel
  d'utilisation et arrête son exécution;
* Si le mot passé utilise une lettre invalide telle que `a` (différente de `u`,
  `d` et `r`), alors le programme affiche sur `stderr` le message "error:
  unrecognized step a", affiche le manuel d'utilisation et arrêter son
  exécution;
* Si le mot de Motzkin est invalide (parce qu'il passe sous le segment `(0,0) -
  (n,0)` ou parce qu'il ne termine pas en `(n,0)`), un message d'erreur en
  conséquence (`"error: the path cannot go below the horizontal axis"`,
  `"error: the path cannot end above the horizontal axis"`) est affiché,
  suivi du manuel d'utilisation, puis le programme arrête son exécution.
* Si le chemin est trop long (largeur qui dépasse 40), le programme s'arrete en affichant l'erreur (`"error:
  the path cannot be wider than 40"`) et le manuel d'utilisation.
