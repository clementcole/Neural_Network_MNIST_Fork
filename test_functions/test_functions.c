#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>

uint32_t flipBytes(uint32_t n)
{
	uint32_t b0, b1, b2, b3;
	b0 = (n & 0x000000ff) << 24u; //bitwise and 255
	b1 = (n & 0x0000ff00) << 8u;  //65,280
	b2 = (n & 0x00ff0000) << 8u;  //1,671,1680
	b3 = (n & 0xff000000) << 24u; //4,278,190,080

	//printf("%d", 24u);

	return (b0 | b1 | b2 | b3);
}





int main(int argc, const char * argv[]) {
	/*From mnist-utils.c */
	//uint32_t n = 40;
	uint32_t n0 = 40, n1 = 50, n2 = 60, n3 = 20, n4 = 5;
	uint32_t x0 = flipBytes(n0), x1 = flipBytes(n1), x2 = flipBytes(n2), x3 = flipBytes(n3), x4 = flipBytes(n4);

	printf("BEFORE n0 = 0x%x, n1 = 0x%x, n2 = 0x%x, n3 = 0x%x,  n4 = 0x%x  \n", n0, n1, n2, n3, n4);

	printf("FLIPED n0 = 0x%x, n1 = 0x%x, n2 = 0x%x, n3 = 0x%x,  n4 = 0x%x  \n", x0, x1, x2, x3, x4);
	//printf("AFTER n =%" PRIu32 "\n",flipBytes(n));
	//printf("AFTER %" PRIu16 "\n",b);
    int i = 5;
    char buffer[33];
    itoa(i, buffer, 2);
    printf("%s", buffer);
	return 0;

}

/*

#include <stdio.h>
#include <inttypes.h>
int main (void) {
    uint32_t a=1234;
    uint16_t b=5678;
    printf("%" PRIu32 "\n",a);
    printf("%" PRIu16 "\n",b);
    return 0;
}

*/