#include <stdio.h>

struct aoi{
    char name;
    int topLeftX;
    int width;
    int topLeftY;
    int height;
    int fixationCount;
    int dwellTime;
};

int main(int argc, char *argv[]) {//sortingCriteria, AOIsFile, DataFolder, ParticipantCount
    FILE *aoi_fp;
    char x;
    int t1;
    aoi_fp=fopen(argv[2], "r");
    fscanf(aoi_fp,"%c %d",&x,&t1);
    printf("%d %c",t1,x);
    fclose(aoi_fp);


    return 0;
}