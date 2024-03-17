# Math interpreter

J'ai créer ce projet afin d'ameliorer mes compétences en programmation. Il permet d'évaluer des expressions mathématiques simples.

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

## Syntaxe

- évaluez et affichez une expression avec :
`print <expression>;`

Exemples :

`print 3 + 4 * 8;`

`print (3 + 9) ** 2;`

`print f(3) + 2;`

`print exp(8);`

- déclarez une fonction avec :
`f(x) = 3*x;`

`g(x) = x**2;`

`fonction(abc) = 4 * abc + 3;`
