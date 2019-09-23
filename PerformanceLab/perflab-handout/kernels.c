/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "gnr220",              /* Team name */

    "Nicholas Lahner",     /* First member full name */
    "gnr220@lehigh.edu",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
		//comment to test things
	// new change
}
char try_rotate_descr[] = "Attempt to optimize through loop unrolling";
void try_rotate(int dim, pixel *src, pixel *dst)
{	
    int i, j;
	//Attempt to unroll outer loop
	
	for (i = 0; i < dim; i += 16)
		for(j = 0; j < dim; j++)
		{
	    	dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
	    	dst[RIDX(dim-1-j, i + 1, dim)] = src[RIDX(i+1, j, dim)];
	    	dst[RIDX(dim-1-j, i + 2, dim)] = src[RIDX(i + 2, j, dim)];
	    	dst[RIDX(dim-1-j, i + 3, dim)] = src[RIDX(i + 3, j, dim)];
	    	dst[RIDX(dim-1-j, i + 4, dim)] = src[RIDX(i + 4, j, dim)];
	    	dst[RIDX(dim-1-j, i + 5, dim)] = src[RIDX(i + 5, j, dim)];
	    	dst[RIDX(dim-1-j, i + 6, dim)] = src[RIDX(i + 6, j, dim)];
	    	dst[RIDX(dim-1-j, i + 7, dim)] = src[RIDX(i + 7, j, dim)];
	    	dst[RIDX(dim-1-j, i + 8, dim)] = src[RIDX(i + 8, j, dim)];
	    	dst[RIDX(dim-1-j, i + 9, dim)] = src[RIDX(i + 9, j, dim)];
	    	dst[RIDX(dim-1-j, i + 10, dim)] = src[RIDX(i + 10, j, dim)];
	    	dst[RIDX(dim-1-j, i + 11, dim)] = src[RIDX(i + 11, j, dim)];
	    	dst[RIDX(dim-1-j, i + 12, dim)] = src[RIDX(i + 12, j, dim)];
	    	dst[RIDX(dim-1-j, i + 13, dim)] = src[RIDX(i + 13, j, dim)];
	    	dst[RIDX(dim-1-j, i + 14, dim)] = src[RIDX(i +14, j, dim)];			
	    	dst[RIDX(dim-1-j, i + 15, dim)] = src[RIDX(i +15, j, dim)];	
		}
}
/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
//    naive_rotate(dim, src, dst);
	try_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
	add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
	//try_rotate
	add_rotate_function(&try_rotate, try_rotate_descr);
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) {
	int ii, jj;
	pixel_sum sum;
	pixel current_pixel;

	initialize_pixel_sum(&sum);
	for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
		for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj+=1) {
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

		}

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * First atttempt at unrolling smooth method
*/
char speedup_smooth_descr[] = "smooth without average calls";
void speedup_smooth(int dim, pixel *src, pixel *dst) 
{
	int i, j;
	pixel_sum firstColumn;
	pixel_sum secondColumn;
	pixel_sum thirdColumn;
	for (i = 0; i < dim; i++)
	{
		secondColumn.blue = 0;
		secondColumn.red = 0;
		secondColumn.green = 0;
		secondColumn.num = 0;

		thirdColumn.blue = 0;
		thirdColumn.red = 0;
		thirdColumn.green = 0;
		thirdColumn.num = 0;
		//if i is less than the far right edge
		if (i + 1 < dim)
		{
			thirdColumn.blue += src[RIDX(i+1, 0, dim)].blue;
			thirdColumn.red += src[RIDX(i+1, 0, dim)].red;
			thirdColumn.green += src[RIDX(i+1, 0, dim)].green;
			thirdColumn.num++;
		}
		thirdColumn.blue += src[RIDX(i, 0, dim)].blue;
		thirdColumn.red += src[RIDX(i, 0, dim)].red;
		thirdColumn.green += src[RIDX(i, 0, dim)].green;
		thirdColumn.num++;
		//if is is greater than the left edge
		if (i > 0)
		{
			thirdColumn.blue += src[RIDX(i-1, 0, dim)].blue;
			thirdColumn.red += src[RIDX(i-1, 0, dim)].red;
			thirdColumn.green += src[RIDX(i-1, 0, dim)].green;
			thirdColumn.num++;
		}

		for (j = 0; j < dim; j++)
		{
			firstColumn = secondColumn;
			secondColumn = thirdColumn;
			thirdColumn.blue = 0;
			thirdColumn.red = 0;
			thirdColumn.green = 0;
			thirdColumn.num = 0;

			if (j + 1 < dim)
			{
				thirdColumn.blue += src[RIDX(i, j+1, dim)].blue;
				thirdColumn.red += src[RIDX(i, j+1, dim)].red;
				thirdColumn.green += src[RIDX(i, j+1, dim)].green;
				thirdColumn.num++;
			}
			if ( i + 1 < dim && j + 1 < dim)
			{
				thirdColumn.blue += src[RIDX(i+1, j+1, dim)].blue;
				thirdColumn.red += src[RIDX(i+1, j+1, dim)].red;
				thirdColumn.green += src[RIDX(i+1, j+1, dim)].green;
				thirdColumn.num++;
			}
			if (i > 0 && j + 1 < dim)
			{
				thirdColumn.blue += src[RIDX(i-1, j+1, dim)].blue;
				thirdColumn.red += src[RIDX(i-1, j+1, dim)].red;
				thirdColumn.green += src[RIDX(i-1, j+1, dim)].green;
				thirdColumn.num++;
			}

			dst[RIDX(i, j, dim)].blue =((firstColumn.blue + secondColumn.blue + thirdColumn.blue)/(firstColumn.num + secondColumn.num + thirdColumn.num));
			dst[RIDX(i, j, dim)].red =  ((firstColumn.red + secondColumn.red + thirdColumn.red)/(firstColumn.num + secondColumn.num + thirdColumn.num));
			dst[RIDX(i, j, dim)].green = ((firstColumn.green + secondColumn.green + thirdColumn.green)/(firstColumn.num + secondColumn.num + thirdColumn.num));
		}
	}
}
char unrollSmooth_descr[] = "smooth: unrolled";
void unrollSmooth(int dim, pixel *src, pixel *dst)
{
	int i, j;

	for (i = 0; i < dim; i+=8) {
		for (j = 0; j < dim; j++) {
			dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
			dst[RIDX(i + 1, j, dim)] = avg(dim, i + 1, j, src);
			dst[RIDX(i + 2, j, dim)] = avg(dim, i + 2, j, src);
			dst[RIDX(i + 3, j, dim)] = avg(dim, i + 3, j, src);
			dst[RIDX(i + 4, j, dim)] = avg(dim, i + 4, j, src);
			dst[RIDX(i + 5, j, dim)] = avg(dim, i + 5, j, src);
			dst[RIDX(i + 6, j, dim)] = avg(dim, i + 6, j, src);
			dst[RIDX(i + 7, j, dim)] = avg(dim, i + 7, j, src);
			dst[RIDX(i + 8, j, dim)] = avg(dim, i + 8, j, src);
		}
	}

}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    //naive_smooth(dim, src, dst);
    speedup_smooth(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
	add_smooth_function(&speedup_smooth, speedup_smooth_descr);
	add_smooth_function(&unrollSmooth, unrollSmooth_descr);
}

