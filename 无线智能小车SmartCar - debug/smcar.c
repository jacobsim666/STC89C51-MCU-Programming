#include "myreg52.h"
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
/**
*�˿ڶ���
*/
//P1^6�ӵ������ģ��ENA,P1^7�ӵ������ģ��ENB
sbit left_motor_pwm_port=P1^6;
sbit right_motor_pwm_port=P1^7;
//��ߵ���Ľӷ�
sbit int1=P1^0;
sbit int2=P1^1;
//�ұߵ���Ľӷ�
sbit int3=P1^2;
sbit int4=P1^3;
//������ģ��
sbit trig=P2^0;
sbit echo=P2^1;
//������
sbit feng=P2^3;
sbit led_left=P1^4;
sbit led_right=P1^5;
//lcd1602Һ����ʾģ��
sbit lcden=P3^4;//EN
sbit lcdrs=P3^5;//RS
sbit lcdrw=P3^6;//RW
sbit dula=P2^6;
sbit wela=P2^7;
/**
*�����嵥
*/
void delayms(uint time);
void USModule_start();
void display(uchar dis);
void calculate_distance();
void USModule_init();
void timer0_init();
void lcd_init();
void write_com(uchar com);
void write_data(uchar dat);
void lcd_show();
void Motors_Handler();
void USMOdule_Handler();
//����������	
void ConfigUART(uint baud);
//���ת��״̬����
void left_motor_go();
void left_motor_back();
void left_motor_stop();

void right_motor_go(); 
void right_motor_back();
void right_motor_stop(); 
void timer2_start();
/**
*�����嵥
*/
//pwmֵԤ��
uchar push_left_pwm_value=0;
uchar push_right_pwm_value=0;
//���ҵ��pwm����
uchar left_pwm_value=0;
uchar right_pwm_value=0;
uchar a,b;
uint successful;//������ģ��ߵ�ƽ����ɹ�
uint US_OK;//���Խ��г��������
uint count;//��ʱ������Ĵ���
uint count1;//��ʱ��1����Ĵ���
uint time;//echo����ĸߵ�ƽ������ʱ��
ulong distance;//������ģ�����
uint bai,shi,ge;
uchar code table[]="0123456789";
uchar code tips[]="DISTANCE:";

//��ʱ����
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	   for(y=114;y>0;y--);
}
//����������ģ��
void USModule_start(){
	trig=1;
	//delay_20us();//��ʱ20us
		 _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  trig=0;
}
//������ģ���ʼ��
void USModule_init(){
	//trig echo�����͵�ƽ
	trig=0;
	echo=0;
}
//��ʱ��1��ʼ��
void timer0_init(){
	TH0=0;
	TL0=0;
	ET0=1;
}
//lcd1602��ʼ��
void lcd_init(){
	dula=0;
	wela=0;
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}
//1602д����
void write_com(uchar com){
	lcdrs=0;
	//ledrw=0;
	P0=com;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
//1602д����
void write_data(uchar dat){
	lcdrs=1;
	//ledrw=0;
	P0=dat;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
//1602����ʾ
void lcd_show(){
	uint num;
	write_com(0x80);
	for(num=0;num<9;num++){
		write_data(tips[num]);
		delayms(5);
	}
}
//���ݴ��ڷ��͵����ݿ��Ƶ��
void Motors_Handler(){
	ConfigUART(9600);
	//while(!RI);
		//RI=0;

		b=SBUF;
		//a=b;
		//SBUF=a;
		switch(b){
			//1��Ascii��Ϊ31����Ӧ��ʮ������Ϊ49
			//����ǰ������A,B,C��Ӧ���١����١�����
			//ǰ��
			case 65:
				//��Ӧ�Ĳ���
			  left_motor_go();
			  right_motor_go();
				break;
			//����
			case 68:
				left_motor_back();
			  right_motor_back();
				break;
			//��ת(ԭ����תȦ)
			case 67:
				left_motor_stop();
			  right_motor_go();
				break;
			//��ת(ԭ����תȦ)
			case 66:
				left_motor_go();
			  right_motor_stop();
				break;
			//ֹͣ
			case 83:
				left_motor_stop();
			  right_motor_stop();
			  break;
		}
		//while(!TI);
		//TI=0;
}
//����������9600
void ConfigUART(uint baud){
	SCON=0x50;
	TH1=256-(11059200/12/32)/baud;
	TL1=TH1;
	TR1=1;//������ʱ��1
}
//����ǰ��
void left_motor_go(){
	int1=1;
	int2=0;
}
//���ֺ���
void left_motor_back(){
	int1=0;
	int2=1;
}
//����ֹͣ
void left_motor_stop(){
	int1=0;
	int2=0;
}
//����ǰ��
void right_motor_go(){
	int3=1;
	int4=0;
}
//���ֺ���
void right_motor_back(){
	int3=0;
	int4=1;
}
//����ֹͣ
void right_motor_stop(){
	int3=0;
	int4=0;
}
//������ģ�鴦��
void USModule_Handler(){
	lcd_show();//lcd����ʾ
	USModule_start();
	while(!echo);//�ȴ��ߵ�ƽ���٣�������ʱ��
	TR0=1;
	while(echo);//�ȴ��ߵ�ƽ�������رռ�ʱ��
	TR0=0;
	successful=1;//�ߵ�ƽ�����ɣ��ɹ�
	time=TH0*256+TL0;//������ʱ���е�ֵ���������
	//����װ���ֵ������
	TH0=0;
	TL0=0;
	distance=(time*1.7)/100;//��λ������
	if(distance>700 || successful==0){
		distance=0;//����������
	}
	if(distance<=10){
			feng=0;
			left_motor_stop();
			right_motor_stop();
			delayms(1000);//�����ϰ�ʱ���ӳ�һ�룬Ȼ��ѡ������ת��
			left_motor_go();
			right_motor_stop();
		}else{
			feng=1;
		}
		bai=distance/100;
		shi=distance%100/10;
		ge=distance%100%10;
		write_data(table[bai]);
		write_data(table[shi]);
		write_data(table[ge]);
		write_data(' ');
		write_data('c');
		write_data('m');
	  delayms(10);//��ʱ10ms�ٽ����´β��
		
}
void timer2_start(){
	//������ʱ��2
	RCAP2H=(65536-1000)/256;//1ms����һ������ж�,��������pwm��
	RCAP2L=(65536-1000)%256;
	T2CON=0;
	ET2=1;
	TR2=1;
}
//������
void main(){
	TMOD=0x21;//��ʱ��0��1��ʹ��
	EA=1;
	timer0_init();
	//lcd_init();
	//successful=0;
	//USModule_init();
	timer2_start();
	push_left_pwm_value=9;
	push_right_pwm_value=9;
	while(1){
		Motors_Handler();//������ģ��
		//USModule_Handler();//��������ģ��
	}
}
void timer2() interrupt 5{
	TF2=0;
	//����pwm��
	//left
	left_pwm_value++;
	right_pwm_value++;
	if(left_pwm_value<=push_left_pwm_value){
		left_motor_pwm_port=1;
	}else{
		left_motor_pwm_port=0;
	}
	if(left_pwm_value==10){
		left_pwm_value=0;
	}
	//right
	if(right_pwm_value<=push_right_pwm_value){
		right_motor_pwm_port=1;
	}else{
		right_motor_pwm_port=0;
	}
	if(right_pwm_value==10){
		right_pwm_value=0;
	}
}