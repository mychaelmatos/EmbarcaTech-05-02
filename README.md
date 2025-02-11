# Projeto Servo Motor com PWM

Este projeto é uma tarefa da residência do CEPEDI de Sistemas Embarcados, Embarcatech. O objetivo do projeto é controlar um servomotor utilizando PWM e observar o comportamento de um LED RGB conectado ao GPIO 12.

## LInk de video demostração e explicação geral

link: https://www.youtube.com/watch?v=LKhhsXXgN5o

## Link para demostração do simulador WOKWI

link : https://wokwi.com/projects/422609833939979265

## Descrição

O projeto utiliza um microcontrolador para controlar um servomotor através de PWM. O código ajusta o ciclo ativo do PWM para mover o servomotor para diferentes posições (0, 90 e 180 graus) e observa o comportamento do LED RGB conectado ao GPIO 12.

## Estrutura do Projeto

- blink.c: Contém a lógica principal para controlar o servomotor e o LED RGB.
- pico_sdk_import.cmake: Arquivo de configuração do SDK do Raspberry Pi Pico.
- CMakeLists.txt: Arquivo de configuração do CMake para compilar o projeto.

## Funcionalidades

- Controle do Servomotor.
- Simulação Wokwi.

## Como Compilar

1. Clone o repositório.
2. Configure o ambiente de desenvolvimento para Raspberry Pi Pico
3. Compile o projeto usando CMake.
4. Conecte a placa no modo BOOTSEL.
5. Carregue o firmware compilado.
6. Use o Serial Monitor para interagir com o sistema.

## Requisitos

- Placa BitDogLab
- Computador Pessoal

## Licença

Este projeto é licenciado sob a [MIT License](LICENSE).

---

Residência do CEPEDI de Sistemas Embarcados, Embarcatech.
