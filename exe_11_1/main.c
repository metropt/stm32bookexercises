#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
#include <misc.h>

static __IO uint8_t ledval;
static __IO uint8_t change;

int main(void)
{
    ledval=0;
    change=0;
    
    GPIO_InitTypeDef  GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStrucuture;

    //Configure TIM2 clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //Configure GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //Configure GPIO PA1
    GPIO_StructInit(&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //Configure GPIO PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //configure NVIC
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    //configure timer
    //PWM frequency = 100hz with 24,000,000hz system clock
    //24,000,000/240 = 100,000
    //100,000/1000 = 100
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock/100000; //0..239
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1; //0..999
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    //PMW1 Mode configuration: Channel2
    //Edge-aligned; not single pulse mode
    TIM_OCStructInit(&TIM_OCInitStrucuture);
    TIM_OCInitStrucuture.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStrucuture.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC2Init(TIM2, &TIM_OCInitStrucuture);

    TIM_SetCompare2(TIM2, 499);

    TIM_Cmd(TIM2, ENABLE);
    
    while(1){
        if(change){
            GPIO_WriteBit(GPIOA, GPIO_Pin_2, (ledval)? Bit_SET : Bit_RESET);
            ledval = 1 - ledval;
            change=0;
        }

    };

    return 0;
}

void TIM2_IRQHandler(void){

    change=1;

    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif
