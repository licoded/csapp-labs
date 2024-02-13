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
  // int Tmax = ~(1 << 31);
  // Oh, no! The shift operator `<<` is not allowed!!!

  // how can I get Tmax not using `<<`???
  // int Tmax = ~0;
  // seems impossible, is there another way to check isTmax without calc/get Tmax?
  //                                i.e. use property of Tmax to check isTmax
  //      Tmax = 0x7fff,ffff
  //      Tmax & x == x, if x is non-negative
  //               == x+(1<<31) == x+(-Tmin), if x is negative
  //
  //      what about the property of r_Tmax = reverse_Tmax == ~(Tmax)?
  //      r_Tmax = 0x1000,0000
  //      r_Tmax ^ x == x-(1<<31) ==    x+Tmin, if x is non-negative
  //                 == x+(1<<31) == x+(-Tmin), if x is negative
  //
  //      Only Tmax+1 = Tmin is a huge change!!! Can I leverage this to check isTmax?
  //      -x = ~x + 1, x-x = x+(-x) = x+ ~x + 1
  //
  //      (x+1)+(-(x+1)) == 0
  //      (Tmax+1)+(-(Tmax+1)) = Tmin + (-Tmin) = Tmin + Tmin
  //
  //      So, I find that only Tmax SAT formula x+1 == -(x+1)

  int x_plus_1 = x + 1;
  int neg__x_plus_1 = (~x_plus_1) + 1;
  int equal_flag = !(x_plus_1 ^ neg__x_plus_1);
  // return equal_flag;

  // Oh, no! From wrong test case -1, I find -1 also SAT the above formula
  // So, I must fix it using following codes
  int neg_one = ~0;
  int is__neg_one = !(x ^ neg_one);

  // I need equal_flag=true, is__neg_one=false
  return equal_flag & (equal_flag ^ is__neg_one);
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
  int Tmin = 1 << 31;
  // int is_Tmin = !(Tmin ^ x);
  int x_is_Tmin = !(Tmin ^ x);
  // int y_is_Tmin = !(Tmin ^ y);

  // approach: negation (<0) is easy to judge, same is non-negation (>=0)
  //            lessOrEqual -- <=
  //            x <= y   <==>    y >= x   <==>   y+(-x) >= 0 
  int neg_x = (~x) + 1;     // CRUCIAL: this neg op has error for Tmin
  int y_minus_x = y + neg_x;
  int y_geq_x_flag = !(y_minus_x & Tmin);  
  
  // return (!is_Tmin) & y_geq_x_flag;

  // fix1 thought: when x is Tmin, x <= y is true, 
  //               so I don't need to deal with the error of neg op
  // return y_geq_x_flag;

  // fix2 solution code:
  // case1: x is Tmin
  int case1_flag = x_is_Tmin;
  // case2: x is not Tmin
  int case2_flag = (!x_is_Tmin) & y_geq_x_flag;
  // return case1_flag | case2_flag;
  // === But the problem is that, y_minus_x may overflow when the sign of x and y are different!!!

  // fix3 solution: fix2 + pre-sign judge
  // int sign_of_x = x >> 31;
  // int sign_of_y = y >> 31;
  // int sign_of_x = (x & Tmin) >> 31;
  // int sign_of_y = (y & Tmin) >> 31;
  // the above two versions are both wrong, because signed shift ops are with sign
  // the below version is OK, but not elegant
  // int sign_of_x = !!(x & Tmin);
  // int sign_of_y = !!(y & Tmin);

  // int sign_differ_flag = sign_of_x ^ sign_of_y;
  // int x_is_neg_flag = sign_of_x;
  // int case0_flag = sign_differ_flag & x_is_neg_flag;

  // the below version is OK and elegant
  int x_is_non_neg = !(x & Tmin);
  int y_is_non_neg = !(y & Tmin);
  int sign_differ_flag = x_is_non_neg ^ y_is_non_neg;
  int x_is_neg_flag = !x_is_non_neg;
  // int case0_flag = sign_differ_flag & x_is_neg_flag;

  // printf("%d", sign_of_x);
  // printf(" ");
  // printf("%d", sign_of_y);
  // printf(" ");
  // printf("%d", case0_flag);
  // printf(" ");
  // printf("%d", sign_differ_flag);
  // printf("\n");

  int check_flag_when_sign_differ = (sign_differ_flag) & x_is_neg_flag;
  int check_flag_when_sign_equal = (!sign_differ_flag) & (case1_flag | case2_flag);
  return check_flag_when_sign_differ | check_flag_when_sign_equal;
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
  // logicalNeg   <==>    isZero

  // approach: >=0 and <=0
  int Tmin = 1 << 31;
  // int x_is_non_neg = !(x & Tmin);   // x >= 0
  // int neg_x = ~x + 1;
  // int neg_x_is_non_neg = !(neg_x & Tmin); //  neg_x >= 0
  // return x_is_non_neg & neg_x_is_non_neg;
  // using illegal ops `!`

  // int x_is_neg = x & Tmin;   // x < 0
  // int neg_x = ~x + 1;
  // int neg_x_is_neg = neg_x & Tmin; //  neg_x < 0
  // return x_is_neg & neg_x_is_neg;

  // thought: I can use ^ to check equal, but the result is zero instead of one
  //                                          how can I turn zero into one? use XOR(^)!!!
  
  // thought: get return_res without !
  // x_is_non_neg & neg_x_is_non_neg == Tmin

  // thought: neg_x == x && x != Tmin
  // thought: neg_x == x && sign_of_x

  // thought: isTmin  <==>  
  //          Tmin/0  -- same ops --> 0/1 OR 1/0???

  // thought: Tmin -- some ops --> 0 OR 1???
  //          TMin ^ (Tmin + 1) = -1
  //            0  ^ (Tmin + 1) = Tmin+1
  //            0  ^ (  0  + 1) = 1

  //          Tmin +/^ (0x0fffffff) = 0xffffffff
  //            0  +/^ (0x0fffffff) = 0x0fffffff

  //          0x00000001 - 1 = 0x00000000
  //          0x00000000 - 1 = 0xffffffff

  // OH!!!
  //          Tmin >> 31 = 0xffffffff +1  = 0
  //            0  >> 31 = 0x00000000 +1  = 1

  int x_and_Tmin = (x & Tmin);   // x >= 0
  int x_is_non_neg = (x_and_Tmin >> 31) + 1;
  // int x_is_non_neg = 1 ^ x_is_neg;   // this line is because I mistake the non_neg and neg at first
  int neg_x = ~x + 1;
  int neg_x_and_Tmin = (neg_x & Tmin); //  neg_x >= 0
  int neg_x_is_non_neg = (neg_x_and_Tmin >> 31) + 1;
  // int neg_x_is_non_neg = 1 ^ neg_x_is_neg;
  return x_is_non_neg & neg_x_is_non_neg;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 12 0000 1100
    1111 0011
-12 1111 0100
       1 0100

    0000 0000 0000 0000
    (-1)*2^7



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
  int Tmin = 1 << 31;
  int neg_1 = ~1 + 1;
  int pow_2_16 = 1 << 16;
  int neg_pow_2_16 = ~pow_2_16 + 1;  // positive - positive, will never overflow
  int xor_mask;
  int and_mask;
  int shift_bits;
  int x_is_non_neg_flag;
  int x_minus_neg_pow_2_16;
  int x_geq_pow_2_16_flag;
  // int temp_x;
  int res;

  // negative numbers: (the first zero idx from the right) + 1  // It's wrong!!!
  //                    except -1, which has no zero

  // negative numbers: (the first one idx from the left)  // That must be wrong!!!

  // negative numbers: (the first zero idx from the left) + 1   // idx is numbered from 1 instead of 0, and from the right hand
  //                    when it comes to -1, the result is 0+1=1
  // positive numbers: (the last one idx from the right) + 1, also apply to 0!!!!
  //                    when it comes to  0, the result is 0+1=1

  // Then, how to calc the first idx???
  // my thought: use the property of x and neg_x!
  //      5: 0000,0101
  //     -5: 1111,1011
  // 5&(-5): 0x0000,0001  --  It's the first one idx from the right of 5

  // If we can reverse the bits of 5, then we can get the first one idx from the left
  //    uh, I can reverse by every 4/8/16 bits, but not elegant
  //      5: 0000,0101
  //    r_5: 1010,0000

  // for positive nums, we can do following to find the last one idx from the right
  //          iteratively >>, and from zero to plus !cur_val
  //          i.e. while(x) {sum++, x >>= 1}
  // int x_is_non_neg = !(x & Tmin);
  // int res_when_non_neg;

  // int temp_x = x;
  // int equal_zero_counts_when_right_shift = 0;
  // x = x >> 1; equal_zero_counts_when_right_shift = equal_zero_counts_when_right_shift + (!x);
  // I realize that the ops numbers this approach needed are way larger than required!!!!

  // for negative nums,
  //          iteratively <<, count when it become Tmin
  //          i.e. while(x!=Tmin) {sum++, x <<= 1}
  // OR
  //          iteratively >>, count when it become -1
  //          i.e. while(x!=-1) {sum++, x >>= 1}
  // int x_is_neg = !x_is_non_neg;
  // int res_when_neg;

  /* The following codes is OK by tests, but using invalid ops */
  // temp_x = x;
  // int equal_zero_counts = 0;
  // int equal_neg_one_counts = 0;
  // for(int i = 0; i < 32; i++) {
  //   equal_zero_counts += (temp_x == 0);
  //   equal_neg_one_counts += (temp_x == -1);
  //   temp_x >>= 1;
  // }
  // res_when_non_neg = (32-equal_zero_counts)+1;
  // res_when_neg = (32-equal_neg_one_counts)+1;
  // return x_is_non_neg ? res_when_non_neg : res_when_neg;

  // thought: pre-calc function/map for all 4 bits num
  //    f(00) = 00, g(00) = 00;
  //    f(01) = 00, g(01) = 00;
  //    arg_f(0) = 0000
  //    arg_f(1) = 0001
  //    arg_f(2) = 0010,0011
  //    arg_f(3) = 0100,0101,0110,0111
  //    arg_f(4) = 1000,...
  //  Sum up: f(XXX) = XXX>=1 + XXX>=2 + XXX>=4 + XXX>=8
  //  f,g

  // check whether can unify negative and non-negative
  // the experiment result turns out it's OK!!!
  /* The following codes is OK by tests, but using invalid ops */
  // temp_x = x;
  // if (x < 0)
  //   temp_x = ~x;
  // x_is_non_neg = !(temp_x & Tmin);
  // int equal_zero_counts = 0;
  // for(int i = 0; i < 32; i++) {
  //   equal_zero_counts += !temp_x;
  //   temp_x >>= 1;
  // }
  // res_when_non_neg = (32-equal_zero_counts)+1;
  // return res_when_non_neg;

  // temp_x = x;
  // if (x < 0)
  //   temp_x = ~x;
  // x_is_non_neg = !(temp_x & Tmin);
  // res_when_non_neg = 1;
  // for(int i = 0; i < 32; i++) {
  //   res_when_non_neg += !!temp_x;
  //   temp_x >>= 1;
  // }
  // return res_when_non_neg;

  // 16bit case
  // > 2^16 >>
  // 16 * 5
  // 3 * 32
  // if (x < 0)
  //   x = ~x;
  // int x_minus_neg_pow_2_16 = x + neg_pow_2_16;
  // int x_geq_pow_2_16_flag = !(x_minus_neg_pow_2_16 & Tmin);
  // int res = 1;
  // res += (x_geq_pow_2_16_flag ? 16 : 0);
  // x = (x_geq_pow_2_16_flag ? x >> 16 : x);
  // x_is_non_neg = !(x & Tmin);
  // for(int i = 0; i < 16; i++) {
  //   res += !!x;
  //   x >>= 1;
  // }
  // return res;

  // if (x < 0)
  //   x = ~x;
  // int x_minus_neg_pow_2_16 = x + neg_pow_2_16;
  // int x_geq_pow_2_16_flag = !(x_minus_neg_pow_2_16 & Tmin);
  // int res = 1;
  // res += (x_geq_pow_2_16_flag ? 16 : 0);
  // x = (x_geq_pow_2_16_flag ? x >> 16 : x);
  // x_is_non_neg = !(x & Tmin);
  // for(int i = 0; i < 16; i++) {
  //   res += !!x;
  //   x >>= 1;
  // }
  // return res;

  /* STEP1: convert neg to equivalent non-neg */
  x_is_non_neg_flag = !(x & Tmin);
  //  0/1   -- same ops -->   -1/0    (Just minus 1 is OK!!!)
  xor_mask = x_is_non_neg_flag + neg_1;
  x = x ^ xor_mask;
  // Tmin/0 -- same ops -->   -1/0    Is there a solution that uses fewer ops than above

  res = 1;
  /* STEP2: convert 32-bits problem to 16-bits problem */
  x_minus_neg_pow_2_16 = x + neg_pow_2_16;
  x_geq_pow_2_16_flag = !(x_minus_neg_pow_2_16 & Tmin);
  and_mask = (!x_geq_pow_2_16_flag) + neg_1;
  shift_bits = 16 & and_mask;
  res = res + shift_bits;
  x = x >> shift_bits;

  /* solve 16-bits problem */
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;
  res = res + !!x;  x = x >> 1;

  return res;
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
