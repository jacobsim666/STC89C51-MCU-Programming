#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar flag;//������ɱ�־λ
uchar msg_r[3];//�յ�����Ϣ
uchar rec;
uchar i;
uchar code msg[]="i get ";//��Ϣ����
void init(){
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=1;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;//�򿪴����ж�
}
void main(){
	init();
	msg_r[0]='b';
	msg_r[1]='e';
	msg_r[2]='a';
	while(1){
		//�ж��Ƿ�����������
    if(flag==1){
			ES=0;//�رմ����ж�
			//������̶�����
			for(i=0;i<6;i++){
				SBUF=msg[i];
				while(!TI);
				TI=0;
			}
			for(i=0;i<3;i++){
				SBUF=msg_r[i];
			  while(!TI);
			  TI=0;
			}
			SBUF=rec;
			while(!TI);
			TI=0;
			ES=1;//���´򿪴����ж�
			flag=0;
		}			
	}
}
void serial() interrupt 4{
	RI=0;
	rec=SBUF;//��������
	flag=1;	
}