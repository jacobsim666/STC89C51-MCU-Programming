#include <reg52.h>
void ConfigUART(unsigned int baud);
unsigned char a,b;
sbit feng=P2^3;
sbit led1=P1^0;
sbit led2=P1^1;
void main(){
	ConfigUART(9600);
	while(1){
		while(!RI);
		RI=0;
		
		//P1=SBUF;//���ջ������е�ֵ��ֵ��P1��
		b=SBUF;
		a=b;
		SBUF=a;
		
		//ע��
		//�������ַ��͹�ȥ������Ϊ16���ƣ�����30ʵ���Ͼ���ʮ���Ƶ�48������switch�жϵ�ʱ��Ӧ���ж�
		//ʮ��������48
		/*if(b>31){
			P1=b;
			feng=0;
		}else{
			P1=0xf0;
			feng=1;
		}*/
		switch(b){
			//����'1'��ʮ������Ϊ31��ʮ����Ϊ49
			case 49:
			  led1=0;
			  led2=0;
				break;
			case 50:
				led1=0;
			  led2=1;
				break;
			case 51:
				led1=1;
			  led2=0;
				break;
			case 52:
				led1=1;
			  led2=1;
				break;
			case 53:
				feng=0;
			  break;
			default:
			  P1=0xff;
			  break;
		}
		while(!TI);
		TI=0;
	}
}
void ConfigUART(unsigned int baud){
	SCON=0x50;
	TMOD&=0x0f;
	TMOD|=0x20;
	TH1=256-(11059200/12/32)/baud;
	TL1=TH1;
	ET1=0;//����ʡ��
	TR1=1;//������ʱ��
}