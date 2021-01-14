#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_carte (int i, int j, int carte[20][20]) ;      //FONCTION : INITIALISATION DE LA CARTE

void affichage_carte(int i, int j, int carte[20][20], int coord[2]) ;       //FONCTION : AFFICHAGE DE LA CARTE

void deplace_personnage(int i, int j, int carte[20][20], int coord[2]) ;       //FONCTION : DEPLACEMENT DU PERSONNAGE

int pointdevie(int i, int j, int carte[20][20], int coord[2], int pv) ;       //FONCTION : POINT DE VIE RESTANT

int clef(int i, int j, int carte[20][20], int coord[2], int c) ;        //FONCTION : NOMBRE DE CLEF

int pieceor(int i, int j, int carte[20][20], int coord[2], int c, int po) ;         //FONCTION : NOMBRE DE PIECE D'OR

int main () {

    int i, j ;
    int carte[20][20] ;
    int coord[2] ;

    int pv ;
    pv = 10 ;

    int c ;
    c = 0 ;

    int po ;
    po = 0 ;

    coord[0]=0 ;
    coord[1]=0 ;

    init_carte(i, j, carte) ;

    while ( ((0<=coord[0])&&(coord[0]<=19)) && ((0<=coord[1])&&(coord[1]<=19)) ) {      //TANT QUE LE PERSONNAGE EST DANS LA MAP

        affichage_carte(i,j, carte, coord) ;    //AFFICHE LA MAP

        printf("\n") ;          //STATISTIQUE DE LA PARTIE EN COURS
        printf("COORDONNEES : ( %d / %d )\n", coord[0], coord[1]) ;
        printf("POINT DE VIE : %d\n", pv) ;
        printf("PIECE D'OR : %d\n", po) ;
        printf("CLEF : %d\n", c) ;

        deplace_personnage(i, j, carte, coord) ;       //REDIRECTION VERS LES FONCTIONS
        pv = pointdevie(i, j, carte, coord, pv) ;
        c = clef(i, j, carte, coord, c) ;
        po = pieceor(i, j, carte, coord, c, po) ;

        if (pv <= 0) {      //SI 0 PV ALORS PARTIE PERDU
            printf("TU AS PERDU, TU AS %d POINT DE VIE\n\n\n", pv);
            return 0;
        }

        if (po >= 10) {        //SI 10 PO ALORS PARTIE GAGNE
            printf("TU AS GAGNE, TU AS OBTENUE %d PIECE D'OR\n\n\n", po);
            return 0;
        }

        if (coord[0] == 25) {      //SI TAPER 0 ALORS FIN DE LA PARTIE
            printf("FIN DE LA PARTIE\n\n\n");
            return 0;
        }

    }       //FIN DE LA BOUCLE TANT QUE

    return 0 ;
}

void init_carte (int i, int j, int carte[20][20]) {      //INITIALISATION DE LA CARTE

    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            carte[i][j] = 0 ;      //REMPLISSAGE D'HERBE
        }
    }

    srand( time( NULL ) );

//MISE EN PLACE DES OBSTACLES
//1==FLEUR
//2==ARBRE
//3==ROCHER
//4==CLEF
//5==PIECE D'OR
//6==CADENAS
//7==PIEGE
//8==MONSTRE

    for (i=0; i<20; i=rand()%21) {
	for (j=0; j<20; j=rand()%21) {
		carte[i][j] = rand()%9;
	}
    }

}

void affichage_carte(int i, int j, int carte[20][20], int coord[2]) {        //AFFICHAGE DE LA CARTE

    system("clear") ;
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            if ((i==coord[0])&&(j==coord[1])) {     //AFFICHAGE DU PERSONNAGE
                printf("X ") ;
            }
            else if (carte[i][j]==0) {      //AFFICHAGE D'HERBE
                printf("- ") ;
            }
            else {
                printf("%d ", carte[i][j]) ;     //AFFICHAGE EMPLACEMENT
            }
        }
        printf("\n") ;
    }

    printf("\n") ;
}

void deplace_personnage(int i, int j, int carte[20][20], int coord[2]) {       //DEPLACEMENT DU PERSONNAGE

    int x ;
    scanf("%d", &x) ;

    i=coord[0] ;
    j=coord[1] ;

    switch(x) {     //INSTURCTION DE DEPLACEMENT

        case 6 :        //DEPLACEMENT A DROITE
            coord[1] = coord[1] + 1 ;
            j++ ;
            if(carte[i][j] == 2 || carte[i][j] == 3 || coord[1]>19 ) {
                coord[1]=coord[1] - 1 ;
            }
        break ;

        case 4 :        //DEPLACEMENT A GAUCHE
            coord[1] = coord[1] - 1 ;
            j-- ;
            if(carte[i][j] == 2 || carte[i][j] == 3 || coord[1]<0 ) {
                coord[1]=coord[1]+1 ;
            }
        break ;

        case 8 :        //DEPLACEMENT EN HAUT
            coord[0] = coord[0] - 1 ;
            i-- ;
            if( carte[i][j] == 2 || carte[i][j] == 3 || coord[0]<0 ) {
                coord[0] = coord[0] + 1 ;
            }
        break ;

        case 2 :        //DEPLACEMENT EN BAS
            coord[0] = coord[0] + 1 ;
            i++ ;
            if( carte[i][j] == 2 || carte[i][j] == 3 || coord[0]>19 ) {
                coord[0] = coord[0] - 1 ;
            }
        break ;

        case 0 :        //POUR METTRE FIN A LA PARTIE
            coord[0] = 25 ;
        break ;

        default :       //SI ERREUR DE DEPLACEMENT
            printf("Erreur de saisie\n") ;
            printf("Tu es sur une case %d\n", carte[i][j]) ;
        break ;
    }

}

int pointdevie(int i, int j, int carte[20][20], int coord[2], int pv) {         //POINT DE VIE RESTANT

    i=coord[0] ;
    j=coord[1] ;

    if((carte[i][j] == 7)||(carte[i][j] == 8)) {    //SI ON SE DEPLACE SUR PIEGE OU MONSTRE 1 POINT DE VIE EST ENLEVER
        pv = pv - 1 ;
        carte[i][j] = 0 ;   //LE PIEGE OU MONSTRE SE CHANGE EN HERBE
    }

    return pv ;
}

int clef(int i, int j, int carte[20][20], int coord[2], int c) {        //NOMBRE DE CLEF

    i=coord[0] ;
    j=coord[1] ;

    if(carte[i][j] == 4) {      //SI ON OBTIENT UNE CLEF ALORS ON A UNE CLEF
        c = c + 1 ;
        carte[i][j] = 0 ;        //LA CLEF CE CHANGE EN HERBE
    }

    return c ;
}

int pieceor(int i, int j, int carte[20][20], int coord[2], int c, int po) {         //NOMBRE DE PIECE D'OR

    i=coord[0];
    j=coord[1];

    if(carte[i][j] == 5) {      //SI ON OBTIENT UNE PIECE D'OR ALORS 1 DE PLUS
        po = po + 1 ;
        carte[i][j] = 0 ;       //LA PIECE D'OR SE CHANGE EN HERBE
    }

    else if((carte[i][j] == 6)&&(c >= 1)) {       //SI ON A UNE CLEF ET ON OBTIENT UN CADENAT ALORS 5 PIECE D'OR DE PLUS
        po = po + 5;
        c = c - 1 ;
        carte[i][j] = 0 ;       //LE CADENAS SE CHANGE EN HERBE
    }

    return po ;
}
