#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int adjacentMineCount;
    bool isMine;
    bool isRevealed;
    bool isFlag;
} Tile;

typedef struct {
    int size;
    Tile** Tiles;
} Grid;

Grid grid;

int vie = 0;
char restart = 'y';
int nbTileRevealed = 0;
int rows, cols;
int difficulty;

void ClearBuffer() {
    while (getchar() != '\n');
}

int Askint(char* message) {
    int i;
    while (1) {
        printf("%s", message);
        if (scanf_s("%d", &i) == 1) {
            ClearBuffer();
            return i;
        }
        else {
            printf("\nVeuillez entrer un nombre valide !\n");
            ClearBuffer();
        }
    }
}

void initGrid() {
    grid.size = rows;
    grid.Tiles = malloc(grid.size * sizeof(Tile*));
    for (int i = 0; i < grid.size; i++) {
        grid.Tiles[i] = malloc(cols * sizeof(Tile));
        for (int j = 0; j < cols; j++) {
            grid.Tiles[i][j].adjacentMineCount = 0;
            grid.Tiles[i][j].isMine = false;
            grid.Tiles[i][j].isRevealed = false;
            grid.Tiles[i][j].isFlag = false;
        }
    }
}

void affichage(int vie) {
    // Affichage de la grille
    printf(" ");
    for (int l = 0; l < cols; l++)
        if (l < 9) {
            printf("  0%d  ", l + 1);
        }
        else {
            printf("  %d  ", l + 1);
        }
    printf("\n");
    for (int k = 0; k < cols; k++) {
        printf("------");
    }
    printf("-\n");

    for (int i = 0; i < rows; i++) {
        printf("|");
        for (int j = 0; j < cols; j++) {
            if (grid.Tiles[i][j].isRevealed && !grid.Tiles[i][j].isFlag) {
                // Afficher la valeur de la tuile si elle est révélée
                if (grid.Tiles[i][j].isMine) {
                    printf("  *  "); // Afficher les mines révélées
                }
                else if (grid.Tiles[i][j].adjacentMineCount >= 0 && grid.Tiles[i][j].adjacentMineCount <= 8) {
                    // Afficher le nombre de mines adjacentes
                    switch (grid.Tiles[i][j].adjacentMineCount) {
                    case 0:
                        printf("\033[0;37m"); // Blanc
                        break;
                    case 1:
                        printf("\033[0;34m"); // Bleu clair
                        break;
                    case 2:
                        printf("\033[0;32m"); // Vert
                        break;
                    case 3:
                        printf("\033[0;31m"); // Rouge
                        break;
                    case 4:
                        printf("\033[0;36m"); // Bleu foncé
                        break;
                    default:
                        printf("\033[0;35m"); // Magenta pour les autres valeurs
                    }
                    printf("  %d  ", grid.Tiles[i][j].adjacentMineCount);
                }
            }
            else if (grid.Tiles[i][j].isFlag) {
                // Afficher le drapeau si la case est marquée
                printf("  F  ");
            }
            else {
                // Afficher une case vide si elle n'est pas révélée ni marquée avec un drapeau
                printf("     ");
            }
            printf("\033[0m"); // Réinitialiser la couleur après chaque case
            printf("|");
        }

        if (i < 9) {
            printf(" 0%d\n", i + 1);
        }
        else {
            printf(" %d\n", i + 1);
        }
        for (int k = 0; k < cols; k++) {
            printf("------");
        }
        printf("-\n");
    }
}

void mines(int difficulty) {
    srand(time(NULL));
    int nbMines;
    if (difficulty == 1)
        nbMines = (rows * cols) / 10;
    if (difficulty == 2)
        nbMines = (rows * cols) / 8;
    if (difficulty == 3)
        nbMines = (rows * cols) / 6;
    for (int m = 0; m < nbMines; m++) {
        int x = rand() % rows;
        int y = rand() % cols;
        if (!grid.Tiles[x][y].isMine) {
            grid.Tiles[x][y].isMine = true;
        }
        else {
            m--;
        }
    }
}

void countMines() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!grid.Tiles[i][j].isMine) {
                int count = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid.Tiles[ni][nj].isMine) {
                            count++;
                        }
                    }
                }
                grid.Tiles[i][j].adjacentMineCount = count;
            }
        }
    }
}

void revealAdjacent(int i, int j) {
    // Vérifie les Tiles autour de la case actuelle
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int ni = i + dx;
            int nj = j + dy;
            // Vérifie si la case est valide et non révélée
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !grid.Tiles[ni][nj].isRevealed) {
                grid.Tiles[ni][nj].isRevealed = true;
                nbTileRevealed++;
                // Si la case révélée a un adjacentMineCount de 0, révèle les Tiles autour
                if (grid.Tiles[ni][nj].adjacentMineCount == 0) {
                    revealAdjacent(ni, nj); // Appel récursif pour révéler les Tiles autour
                }
            }
        }
    }
}

void playerMove() {
    int i, j;

    do {
        // Demander les coordonnées du joueur
        i = Askint("Entrez la ligne : ");
        j = Askint("Entrez la colonne : ");
        if (i < 1 || i > rows || j < 1 || j > cols) {
            printf("Coordonnées invalides. Veuillez entrer des valeurs comprises entre 1 et %d pour les lignes, et entre 1 et %d pour les colonnes.\n", rows, cols);
        }
    } while (i < 1 || i > rows || j < 1 || j > cols);

    if (i <= rows && j <= cols) {
        int action;
        do {
            // Demander à l'utilisateur quelle action effectuer
            printf("Que voulez-vous faire ?\n1. Révéler la case\n2. Placer/retirer un drapeau\nVotre choix : ");
            scanf_s("%d", &action);
            ClearBuffer();

            switch (action) {
            case 1:
                // Révéler la case choisie par le joueur
                // Gérer les drapeaux dans la fonction d'affichage
                if (!grid.Tiles[i - 1][j - 1].isRevealed && !grid.Tiles[i - 1][j - 1].isFlag) {
                    // Révéler la case si elle n'est pas déjà révélée ni marquée d'un drapeau
                    if (grid.Tiles[i - 1][j - 1].isMine) {
                        printf("Vous avez perdu\n");
                        // Afficher toutes les bombes lorsque le joueur perd
                        for (int x = 0; x < rows; x++) {
                            for (int y = 0; y < cols; y++) {
                                grid.Tiles[x][y].isRevealed = true;
                            }
                        }
                        affichage(vie);
                        vie = 1;
                    }
                    else {
                        // Révéler la case et les cases adjacentes si elle ne contient pas de mine
                        grid.Tiles[i - 1][j - 1].isRevealed = true;
                        nbTileRevealed++;
                        if (grid.Tiles[i - 1][j - 1].adjacentMineCount == 0) {
                            revealAdjacent(i - 1, j - 1);
                        }
                    }
                }
                else {
                    printf("Cette case a déjà été révélée ou marquée avec un drapeau. Veuillez choisir une autre action.\n");
                }
                break;
            case 2:
                // Placer ou retirer un drapeau sur la case choisie par le joueur
                if (!grid.Tiles[i - 1][j - 1].isRevealed) {
                    grid.Tiles[i - 1][j - 1].isFlag = !grid.Tiles[i - 1][j - 1].isFlag; // Inverser l'état du drapeau
                }
                else {
                    printf("Impossible de placer un drapeau sur une case déjà révélée. Veuillez choisir une autre action.\n");
                }
                break;
            default:
                printf("Veuillez entrer 1 ou 2 pour choisir une action valide.\n");
            }
        } while (action != 1 && action != 2);
    }
}

void checkWinner() {
    int nbAllTile = rows * cols;
    int nbMines;
    switch (difficulty) {
    case 1:
        nbMines = nbAllTile / 10;
        break;
    case 2:
        nbMines = nbAllTile / 8;
        break;
    case 3:
        nbMines = nbAllTile / 6;
        break;
    default:
        nbMines = nbAllTile / 8; // Par défaut, utilisez la densité de mines de la difficulté moyenne
    }
    int nbSafeTiles = nbAllTile - nbMines; // Nombre total de cases sans mines
    if (nbTileRevealed == nbSafeTiles) {
        vie = 2; // Toutes les cases sans mines ont été révélées, le joueur a gagné
    }
}


void play() {
    while (restart == 'y' || restart == 'Y') {
        difficulty = Askint("Entrez votre difficulté :\n1 : difficulté faible (nombre d'apparition des bombes est de 1/10)\n2 : difficulté moyenne (nombre d'apparition des bombes est de 1/8)\n3 : difficulté élevée (nombre d'apparition des bombes est de 1/6)\n\nVotre réponse : ");

        while (difficulty < 1 || difficulty > 3) {
            printf("Veuillez entrer un chiffre entre 1 et 3 pour choisir la difficulté.\n");
            difficulty = Askint("Entrez votre difficulté :\n1 : difficulté faible (nombre d'apparition des bombes est de 1/10)\n2 : difficulté moyenne (nombre d'apparition des bombes est de 1/8)\n3 : difficulté élevée (nombre d'apparition des bombes est de 1/6)\n\nVotre réponse : ");
        }

        rows = Askint("Entrez le nombre de lignes : ");
        cols = Askint("Entrez le nombre de colonnes : ");
        initGrid();
        mines(difficulty);
        countMines();
        nbTileRevealed = 0;
        vie = 0;
        while (vie == 0) {
            affichage(vie); // Correction : ajouter l'argument 'vie'
            playerMove();
            checkWinner();
        }
        if (vie == 2) {
            affichage(vie); // Correction : ajouter l'argument 'vie'
            printf("Vous avez gagné !\n");
        }
        printf("Voulez-vous recommencer ? (Y/N) : ");
        scanf_s(" %c", &restart); // Correction : remplacer scanf_s par scanf
        ClearBuffer();
        while (restart != 'y' && restart != 'Y' && restart != 'n' && restart != 'N') {
            printf("Veuillez entrer des caractères valides (Yy/Nn) : ");
            scanf_s(" %c", &restart); // Correction : remplacer scanf_s par scanf
            ClearBuffer();
        }
    }
}

int main() {
    play();
    printf("Merci d'avoir joué, au revoir !");
    return 0;
}
