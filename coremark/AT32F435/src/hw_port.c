#include <stdio.h>

#include "at32f435_437.h"

volatile int SysTick_10ms = 0;

void system_clock_config(void);
void SerialInit(void);

void hw_init(void)
{
	system_clock_config();
	
	SerialInit();
	
	SysTick_Config(SystemCoreClock / 100);
	
	printf("SystemCoreClock = %d\n\n", SystemCoreClock);
}


void SysTick_Handler(void)
{
	SysTick_10ms++;
}


void system_clock_config(void)
{
  /* reset crm */
  crm_reset();

  /* enable pwc periph clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

  /* config ldo voltage */
  pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V3);

  /* set the flash clock divider */
  flash_clock_divider_set(FLASH_CLOCK_DIV_3);

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

  /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource
  common frequency config list: pll source selected  hick or hext(8mhz)
  _________________________________________________________________________________________________
  |        |         |         |         |         |         |         |         |        |        |
  |pll(mhz)|   288   |   252   |   216   |   192   |   180   |   144   |   108   |   72   |   36   |
  |________|_________|_________|_________|_________|_________|_________|_________|_________________|
  |        |         |         |         |         |         |         |         |        |        |
  |pll_ns  |   144   |   126   |   108   |   96    |   90    |   72    |   108   |   72   |   72   |
  |        |         |         |         |         |         |         |         |        |        |
  |pll_ms  |   1     |   1     |   1     |   1     |   1     |   1     |   1     |   1    |   1    |
  |        |         |         |         |         |         |         |         |        |        |
  |pll_fr  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_8  |   FR_8 |   FR_16|
  |________|_________|_________|_________|_________|_________|_________|_________|________|________|

  if pll clock source selects hext with other frequency values, or configure pll to other
  frequency values, please use the at32 new clock  configuration tool for configuration.  */
  crm_pll_config(CRM_PLL_SOURCE_HEXT, 96, 1, CRM_PLL_FR_4);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}


void SerialInit(void)
{
	gpio_init_type gpio_init_struct;
	gpio_default_para_init(&gpio_init_struct);
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_9 | GPIO_PINS_10;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init(GPIOA, &gpio_init_struct);
	
	gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9,  GPIO_MUX_7);	// USART1_TX
	gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_7);	// USART1_RX
	
	
	usart_init(USART1, 115200, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(USART1, TRUE);
	usart_receiver_enable(USART1, TRUE);
	usart_enable(USART1, TRUE);
}

int fputc(int ch, FILE *f)
{
	while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
	usart_data_transmit(USART1, ch);
	
	return ch;
}
