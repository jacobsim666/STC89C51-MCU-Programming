#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int	   //52ϵ�е�Ƭ��ͷ�ļ�
sbit led1=P1^0;		   //������Ƭ��p1�ڵ�һ��
sbit led2=P1^1;
//void delay(uint time1,uint time2);
/** �������
void main(){
   //led1=0;		       //������һ���Ź������
   //led2=0;
   //P1=0x00;					//�������еĶ�����
   //P1=0xaa;						//1,3,5,7��
   P1=0x55;					//2,4,6,8��
}*/
/**
void main(void){
   P1=0xFE;
   while(1);
}*/
/**void main(void){
  unsigned char i,j;
  for(i=255;i>0;i--)
    for(j=255;j>0;j--)
  P1=0xfe;
}*/

/**void main(void){
    //��ѭ��
	while(1){
	    led1=0;
		led2=1;
		//��ʱ
		delay(100,100);
		led1=1;
		led2=0;
		//��ʱ
		delay(100,100);
	};
}*/
//void delay(uint time1,uint time2){
  //  uint i,j;
    //for(i=time1;i>0;i--)
	    //for(j=time2;j>0;j--);
//}
//���Ʋ���a<<1;���Ʋ���a>>1
//unsigned char a;
//void main(void){
  //  a=0xFF;
	//while(1){
   //     a=a>>1;
	//	P1=a;
	//	delay(200,200);
	//	if(a==0x00){
	//	    a=0xFF;
	//	}
	//}
//}
//��������ģ���Ƿ��ܹ������շ�����
void init()
   { 
		 //��ȫ����
		 //led1=0;
		 //led2=0;
		 ////init
		 //�ر����ж�
		 ES=0;
		 //���ڹ���ģʽ1
		 SCON=0x50;//��ͬ��sm0=0,sm1=1,ren=1
		 TMOD=0x20;//��ʱ��T1����ģʽ2
		 TH1=0xfd;
		 TL1=0xfd;
		 TR1=1;//��ʱ��1��ʼ����
		 TI=0;
		 RI=0;
		 EA=1;
		 ES=1;
   }
  void actionforSBUF(uchar a){
           //ES=0;
           //RI=0;  
           //a=SBUF; 
			//SBUF=a;
			//a=SBUF;
          
     switch(a)
    {
      case 31:  
				led1=0;
        led2=1;			
			  break;  
      case 32:  
				led1=1;
        led2=0;			
			  break;   
      default: 
				led1=0;
			  led2=0;
			  break;
     } 
  //ES=1;
}
    void main()
    {
        init();
        while(1){
					if(RI){
						RI=0;
						//a=SBUF;
					}
					actionforSBUF(SBUF);
				}
     }
		
