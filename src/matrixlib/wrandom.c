/*
 * @Author: Weijie Li 
 * @Date: 2018-11-12 19:16:04 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2018-11-12 20:49:44
 */

#include <matrixlib/wrandom.h>

#ifdef CUSTOM_RANDOM_FUNC

uint32_t wRand31() {
// please set the <Custom random function> in here

}

#else

#include<time.h> 
#include <stdlib.h>

static int inited = 0;

uint32_t wRand31() {
    if (inited==0) {
        inited = 1;
        srand(time(0)); 
    }
    return rand();
}

#endif

uint32_t wRand32() {
    uint32_t res = wRand31() ^ (wRand31() << 1);
    return res;
}

uint64_t wRand64() {
    uint64_t a,b,c;
    a = wRand31();
    b = wRand31();
    c = wRand31();
    uint64_t res= a ^ (b<<21) ^ (c<<42) ;
    return res;
}

// // Rand a list of Number
// static int random_rand(unsigned char *output, size_t size);

// // Rand a list of int32
// static int random_rand_int_array(int *output, int count);

// Rand a list of int32 (if ctx==NULL, then init a global ctx)
int randomList(int *list, int len){
    if (list == NULL)
        return -1;
    while(len--) {
        *list = wRand31();
    }
    return 0;
}

int randomShuffleU8(uint8_t *list, int len) {
    int t, roundCnt, ret;
    unsigned int *randNumbers;
    randNumbers = (unsigned int *)malloc((len + 10) * sizeof(unsigned int));
    randomList((int*) randNumbers, len);
    while (len > 0) {
        int r = randNumbers[len] % len;
        len--;
        uint8_t tmp = *(list + len);
        *(list + len) = *(list + r);
        *(list + r) = tmp;
    }
    free(randNumbers);
    return 0;
}




