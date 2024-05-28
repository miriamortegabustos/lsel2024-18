#include "snake_input.h"
#include "stm32_init.h"

#include "stm32f4xx.h"

#include "stm32_bsp.h"

#include <stdlib.h>  // Para la función abs()


static int button_flag;
static int button_heading;

ACCELERO_DrvTypeDef* acc;


static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure PA0 pin as input floating */
  /* TODO Fill init */
  //GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  //HAL_GPIO_Init(xxx, xxx);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}


int
snake_input_init(snake_game_t* p_game)
{
  if (!stm32_init()) {
    return 0;
  }
  /* TODO Clear flag */
  button_heading = UP;
  EXTILine0_Config();

  //Acc
  acc = bsp_get_accelero();
  acc->Init(bsp_get_accelero_config()); //incializo el ACC
  COMPASSACCELERO_IO_Init();

  return 1;
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_0)
  {
    /* TODO Set flag */ 
      button_flag=1;

  }
}


void
snake_input_update_new_heading (snake_game_t* p_game)
{
    p_game->new_heading = p_game->snake.heading;
    /* Global variable button_heading indicates last heading value of button */
    /* Change: every USER button pressed, change button_heading COUNTERCLOCKWISE: */
    /* From LEFT to DOWN */
    /* From DOWN to RIGHT */
    /* From RIGHT to UP */
    /* From UP to LEFT */
    /* TODO Check flag, clear and update new_heading and stm32 heading */


    // if (button_flag){
      
    //   switch (button_heading)
    //   {
    //   case LEFT:
    //     p_game->new_heading = DOWN;
    //     break;
    //   case DOWN:
    //     p_game->new_heading = RIGHT;
    //     break;
    //   case RIGHT:
    //     p_game->new_heading = UP;
    //     break;
    //   case UP:
    //     p_game->new_heading = LEFT;

    //     break;  
    //   }    
    //   button_heading = p_game->new_heading;    
    //     button_flag=0;
    // }

    //ACCC
    int16_t valoresXYZ [3];

    LSM303DLHC_AccReadXYZ(valoresXYZ);

    if (abs(valoresXYZ[0])>abs(valoresXYZ[1])){   //eje X
        if (valoresXYZ[0]>0){
            p_game->new_heading = RIGHT;
        }else{
            p_game->new_heading = LEFT;
        }

    }else{      //eje Y
        if (valoresXYZ[1]>0){
            p_game->new_heading = UP;
        }else{
            p_game->new_heading = DOWN;
        }
    }


}

void
snake_input_close(snake_game_t* p_game)
{
  HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}

