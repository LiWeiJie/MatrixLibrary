/*
 * @Author: Weijie Li 
 * @Date: 2017-11-27 16:44:54 
 * @Last Modified by: Weijie Li
 * @Last Modified time: 2018-07-30 21:41:31
 */

#include "matrixlib/affine_transform.h"


int GenRandomAffineTransform(AffineTransform *at, AffineTransform *at_inv, int dim) {
    at->linear_map = GenMatGf2(dim, dim);
    at->vector_translation = GenMatGf2(dim, 1);

    at_inv->linear_map = GenMatGf2(dim, dim);
    at_inv->vector_translation = GenMatGf2(dim, 1);

    RandomMatGf2(at->linear_map);
    while (IsMatGf2Invertible(at->linear_map)==0) {
        RandomMatGf2(at->linear_map);
    }    
    RandomMatGf2(at->vector_translation);

    MatGf2Inv(at->linear_map, &(at_inv->linear_map));
    MatGf2Mul(at_inv->linear_map, at->vector_translation, &(at_inv->vector_translation));

    return 0;
}

int GenIndAffineTransform(AffineTransform *at, AffineTransform *at_inv, int dim) {
    at->linear_map = GenIndMatrix(dim);
    at->vector_translation = GenMatGf2(dim, 1);

    at_inv->linear_map = GenIndMatrix(dim);
    at_inv->vector_translation = GenMatGf2(dim, 1);
    return 0;
}

// left mul mat * at.linear_map
int ApplyAffineTransformRight(const MatGf2 mat, const AffineTransform at, MatGf2* dst) {
    // MatGf2 to_be_free = *dst;
    MatGf2Mul(mat, at.linear_map, dst);
    MatGf2Add(at.vector_translation, *dst, dst);
    // MatGf2Free(to_be_free);
    return 0;
}

// left mul at.linear_map * mat
int ApplyAffineTransform(const AffineTransform at, const MatGf2 mat, MatGf2* dst) {
    // MatGf2 to_be_free = *dst;
    MatGf2Mul(at.linear_map, mat, dst);
    MatGf2Add(at.vector_translation, *dst, dst);
    // MatGf2Free(to_be_free);
    return 0;
}

//  affine.linear * u16 + affine.vector
uint32_t ApplyAffineToU32(const AffineTransform aff, uint32_t data) {
    MatGf2 mat_x = NULL;
    ReAllocatedMatGf2(32, 1, &mat_x);
    InitVecFromBit(data, mat_x);
    MatGf2Add( MatGf2Mul(aff.linear_map, mat_x, &mat_x), aff.vector_translation, &mat_x);
    uint32_t result = get32FromVec(mat_x);
    MatGf2Free(mat_x);
    mat_x = NULL;
    return result;
}

uint16_t ApplyAffineToU16(const AffineTransform aff, uint16_t data) {
    MatGf2 mat_x = NULL;
    ReAllocatedMatGf2(16, 1, &mat_x);
    InitVecFromBit(data, mat_x);
    MatGf2Add( MatGf2Mul(aff.linear_map, mat_x, &mat_x), aff.vector_translation, &mat_x);
    uint16_t result =  (uint16_t)getDigitalFromVec(mat_x);
    MatGf2Free(mat_x);
    mat_x = NULL;
    return result;
}

//  affine.linear * u8 + affine.vector
uint8_t ApplyAffineToU8(const AffineTransform aff, uint8_t data) {
    MatGf2 mat_x = NULL;
    ReAllocatedMatGf2(8, 1, &mat_x);
	InitVecFromBit(data, mat_x);
    MatGf2Add( MatGf2Mul(aff.linear_map, mat_x, &mat_x), aff.vector_translation, &mat_x);
    uint8_t result = (uint8_t)getDigitalFromVec(mat_x);
    MatGf2Free(mat_x);
    mat_x = NULL;
    return result;
}

// u32 * affine.linear + affine.vector
uint32_t U32MulAffine(uint32_t data, const AffineTransform aff) {
    MatGf2 mat_x = NULL;
    ReAllocatedMatGf2(32, 1, &mat_x);
    InitVecFromBit(data, mat_x);

    MatGf2 mat_y = NULL;
    MatGf2Transpose(aff.linear_map, &mat_y);

    MatGf2Add( MatGf2Mul(mat_y, mat_x, &mat_x), aff.vector_translation, &mat_x);
    uint32_t result = get32FromVec(mat_x);
    MatGf2Free(mat_x);
    mat_x = NULL;
    MatGf2Free(mat_y);
    mat_y = NULL;
    return result;
}

uint16_t U16MulAffine(uint16_t data, const AffineTransform aff) {
    MatGf2 mat_x = NULL;
    ReAllocatedMatGf2(16, 1, &mat_x);
    InitVecFromBit(data, mat_x);
    
    MatGf2 mat_y = NULL;
    MatGf2Transpose(aff.linear_map, &mat_y);
    
    MatGf2Add( MatGf2Mul(mat_y, mat_x, &mat_x), aff.vector_translation, &mat_x);
    uint16_t result =  (uint16_t)getDigitalFromVec(mat_x);
    MatGf2Free(mat_x);
    mat_x = NULL;
    MatGf2Free(mat_y);
    mat_y = NULL;
    return result;
}

// u8 * affine.linear + affine.vector
uint8_t U8MulAffine(uint8_t data, const AffineTransform aff) {
    MatGf2 mat_x = NULL;
    ReAllocatedMatGf2(8, 1, &mat_x);
	InitVecFromBit(data, mat_x);

    MatGf2 mat_y = NULL;
    MatGf2Transpose(aff.linear_map, &mat_y);
    
    MatGf2Add( MatGf2Mul(mat_y, mat_x, &mat_x), aff.vector_translation, &mat_x);
    uint8_t result = (uint8_t)getDigitalFromVec(mat_x);
    MatGf2Free(mat_x);
    mat_x = NULL;
    MatGf2Free(mat_y);
    mat_y = NULL;
    return result;
}

int AffineTransformRelease(AffineTransform *aff) {
    MatGf2Free(aff->linear_map);
    aff->linear_map = NULL;
    MatGf2Free(aff->vector_translation);
    aff->vector_translation = NULL;
    return 0;
}

int AffineTransformFree(AffineTransform *aff) {
    return AffineTransformRelease(aff);
}

uint8_t * ExportAffineToStr(const AffineTransform* aff) {
    uint8_t *a = ExportMatGf2ToStr(aff->linear_map);
    uint8_t *b = ExportMatGf2ToStr(aff->vector_translation);
    uint32_t * sz = (uint32_t *)a;
    int sza = *sz;
    sz ++;
    sza = sza * (*sz);

    sz = (uint32_t *)b;
    int szb = *sz;
    sz ++;
    szb = szb * (*sz);

    uint8_t * result = malloc(5*sizeof(uint32_t) + sza + szb);
    uint32_t * u32ptr = (uint32_t*)result;
    *u32ptr = 5*sizeof(uint32_t) + sza + szb;
    memcpy(result + sizeof(uint32_t), a, sza*sizeof(char) + 2*sizeof(uint32_t));
    memcpy(result + sizeof(uint32_t) + sza*sizeof(char) + 2*sizeof(uint32_t),  b,  szb*sizeof(char) + 2*sizeof(uint32_t));

    free(a);
    free(b);

    return result;
}

AffineTransform ImportAffineFromStr(const uint8_t *source) {
    source += sizeof(uint32_t);
    AffineTransform result;
    result.linear_map = ImportMatGf2FromStr(source);

    uint32_t * sz = (uint32_t *)source;
    int sza = *sz;
    sz ++;
    sza = sza * (*sz);

    result.vector_translation = ImportMatGf2FromStr(source + sza + 2*sizeof(uint32_t));
    return result;
}