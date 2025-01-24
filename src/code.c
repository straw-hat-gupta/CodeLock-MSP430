#include <msp430.h>

#define PASSCODE_LENGTH 4
const char correctPasscode[PASSCODE_LENGTH] = {'1', '2', '3', '4'}; // Example passcode
char enteredPasscode[PASSCODE_LENGTH];
unsigned int passcodeIndex = 0;

// Button pin definitions
#define BUTTON_0_PIN BIT5 // P6.0
#define BUTTON_1_PIN BIT4 // P3.2
#define BUTTON_2_PIN BIT3 // P3.3
#define BUTTON_3_PIN BIT6 // P2.4
#define BUTTON_4_PIN BIT6 // P6.1
#define BUTTON_5_PIN BIT2 // P3.6
#define BUTTON_6_PIN BIT7 // P2.7
#define BUTTON_7_PIN BIT2 // P1.3
#define BUTTON_8_PIN BIT1 // P1.4
#define BUTTON_9_PIN BIT4 // P1.5

// Function prototypes
void initialize();
void initButtons();
void initDisplay();
void updateDisplay();
void checkPasscode();
void resetPasscodeInput();
void displayDigit(char digit, unsigned int position);
void clearDisplay();
void setupPWM();
void rotateServo(unsigned int angle);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    initialize();
    _BIS_SR(GIE); // Enable global interrupts
    clearDisplay();
    setupPWM();
    while (1) {
        __low_power_mode_3(); // Enter low power mode (assumes no need for ACLK)
    }
}

void initialize() {
    // Initialize GPIO, clocks, and any other peripherals here
    P1DIR |= BIT0; // Assuming P1.0 drives an LED
    P1OUT &= ~BIT0; // Initially turn off LED

    // Initialize keypad pins and interrupts
    initButtons();

    // Initialize 7-segment display pins
    initDisplay();
}

void initButtons() {
    // Initialize button 0 to 9 pins as input with pull-up resistors
    // and enable interrupts for falling edge

    // P1.x buttons (Buttons 7, 8, and 9)
    P1DIR &= ~(BUTTON_7_PIN | BUTTON_8_PIN | BUTTON_9_PIN); // Set as input
    P1REN |= (BUTTON_7_PIN | BUTTON_8_PIN | BUTTON_9_PIN);  // Enable pull-up/down resistors
    P1OUT |= (BUTTON_7_PIN | BUTTON_8_PIN | BUTTON_9_PIN);  // Select pull-up mode
    P1IES |= (BUTTON_7_PIN | BUTTON_8_PIN | BUTTON_9_PIN);  // Interrupt on falling edge
    P1IE |= (BUTTON_7_PIN | BUTTON_8_PIN | BUTTON_9_PIN);   // Enable interrupts
    P1IFG &= ~(BUTTON_7_PIN | BUTTON_8_PIN | BUTTON_9_PIN); // Clear interrupt flags

    // P2.x buttons (Buttons 3 and 6)
    P2DIR &= ~(BUTTON_3_PIN | BUTTON_6_PIN);
    P2REN |= (BUTTON_3_PIN | BUTTON_6_PIN);
    P2OUT |= (BUTTON_3_PIN | BUTTON_6_PIN);
    P2IES |= (BUTTON_3_PIN | BUTTON_6_PIN);
    P2IE |= (BUTTON_3_PIN | BUTTON_6_PIN);
    P2IFG &= ~(BUTTON_3_PIN | BUTTON_6_PIN);

    // P3.x buttons (Buttons 1, 2, and 5)
    P3DIR &= ~(BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_5_PIN);
    P3REN |= (BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_5_PIN);
    P3OUT |= (BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_5_PIN);
    P3IES |= (BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_5_PIN);
    P3IE |= (BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_5_PIN);
    P3IFG &= ~(BUTTON_1_PIN | BUTTON_2_PIN | BUTTON_5_PIN);

    // P6.x buttons (Buttons 0 and 4)
    P6DIR &= ~(BUTTON_0_PIN | BUTTON_4_PIN);
    P6REN |= (BUTTON_0_PIN | BUTTON_4_PIN);
    P6OUT |= (BUTTON_0_PIN | BUTTON_4_PIN);
    P6IES |= (BUTTON_0_PIN | BUTTON_4_PIN);
    P6IE |= (BUTTON_0_PIN | BUTTON_4_PIN);
    P6IFG &= ~(BUTTON_0_PIN | BUTTON_4_PIN);
}

void initDisplay() {
    // Set all display control pins to output and clear them
    P6DIR |= 0xFF; // Set all P6 pins as output for 7-segment data
    P3DIR |= 0xC0; // Control bits (P3.6, P3.7) for display selection
    P7DIR |= BIT0; // Strobe control on P7.0
    clearDisplay();
}

void clearDisplay() {
    P6OUT = 0x00; // Clear all segments
    for (unsigned int i = 0; i < 4; i++) {
        displayDigit(' ', i); // Clear each display position
    }
}

void displayDigit(char digit, unsigned int position) {
    switch(digit) {
        case '0': P6OUT = 0x3F; break;
        case '1': P6OUT = 0x06; break;
        case '2': P6OUT = 0x5B; break;
        case '3': P6OUT = 0x4F; break;
        case '4': P6OUT = 0x66; break;
        case '5': P6OUT = 0x6D; break;
        case '6': P6OUT = 0x7D; break;
        case '7': P6OUT = 0x07; break;
        case '8': P6OUT = 0x7F; break;
        case '9': P6OUT = 0x6F; break;
        default:  P6OUT = 0x00; break; // Clear display for any other input
    }

    unsigned int displayPosition = 3 - (position % 4);
    P3OUT = (P3OUT & ~(BIT6 | BIT7)) | (displayPosition << 6);

    P7OUT &= ~BIT0; // Set strobe low to latch the data
    __delay_cycles(500);
    P7OUT |= BIT0; // Set strobe high again
}

void updateDisplay() {
    for (unsigned int i = 0; i < passcodeIndex; i++) {
        displayDigit(enteredPasscode[i], i);
    }
}

void checkPasscode() {
    for (unsigned int i = 0; i < PASSCODE_LENGTH; i++) {
        if (enteredPasscode[i] != correctPasscode[i]) {
            resetPasscodeInput();
            clearDisplay();
            return; // Incorrect passcode, exit the function
        }
    }
    // If correct passcode is entered
    rotateServo(180); // Unlock action
    __delay_cycles(3000000); // Delay for a visible unlock duration
    rotateServo(0); // Lock action after delay
    resetPasscodeInput();
    clearDisplay();
}

void resetPasscodeInput() {
    passcodeIndex = 0;
    for (unsigned int i = 0; i < PASSCODE_LENGTH; i++) {
        enteredPasscode[i] = 0;
    }
}

void setupPWM() {
    // PWM setup for servo control
    P1DIR |= BIT2; // P1.2 output
    P1SEL |= BIT2; // P1.2 select TA0.1
    TA0CCR0 = 20000 - 1; // 20ms period
    TA0CCTL1 = OUTMOD_7; // Reset/set mode
    TA0CTL = TASSEL_2 | MC_1 | TACLR; // SMCLK, up mode, clear TAR
}

void rotateServo(unsigned int angle) {
    if (angle > 180) angle = 180;
    unsigned int dutyCycle = 320 + (angle * (2620 - 320) / 180);
    TA0CCR1 = dutyCycle;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void) {
    if (P1IFG & BUTTON_7_PIN) {
        enteredPasscode[passcodeIndex++] = '7';
        P1IFG &= ~BUTTON_7_PIN; // Clear interrupt flag
    }
    else if (P1IFG & BUTTON_8_PIN) {
        enteredPasscode[passcodeIndex++] = '8';
        P1IFG &= ~BUTTON_8_PIN;
    }
    else if (P1IFG & BUTTON_9_PIN) {
        enteredPasscode[passcodeIndex++] = '9';
        P1IFG &= ~BUTTON_9_PIN;
    }
    updateDisplay();
    if (passcodeIndex == PASSCODE_LENGTH) {
        checkPasscode();
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2_ISR(void) {
    if (P2IFG & BUTTON_0_PIN) {
        enteredPasscode[passcodeIndex++] = '0';
        P2IFG &= ~BUTTON_0_PIN;
    }
    else if (P2IFG & BUTTON_1_PIN) {
        enteredPasscode[passcodeIndex++] = '1';
        P2IFG &= ~BUTTON_1_PIN;
    }
    else if (P2IFG & BUTTON_2_PIN) {
        enteredPasscode[passcodeIndex++] = '2';
        P2IFG &= ~BUTTON_2_PIN;
    }
    else if (P2IFG & BUTTON_3_PIN) {
        enteredPasscode[passcodeIndex++] = '3';
        P2IFG &= ~BUTTON_3_PIN;
    }
    else if (P2IFG & BUTTON_4_PIN) {
        enteredPasscode[passcodeIndex++] = '4';
        P2IFG &= ~BUTTON_4_PIN;
    }
    else if (P2IFG & BUTTON_5_PIN) {
        enteredPasscode[passcodeIndex++] = '5';
        P2IFG &= ~BUTTON_5_PIN;
    }
    else if (P2IFG & BUTTON_6_PIN) {
        enteredPasscode[passcodeIndex++] = '6';
        P2IFG &= ~BUTTON_6_PIN;
    }
    updateDisplay();
    if (passcodeIndex == PASSCODE_LENGTH) {
        checkPasscode();
    }
}