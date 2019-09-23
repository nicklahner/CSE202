/* 
 * CS:APP Data Lab 
 * 
 * Nick Lahner - gnr 220
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    //Do the | operation of both inverses ~, then invert ~ that number

  return ~((~x)|(~y));
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	//when x is the max integer, this will overflow to 0x80000000
	int overflow = x + 1; 
	overflow += x;	
	return !(~overflow) & !!(~x);

}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	//places 1 in the most significant bit position
	//Shift of 31 causes it to be -2147483648 (most negative two's complement int)	
  return 1 << 31 ;
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  //This creates an integer with alternating 1 and 0 bits by shifting 4 and then adding 

  int word = 0x5;
  word = (word << 4) + 0x5; 
  word = (word << 8) + word; 
  word = (word << 16) + word; 
  
 return word;
}
//2
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
  // We will & the argument with 0x55555555, the max integer with even numbered bits set to 1 
  // where other bits are 0. If we perform the ! operation, then any zero number will become 1, and any number greater other than 0 will become zero. Performing the ! operation on that again then gets the once "greater than" number back to 1, and "once zero number" back to zero.
  int evenBitNum = ((((((0x55 << 8) | 0x55) << 8) | 0x55) << 8) | 0x55);
  int y = x & evenBitNum;
  return ! (!y);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
   
	int res = 0; 
   //Get bytes at the n and m position
   int nByte = (x >> ( n << 3) & 0xff); 
   int mByte = (x >> ( m << 3) & 0xff); 
    
   //Create a byte of 1's within an int of 0's
   int newN = 0xff << (n << 3);
   int newM = 0xff << (m << 3);
   //mask that has bytes to be swapped 
   int mask = (newN | newM);
   
   //Byte spaces now filled with zero's
   mask ^= ~0;
   return (((x & mask) | (nByte << ( m << 3))) | mByte << ( n << 3));
}
/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
	//Finds out if x is negative
	int isNeg;
	int result;
	isNeg = !!(x>>31); 
    x = (x + (isNeg << n) + (x>>31));
 	// To calculate the exponent, shift to the by n 
 	//Works for positive numbers
	result = x >> n; 
	return result;
}

/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
	
	//Binary number with all bits turned to 1
    int num = ~0;
	//Shifts the number to have all zeros to the right of the highbit and 1's to the left
	//The extra one shift is needed since 0-31 and not 1-32
	int highBit = num << highbit << 1;
	//Shifts num so that 0's are to the right of the lowbit and 1s to the left
	int lowBit = num << lowbit;
	return lowBit & (highBit ^ lowBit);	
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  	int lastFour;
	int nums8;
	int num0;
	int isInOnesRange;
	int greaterThan9;

	//This gets a bit 1 or 0 to represent if the number is  between 0x0 and 0x3
    int isInThreesRange = !((x>>4) ^ 0x3);
	//This bit will represent whether the number is between 1-8
	int nums1_79 = (!(!((x & 0x7))));
	//This bit will represent whether the number is 8 or 9
	lastFour = x & 0xf;
	nums8 = !(lastFour^0x8);
	num0 = !(lastFour);
	isInOnesRange = num0 | (nums1_79 ^ nums8); 
	greaterThan9 = (!(!(x& 0x8))  & !(!(x&0x6 )) );
	return isInThreesRange & (isInOnesRange ^ greaterThan9);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {	
	//Find if the numbers have opposite signs, used ! to prevent -1 from being used in further computations
    int oppSigns = !(x >> 31) ^ !(y >> 31);
	//Confirms that x is negative since they have different signs and x has 1 in the MSB
	int xNegAndLess = oppSigns & (x >> 31);
	//Find out if x is positive and y is negative, prevents overflow
	int xPosAndYNeg = oppSigns & !!(y >> 31);
    //Subtract x from y, if 0 or positive difference then return 
	int sameSignLess = !((y + (~x + 1)) >> 31); 	
	return (xNegAndLess | (sameSignLess & ~ xPosAndYNeg));	
}
//
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
 	//Folds int in half to count 1's through the ^ operation, if there is an even amount then return 0  
  int half = ((x ^ (x << 16)) >> 16);
  int second = ((half ^ (half << 8)) >> 8);  
  int third = ((second ^ (second << 4)) >> 4); 
  int fourth = ((third ^ (third << 2)) >> 2); 
  int fifth = ((fourth ^ (fourth << 1)) >> 1); 
  return fifth & 1;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
 	//Folds int in half to condense down to 1, This continous | operateion will boil down to 1 or 0 return
 	int half = x | ( x >> 16);
 	int second = half | (half >> 8);	
 	int third = second | (second >> 4);
 	int fourth = third | (third >> 2);
	int fifth = fourth | (fourth >> 1);
	return (~fifth & 1);		
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
    int exponent; 
	//Shift to get exponent
	exponent = (uf >> 23 ) & 0xff;
	if((exponent == 255) && uf << 9)
	{
		return uf;
	} 
	return uf & 0x7fffffff;
}

int floatIsLess(unsigned uf, unsigned ug) {
    int expF;
	int expG;
	int fracF;
	int fracG;
	expF = ((uf >> 23) & 0xff);
	expG = ((ug >> 23) & 0xff);
	fracF = (ug << 9);
	fracG = (ug << 9); 

	//printf("Testing... floatIsLess      first Float :\t%d      second float: \t%d\n", uf, ug);
	//printf("Variables.... expF:\t%d\texpG:\t%d\t\n",expF, expG);		
	if(expF <= expG)
	{
		//uf has a lower exponent than ug	
		//uf has a lower exponent and fraction so it is less than
		if(fracF< fracG)
		{   
			return 1;
		}
		
		//uf has the same exponent as ug
		if(expF == expG)
		{
			
			//frac f is less than frac g so return 1
			if(fracF < fracG)
			{
				return 1;
			}
			return 0;	
		}
	}
	return 0;
}
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	printf("Testing floatScale2...      uf:\t%d\t \n", uf);
	//Argument passed is 0, return number
	if((uf & 0x7fffffff) == 0)
	{	
		return uf;
	}
	return uf + (1 << 23);	
}
