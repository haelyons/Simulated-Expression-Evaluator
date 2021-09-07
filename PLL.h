// Pre-processor Directives Section
// Constant declarations to access port register addresses using symbolic names

//PLL related Defines
#define SYSCTL_RIS_R          (*((volatile unsigned long *)0x400FE050))
#define SYSCTL_RCC_R          (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R         (*((volatile unsigned long *)0x400FE070))

//SysTick related Defines
#define NVIC_ST_CTRL_R        (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R     (*((volatile unsigned long *)0xE000E018))

// GPIO Run Mode Clock Gating Control Register
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))

// GPIO Peripheral Ready Register
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))


// Function Prototypes
void SysTick_Init(void);
void PLL_Init(void);
void SysTick_Wait(unsigned long delay);
