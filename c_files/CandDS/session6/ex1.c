#include<stdio.h>

typedef struct sampStruct
{

  unsigned int intValue1;
  unsigned short shValue;
  unsigned int intValue2;
  unsigned char chValue;
  unsigned int intValue3;

}sampStruct_t;

main(void)
{
  sampStruct_t st;
  printf("size of the structure variable  = %d\n", sizeof(st));
  printf("addr of the structure variable  = %d\n", &st);

  printf("addr of intValue1 = %d\n", &(st.intValue1));
  printf("addr of shValue = %d\n", &(st.shValue));
  printf("addr of intValue2 = %d\n", &(st.intValue2));
  printf("addr of chValue = %d\n", &(st.chValue));
  printf("addr of intValue3 = %d\n", &(st.intValue3));

  printf("size of intValue1 = %d\n", sizeof(st.intValue1));
  printf("size of shValue = %d\n", sizeof(st.shValue));
  printf("size of intValue2 = %d\n", sizeof(st.intValue2));
  printf("size of chValue = %d\n", sizeof(st.chValue));
  printf("size of intValue3 = %d\n", sizeof(st.intValue3));
}
  
  
  

