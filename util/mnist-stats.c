/**
 * @file mnist-stats.c
 * @brief Utitlies for displaying processing details in the terminal
 * @author Matt Lind
 * @date July 2015
 */

#include <string.h>

#include "screen.h"
#include "mnist-utils.h"
#include "mnist-stats.h"




/**
 * @details Outputs a 28x28 text frame at a defined screen position
 */

void displayImageFrame(int row, int col){
    
    if (col!=0 && row!=0) locateCursor(row, col);

    printf("------------------------------\n");
    
    for (int i=0; i<MNIST_IMG_HEIGHT; i++){
        for (int o=0; o<col-1; o++) printf(" ");
        printf("|                            |\n");
    }

    for (int o=0; o<col-1; o++) printf(" ");
    printf("------------------------------");
    
}




/**
 * @details Outputs a 28x28 MNIST image as charachters ("."s and "X"s)
 */

void displayImage(MNIST_Image *img, int row, int col){

    char imgStr[(MNIST_IMG_HEIGHT * MNIST_IMG_WIDTH)+((col+1)*MNIST_IMG_HEIGHT)+1];
    strcpy(imgStr, "");
    
    for (int y=0; y<MNIST_IMG_HEIGHT; y++){
        
        for (int o=0; o<col-2; o++) strcat(imgStr," ");
        strcat(imgStr,"|");
        
        for (int x=0; x<MNIST_IMG_WIDTH; x++){
            strcat(imgStr, img->pixel[y*MNIST_IMG_HEIGHT+x] ? "X" : "." );
        }
        strcat(imgStr,"\n");
    }
    
    if (col!=0 && row!=0) locateCursor(row, 0);
    printf("%s",imgStr);
}


/* 
* OUTPUT TESTING IMAGES TO FILE
*/
void image_pixel_testing(MNIST_Image *img, int row, int col)
{
    FILE *fp;
    fp = fopen("image_pixel_testing", "a");
    static int image_counter = 0;

    char imgStr[(MNIST_IMG_HEIGHT * MNIST_IMG_WIDTH)+((col+1)*MNIST_IMG_HEIGHT)+1];
    strcpy(imgStr, "");
    
    fprintf(fp, "IMAGE NUMBER [%d]\n\n", image_counter);
    image_counter++;
    for (int y=0; y<MNIST_IMG_HEIGHT; y++){
        
        for (int o=0; o<col-2; o++) strcat(imgStr," ");
        //strcat(imgStr,"|");
        
        for (int x=0; x<MNIST_IMG_WIDTH; x++){
            strcat(imgStr, img->pixel[y*MNIST_IMG_HEIGHT+x] ? "X" : "." );
        }
        strcat(imgStr,"\n");
    }
    
    if (col!=0 && row!=0) locateCursor(row, 0);
    fprintf(fp, "%s",imgStr); 
    fprintf(fp, "%s", "------------------------------------\n");
    fprintf(fp, "%s", "------------------------------------\n");
    fclose(fp);

}

//HERE 8/15/2017
void fpga_input(MNIST_Image *img, int row, int col)
{
    FILE *fp;
    fp = fopen("fpga_input", "a");
    static int image_counter = 0;

    char imgStr[(MNIST_IMG_HEIGHT * MNIST_IMG_WIDTH)+((col+1)*MNIST_IMG_HEIGHT)+1];
    strcpy(imgStr, "");
    
    //fprintf(fp, "IMAGE NUMBER [%d]\n\n", image_counter);
    image_counter++;
    for (int y=0; y<MNIST_IMG_HEIGHT; y++){
        
        for (int o=0; o<col-2; o++) strcat(imgStr," ");
        //strcat(imgStr,"|");
        
        for (int x=0; x<MNIST_IMG_WIDTH; x++){
            strcat(imgStr, img->pixel[y*MNIST_IMG_HEIGHT+x] ? "1" : "0" );
        }
        strcat(imgStr,"\n");
    }
    
    if (col!=0 && row!=0) locateCursor(row, 0);
    fprintf(fp, "%s",imgStr); 
    //fprintf(fp, "%s", "------------------------------------\n");
    //fprintf(fp, "%s", "------------------------------------\n");
    fclose(fp);
}

/* 
* OUTPUT TRAINING IMAGES TO FILE
*/
void image_pixel_training(MNIST_Image *img, int row, int col)
{
    FILE *fp;
    fp = fopen("image_pixel_training", "a");

    char imgStr[(MNIST_IMG_HEIGHT * MNIST_IMG_WIDTH)+((col+1)*MNIST_IMG_HEIGHT)+1];
    strcpy(imgStr, "");

    for (int y=0; y<MNIST_IMG_HEIGHT; y++){
        
        for (int o=0; o<col-2; o++) strcat(imgStr," ");
        //strcat(imgStr,"|");
        
        for (int x=0; x<MNIST_IMG_WIDTH; x++){
            strcat(imgStr, img->pixel[y*MNIST_IMG_HEIGHT+x] ? "X" : "." );
        }
        strcat(imgStr,"\n");
    }
    
    if (col!=0 && row!=0) locateCursor(row, 0);
    fprintf(fp, "%s",imgStr); 

    fclose(fp);
}


/**
 * @details Outputs reading progress while processing MNIST training images
 */

void displayLoadingProgressTraining(int imgCount, int y, int x){
    
    float progress = (float)(imgCount+1)/(float)(MNIST_MAX_TRAINING_IMAGES)*100;
    
    if (x!=0 && y!=0) locateCursor(y, x);
    
    printf("1: TRAINING: Reading image No. %5d of %5d images [%d%%]",(imgCount+1),MNIST_MAX_TRAINING_IMAGES,(int)progress);
    
}




/**
 * @details Outputs reading progress while processing MNIST testing images
 */

void displayLoadingProgressTesting(int imgCount, int y, int x){
    
    float progress = (float)(imgCount+1)/(float)(MNIST_MAX_TESTING_IMAGES)*100;
    
    if (x!=0 && y!=0) locateCursor(y, x);
    
    printf("2: TESTING:  Reading image No. %5d of %5d images [%d%%]\n                                  ",(imgCount+1),MNIST_MAX_TESTING_IMAGES,(int)progress);
    
}




/**
 * @details Outputs image recognition progress and error count
 */

void displayProgress(int imgCount, int errCount, int y, int x){
    
    double successRate = 1 - ((double)errCount/(double)(imgCount+1));
    
    if (x!=0 && y!=0) locateCursor(y, x);
    
    printf("Result: Correct=%5d  Incorrect=%5d  Success-Rate=%5.2f%% \n",imgCount+1-errCount, errCount, successRate*100);
    
    
}

