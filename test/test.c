#include <stdio.h>
#include <stdint.h>
#include <matrixlib/wrandom.h>
#include <matrixlib/matrixlib_cfg.h>

int math_test();

int main(int argc, char **argv) {
    printf("Version: %d.%d\n", MATRIXLIB_VERSION_MAJOR, MATRIXLIB_VERSION_MINOR);
    math_test();
	return 0;
}