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
    Tile* Tiles;
} Grid;

Grid grid;

int vie = 0;
char restart = 'y';
int nbTileRevealed = 0;
int rows, cols;

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
    grid.Tiles = malloc(rows * sizeof(Tile*));
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
                // Vérifie si la case contient un chiffre
                if (grid.Tiles[i][j].adjacentMineCount >= 0 && grid.Tiles[i][j].adjacentMineCount <= 8) {
                    // Changer la couleur en fonction de la valeur adjacente à la mine
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
                        // Ajoutez des cas pour les autres valeurs selon vos préférences
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
            else {
                printf("     ");
            }
            printf("\033[0m"); // Réinitialiser la couleur après chaque case
            printf("|");
        }
        
        if (i < 9) {
            printf(" 0%d\n", i + 1);
        }
        else{
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
    int nbMines = (rows * cols) / 8;
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
                    revealAdjacent(i - 1, j - 1); // Appel de la fonction pour révéler les Tiles autour
                }
            }
        }
        else {
            printf("Cette case a déjà été révélée. Veuillez choisir une autre case.\n");
        }
    }
}


void checkWinner() {
    int nbMines = (rows * cols) / 8;
    int nbAllTile = rows * cols;
    if (nbTileRevealed == nbAllTile - nbMines) {
        vie = 2;
    }
}

void play() {
    rows = Askint("Entrez le nombre de lignes : ");
    cols = Askint("Entrez le nombre de colonnes : ");

    while (restart == 'y' || restart == 'Y') {
        initGrid();
        mines();
        countMines();
        nbTileRevealed = 0;
        vie = 0;
        while (vie == 0) {
            affichage();
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