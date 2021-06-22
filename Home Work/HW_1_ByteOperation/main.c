#include <stdio.h>

int main(){

int a = 0xCCDDAABB;
int b = 0x00CCAABB;
unsigned char c;

for(int i = 0; i < sizeof(typeof(a)); i++) {
    c = (a & 0xFF);
    printf("%d bite of a = %X\n",i,c);
    a = a >> 8;
}

printf("before b = %X\n",b);
b^= 0x11 << 16;
printf("after b = %X\n",b);

}
