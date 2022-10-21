#include <string.h>
int
parse_rwx_permissions(const char *str)
{
    int output = 0;
    char s[9] = {"rwxrwxrwx"};
    if (str == NULL || strlen(str) != 9) {
        return -1;
    }
    for (int i = 0; i < 9; ++i) {
        if (str[i] == '-' || str[i] == 'r' || str[i] == 'w' || str[i] == 'x') {
            if (s[i] == str[i]) {
                output ++;
                output <<= 1;
            } else if (str[i] == '-') {
                output <<= 1;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
    output >>= 1;
    return output;
};