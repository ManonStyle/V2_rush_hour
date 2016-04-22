#include <stdio.h>
#include <stdbool.h>

typedef struct liste_c{
  cgame  game;
  game * nextgame;
  int nbelement=0;
}liste;



bool estVide(liste l){
  return l->nbelement==0;
}



void insererEnTete(liste l,cgame g){
  game=g->game;
  nbelement++;
  nextgame=null; 
}


void insererElement(liste l,cgame g){
  if(estVide(l))
    insererEnTete(l,g);
  else{
    while(g->nextgame!=null){
      game->nextgame++;
    }
  }
  if(g->nextgame==null){
    game->nextgame=g;
    nbelement++;
  }
  
}


cgame recupererElement(liste l,cgame g){
}

void supprimerElement(liste l,cgame g){
}



int solveur(game g,tablehash t){
  /*lancement d'un nouveau jeu*/



  /*verification des déplacements*/

      insererElement(tablehash t,cgame g)
	/*verification de la piece gagnante*/


	

  
}

