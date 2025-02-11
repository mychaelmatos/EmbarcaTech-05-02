#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"

// Definições dos pinos
#define SERVO_PIN 22
#define LED_PIN 12
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// Configurações do PWM para o servo (50Hz)
const uint32_t PWM_FREQ = 50;
const uint32_t CLOCK_DIV = 64;
const uint32_t WRAP_VALUE = 39062;  // 125MHz / 64 / 50Hz = 39062.5

// Valores de pulso para os ângulos do servo (em microssegundos)
const uint16_t PULSE_180 = 2400;
const uint16_t PULSE_90 = 1470;
const uint16_t PULSE_0 = 500;

// Função para converter microssegundos em valor de duty cycle
uint16_t us_to_duty(uint32_t us) {
    return (uint16_t)((float)us * WRAP_VALUE / 20000.0f);
}

// Função para mover o servo suavemente
void move_servo_smooth(uint slice, uint16_t start_us, uint16_t end_us) {
    int16_t step = (start_us < end_us) ? 5 : -5;  // Incremento de 5µs
    uint16_t current_us = start_us;

    while ((step > 0 && current_us <= end_us) || 
           (step < 0 && current_us >= end_us)) {
        // Atualiza servo e LED
        pwm_set_gpio_level(SERVO_PIN, us_to_duty(current_us));
        pwm_set_gpio_level(LED_PIN, us_to_duty(current_us));
        
        // Atraso para movimento suave
        sleep_ms(10);
        current_us += step;
    }
}

// Função para configurar o PWM
uint setup_pwm(uint gpio, uint32_t freq) {
    // Configura o pino como PWM
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    
    // Obtém o slice do PWM para o GPIO
    uint slice = pwm_gpio_to_slice_num(gpio);
    
    // Configura o PWM
    pwm_set_clkdiv(slice, CLOCK_DIV);
    pwm_set_wrap(slice, WRAP_VALUE);
    pwm_set_enabled(slice, true);
    
    return slice;
}

void move_servo(uint slice, uint16_t pulse_width) {
    pwm_set_gpio_level(SERVO_PIN, us_to_duty(pulse_width));
    pwm_set_gpio_level(LED_PIN, us_to_duty(pulse_width));
    sleep_ms(5000);
}

void uart_init_custom() {
    // Inicializa a UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

int main() {
    // Inicializa a UART
    uart_init_custom();
    
    // Configura PWM para servo e LED
    uint servo_slice = setup_pwm(SERVO_PIN, PWM_FREQ);
    uint led_slice = setup_pwm(LED_PIN, PWM_FREQ);
    
    // Move para 180 graus (2400µs)
    uart_puts(UART_ID, "Movendo para 180 graus\n");
    move_servo(servo_slice, PULSE_180);
    
    // Move para 90 graus (1470µs)
    uart_puts(UART_ID, "Movendo para 90 graus\n");
    move_servo(servo_slice, PULSE_90);
    
    // Move para 0 graus (500µs)
    uart_puts(UART_ID, "Movendo para 0 graus\n");
    move_servo(servo_slice, PULSE_0);
    
    // Movimento suave de 0 a 180 graus e volta
    uart_puts(UART_ID, "Iniciando movimento suave...\n");
    move_servo_smooth(servo_slice, PULSE_0, PULSE_180);
    sleep_ms(1000);
    move_servo_smooth(servo_slice, PULSE_180, PULSE_0);
    sleep_ms(1000);
    
    return 0;
}