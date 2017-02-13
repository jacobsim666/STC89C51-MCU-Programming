#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
//P1^6�ӵ������ģ��ENA,P1^7�ӵ������ģ��ENB
sbit left_motor_pwm_port=P1^6;
sbit right_motor_pwm_port=P1^7;
//��ߵ���Ľӷ�
sbit int1=P1^0;
sbit int2=P1^1;
//�ұߵ���Ľӷ�
sbit int3=P1^2;
sbit int4=P1^3;

//������
//���ת��״̬����
void left_motor_go();
void left_motor_back();
void left_motor_stop();

void right_motor_go(); 
void right_motor_back();
void right_motor_stop(); 
//����������
void ConfigUART(unsigned int baud);
//void run();
//void init();
//void change_pwm_left();
//void change_pwm_right();
//void delayms(uint z);
//pwmֵԤ��
uchar push_left_pwm_value=0;
uchar push_right_pwm_value=0;
//���ҵ��pwm����
uchar left_pwm_value=0;
uchar right_pwm_value=0;
//���������
sbit feng=P2^3;
unsigned char a,b;
void main(){
	ConfigUART(9600);
	while(1){
		while(!RI);
		RI=0;

		b=SBUF;
		a=b;
		SBUF=a;
		switch(b){
			//1��Ascii��Ϊ31����Ӧ��ʮ������Ϊ49
			//����ǰ������A,�ͷŷ���a
			//ǰ��
			case 65:
				//��Ӧ�Ĳ���
			  left_motor_go();
			  right_motor_go();
				break;
			//case 97:
				//ֹͣ
			  //left_motor_stop();
			  //right_motor_stop();
			  //break;
			
			
			//����
			case 68:
				left_motor_back();
			  right_motor_back();
				break;
			//case 100:
				//ֹͣ
			  //left_motor_stop();
			  //right_motor_stop();
			  //break;
			
			
			//��ת(ԭ����תȦ)
			case 67:
				left_motor_stop();
			  right_motor_go();
				break;
			//case 99:
				//ֹͣ
			  //left_motor_stop();
			  //right_motor_stop();
				//break;
			
			
			//��ת(ԭ����תȦ)
			case 66:
				left_motor_go();
			  right_motor_stop();
				break;
			//case 98:
				//left_motor_stop();
			  //right_motor_stop();
				//break;
			
			//ֹͣ
			case 69:
				left_motor_stop();
			  right_motor_stop();
			//Ĭ��
			default:
				left_motor_stop();
			  right_motor_stop();
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
	ET1=0;//����ʡ�Բ�д
	TR1=1;//������ʱ��
}
void left_motor_go(){
	int1=1;
	int2=0;
}
void left_motor_back(){
	int1=0;
	int2=1;
}
void left_motor_stop(){
	int1=0;
	int2=0;
}
void right_motor_go(){
	int3=1;
	int4=0;
}
void right_motor_back(){
	int3=0;
	int4=1;
}
void right_motor_stop(){
	int3=0;
	int4=0;
}
/*
void delayms(uint z){
  uint x,y;
  for(x=z;x>0;x--)
    for(y=114;y>0;y--);
}
void init(){
  TMOD=0X01;
  TH0= 0XF8;      //50ms??
  TL0= 0X30;
  TR0= 1;
  ET0= 1;
  EA = 1;
}
void run(uchar val1,uchar val2){
  //set pwm value
  push_left_pwm_value=val1;
  push_right_pwm_value=val2;
  left_motor_go;
  right_motor_go;
}
void change_pwm_left(){
  //generate left pwm
  if(left_motor_stop){
    if(left_pwm_value<=push_left_pwm_value){
      left_motor_pwm_port=1;
    }else{
      left_motor_pwm_port=0;
    }
    if(left_pwm_value>=10){
      left_pwm_value=0;
    }
  }else{
    left_motor_pwm_port=0;
  }
}
void change_pwm_right(){
    //generate right pwm
  if(right_motor_stop){
    if(right_pwm_value<=push_right_pwm_value){
      right_motor_pwm_port=1;
    }else{
      right_motor_pwm_port=0;
    }
    if(right_pwm_value>=10){
      right_pwm_value=0;
    }
  }else{
    left_motor_pwm_port=0;
  }
}
void timer0() interrupt 1{
    TH0= 0XF8;      //1ms
    TL0= 0X30;
    left_pwm_value++;
    right_pwm_value++;
    change_pwm_left();
    change_pwm_right();
}
*/