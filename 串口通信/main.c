#include <reg52.h>
//#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar num;
//main
/*void delayms(uint z){
    uint x,y;
	for(x<z;x>0;x--)
	    for(y=114;y>0;y--);
}*/
void UART_init(){
    TMOD=0x20;//T1�����ڷ�ʽ2
	TH1=0xfd;
	TL1=0xfd;  //������Ϊ9600
	TR1=1;    //����T1��ʱ��
	SM0=0;    //
	SM1=1;    //���ڹ����ڷ�ʽ1
	REN=1;    //�����������λ
	EA=1;     //�����ж�
	ES=1;     //�����жϴ�
}
void main(){
	UART_init();
	while(1);
		//{
		//SBUF=num;
		
		//while(!RI);
		//P1=SBUF;
		//RI=0;
		//num++;
		//delayms(5000);
	//}
}
void UART() interrupt 4{
	// if (TI)
	// {
	// 	SBUF=num;
	// 	TI=0;
	// }
	if (RI)  //����Ƿ�������
	{
		num=SBUF;  //numȡ������
		P1=SBUF;
		num++;
		RI=0;
		SBUF=num;
		while(!TI);
		TI=0;
	}
}