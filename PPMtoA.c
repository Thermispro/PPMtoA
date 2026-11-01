#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
int main()
{
    FILE * pfile;
    int i,height = 0,width = 0,j = 0;
    uint8_t luminance;
    char *fileNameString = (char *)malloc(500);
    printf("Enter name of ppm file: \n");
    scanf("%s",fileNameString);
    pfile = fopen(fileNameString,"rb");
    if(pfile == NULL)
    {
        printf("Error in opening file\n");
        return 0;
    }
    free(fileNameString);
    char *pFileString = (char *)malloc(3);
    uint8_t *raster = (uint8_t *)malloc(6);
    fscanf(pfile, "%s",pFileString);
    if(*pFileString != 'P' || *(pFileString + 1) != '6')
    {
        printf("%s\n",pFileString);
        printf("Header of file is not of expected .ppm format\n");
        return 1;
    }
    fscanf(pfile, "%d",&width);
    fscanf(pfile, "%d",&height);
    free(pFileString);
   for(i=0;i < width*(height/2)*3;i = i+3)
    {
        fread(raster,1,1,pfile);
        fread(raster + 1,1,1,pfile);
        fread(raster + 2,1,1,pfile);
        fseek(pfile,(width*3) - 3,SEEK_CUR);
        fread(raster + 3,1,1,pfile);
        fread(raster + 4,1,1,pfile);
        fread(raster + 5,1,1,pfile);
        luminance = ((0.2126*raster[0] + 0.7152*raster[1] + 0.0722*raster[2]) + (0.2126*raster[3] + 0.7152*raster[4] + 0.0722*raster[5]))/2;
        fseek(pfile,(-(width*3)),SEEK_CUR);
        if(luminance > 0 && luminance < 25)
        {
            printf("%c",64);
        }
        else if(luminance > 26 && luminance < 53)
        {
            printf("%c",37);
        }
        else if(luminance > 52 && luminance < 78)
        {
            printf("%c",35);
        }  
        else if(luminance > 77 && luminance < 104)
        {
            printf("%c",42);
        }
        else if(luminance > 103 && luminance < 129)
        {
            printf("%c",43);
        }
        else if(luminance > 128 && luminance < 155)
        {
            printf("%c",61);
        }
        else if(luminance > 154 && luminance < 180)
        {
            printf("%c",45);
        }
        else if(luminance > 179 && luminance < 206)
        {
            printf("%c",58);
        }
        else if(luminance > 205 && luminance < 229)
        {
            printf("%c",46);
        }
        else
        {
            printf("%c",32);
        }
        if(j % width == 0 && j!= 0)
        {
            printf("\n");
            fseek(pfile,(width*3),SEEK_CUR);
        }
        j++;
    }
    free(raster);
    getchar();
    return 0;
}
