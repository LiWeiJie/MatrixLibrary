/*
 * @Author: Weijie Li 
 * @Date: 2017-11-27 18:59:05 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2017-12-13 23:37:32
 */



#include "matrixlib/matrix_gf2.h"
#include "matrixlib/affine_transform.h"

#define CSL32(x,i)					\
	(((x) << i) | ((x) >> (32-i)))

int math_test() {
    printf("--------------Math Utils Test--------------\n");
 
    printf("------------------------------\n");
    printf("MatGf2 import export test:\n");

    MatGf2 tva, tvb;
    int rn = 10;
    int cn = 10;
    
    tva = GenRandomMatGf2(rn, cn);
    void * s_mat;
    s_mat = ExportMatGf2ToStr(tva);
    tvb = ImportMatGf2FromStr(s_mat);
    DumpMatGf2(tva);
    DumpMatGf2(tvb);
    printf("Equal : %d\n", MatGf2Cmp(tva, tvb)==0);

    MatGf2Free(tva);
    MatGf2Free(tvb);
    free(s_mat);

    printf("------------------------------\n");
    printf("AffineTransform import export test:\n");

    AffineTransform ata, atb;
    GenRandomAffineTransform(&ata,  &atb, 32);
    
    s_mat = ExportAffineToStr(&ata);
    atb = ImportAffineFromStr(s_mat);
    DumpMatGf2(ata.linear_map);
    DumpMatGf2(ata.vector_translation);
    DumpMatGf2(atb.linear_map);
    DumpMatGf2(atb.vector_translation);
    printf("Equal : %d\n", MatGf2Cmp(ata.linear_map, atb.linear_map)==0);
    printf("Equal : %d\n", MatGf2Cmp(ata.vector_translation, atb.vector_translation)==0);

    AffineTransformFree(&ata);
    AffineTransformFree(&atb);
    free(s_mat);
    
    printf("------------------------------\n");

    int i;
    MatGf2 X = NULL;
    ReAllocatedMatGf2(2,2, &X);
    MatGf2 A,B;
    A = B = NULL;
    int data[] ={1,4,8,2, 7,5};
    InitMatGf2ByValueArray(data, X);
    DumpMatGf2(X);

    printf("random 4 * 4 matrix and its inv: \n");
    MatGf2 Y = NULL;
    ReAllocatedMatGf2(4, 4, &Y);
    RandomMatGf2(Y);

    while (IsMatGf2Invertible(Y)==0) {
        RandomMatGf2(Y);
    }
    MatGf2 Z = NULL;
    MatGf2Inv(Y, &Z);
    DumpMatGf2(Y);
    DumpMatGf2(Z);
    MatGf2Mul(Y, Z, &X);
    DumpMatGf2(X);

    // int data2[] = {  1, 1, 1, 1, \
    //                 0, 1, 0, 1, \
    //                 0, 1, 1, 0, \
    //                 0, 0, 1, 0};
    // InitMatGf2ByValueArray(Y, data2);
    // Z = MatGf2Inv(Y);
    // X = MatGf2Mul(NULL, Y, Z);
    // DumpMatGf2(Y);
    // DumpMatGf2(Z);
    // DumpMatGf2(X);
    // DumpMatGf2(Y);

    
    
    

    
    // printf("------------------------------\n");
    // printf("random affine augment matrix:\n");
    
    // genRandomAffineAugmentedMatrix(X, Y, 32);
    // // DumpMatGf2(X);
    // // DumpMatGf2(Y);

    // NTL::vec_GF2 vg;
    // random(vg, 33);
    // vg.put(32, 1);

    // dumpVector(vg);
    // printf("%u\n", get32FromVec(vg));

    // NTL::vec_GF2 vr;
    // vr = X*vg;
    // dumpVector(vr);
    // printf("%u\n", get32FromVec(vr)); 
    
    // vr = Y*vr;
    // dumpVector(vr);
    // printf("%u\n", get32FromVec(vr));      
    
    // printf("------------------------------\n");
    // printf("random 2 affine augmented matrix xor before and after:\n");

    // NTL::vec_GF2 v_a, vb, vc, v_result;
    // random(v_a, 33);
    // random(vb, 33);
    // printf("vector a: %u\n", get32FromVec(v_a));
    // printf("vector b: %u\n", get32FromVec(vb));
    
    // printf("before affine:\n");
    // v_result = v_a + vb;
    // dumpVector(v_result);

    // printf("after affine and deaffine:\n");
    // v_result = X*v_a + X*vb;
    // v_result = Y*v_result;
    // dumpVector(v_result);

    // printf("single xor between u32:\n");
    // getVecFrom32(v_result, get32FromVec(v_a)^get32FromVec(vb));
    // dumpVector(v_result);

    printf("------------------------------\n");
    printf("random affine matrix:\n");
    
    AffineTransform at, at_inv;
    MatGf2 v_a, v_b, v_c, v_result, v_show;
    v_a = v_b = v_c = v_result = v_show = NULL;

    GenRandomAffineTransform(&at, &at_inv, 32);

    ReAllocatedRandomMatGf2(32, 1, &v_a);

    MatGf2Transpose(v_a, &v_show);
    DumpMatGf2(v_show);
    printf("%u\n\n", get32FromVec(v_a));

    MatGf2Mul(at.linear_map, v_a, &v_b);
    MatGf2Add(at.vector_translation, v_b, &v_b);
    // v_b = X*vg+V;
    MatGf2Transpose(v_b, &v_show);
    DumpMatGf2(v_show);
    printf("%u\n\n", get32FromVec(v_b)); 
    
    MatGf2Mul(at_inv.linear_map, v_b, &v_a);
    MatGf2Add(at_inv.vector_translation, v_a, &v_a);
    // vr = Y*(vr+V);
    MatGf2Transpose(v_a, &v_show);
    DumpMatGf2(v_show);
    printf("%u\n\n", get32FromVec(v_a));   

    printf("------------------------------\n");
    printf("random 3 affine matrix xor before and after:\n");

    ReAllocatedRandomMatGf2(32, 1, &v_a);
    ReAllocatedRandomMatGf2(32, 1, &v_b);
    ReAllocatedRandomMatGf2(32, 1, &v_c);
    MatGf2Add(MatGf2Add(v_a, v_b, &v_result), v_c, &v_result);
    printf("before affine:\n");
    printf("vector a: %u\n", get32FromVec(v_a));
    printf("vector b: %u\n", get32FromVec(v_b));
    printf("vector c: %u\n", get32FromVec(v_c));
    printf("vector xor: %u\n", get32FromVec(v_result));
    printf("\n");
    
    printf("after affine:\n");
    ApplyAffineTransform(at, v_a, &v_a);
    ApplyAffineTransform(at, v_b, &v_b);
    ApplyAffineTransform(at, v_c, &v_c);
    printf("vector a: %u\n", get32FromVec(v_a));
    printf("vector b: %u\n", get32FromVec(v_b));
    printf("vector c: %u\n", get32FromVec(v_c));
    // dumpVector(v_result);
    printf("\n");

    printf("after deaffine:\n");
    MatGf2Add(MatGf2Add(v_a, v_b, &v_result), v_c, &v_result);
    ApplyAffineTransform(at_inv, v_result, &v_result);
    printf("vector xor: %u\n", get32FromVec(v_result));

    printf("------------------------------\n");
    printf("random matrix diag test:\n");

    ReAllocatedMatGf2(2,2, &X);
    RandomMatGf2(X);
    ReAllocatedMatGf2(3,3, &Y);
    RandomMatGf2(Y);
    MatGf2Diag(X, Y, &Z);

    printf("matrix A:\n");
    DumpMatGf2(X);
    printf("matrix B:\n");
    DumpMatGf2(Y);
    printf("matrix After combined:\n");
    DumpMatGf2(Z);

    printf("------------------------------\n");
    printf("CSL matrix test:\n");

    printf("x + (x<<<2) + (x<<<10) + (x<<<18) + (x<<<24) : \n");

    ReAllocatedRandomMatGf2(32, 1, &v_a);
    long r = get32FromVec(v_a);
    
    // unsigned long r = 0xE4466CC3;
    // v_a = InitMatGf2(1, 32);
    // InitMatrixFromBitArray(&r, v_a);
    // v_a = MatGf2Transpose(v_a);

    unsigned long csl_r = (r) ^  CSL32((r),  2) ^				\
                        CSL32((r), 10) ^				\
                        CSL32((r), 18) ^				\
                        CSL32((r), 24);
    printf("random int:\t%lX\n", r);
    MatGf2Transpose(v_a, &v_show);
    DumpMatGf2(v_show);
    printf("after CSL:\t%X\n", (unsigned int)csl_r);

    ReAllocatedMatGf2(1,32, &X);
    InitMatrixFromBitArray(&csl_r, X);
    DumpMatGf2(X);
    printf("\n");
    unsigned long csl_m =    (1<<31) ^ \
                    (1<<29) ^ \
                    (1<<21) ^ \
                    (1<<13) ^ \
                    (1<<7);
    unsigned long csl_ms[32];
    csl_ms[0] = csl_m;
    for (i=1; i<32; i++) {
        long t = csl_ms[i-1];
        csl_ms[i] = (((t>> 1) & 0x7fffffff) | (t << (31)));
    } 
                    
    ReAllocatedMatGf2(32,32, &X);
    InitMatrixFromBitArray(csl_ms, X);

    MatGf2Mul(X, v_a, &v_a);
    r = get32FromVec(v_a);
    printf("random int after CSL matrix:\t%lX\n", r);
    MatGf2Transpose(v_a, &v_show);
    DumpMatGf2(v_show);
    
    // printf("CSL matrix:\n");
    // DumpMatGf2(X);

    printf("------------------------------\n");
    printf("Diag matrix xor test:\n");
    printf("random 3 affine diag matrix xor before and after:\n");

    ReAllocatedRandomMatGf2(32, 1, &v_a);
    ReAllocatedRandomMatGf2(32, 1, &v_b);
    ReAllocatedRandomMatGf2(32, 1, &v_c);
    MatGf2Add( MatGf2Add(v_a, v_b, &v_result), v_c, &v_result);
    printf("before affine:\n");
    printf("vector a: %u\n", get32FromVec(v_a));
    printf("vector b: %u\n", get32FromVec(v_b));
    printf("vector c: %u\n", get32FromVec(v_c));
    printf("vector xor: %u\n", get32FromVec(v_result));
    printf("\n");
    
    MatGf2 Xi[4];
    for (i=0; i<4; i++) {
        Xi[i] = GenInvertibleMatGf2(8, 8);
    }
    MatGf2 s, t; 
    s = t = NULL;
    MatGf2Diag(Xi[0], Xi[1], &s);
    MatGf2Diag(s, Xi[2], &t);
    MatGf2Diag(t, Xi[3], &X);
    // DumpMatGf2(X);
    printf("after affine:\n");
    long a,b,c;
    a = get32FromVec(v_a);
    b = get32FromVec(v_b);
    c = get32FromVec(v_c);
    MatGf2 vt = NULL;
    unsigned long te;
    ReAllocatedMatGf2(8,1, &vt);

    te = (a>>24 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Mul(Xi[0], vt, &v_a);
    te = (a>>16 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_a, MatGf2Mul(Xi[1], vt, &v_show), &v_a); 
    te = (a>> 8 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_a, MatGf2Mul(Xi[2], vt, &v_show), &v_a); 
    te = (a     & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_a, MatGf2Mul(Xi[3], vt, &v_show), &v_a); 

    te = (b>>24 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Mul(Xi[0], vt, &v_b);
    te = (b>>16 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_b, MatGf2Mul(Xi[1], vt, &v_show), &v_b); 
    te = (b>> 8 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_b, MatGf2Mul(Xi[2], vt, &v_show), &v_b); 
    te = (b     & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_b, MatGf2Mul(Xi[3], vt, &v_show), &v_b); 

    te = (c>>24 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Mul(Xi[0], vt, &v_c);
    te = (c>>16 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_c, MatGf2Mul(Xi[1], vt, &v_show), &v_c); 
    te = (c>> 8 & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_c, MatGf2Mul(Xi[2], vt, &v_show), &v_c); 
    te = (c     & 0xff);
    InitVecFromBit(te, vt);
    MatGf2Stack(v_c, MatGf2Mul(Xi[3], vt, &v_show), &v_c); 


    
    printf("vector a: %u\n", get32FromVec(v_a));
    printf("vector b: %u\n", get32FromVec(v_b));
    printf("vector c: %u\n", get32FromVec(v_c));
    // dumpVector(v_result);
    printf("\n");

    printf("after deaffine:\n");
    MatGf2Add( MatGf2Add( v_a, v_b, &v_result), v_c, &v_result);
    MatGf2Inv(X, &v_show);
    MatGf2Mul(v_show , (v_result), &v_result);
    printf("vector xor: %u\n", get32FromVec(v_result));


    



    return 0;
}

