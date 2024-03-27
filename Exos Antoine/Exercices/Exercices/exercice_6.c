/*#include <stdio.h>
#include <stdlib.h>

int main() {
	// 1 - Allouer une case
	// 2 - Ajout d'une valeur == ajout d'un espace mémoire

	int size = 1;

	float* Array = (float*)malloc(sizeof(float) * size);
	if (Array == NULL) exit(1);

	int values = 0;


	for (int i = 0; i < size; i++) {

		printf("Un nombre positif : ");
		scanf_s("%d", &values);

		if (values < -1) exit(1);

		if (values > 0) {
			Array[i] = values;

			size++;

			float* tArray = (float*)malloc(sizeof(float) * size);
			if (tArray == NULL) exit(1);

			for (int j = 0; j < size - 1; j++) {
				tArray[j] = Array[j];
				printf("[%d] => %f \n", j, Array[j]);
			}
			Array = tArray;
		}

		if (values == -1) {
			for (int j = 0; j < size - 1; j++) {
				printf("[%d] => %f \n", j, Array[j]);
			}
		}

	}
}*/