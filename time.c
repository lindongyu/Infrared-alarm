#include "iostm8s003f3.h"
#include "time.h"
#include "speaker.h"
#include "search.h"

unsigned int hours,minutes, seconds, msec,Hours,Minutes_5,Seconds_10;
char flag_time=0,HOUERS = 0;
long int test = 0,test2=0;
char flag_mode = 0;

void  GPIO_PWM_INIT(void)   // PCC  TIM1 CH3    
{   
    PC_DDR |= 0x40;
    PC_CR1 |= 0x40;
    PC_CR2 |= 0x40;
    
    PC_ODR &= 0xBF;

}

void TIM1_Config(void)   // 5k  hz
{                     
			
  TIM1_PSCRH = 0;  //��Ԥ��Ƶϵ��32����Ƶ��Ϊ2M/32=62500  ע�ⲻͬ��ʱ���ķ�Ƶ���㹫ʽ
  TIM1_PSCRL = 3;   //0.5m
  TIM1_ARRH=0x00;  //�����Զ�װ�ؼĴ�����ֵΪ 62500����ô��ʱ�ж����ڸպ�Ϊ1s
  TIM1_ARRL=0X64;  //64

  TIM1_CCR1H=0/256;
  TIM1_CCR1L=0%256;
  TIM1_CCMR1 |=0X60;//ΪPWM1ģʽ
   
  	TIM1_CR1 |= 0x04;		//URS����Ϊ����sʱ��������ֹͣ���ҽ����������ʱ�ж���Ч
	TIM1_EGR |= 0x01;		//UG ����һ�������¼���������װ����ʼ��������
	TIM1_IER |= 0x01;		//_UIE��_UIE������ж�
  
  TIM1_CCER1 |=0X01;//����������ߵ�ƽ��Ч
  TIM1_OISR |=0X01;//����״̬Ϊ��
  TIM1_BKR |=0X80;
}

void TIM2_Config(void)
{
	TIM2_PSCR = 3;			//1M
	TIM2_ARRH = 0x61;		//�����Զ�װ�ؼĴ�����ֵΪ 1000����ô��ʱ�ж����ڸպ�Ϊ1Ms
	TIM2_ARRL = 0xA8;		
	TIM2_CR1 |= 0x04;		//urs����Ϊ����sʱ��������ֹͣ���ҽ����������ʱ�ж���Ч
	TIM2_EGR |= 0x01;		//UG����һ�������¼���������װ����ʼ��������
	TIM2_IER |= 0x01;		//UIE��UIE������ж�
	
}


#pragma vector = 13
__interrupt void TIM1_Overflow_IRQHandler(void)
{
  TIM1_SR1 = 0x00;		//����жϱ�־
  test++;
  if((mode3_flag==1)||(mode4_flag==1))
  {
      if(test >= 5000)
      {
            seconds ++;
           test = 0;
                              if((hours==Hours)&&((Minutes_5*5)==minutes)&&((Seconds_10*10)==seconds)) 
                       {
                         hours=0;
                         minutes=0;
                         seconds=0;
                         Hours=0;
                         Minutes_5=0;
                         Seconds_10=0;
                           if(mode4_flag==1)
                           {
                            //speaker = 0;    //����
                             speaker = 6; 
                             mode4_flag=0;

                           }
                           else if(mode3_flag==1)
                           {
                            speaker = 2;
                            mode3_flag=0;
                           }
                       }
           
           if(seconds>59)			//seconds����59�����㣬minutes��1
          {
             seconds = 0;
             minutes ++;

             if(minutes>59)		//minutes����59������
             {
               hours++;
               minutes=0;
             }  
          }
      }
  }
}



#pragma vector = 15
__interrupt void TIM2_Overflow_IRQHandler(void)

{
  
	TIM2_SR1 = 0x00;		//����жϱ�־
	//msec ++;				//ÿ 1ms�ж�һ�Σ�
	//if(msec>=100)			//
	//{
         test2++;
         
		msec = 0;
              if(flag_mode==2)
                {
		speaker_on();
                }
                if( (flag_mode==1) || (flag_mode==5) )
                {
                speaker_off();  //��ʱTIM2 ���ڼ�����
                }
     //  }

 
    
 }




