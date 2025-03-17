# Christmas Lights Simulation
 	This project implements a dynamic Christmas light display using an ATmega32 microcontroller on the EasyAVR7 development board. The system utilizes timers, analog-to-digital conversion (ADC), and pulse-width modulation (PWM) to control three distinct lighting patterns. Additionally, a 7-segment display is used to indicate the active mode, enhancing user interaction.

	Features:
- Three lighting patterns controlled by a button
- Timers for precise LED sequencing
- Analog-to-digital conversion (ADC) to adjust speed
- 7-segment display to indicate active mode (HOHO, JOY, or 2025)
- PWM control for LED brightness adjustments
- Optimized register-level programming for efficiency
- Runs on an 8 MHz system clock (f_CPU)

	Hardware Requirements:
-EasyAVR7 development board
-ATmega32 microcontroller
-LEDs connected to PORTD
-7-segment display connected to PORTC & PORTA
-Push button (connected to PB7) for mode selection
-Potentiometer for ADC input (connected to ADC6)
-Power supply (5V)

	Software Requirements:
-Microchip Studio (for development and debugging)
-AVR-GCC (compiler)

	How It Works:
    The system cycles through three lighting patterns, selected via a push button on PB7. The 7-segment display updates to show the corresponding mode:

Pattern 1: HOHO 
LEDs light up sequentially.
Display alternates between "H" and "O".

Pattern 2: JOY 
Two alternating LED groups blink in a rhythmic pattern.
Display cycles through "J", "O", and "Y".

Pattern 3: 2025 
LEDs sweep forward and backward in a dynamic motion.
Display shows the year "2025".
The ADC (Analog-to-Digital Converter) reads values from a potentiometer to dynamically adjust the blinking speed.

     Timer & Interrupts
Timer2 (CTC Mode): Generates an interrupt for pattern switching and LED updates.
Timer0 (PWM Mode): Controls LED brightness.
Interrupt Service Routine (ISR): Handles button presses and pattern transitions.
