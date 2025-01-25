#include <stdio.h>
#include <dirent.h>

int main(){
    FILE *fp;
    char ch;
    int blanks=0, lines=0, characters=0;

    fp =fopen("abc.txt","r");

    if(fp==NULL){
        printf("UNABLE TO OPEN DIR");
        return 1;
    }
    while ((ch=fgetc(fp)) !=EOF)
    {
        characters++;
        if(ch==' '){
            blanks++;
        }
        else if(ch=='\n'){
            lines++;
        }
    }
    fclose(fp);
    printf("Characters: %d\n",characters);
    printf("Blanks: %d\n",blanks);
    printf("Lines: %d\n",lines);

    return 0;
    
}