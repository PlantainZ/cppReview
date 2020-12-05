
///【1.递归快速幂计算】
/*给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
保证base和exponent不同时为0*/
public class Solution {
    //主计算函数。
    public static double Power(double base, int exp) {
        boolean flag = exp < 0;
        if (flag) { exp = -exp;}//exp保证为正
        double result = getPower(base, exp);
        return flag ? 1 / result : result;
    }


    public static double getPower(double base, int exp) {
        if (exp == 0) { return 1;}
        if (exp == 1) { return base;}//异常返回情况

        double ans = getPower(base, exp >> 1);
        //exp递归式右移，每次右移exp都/2
        ans *= ans;
        //想象，如果迭代到最后是2(10)，那ans一开始就是2，2*2 = 2^2，
        //然后返回4，再4*4 = 2^2 * 2^2，也就是每次exp-2都是合理的！
        if ((exp & 1) == 1) { ans *= base;}
        // 2^10 -> 2^5 -> 2^2 -> 2^1 -> 2^0 右移顺序
        //32*32<-4*4*2 <- 2*2 <- 1*2 <- 1
        return ans;
    }
}
