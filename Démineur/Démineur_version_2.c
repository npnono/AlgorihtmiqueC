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
    grid.Tiles = malloc(sizeof(Tile*) * rows);
    for (int i = 0; i < rows; i++) {
        grid.Tiles[i] = malloc(cols * sizeof(Tile));
        for (int j = 0; j < cols; j++) {
            grid.Tiles[i][j].adjacentMineCount = 0;
            grid.Tiles[i][j].isMine = false;
            grid.Tiles[i][j].isRevealed = false;
            grid.Tiles[i][j].isFlag = false;
        }
    }
}

void affichage() {
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
            if (grid.Tiles[i][j].isRevealed) {
                if (grid.Tiles[i][j].isMine && vie != 0) {
                    printf("  *  "); // Affiche une mine si la case est une mine et que le joueur a perdu
                }
                else {
                    // Affiche le nombre de mines adjacentes
                    if (grid.Tiles[i][j].adjacentMineCount >= 0 && grid.Tiles[i][j].adjacentMineCount <= 8) {
                        // Changer la couleur en fonction du nombre de mines adjacentes
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
                    else {
                        printf("\033[0;37m"); // Blanc pour les autres caractères
                        printf("     ");
                    }
                }
            }
            else if (vie != 0 && grid.Tiles[i][j].isMine) {
                printf("  *  "); // Affiche une mine si le joueur a perdu et la case est une mine
            }
            else if (grid.Tiles[i][j].isFlag) {
                printf("\033[0;31m"); // Rouge pour les drapeaux
                printf("  F  "); // Affiche "F" pour indiquer un drapeau
            }
            else {
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




void mines() {
    srand(time(NULL));
    int nbMines;
    if (difficulty == 1)
        nbMines = (rows * cols) / 10;
    else if (difficulty == 2)
        nbMines = (rows * cols) / 8;
    else if (difficulty == 3)
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
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int ni = i + dx;
            int nj = j + dy;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !grid.Tiles[ni][nj].isRevealed) {
                grid.Tiles[ni][nj].isRevealed = true;
                nbTileRevealed++;
                if (grid.Tiles[ni][nj].adjacentMineCount == 0) {
                    revealAdjacent(ni, nj);
                }
            }
        }
    }
}

void playerMove() {
    int i, j;
    do {
        i = Askint("Entrez la ligne : ");
        j = Askint("Entrez la colonne : ");
        if (i < 1 || i > rows || j < 1 || j > cols) {
            printf("Coordonnées invalides. Veuillez entrer des valeurs comprises entre 1 et %d pour les lignes, et entre 1 et %d pour les colonnes.\n", rows, cols);
        }
    } while (i < 1 || i > rows || j < 1 || j > cols);

    if (i <= rows && j <= cols) {
        if (!grid.Tiles[i - 1][j - 1].isRevealed) {
            if (grid.Tiles[i - 1][j - 1].isMine) {
                printf("Vous avez perdu\n");
                affichage();
                vie = 1;
            }
            else {
                grid.Tiles[i - 1][j - 1].isRevealed = true;
                nbTileRevealed++;
                if (grid.Tiles[i - 1][j - 1].adjacentMineCount == 0) {
                    revealAdjacent(i - 1, j - 1);
                }
            }
        }
        else {
            printf("Cette case a déjà été révélée. Veuillez choisir une autre case.\n");
        }
    }
}

void wantFlag() {
    char choice;
    printf("Voulez-vous placer ou retirer un drapeau sur une case ? (Y/N) : ");
    scanf_s(" %c", &choice);
    ClearBuffer();
    if (choice != 'Y' && choice != 'y') {
        printf("Vous avez choisi de ne pas placer ou retirer de drapeau.\n");
        return;
    }

    while (1) {
        int i, j;
        printf("Entrez la ligne : ");
        i = Askint("");
        printf("Entrez la colonne : ");
        j = Askint("");

        if (i < 1 || i > rows || j < 1 || j > cols || grid.Tiles[i - 1][j - 1].isRevealed) {
            if (i < 1 || i > rows || j < 1 || j > cols) {
                printf("Coordonnées invalides. Veuillez entrer des valeurs comprises entre 1 et %d pour les lignes, et entre 1 et %d pour les colonnes.\n", rows, cols);
            }
            else {
                printf("Impossible de placer un drapeau sur une case déjà révélée.\n");
            }
            continue;
        }

        if (grid.Tiles[i - 1][j - 1].isFlag) {
            grid.Tiles[i - 1][j - 1].isFlag = false;
            printf("Drapeau retiré de la case (%d, %d).\n", i, j);
        }
        else {
            grid.Tiles[i - 1][j - 1].isFlag = true;
            printf("Drapeau placé sur la case (%d, %d).\n", i, j);
        }
        affichage();

        printf("Voulez-vous placer ou retirer un autre drapeau sur une case ? (Y/N) : ");
        scanf_s(" %c", &choice);
        ClearBuffer();
        if (choice != 'Y' && choice != 'y') {
            printf("Vous avez choisi de ne pas placer ou retirer de drapeau.\n");
            break;
        }
    }
}

void checkWinner() {
    int nbMines;
    if (difficulty == 1)
        nbMines = (rows * cols) / 10;
    else if (difficulty == 2)
        nbMines = (rows * cols) / 8;
    else if (difficulty == 3)
        nbMines = (rows * cols) / 6;

    int nbAllTile = rows * cols;
    if (nbTileRevealed == nbAllTile - nbMines) {
        vie = 2;
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
        mines();
        countMines();
        nbTileRevealed = 0;
        vie = 0;
        while (vie == 0) {
            affichage();
            wantFlag();
            playerMove();
            checkWinner();
        }
        if (vie == 2) {
            affichage();
            printf("Vous avez gagné !\n");
        }
        printf("Voulez-vous recommencer ? (Y/N) : ");
        scanf_s(" %c", &restart);
        ClearBuffer();
        while (restart != 'y' && restart != 'Y' && restart != 'n' && restart != 'N') {
            printf("Veuillez entrer des caractères valides (Yy/Nn) : ");
            scanf_s(" %c", &restart);
            ClearBuffer();
        }
    }
}

int main() {
    play();
    printf("Merci d'avoir joué, au revoir !");
    return 0;
}
