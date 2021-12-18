#include <stdio.h>


long long determinante(int n, int matriz[n][n]){
	if (n == 2){
        return matriz[0][0] * matriz[1][1] - matriz[1][0]*matriz[0][1];
	}

    int det = 0;

	for(int i = 0; i < n; i++){
        int new_matrix[n-1][n-1];
        int l = 0;
        int c = 0;

        for(register int j = 1; j < n; j++){
            for(register int k = 0; k < n; k++){
                if (k != i){
                    new_matrix[l][c] = matriz[j][k];
                    c = (c + 1)%(n-1);
                    if(c == 0){
                        l++;
                    }
                }
            }
        }
        if (i%2 == 0){
            det += matriz[0][i] * determinante(n-1, new_matrix);
        }else{
            det -= matriz[0][i] * determinante(n-1, new_matrix);
        }
	}

	return det;
}



int main(){
    int a[5][5] = {{1, 3, 4, 2, -1},
                   {-3, 4, 5, 1, 2},
                   {2, 2, 3, -4, 6},
                   {9, 2, 7, -1, 0},
                   {0, 2, -4, 5, 5}};

    int det = determinante(5, a);
    printf("%d", det);

	return 0;
}

