# Réponses questions

### 1ères mesures
*Le résultat est le nombre d’opérations par seconde (quelles operations ?)*
- oui

*Essayez différentes optimisations à l’aide des arguments -O2 et -O3 de gcc et commentez les
résultats.*
- On peut voir une réduction du nombre d'opérations avec -02 et encore une réduction avec -03

### Multi-tâche : Commandes utiles
*Cette commande vous permet d’observer le statut des processus en cours d’exécution : Que signifient
les lettres et symboles de la colonne STAT ? Etablissez une petite table contenant les symboles, l’état
du processus et une brève description de leur sens.*

![](/cours_REDS/PTR/PIERRICK/labo1_ptr/STATE_CODES.png)

### Ordonnancement en temps partagé
*Pouvez-vous expliquer le résultat de ces trois commandes ? Si vous avez des doutes, ajoutez getpid()
à la sortie des printf de cpu_loop.c.*
- NON

*Si vous ouvrez 2 shells et utilisez la même commande taskset dans chacun, et exécutez ensuite la
commande suivante sur le premier shell :*

`$ sleep 1; ./cpu_loop & ./cpu_loop`

*Et au même instant la commande suivante sur le second :*

`$ ./cpu_loop & ./cpu_loop`

*Quel résultat obtenez-vous ? Pourquoi ?*

- OUI

### Migration de tâches
*Exécutez ensuite, à l’aide de la commande taskset précédemment vue, le logiciel cpu_loop sur le  même  CPU  où get_cpu_number tourne.  Qu’est-ce  qu’il  se  passe ?*
- Get_CPU se fait déloger de son emplacement.

*Restreignez  l’exécution  de get_cpu_numbersur 2-3 CPUs, ouvrez un nombre correspondant de terminaux et essayez de déloger get_cpu_number de son CPU. Utilisez la commande htop pour visualiser la charge du système et commentez par écrit*
- Get_cpu_number se fait déloger à chaque lancement de cpu_look sur un des CPUs. Dans htop, on peut voir la charge passer d'un processeur à l'autre lors du lancement d'un cpu_look.


### Codage
*Commentaires*

*Quelles sont les différences entre niceness et priorités ?*
La niceness est une priorité user-space alors que la priorité concerne le kernel linux.
