### Variables d'environnements (varenv)
#### Constructeur

```c
t_varenv    varenv_construct(char **src);
```
Le constructeur renvoie une structure `t_varenv` qui contient le nombre de variables et un pointeur sur la première variable de la liste (`t_envitem`), il prend en argument un tableau de chaînes de caractères (`**args` du main).
#### Destructeur
```c
void	    varenv_kill(t_varenv *ve);
```
#### Built-in
```c
void	    builtin_env(t_varenv *ve);
void	    builtin_export(t_varenv *ve, int argc, char **args);
void	    builtin_unset(t_varenv *ve, int argc, char **args);
```
Les built-in prennent le nombre d'arguments à passer et la liste de ces derniers.
