    int satsum(int v1, int v2) {
    int int_max = 0;
    int int_min = 0;
    int const1 = ~0;
    unsigned int x = const1;
    int one = const1 * const1;
    x = x << one;
    x = x >> one;
    int_max = x;
    int_min = int_max * const1 + const1;
    int res = 0;
    if (v1 > 0 && v2 > 0 && (int_max - v2 <v1)) {
    res = int_max;
    } else if (v1 < 0 && v2 <0 && (int_min - v2 > v1)) {
    res = int_min;
    } else {
    res = v1 + v2;
    }
    return res;
    }
