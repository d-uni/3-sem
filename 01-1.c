    STYPE bit_reverse(STYPE value)
    {
        UTYPE value2 = 0;
        UTYPE value_unsigned = value;
        STYPE i = sizeof(STYPE)*8;
        while(i-1){
            value2 = value2 | (value_unsigned & 0x00000001);
            value_unsigned = value_unsigned >> 1;
            value2 = value2 << 1;
            i--;
        }
        value2 = value2 | (value_unsigned & 0x00000001);
        value = value2;
        return value;
    }
