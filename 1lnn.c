/**
 * @file 1lnn.c
 * @brief Machine learning functionality for a 1-layer neural network
 * @author Matt Lind
 * @date July 2015
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "mnist-utils.h"
#include "1lnn.h"




/**
 * @details Returns an output vector with targetIndex set to 1, all others to 0
 */

Vector getTargetOutput(int targetIndex){
    Vector v;
    for (int i=0; i<NUMBER_OF_OUTPUT_CELLS; i++){
        v.val[i] = (i==targetIndex) ? 1 : 0;
    }
    return v;
}




/**
 * @details Initialize layer by setting all weights to random values [0-1]
 * @attention It actually makes no difference whether the weights are
 * initialized to a constant (e.g. 0.5) or to a random number.
 * The result (85% success rate) will not change significantly.
 */

void initLayer(Layer *l){
    
    for (int o=0; o<NUMBER_OF_OUTPUT_CELLS; o++){
        
        for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
            l->cell[o].input[i]=0;
            l->cell[o].weight[i]=rand()/(double)(RAND_MAX);
        }
        
        l->cell[o].output = 0;
        l->cell[o].bias = 0;
    }
}


/**
    Display weights for each input
*/
void print_weight(Layer *l)
{
    FILE *fp;
    fp = fopen("weights", "a");
    for(int o=0; o<NUMBER_OF_OUTPUT_CELLS; o++)
    {
        for(int i =0; i < NUMBER_OF_INPUT_CELLS; i++)
        {
            fprintf(fp, "%f\n", l->cell[o].weight[i]);
        }
    }fclose(fp);
}
/**
 * @details The output prediction is derived by simply sorting all output values
 * and using the index (=0-9 number) of the highest value as the prediction.
 */
void sort_weights()
{
    //FILE *fp, *fp0, *fp1, *fp2, *fp3, *fp4, *fp5, *fp6,*fp7 ,*fp8, *fp9;
    FILE *fp, *fp_weights[10];
    char buff[255];
    char ch;
    char comma = ',';
    char *filename[10] = {"weights_0", "weights_1", "weights_2", "weights_3", "weights_4", "weights_5", "weights_6", "weights_7", "weights_8", "weights_9"};
    int i, j = 0;
    fp = fopen("weights", "r+");
    /*
    fp[0] = fopen(filename[0], "a");
    fp[1] = fopen(filename[1], "a");
    fp[2] = fopen(filename[2], "a");
    fp[3] = fopen(filename[3], "a");
    fp[4] = fopen(filename[4], "a");
    fp[5] = fopen(filename[5], "a");
    fp[6] = fopen(filename[6], "a");
    fp[7] = fopen(filename[7], "a");
    fp[8] = fopen(filename[8], "a");
    fp[9] = fopen(filename[9], "a");
    */

    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    ch = fgetc(fp);
    while (ch != EOF)
    {
        ch = fgetc(fp);
        fp_weights[j] = fopen(filename[j], "a");
        fprintf(fp_weights[j], "%c", ch);

        if (ch == '\n')
        {
            fprintf(fp_weights[j], "%c", comma);
            i++;
        }

        if ( (i % 784) == 0) 
        {
                fclose(fp_weights[j]);
                j++;
        }
    }
    printf("i = %d", i);
    fclose(fp);

    /*
    fclose(fp0);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    fclose(fp7);
    fclose(fp8);
    fclose(fp9);
    */

}


int getLayerPrediction(Layer *l){
   // FILE *fp;
   // char buffer[255];

   // fp = fopen("weights.txt", "a");


    double maxOut = 0;
    int maxInd = 0;
    
    for (int i=0; i<NUMBER_OF_OUTPUT_CELLS; i++){
        
        if (l->cell[i].output > maxOut){
            maxOut = l->cell[i].output;
            maxInd = i;
        }
        //fprintf(fp, "%s %s %d %s %s %f \n", "weight", "[", i, "]", "=", l->cell[i].weight);

    }
   // fclose(fp);
    return maxInd;
    
}




/**
 * @details Creates an input vector of length NUMBER_OF_INPUT_CELLS
 * of a given MNIST image, setting input vector cells to [0,1]
 * based on the pixels of the image.
 * Scalar pixel intensity [=grey-scale] is ignored, only 0 or 1 [=black-white].
 */

void setCellInput(Cell *c, MNIST_Image *img){
    
    for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
        c->input[i] = img->pixel[i] ? 1 : 0;
    }
}




/**
 * @details Calculates a cell's output by suming all input-weight-products
 * and normalizes to [0-1].
 */

void calcCellOutput(Cell *c){
    
    c->output=0;
    
    for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){ //From 0 to 784 for each cell
        //Multiply and accumulate the inputs * weights
        c->output += c->input[i] * c->weight[i];
    }
    
    //Normalize the outputs
    c->output /= NUMBER_OF_INPUT_CELLS;             // normalize output (0-1)
}




/**
 * @details Returns the difference between a target value and the cell's ouput
 */

double getCellError(Cell *c, int target){

    double err = target - c->output;

    return err;
}




/**
 * @details Updates a cell's weights based on given error and LEARNING_RATE
 */

void updateCellWeights(Cell *c, double err){
    
    for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
        c->weight[i] += LEARNING_RATE * c->input[i] * err;
    }
}




/**
 * @details Performs the training algorithm:
 * feeding input, calculate output, calculate error, update weights)
 */

void trainCell(Cell *c, MNIST_Image *img, int target){
    
    setCellInput(c, img);
    calcCellOutput(c);
    
    // learning (by updating the weights)
    double err = getCellError(c, target);
    updateCellWeights(c, err);
}




/**
 * @details Performs the testing of the trained network
 * Same as training a cell, but without updating weights (learning)
 */

void testCell(Cell *c, MNIST_Image *img, int target){
    
    setCellInput(c, img);
    calcCellOutput(c);

    //printf("weights = %f", c->weight);
    /* Write to a file in weights for each cell */
    //FILE *fp;
    //fopen("weights", "a");
    //fprintf(fp, "%s %s %f\n","weights = ", c->weight);
    //fclose(fp);
    
}
