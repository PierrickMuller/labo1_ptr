# Réponses questions

### Migration de tâches
*Exécutez ensuite, à l’aide de la commande taskset précédemment vue, le logiciel cpu_loop sur le  même  CPU  où get_cpu_number tourne.  Qu’est-ce  qu’il  se  passe ?*
- Get_CPU se fait déloger de son emplacement.

*Restreignez  l’exécution  de get_cpu_numbersur 2-3 CPUs, ouvrez un nombre correspondant de terminaux et essayez de déloger get_cpu_number de son CPU. Utilisez la commande htop pour visualiser la charge du système et commentez par écrit*
- Get_cpu_number se fait déloger à chaque lancement de cpu_look sur un des CPUs. Dans htop, on peut voir la charge passer d'un processeur à l'autre lors du lancement d'un cpu_look.
