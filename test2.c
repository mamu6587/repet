#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*

int isPalindrome(char* word){

    int c = (strlen(word)/2);

for(int i = 0;i < c;i++) {
if (!(word[i] == word[(c-i)])) {return 1;}
}
return 0;


}

int main(int argc,char **argv){
    if (argc < 2){return 0;}

printf("test %d = %d",1,isPalindrome("Anka"));
printf("test %d = %d",2,isPalindrome("Anna"));
printf("test %d = %d",3,isPalindrome("Annakkanna"));
printf("test %d = %d",4,isPalindrome("Anakana"));
//return isPalindrome(*argv);
}
*/


int main(){
    int x = 3;
int* ptr1 = &x;
int* ptr2 = &x;
int* ptr3 = ptr2;
int* ptr4 = x;

printf("&x = %p\n ptr1 address %p value %d\n", &x, ptr1, *ptr1);
printf("ptr2 address %p value %d\n",ptr2, *ptr2);
printf("\n ptr3 address %p value %d\n",ptr3, *ptr3);
printf("\n ptr4 address %p value %d\n",ptr4, ptr4);
printf("ptr1 == ptr 2 =%d\n ptr 2 == ptr 3 = %d\n ptr 3 == ptr 4 =%d \n ptr 1 == ptr 3 = %d ptr 1 == ptr 4 = %d\n",(ptr1 == ptr2),(ptr2 == ptr3),(ptr3 == ptr4),(ptr1 == ptr3),(ptr1 == ptr4));
printf("ptr2 == ptr 4 =%d", (ptr2 == ptr4));
}
