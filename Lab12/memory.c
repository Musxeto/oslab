#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){
    double pages,mem,phyFrames,p,f,d, las, pas;
    printf("Enter Logical Address Space Information\n");
    printf("\n Enter NUmber of Pages:");
    scanf("%lf", &pages);
    printf("\n Enter Total Memory: ");
    scanf("%lf",&mem);
    printf("\n ENter frames: ");
    scanf("%lf",&phyFrames);
    p = log2(pages);
    printf("\n No. of bits needed for p: %lf", ceil(p));
    f = log2(phyFrames);
    printf("\n No. of bits needed for f: %lf", ceil(f));
    d = log2(mem);
    printf("\n No. of bits needed for d: %lf", ceil(d));
    las = p+d;
    printf("\n LOgical Address Size: %lf",las);
    pas = f+d;
    printf("\n Physical Address Size: %lf",pas);
}