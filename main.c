#include <stdio.h>
#include <string.h>


#define  LIGNE     10
#define  COLONNE   10
#define  VIDE      ' '
#define  JOUEURX   'X'
#define  JOUEURO   'O'
#define  GANGNER    4

void afficher_tableaux(char tab[LIGNE][COLONNE]);

void remplir_tableau(char tab[LIGNE][COLONNE]);

int vérifVertical(char tab[LIGNE][COLONNE], int collone, char piece);
int verifHorizentale(char tab[LIGNE][COLONNE], int ligne, char piece);
void jouer();
void afficher_tableaux(char tab[LIGNE][COLONNE]) {
    for (int i = 0; i < LIGNE; ++i) {
        printf(" %d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < LIGNE; ++i) {
        for (int j = 0; j < COLONNE; ++j) {
            printf("|%c", tab[i][j]);
        }
        printf("|\n");
    }
}
void remplir_tableau(char tab[LIGNE][COLONNE]) {
    for (int i = 0; i < LIGNE; ++i) {
        for (int j = 0; j < COLONNE; ++j) {
            tab[i][j] = VIDE;
        }
    }
}



int vérifVertical(char tab[LIGNE][COLONNE], int collone, char piece) {
    int compteur = 0;
    for (int i = 9; i >= 0; --i) {
        if (tab[i][collone] == piece) {
            compteur++;
        } else {
            break;
        }
    }
    if (compteur >= GANGNER) {
        return 1;
    } else {
        return 0;
    }

}


int verifHorizentale(char tab[LIGNE][COLONNE], int ligne, char piece) {
    int compteur = 0;
    for (int i = 0; i < COLONNE; ++i) {
        if (tab[ligne][i] == piece) {
            compteur++;
        } else {
            break;
        }
    }
    if (compteur >= GANGNER) {
        return 1;
    } else {
        return 0;
    }

}


int vérifLesDiagonalHautDroite(char tab[LIGNE][COLONNE], int ligne, int collone, char piece) {
    int compteur = -1;
    int i, j = collone;
    for (i = ligne; i >= 0; --i) {
        if (tab[i][j] == piece) {
            compteur++;
            j++;
        } else {
            break;
        }
    }
    j = collone;
    for (int i = ligne; i < LIGNE; ++i) {
        if (tab[i][j] == piece) {
            compteur++;
            j--;
        } else {
            break;
        }
    }
    if (compteur >= GANGNER) {
        return 1;
    } else {
        return 0;
    }
}

int vérifLesDiagonaleHautGauche(char tab[LIGNE][COLONNE], int ligne, int collone, char piece) {
    int compteur = -1;
    int j = collone;
    for (int i = ligne; i >= 0; --i) {
        if (tab[i][j] == piece) {
            compteur++;
            j--;
        } else {
            break;
        }
    }
    j = collone;
    for (int i = ligne; i < LIGNE; i++) {
        if (tab[i][j] == piece) {
            compteur++;
            j++;
        } else {
            break;
        }
    }
    if (compteur >= GANGNER) {

        return 1;
    } else {
        return 0;
    }

}

/*int vérifLesDiagonaleBasDroit(char tab[LIGNE][COLONNE], int ligne, int collone, char piece) {
    int compteur = 0;
    for (int i = ligne; i < LIGNE; i++) {
        if (tab[i][collone] == piece) {
            compteur++;
            collone++;
        } else {
            break;
        }
    }
    if (compteur >= GANGNER) {
        return 1;
    } else {
        return 0;
    }
}*/
/*
int vérifLesDiagonaleBasGauche(char tab[LIGNE][COLONNE], int ligne, int collone, char piece) {
    int compteur = 0;
    for (int i = ligne; i < LIGNE; ++i) {
        if (tab[i][collone] == piece) {
            compteur++;
            collone--;
        } else {
            break;
        }
    }
    if (gagnant(compteur)) {
        return 1;
    } else {
        return 0;
    }
}
*/
int gagnerDigonale(char tab[LIGNE][COLONNE], int ligne, int collone, char piece) {
    if (vérifLesDiagonalHautDroite(tab, ligne, collone, piece) ||
        vérifLesDiagonaleHautGauche(tab, ligne, collone, piece) /*||
        vérifLesDiagonaleBasDroit(tab, ligne, collone, piece) ||
        vérifLesDiagonaleBasGauche(tab, ligne, collone, piece) */) {
        return 1;
    } else {
        return 0;
    }
}


int saisie_utilisateur(char tab[LIGNE][COLONNE], int joueur) {
    int colonne;
    int compteur;
    int tourDeBoucle = 0;
    scanf("%d", &colonne);
    compteur = 0;
    colonne = colonne - 1;
    for (int ligne = LIGNE - 1; ligne >= 0 && compteur == 0; ligne--) {
        if (tab[ligne][colonne] == VIDE) {
            if (joueur == 1) {
                tab[ligne][colonne] = JOUEURX;
                compteur++;
                tourDeBoucle++;
                if (vérifVertical(tab, colonne, JOUEURX) || verifHorizentale(tab, ligne, JOUEURX) ||
                    gagnerDigonale(tab, ligne, colonne, JOUEURX)) {
                    return 1;
                }
            } else {
                tab[ligne][colonne] = JOUEURO;
                compteur++;
                tourDeBoucle++;
                if (vérifVertical(tab, colonne, JOUEURO) || verifHorizentale(tab, ligne, JOUEURO) ||
                    gagnerDigonale(tab, ligne, colonne, JOUEURO)) {
                    return 1;
                }
            }
        }
    }
    printf("\n");
    if (compteur == 0) {
        printf("Choisi une autre colonne cette colonne est complet\n");
    }
    return 0;
}


void jouer() {
    int compteur = 0, reponse = 0;
    char nomJoueur1[100];
    char nomJoueur2[100];
    printf("Entrez le nom d'utilisateur1: ");
    scanf("%s", &nomJoueur1);
    printf("Entrez le nom d'utilisateur2: ");
    scanf("%s", &nomJoueur2);
    printf("Bienvenue, %s! vous êtes %c\n", nomJoueur1, JOUEURX);
    printf("Bienvenue, %s! vous êtes %c\n", nomJoueur2, JOUEURO);

    char tab[LIGNE][COLONNE];
    remplir_tableau(tab);


    do {
        afficher_tableaux(tab);
        if (compteur % 2 == 0) {
            printf("%s! Saisissez-vous le nombre de collone! vous êtes X : ", nomJoueur1);
            if (saisie_utilisateur(tab, 1)) {
                afficher_tableaux(tab);
                printf("Bravo %s! vous avez gangé!!!", nomJoueur1);
                reponse++;
            }
            compteur++;
        } else {
            printf("%s! Saisissez-vous le nombre de collone vous êtes 0 : ", nomJoueur2);
            if (saisie_utilisateur(tab, 2)) {
                afficher_tableaux(tab);
                printf("Bravo %s! vous avez gangé!!!", nomJoueur2);
                reponse++;
            }
            compteur++;
        }
    } while (reponse == 0);


}


int main() {
    jouer();
    return 0;
}
