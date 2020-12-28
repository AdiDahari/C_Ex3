#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txtfind.h"
#define LINE 256
#define WORD 30
#define INV "Invalid input! Try again.\n"
#define ALOCFAIL "Failed to allocate memory.\n"
char *search = NULL;
char *text = NULL;
int getline1(char s[]){
    int count = 0;
    char curr = s[count];
    while(curr != '\n' && curr != '\0' && curr < LINE){
        curr = s[++count];
    }
    return count;
}
int getword(char w[]){
    int count = 0;
    char curr = w[count];
    while(curr != '\n' && curr != ' ' && curr != '\t' && curr != '\0' && count < WORD){
        curr = w[++count];
    }
    return count;
}
int substring( char str1[], char str2[]){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for(int i = 0; i < len1; i++){
        if(str2[0] == str1[i]){
            for(int j = 1; j < len2; j++){
                if(str2[j] != str1[i+j]) break;
                if(j == len2-1) return 1;
            }
        }
    }
    return 0;
}
int similar (char *s, char *t, int n){
    int count = 0, j = 0;
    int s_len = strlen(s);
    if(*(s+s_len-1) == '\r') s_len--;
    int t_len = strlen(t);
    if(s_len - n > t_len) return 0;
    for(int i = 0; i < s_len && j < t_len; i++){
        if(*(s+i) != *(t+j)) count++;
        else j++;
        if(count > n) return 0;
    }
    if(j < t_len) return 0;
    else return 1;
}
void print_lines(char *str){
    int len = strlen(str);
    int i = 0;
    while(*(str+i) != '\0' && i < len){
        int line_len = getline1(str+i);
        char *line = NULL;
        line = (char*)malloc((line_len+1) * sizeof(char));
        if(line == NULL){
             printf(ALOCFAIL);
             return;
        }
        strncpy(line, str+i, line_len);
        if(substring(line, search) == 1) printf("%s\n", line);
        i+= line_len+1;
    }
}
void print_similar_words(char *str){
    int len = strlen(str);
    int i = 0;
    while(*(str+i) != '\0' && i < len){
        int word_len = getword(str+i);
        char *word = NULL;
        word = (char*)malloc((word_len+1) * sizeof(char));
        if(word == NULL){
            printf(ALOCFAIL);
            return;
        }
        strncpy(word, str+i, word_len);
        if(similar(word, search, 1) == 1) printf("%s\n", word);
        i+=word_len+1;
    }
}
int main(){
    text = calloc(1,sizeof(char));
    char *buffer = (char*)malloc(250*LINE*sizeof(char));
    if(buffer == NULL){
            printf(ALOCFAIL);
            return-1;
        }
    printf("Please enter the text: \n");
    while(fgets(buffer, 250*LINE , stdin)){
        text = realloc(text, strlen(text)+1+strlen(buffer));
        if(text == NULL){
            printf(ALOCFAIL);
            return-1;
        }
        strcat(text, buffer);
    }
    int word = getword(text);
    search = (char*)malloc((word+1)*sizeof(char));
    strncpy(search, text, word);
    char choose = *(text + word + 1);
    if(choose != 'a' && choose != 'b'){
        printf(INV);
        return -1;
    }
    int line1 = getline1(text)+1;
    int line2 = getline1(text+line1)+1;
    text += line1+line2;
    if(choose == 'a') print_lines(text);
    else print_similar_words(text);
    return 0;
    
}
