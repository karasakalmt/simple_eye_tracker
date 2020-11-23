# Simple Eye Tracker Data Analyzer

It is built for analyzing fixation count and dwell time data on predeclared area of interests on developing any UX design and sorting data via using heap algorithms.  
It works with command line arguements which are:  
- **sortingCriteria:** 1 for sort by fixation count 2 for sort by dwell time.  
- **AOIsFile:** Area of intersets' file location, this file includes AOIs with the following properties name, top-left-x, width, top-left-y, and height respectively.  
We have following properties in the structure of it:  
```C
char name;  
    int topLeftX;  
    int width;  
    int topLeftY;  
    int height;  
    int fixationCount;  
    int dwellTime;  
```  
- **DataFolder:** Data folder has the data of fixation index, x, y, and fixation duration each person has their own data file as 1.txt, 2.txt,... so on.  
- **ParticipantCount:** User chooses how much people they want to include inside computation.  

Thus the program computate fixation count, and dwell time on every AOI then builds heap tree and sorts afterwards.  
This project can be implemented on Adobe XD or such software.
