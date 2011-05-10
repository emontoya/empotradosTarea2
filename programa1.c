#include <stdio.h>
#include <stint.h>
int main(){
 uint32_t x=0xEC4C2C;
 uint32_t y=0xFF;
 
 printf("%d", (x>>24)&y);
 printf(".%d", (x>>16)&y);
 printf(".%d", (x>>8)&y);
 printf(".%d", (x&y);



 return 0;
}
