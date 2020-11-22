#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct aoi{
    char name;
    int topLeftX;
    int width;
    int topLeftY;
    int height;
    int fixationCount;
    int dwellTime;
};
int aoiFinder(struct aoi[], int, int, int);
void printAOIs(struct aoi[], int);
void computeFixationCount(struct aoi[],char *,int, int);
void computeDwellTime(struct aoi[],char *, int, int);
int parentIndex(int);
int leftIndex(int);
int rightIndex(int);
void swap(struct aoi[], int, int);
int heapHeight(double);
void heapify(struct aoi[], int, int, int);
void buildHeap(struct aoi[], int, int);
void heapSort(struct aoi[], int, int);
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
    int len_aoi=counter;
    struct aoi aois[counter+1];
    aoi_fp = fopen(argv[2], "r");
    for (counter=1; !feof(aoi_fp);counter++)//initializes the array of aois
    {
        fscanf(aoi_fp, "%c %d %d %d %d ", &aois[counter].name, &aois[counter].topLeftX, &aois[counter].width, &aois[counter].topLeftY, &aois[counter].height);
        aois[counter].fixationCount=0;
        aois[counter].dwellTime=0;
    }

    int people;
    people = atoi(argv[4]);
    printAOIs(aois, len_aoi);
    computeFixationCount(aois, argv[3], people, len_aoi);
    computeDwellTime(aois, argv[3], people, len_aoi);
    printAOIs(aois, len_aoi);
    buildHeap(aois,atoi(argv[1]),len_aoi);
    //heapSort(aois,2,len_aoi);
    printAOIs(aois, 23);

    return 0;
}

int aoiFinder(struct aoi aois[], int x, int y, int len)
{
    int index;//Index of AOI
    for(index=0; index<len; index++)
    {
        if(x>=aois[index].topLeftX && x<=aois[index].topLeftX+aois[index].width && y>=aois[index].topLeftY && y<=aois[index].topLeftY+aois[index].height)
            break;
    }
    if(index==21 && !(x>=aois[index].topLeftX && x<=aois[index].topLeftX+aois[index].width && y>=aois[index].topLeftY && y<=aois[index].topLeftY+aois[index].height))
        return -1;
    return index;
}

void printAOIs(struct aoi aois[], int len)
{
    int index;//Index of AOI
    printf("AOI Fixation-count Dwell-time\n");
    for(index=1; index<len; index++)
    {
        printf("%d %c\t%d\t%d ms\n",index, aois[index].name, aois[index].fixationCount, aois[index].dwellTime);
    }
}

void computeFixationCount(struct aoi aois[],char *folder,int people, int len)
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
            index = aoiFinder(aois, x, y, len);
            if(index==-1)//in the case if point is not in any AOI
                continue;
            aois[index].fixationCount++;
        }
    }
}

void computeDwellTime(struct aoi aois[],char *folder,int people, int len)
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
            index = aoiFinder(aois, x, y, len);
            if(index==-1)//in the case if point is not in any AOI
                continue;
            aois[index].dwellTime+=duration;
        }
    }
}

int parentIndex(int index)
{
    return index/2;
}
int leftIndex(int index)
{
    return index*2;
}
int rightIndex(int index)
{
    return index*2+1;
}
void swap(struct aoi aois[], int index_1, int index_2)
{
    struct aoi tmp;
    tmp.name = aois[index_1].name;
    tmp.width = aois[index_1].width;
    tmp.height = aois[index_1].height;
    tmp.dwellTime = aois[index_1].dwellTime;
    tmp.fixationCount = aois[index_1].fixationCount;
    tmp.topLeftY = aois[index_1].topLeftY;
    tmp.topLeftX = aois[index_1].topLeftX;

    aois[index_1].name = aois[index_2].name;
    aois[index_1].width = aois[index_2].width;
    aois[index_1].height = aois[index_2].height;
    aois[index_1].dwellTime = aois[index_2].dwellTime;
    aois[index_1].fixationCount = aois[index_2].fixationCount;
    aois[index_1].topLeftY = aois[index_2].topLeftY;
    aois[index_1].topLeftX = aois[index_2].topLeftX;

    aois[index_2].name = tmp.name;
    aois[index_2].width = tmp.width;
    aois[index_2].height = tmp.height;
    aois[index_2].dwellTime = tmp.dwellTime;
    aois[index_2].fixationCount = tmp.fixationCount;
    aois[index_2].topLeftY = tmp.topLeftY;
    aois[index_2].topLeftX = tmp.topLeftX;
}
int heapHeight(double len)
{
    return ceil(log(len-1)/log(2))-1;
}
void heapify(struct aoi aois[], int index, int command, int arr_len)
{
    int largest,left,right,l_index,r_index,parent;
    l_index=leftIndex(index);
    r_index=rightIndex(index);
    arr_len--;
    if(command==1)
    {
        parent = aois[index].fixationCount;
        printf(" index: %d parent: %c %d",index,aois[index].name,parent);
        left = aois[l_index].fixationCount;
        printf(" index: %d left: %c %d",l_index,aois[l_index].name,left);
        right = aois[r_index].fixationCount;
        printf(" index: %d right: %c %d\n",r_index,aois[r_index].name,right);
    }
    else
    {
        parent= aois[index].dwellTime;
        printf(" parent: %c %d",aois[index].name,parent);

        left = aois[leftIndex(index)].dwellTime;
        printf(" left: %c %d",aois[l_index].name,left);

        right = aois[rightIndex(index)].dwellTime;
        printf(" right: %c %d\n",aois[r_index].name,right);

    }
    if(l_index<=arr_len+1 && left>parent)
    {
        largest=l_index;
        if(r_index<=arr_len+1 && right>parent)
            largest=r_index;
    }
    else
        largest=index;
    if(r_index<=arr_len+1 && right>parent)
        largest=r_index;
    if (largest != index)
    {
        swap(aois,index,largest);
        heapify(aois,largest,command,arr_len);
        heapify(aois,index,command,arr_len);

    }
}
void buildHeap(struct aoi aois[], int command, int arr_len)
{
    for(int index=arr_len/2; index>=1; index--)
    {
        printf("%d\n",index);
        heapify(aois, index, command, arr_len);
    }
}

/*void heapSort(struct aoi aois[], int command, int arr_len)
{
    buildHeap(aois, command, arr_len);
    for(int i=arr_len; i>2; i--)
    {
        swap(aois,1,i);
        arr_len--;
        heapify(aois, i, command, arr_len);
    }
}*/