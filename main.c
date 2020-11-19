#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct aoi{
    char name;
    int topLeftX;
    int width;
    int topLeftY;
    int height;
    int fixationCount;
    int dwellTime;
};
int aoiFinder(struct aoi[], int, int);
void printAOIs(struct aoi[]);
void computeFixationCount(struct aoi[],char *,int);
void computeDwellTime(struct aoi[],char *,int);
int main(int argc, char *argv[]) {//sortingCriteria, AOIsFile, DataFolder, ParticipantCount
    FILE *aoi_fp, *user;
    char char_aoi;
    int counter,top_left_x,top_left_y,width,height;
    aoi_fp = fopen(argv[2], "r");
    if (aoi_fp==NULL)
    {
        printf("There is no such file.");
        return 0;
    }
    for (counter=0; !feof(aoi_fp);counter++)//counts the aois
    {
        fscanf(aoi_fp, "%c %d %d %d %d ", &char_aoi, &top_left_x, &width, &top_left_y, &height);
    }
    fclose(aoi_fp);
    struct aoi aois[counter];
    aoi_fp = fopen(argv[2], "r");
    for (counter=0; !feof(aoi_fp);counter++)//initializes the array of aois
    {
        fscanf(aoi_fp, "%c %d %d %d %d ", &aois[counter].name, &aois[counter].topLeftX, &aois[counter].width, &aois[counter].topLeftY, &aois[counter].height);
        aois[counter].fixationCount=0;
        aois[counter].dwellTime=0;
    }
    /*for(counter=1;counter <= atoi(argv[4]);counter++)//opens the user data files
    {
        sprintf(user_number,"%d.txt",counter);
        puts(user_number);
    }*/
    int people;
    people = atoi(argv[4]);
    printAOIs(aois);
    computeFixationCount(aois, argv[3], people);
    printAOIs(aois);
    return 0;
}

int aoiFinder(struct aoi aois[], int x, int y)
{
    int index;//Index of AOI
    for(index=0; index<22/*aois[index]!=NULL*/; index++)
    {
        if(x>=aois[index].topLeftX && x<=aois[index].topLeftX+aois[index].width && y>=aois[index].topLeftY && y<=aois[index].topLeftY+aois[index].height)
            break;
    }
    if(index==21 && !(x>=aois[index].topLeftX && x<=aois[index].topLeftX+aois[index].width && y>=aois[index].topLeftY && y<=aois[index].topLeftY+aois[index].height))
        return -1;
    return index;
}

void printAOIs(struct aoi aois[])
{
    int index;//Index of AOI
    printf("AOI Fixation-count Dwell-time\n");
    for(index=0; index<22/*aois[index]!=NULL*/; index++)
    {
        printf("%c\t%d\t%d ms\n", aois[index].name, aois[index].fixationCount, aois[index].dwellTime);
    }
}

void computeFixationCount(struct aoi aois[],char *folder,int people)
{
    FILE *user;
    int x,y,index,line,duration;
    char user_file[15];
    for(int counter=1;counter <= people;counter++)//opens the user data files
    {
        char line_size[20];
        sprintf(user_file,"%s/%d.txt",folder,counter);
        user = fopen(user_file,"r");
        fgets(line_size, sizeof(line_size), user);
        while(!feof(user))//initializes the array of aois
        {
            fscanf(user, "%d %d %d %d ", &line, &x, &y, &duration);
            index = aoiFinder(aois, x, y);
            if(index==-1)//in the case if point is not in any AOI
                continue;
            aois[index].fixationCount++;
        }
    }
}
