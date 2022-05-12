#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct group{
    long long int data;
    long long int data2;
    int id;
}group;

long long int hash(char *s, int l,long long int d, long long int q){
    long long int p = 0;
    for(int i = 0; i < l; i++){
        p = (d * p + (s[i]-'!')) % q;
    }
    return p;
}

void compute_hash_adjust(long long int *hash_adjust, int l, long long int d, long long int q){
    hash_adjust[l-1] = 1;
    for(int i = l-2; i >= 0; i--){
        hash_adjust[i] = (d * hash_adjust[i+1]) % q;
    }
}

void adjust_hash(group *hash_group, long long int *hash_num, char **s, int k, long long int *hash_adjust, int j, long long int q){
    for(int i = 0; i < k; i++){
        hash_group[i].data = (hash_num[i] - (s[i][j] - '!') * hash_adjust[j] % q + q) % q;
    }
}

void adjust_hash2(group *hash_group, long long int *hash_num, char **s, int k, long long int *hash_adjust, int j, long long int q){
    for(int i = 0; i < k; i++){
        hash_group[i].data2 = (hash_num[i] - (s[i][j] - '!') * hash_adjust[j] % q + q) % q;
    }
}

int cmp(const void *a, const void *b){
    if((*(group*)a).data > (*(group*)b).data){
        return 1;
    }
    else if((*(group*)a).data < (*(group*)b).data){
        return -1;
    }
    else{
        if((*(group*)a).data2 > (*(group*)b).data2){
            return 1;
        }
        else if((*(group*)a).data2 < (*(group*)b).data2){
            return -1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

int main(){
    int k, l, flag;
    long long int d = 94;
    long long int d2 = 97;
    long long int q = (__LONG_LONG_MAX__ / 94) + 1;
    long long int q2 = (__LONG_LONG_MAX__ / 97) + 1;
    scanf("%d%d%d", &k, &l, &flag);
    char **s_group = malloc(sizeof(char*) * k);
    for(int i = 0; i < k; i++){
        s_group[i] = malloc(sizeof(char) * (l + 1));
    }
    for(int i = 0; i < k; i++){
        scanf("%s", s_group[i]);
    }

    long long int *hash_num = malloc(sizeof(group)*k);
    long long int *hash_num2 = malloc(sizeof(group)*k);
    for(int i = 0; i < k; i++){
        hash_num[i] = hash(s_group[i], l, d, q);
        hash_num2[i] = hash(s_group[i], l, d2, q2);
    }

    long long int *hash_adjust = malloc(sizeof(long long int) * l);
    long long int *hash_adjust2 = malloc(sizeof(long long int) * l);
    compute_hash_adjust(hash_adjust, l, d, q);
    compute_hash_adjust(hash_adjust2, l, d2, q2);

    long long int pairs_sum = 0;
    long long int same_pairs = 0;

    if(flag == 1){
        group *hash_group = malloc(sizeof(group)*k);
        for(int i = 0; i < k; i++){
            hash_group[i].data = hash_num[i];
            hash_group[i].data2 = hash_num2[i];
            hash_group[i].id = i;
        }
        qsort(hash_group, k, sizeof(group), cmp);
        long long int a = 1;
        int b = 0;
        for(int i = 0; i <= k-2; i++){
            if(hash_group[i].data == hash_group[i+1].data && hash_group[i].data2 == hash_group[i+1].data2){
                a++;
                b = 1;
            }
            else{
                b = 0;
            }
            if(a > 1 && (b == 0 || i == k - 2)){
                same_pairs += a * (a - 1) / 2;
                a = 1;
            }
        }
        free(hash_group);
    }
    
    for(int j = 0; j < l; j++){
        group *hash_group = malloc(sizeof(group)*k);
        for(int i = 0; i < k; i++){
            hash_group[i].id = i;
        }
        adjust_hash(hash_group, hash_num, s_group, k, hash_adjust, j, q);
        adjust_hash2(hash_group, hash_num2, s_group, k, hash_adjust2, j, q2);
        qsort(hash_group, k, sizeof(group), cmp);
        if(flag == 0){
            for(int i = 0; i <= k-2; i++){
                if(hash_group[i].data == hash_group[i+1].data && hash_group[i].data2 == hash_group[i+1].data2){
                    printf("Yes\n%d %d", hash_group[i].id, hash_group[i+1].id);
                    return 0;
                }
            }
        }
        else{
            long long int a = 1;
            int b = 0;
            long long int similar_pairs = 0;
            for(int i = 0; i <= k-2; i++){
                if(hash_group[i].data == hash_group[i+1].data && hash_group[i].data2 == hash_group[i+1].data2){
                    a++;
                    b = 1;
                }
                else{
                    b = 0;
                }
                if(a > 1 && (b == 0 || i == k - 2)){
                    similar_pairs += a * (a - 1) / 2;
                    a = 1;
                }
            }
            pairs_sum += similar_pairs - same_pairs;
        }
        free(hash_group);
    }

    pairs_sum += same_pairs;

    if(flag == 1){
        if(pairs_sum > 0){
            printf("Yes\n%lld", pairs_sum);
        }
        else{
            printf("No");
        }
    }
    else{
        printf("No");
    }
    

    return 0;
}