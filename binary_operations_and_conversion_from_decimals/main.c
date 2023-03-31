int main(){
    unsigned int a, b;
    scanf("%d %d", &a, &b);
    
    int bits1[32];
    for (int i = 0; i < 32; i++) bits1[i] = 0;
    
    int bits2[32];
    for (int i = 0; i < 32; i++) bits2[i] = 0;
    
    int result_sum[32];
    for (int i = 0; i < 32; i++) result_sum[i] = 0;
    
    int pos_bit = 31;
    
    while (a >= 2){
        if (a%2 == 1){
            bits1[pos_bit] = 1;
        }
        pos_bit--;
        a = a/2;
    }
    
    if (a == 0){
        bits1[--pos_bit] = 1;
    }else{
        bits1[pos_bit] = 1;
    }
    
    int pos_bit2 = 31;
    
    while (b >= 2){
        if (b%2 == 1){
            bits2[pos_bit2] = 1;
        }
        pos_bit2--;
        b = b/2;
    }
    
    if (b == 0){
        bits2[--pos_bit2] = 1;
    }else{
        bits2[pos_bit2] = 1;
    }
    
    printf("Representation number one: ");
    for (int i = pos_bit; i < 32; i++) printf("%d", bits1[i]);
    printf("\nRepresentation number two: ");
    for (int i = pos_bit2; i < 32; i++) printf("%d", bits2[i]);
    
    //soma
    int sobra_um = 0;
    for (int i = 31; i >= 0; i--){
        if (bits1[i] && bits2[i]){
            if (sobra_um) result_sum[i] = 1;
            else sobra_um = 1;
        } 
        else if (bits1[i]^bits2[i]){
            if (!sobra_um) result_sum[i] = 1;
            else sobra_um = 1;
        }
        else if (!bits1[i] && !bits2[i] && sobra_um){
            sobra_um = 0;
            result_sum[i] = 1;
        }
    }
    
    int len = 0;
    
    if (pos_bit2 == pos_bit) len = pos_bit - 1;
    else if (pos_bit2 > pos_bit) len = pos_bit;
    else if (pos_bit > pos_bit2) len = pos_bit2;
    
    printf("\nRepresentation of sum: ");
    for (int i = len; i < 32; i++) printf("%d", result_sum[i]);
    
    return 0;    
}
