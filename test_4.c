#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void print_palindrome(int a, int b, char *s, char *s_opp, int n){
    if(a == b && a == n){
        printf("%s", s);
        return;
    }
    if(a == b){
        for(int i = 0; i < n - a; i++){
            printf("%c", s_opp[i]);
        }
        printf("%s\n", s);
        for(int i = 0; i < n - b; i++){
            printf("%c", s[i]);
        }
        printf("%s", s_opp);
    }
    else if(a > b){
        for(int i = 0; i < n - a; i++){
            printf("%c", s_opp[i]);
        }
        printf("%s", s);
    }
    else if (a < b){
        for(int i = 0; i < n - b; i++){
            printf("%c", s[i]);
        }
        printf("%s", s_opp);
    }

}

void find_lps(char *s, int *lps, int n){
    int index = 1;
	int len = 0;
	
	while(index < n){
		if(s[index] == s[len]){
			len += 1;
			lps[index] = len;
			index += 1;
        }
		else{
			if(len == 0){
				lps[index] = 0;
				index += 1;
            }
			else{
				len = lps[len-1];
            }
        }
    }
}

int main(){
    char *s = malloc(sizeof(char) * 10000050);
    scanf("%s", s);
    char *s_opp = malloc(sizeof(char) * 10000050);
    int n = strlen(s);
    for(int i = n-1; i >= 0; i--){
        s_opp[n-1-i] = s[i];
    }
    char *s_final1 = malloc(sizeof(char) * 20000050);
    char *s_final2 = malloc(sizeof(char) * 20000050);
    s_final1[n] = ' ';
    s_final2[n] = ' ';
    for(int i = 0; i < n; i++){
        s_final1[i] = s[i];
        s_final1[n+1+i] = s_opp[i];
        s_final2[i] = s_opp[i];
        s_final2[n+1+i] = s[i];
    }
    int *lps1 = calloc(20000050, sizeof(int));
    int *lps2 = calloc(20000050, sizeof(int));

    find_lps(s_final1, lps1, 2*n+1);
    int a = lps1[2*n];
    find_lps(s_final2, lps2, 2*n+1);
    int b = lps2[2*n];

    printf("%d\n", a > b ? n - a : n - b);

    print_palindrome(a, b, s, s_opp, n);

    return 0;
}