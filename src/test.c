/*
 * test.c
 *
 *  Created on: 2019/03/11
 *      Author: AshGarden
 */


#include "ringbuff.h"

typedef struct
{
	int 	i;
	char	c[10];
	short	s;
}MyStruct;

int main(int argc, char **argv) {
	int i;
	char str[100];
	MyStruct st;
	RINGMNG_T*	intRing;
	RINGMNG_T*	strRing;
	RINGMNG_T*	stRing;

	intRing = CreateRBMandRBD(10,sizeof(int));

	for(i=0;i<3;i++)
	{
		WriteRB(intRing,&i);
	}

	while(ReadRB(intRing,&i))
	{
		printf("%d\n",i);
	}


	strRing = CreateRBMandRBD(10,100);

	for(i=100;i<103;i++)
	{
		sprintf(str,"%d",i);
		WriteRB(strRing,str);
	}

	while(ReadRB(strRing,str))
	{
		printf("%s\n",str);
	}


	stRing = CreateRBMandRBD(10,sizeof(MyStruct));
	for(i=200;i<208;i++)
	{
		st.i = i;
		st.s = i*2;
		sprintf(st.c,"%d",i*10);
		WriteRB(stRing,&st);
	}

	while(ReadRB(stRing,&st) )
	{
		printf("i=%d\n",st.i);
		printf("s=%d\n",st.s);
		printf("c=%s\n",st.c);
	}


}
