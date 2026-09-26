/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);              //x&y 的反面是至少一个0, ~x|~y
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);      //x^y = (x|y) & ~(x&y)
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!(x && y))
        return !x && !y;
    x = x >> 31;
    y = y >> 31;
    if(x ^ y)
        return 0;
    else
        return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;       //r = 到目前一共找到了多少位
    int s;              //本次要位移多少位

    s = (v > 0xFFFF) << 4;   //判断在高16位还是低16位
    //若在高16位，则左移16位，及2^4
    v = v >> s;      //继续判断位于16位里的哪一部分，除以2^4
    r = r | s;         //又由于s是2^4,2^3,2^2,2^1, 2^0,所以|可以当作+用

    s = (v > 0xFF) << 3;
    v = v >> s;
    r = r | s;

    s = (v > 0xF) << 2;
    v = v >> s;
    r = r | s;

    s = (v > 0x3) << 1;
    v = v >> s;
    r = r | s;

    r = r | (v > 1);

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns = n << 3;           //1个字节取8位
    int ms = m << 3;
    int a = (x >> ns) & 0xFF;   //用0xFF取最低8位
    int b = (x >> ms) & 0xFF;
    int c = a ^ b;    //a ^ (a ^ b) = b；b ^ (a ^ b) = a
    x = x^(c << ns);
    x = x^(c << ms);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned ans = 0;
    int i = 32;
    while(i){
        ans = ans<<1 | (v & 1);
        v = v>> 1;
        i -= 1;
    }
    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1<<31)>>n)<<1);
    return (x>>n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */

int leftBitCount(int x) {
    int count = 0;
    int s;

    s = (!~(x >> 16)) << 4;
    count = count + s;
    x = x << s;

    s = (!~(x >> 24)) << 3;
    count = count + s;
    x = x << s;

    s = (!~(x >> 28)) << 2;
    count = count + s;
    x = x << s;

    s = (!~(x >> 30)) << 1;
    count = count + s;
    x = x << s;

    s = !~(x >> 31);
    count = count + s;
    x = x << s;

    count = count + ((x >> 31) & 1);

    return count;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
    //单精度浮点数，包含符号、指数、小数。分别占1,8,23位
    //需要舍去，如果太大的话，超过23位表示。四舍五入
    //难炸了
unsigned float_i2f(int x) {
    unsigned sign;
    unsigned ux;
    unsigned norm;
    unsigned main;
    unsigned tail;
    int e = 31;

    if (x == 0)
        return 0;

    // 符号位 
    sign = x & 0x80000000u;

    //取绝对值，用 unsigned 避免 INT_MIN 溢出 
    ux = x;
    if (sign)
        ux = ~ux + 1;

    // 找最高的 1 在第几位 
    while (!(ux >> e))
        e = e - 1;

    norm = ux << (31 - e);

    main = norm >> 8;
    tail = norm & 0xFF;

    if (tail > 0x80) {
        main = main + 1;
    } else if (tail == 0x80) {
        if (main & 1)
            main = main + 1;
    }
    return sign | (((e + 126) << 23) + main);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000u;  //u unsigned int  取出符号
    unsigned exp = uf & 0x7F800000u;   //找出指数部分

    if (exp == 0x7F800000u)    //处理NaN和无穷
        return uf;

    if (exp == 0)  //uf为0或者太小了  不能单纯exp + 1
        return sign | ((uf & 0x7FFFFFFFu) << 1);   //直接位移

    if (exp == 0x7F000000u)    //会溢出
        return sign | 0x7F800000u;   //所以直接返回

    return uf + (1 << 23);   //正常浮点数exp+1
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */

 //double 的64位结构 1 ： 11 ： 52
 //  uf2 - The higher 32 
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign;
    unsigned exp;
    unsigned high;
    unsigned value;
    int E;
    int result;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7FF;  //取出11位的exp

    if (!((exp > 0x7FF) | (exp < 0x7FF)))    //overflow
        return 0x80000000u;

    E = exp;
    E = E - 1023;  //算32位下的exp

    if (E < 0)     //太小了，向0取整
        return 0;

    if (E >= 31)   //overflow
        return 0x80000000u;

    high = (uf2 & 0xFFFFF) | (1 << 20);   //隐藏的1 + fraction前20位。

    if (E <= 20)
        value = high >> (20 - E);  //整数部分完全在high里
    else
        value = (high << (E - 20)) | (uf1 >> (52 - E));

    result = value; 
    //整数部分为E+1， high有21位

    if (sign)
        return -result;
    else
        return result;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)    //单精度 float 能表示的最小正非零值
        return 0;

    if (x < -126)   //denormal 的 exponent 字段固定是：00000000
        return 1 << (x + 149);

    if (x <= 127)
        return (x + 127) << 23;

    return 0x7F800000u;
}