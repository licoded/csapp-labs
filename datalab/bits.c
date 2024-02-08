/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // Approach1: reverse each bit of x/y, then & with another!
  //        That's wrong! ~x & y is not enough, need combine with x & ~y
  //        But only using ~ & operators, I can't do the combination
  // return ((~x) & y);


  // Approach2: try reverse direction, try to get ~(x ^ y)
  //      Impl1: ~(x & y) is wrong when a==b, it returns a but we want zero
  //      Impl2: think how to fix Impl1...  What 0/1 means in (x & y)?
  //        x & y:
  //            0 bit: a and b are different
  //                  OR both a and b are 0
  //            1 bit: both a and b are 1
  //
  //        ===================================
  //
  //        ~(x & y):
  //            0 bit: both a and b are 1
  //            1 bit: a and b are different
  //                  OR both a and b are 0
  //        fix solution:
  //            So, we just need to use `both_0` to block the part where `both a and b are 0`
  //                                           i.e. only save the other parts by using 1
  int reverse = x & y;
  int both_0 = (~x) & (~y);
  return ((~reverse) & (~both_0));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int Tmax = ~(1 << 31);
  return !(x ^ Tmax);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
   * My initial thought/approach is just OK/right!
   * But I mistook the definition of odd bit: the number is from 0 instead of 1!
   *
   * I intentionally keep the printfs for Debug.
   */

  // printf("=== 0x%lx", x);
  int odd_sm_base = 0xAA;
  int odd_mid = odd_sm_base + (odd_sm_base << 8);
  int odd_all = odd_mid + (odd_mid << 16);

  int and_res = odd_all & x;
  // printf("\t\t0x%lx", and_res);
  // and_res should equal to odd_all
  // printf("\t\t0x%lx", and_res ^ odd_all);
  int equal_flag = !(and_res ^ odd_all);
  // printf("\n");
  return equal_flag;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*
   * My initial thought/approach is just OK/right!
   * But I don't know how to deal with the boundary value: 0x8000,0000
   * 
   * Finally, I try C compile to tell me the result of -(INT_MAX), which is itself
   *          I wonder why design/dispatch this, just adjust to the trans formula `~x+1`?
   */
  return (~x) + 1;
}
//3
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
  /*
   * My approach: not as before (compare the numbers) 
   *        STEP1: all bits before 0x3[0-9] are 0
   *        STEP2: check the last 2nd bit in hex are 3
   *        STEP3: check the last 1st bit in hex are 0-9, not A-F
   */

  /* STEP1 */
  // int before_mask = ~(0xff); // simplication/reduction of (~1) ^ (0xff);
  // int before_and_res = before_mask & x;
  // int before_check_flag = !(before_and_res ^ before_mask);
  // int before_check_flag = !(x & (~0xff)); // more easier and clean than above

  /*
   * The above approach is not easy, seems stupid, so I choose to change to
   * My approach2: just as before (compare the numbers) 
   *        STEP1: check whether not less than (>=) 0x30
   *        STEP2: check whether not more than (<=) 0x39
   * 
   * Tools needed: 
   *        1. check result is non-positive or non-negative
   *              non-negative (>=) is very easy, just accroding to the highest binary bit
   *        2. trans `>=` logic to `<=`, or reversely
   *              `a <= b` to `b >= a`
   *        3. trans `-` logic to `+`
   *              `a-b >= 0` --> `a+(-b) >= 0`
   */

  int Tmin = 1 << 31; // Tmin

  // x >= 0x30 --> x + (-0x30) >= 0
  int x_sub_0x30 = x + (~0x30 + 1);
  int x_geq_0x30_flag = !(x_sub_0x30 & Tmin);

  // x <= 0x39 --> 0x39 + (-x) >= 0
  int _0x39_sub_x = 0x39 + (~x + 1);
  // whether x
  int x_leq_0x39_flag = !(_0x39_sub_x & Tmin);

  return x_geq_0x30_flag & x_leq_0x39_flag;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* STEP1: change x to `0/1` only */
  // x = !x;    // better than !!x, wrong!!!
  // x = x ^ 0; // better than !!x, wrong!!!
  // x = !!x;

  int z_flag = !x;
  int y_flag = !z_flag;

  /* STEP2: how to choose y or z by `0/1` */
  // My approach: 
  //      0/1   --same op-->    0/Tmax          WRONG!!!
  //      0/1   --same op-->    0/-1            RIGHT!!!
  // int Tmax = ~(1 << 31);
  //      0/1   --Tmax op-->    -1/Tmax
  //            --   +1  -->    0/Tmin
  //      0/1   --  <<31 -->    0/Tmin
  //            -- +(0/1)-->    0/(-Tmax)
  //            --   neg -->    0/Tmax

  // int neg_y_res_part = (y_flag << 31) + y_flag;
  // int y_res_part = (~neg_y_res_part) + 1;
  // int neg_z_res_part = (z_flag << 31) + z_flag;
  // int z_res_part = (~neg_z_res_part) + 1;
  // return y_res_part + z_res_part;
  // has problem, because `-Tmin == Tmin`!!!

  // how to fix `Tmin` case???

  // Oh, My approach is totally right, there is no `Tmin` case
  //      only the impl is wrong
  // int neg_y_mask = (y_flag << 31) + y_flag;
  // int y_mask = (~neg_y_mask) + 1;
  // int y_res_part = y_mask & y;
  // int neg_z_mask = (z_flag << 31) + z_flag;
  // int z_mask = (~neg_z_mask) + 1;
  // int z_res_part = z_mask & z;
  // return y_res_part + z_res_part;

  // Oh, Line310 is wrong!!! Newly added Line311 is right!
  int y_mask = (~y_flag) + 1;
  int y_res_part = y_mask & y;
  int z_mask = (~z_flag) + 1;
  int z_res_part = z_mask & z;
  return y_res_part + z_res_part;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  return 2;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return 2;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
//float
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
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
