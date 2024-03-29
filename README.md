# Math interpreter

J'ai créé ce projet afin d'améliorer mes compétences en programmation. Il permet d'évaluer des expressions mathématiques simples.

## Utilisation

```bash
git clone https://github.com/artus25200/math-interpreter.git
cd math-interpreter
make
./bin/math -f math.txt
````

```bash
./bin/math [-f fichier] [-d/-debug] [-ast]
```
Si aucun fichier n'est spécifié, le programme demandera à l'utilisateur d'entrer une expression :
```console
$ ./bin/math
>>> print 2 * 4;
Result : 8
```

## Syntaxe

- évaluez et affichez une expression avec :
`print <expression>;`

Exemples :

`print 3 + 4*8;`

`print (3 + 9)**2;`

`print f(3) + 2;`

`print exp(8);`

- déclarez une fonction avec :

`f(x) = 3*x;`

`g(x) = x**2;`

`fonction(abc) = 4 * abc + 3;`
