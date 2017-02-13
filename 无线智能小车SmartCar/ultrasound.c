/**
*������ģ���ʹ����ϰ
*Trig��P2^0,Echo��P2^1
*/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long
sbit trig=P2^0;
sbit echo=P2^1;

sbit dula=P2^6;
sbit wela=P2^7;

sbit feng=P2^3;

//lcd1602
sbit lcden=P3^4;//EN
sbit lcdrs=P3^5;//RS
sbit lcdrw=P3^6;//RW

uint successful;
uint count;//��ʱ������Ĵ���
uint time;//echo����ĸߵ�ƽ������ʱ��
ulong distance;
uint bai,shi,ge;
uchar code table[]="0123456789";
uchar code tips[]="DISTANCE:";
uchar code nothing[]="NOTHING GET";
//������
void delayms(uint);
void startModule();
void display(uchar);
void calculate_distance();
void ultrasound_module_init();
void timer1_init();
void write_data(uchar);
void write_com(uchar);
void lcd_show();
//
void delayms(uint time){
	uint x,y;
	for(x=time;x>0;x--)
	   for(y=110;y>0;y--);
}
void startModule(){
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
/*�������ʾ
void display(uint b,uint s,uint g){
	delayms(5);
	dula=1;
	P0=table[b];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfe;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[s];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
	
	dula=1;
	P0=table[g];
	dula=0;
	
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delayms(5);
}*/
//LCD1602��ʾ
void display(uchar dis){
	if(dis==0){
		uint num;
		for(num=0;num<11;num++){
			write_data(nothing[num]);
			delayms(5);
		}
  }else if(dis==1){
		if(distance<=10){
			feng=0;
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
  }
	
}
void calculate_distance(){
	time=TH1*256+TL1;//������ʱ���е�ֵ���������
	time+=count*65536;
	//����װ���ֵ������
	TH1=0;
	TL1=0;
	distance=(time*1.7)/100;//��λ������
	if(distance>100 || successful==0){
		distance=0;//����������
	}else{
		display(1);
	}
}
void ultrasound_module_init(){
	//trig echo�����͵�ƽ
	trig=0;
	echo=0;
}
void timer1_init(){
	TMOD=0x10;//��ʱ��1
	EA=1;
	TH1=0;
	TL1=0;
}

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
void write_com(uchar com){
	lcdrs=0;
	//ledrw=0;
	P0=com;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
void write_data(uchar dat){
	lcdrs=1;
	//ledrw=0;
	P0=dat;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}
void lcd_show(){
	uint num;
	write_com(0x80);
	for(num=0;num<9;num++){
		write_data(tips[num]);
		delayms(5);
	}
}

void main(){
	lcd_init();
	successful=0;
	ultrasound_module_init();
	timer1_init();
	//echo�ӵ͵�ƽ����˸ߵ�ƽ�����������ݸߵ�ƽ������ʱ�����������
	//echo�ߵ�ƽ����ʱ��;��������
	while(1){
		//��ʼ��20us�ߵ�ƽ
		lcd_show();
	  startModule();
		while(!echo);//�ȴ��ߵ�ƽ���٣�������ʱ��
		TR1=1;
		while(echo);//�ȴ��ߵ�ƽ�������رռ�ʱ��
		TR1=0;
		successful=1;//�ߵ�ƽ�����ɣ��ɹ�
		calculate_distance();//�������
		delayms(10);//��ʱ10ms�ٽ����´β��
	}
}
//�жϷ������
void timer1() interrupt 1{
	count++;
	TH1=0;
	TL1=0;
}