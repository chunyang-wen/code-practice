#!bin/env awk

# knuth's shuffle

BEGIN {
    FS="\t";
    OFS="\t";
    LEN = 10;
    arr; # alg
}
{
    for (i = 0; i < LEN; ++i) {
        j = rand() * (LEN - i - 1) + i;
        t = arr[j]
        arr[j] = arr[i];
        arr[j] = t;
    }
}
