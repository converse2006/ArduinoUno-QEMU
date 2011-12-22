#ifndef CPU_ATMEL_H 
#define CPU_ATMEL_H

#define TARGET_LONG_BITS 32
#define ELF_MACHINE EM_AVR

#define CPUState struct CPUATMELState

#include "cpu-defs.h"
#include "softfloat.h"

#define TARGET_PHYS_ADDR_SPACE_BITS 32
#define TARGET_VIRT_ADDR_SPACE_BITS 32

#define NB_MMU_MODES 2
//FIXME TODO: Figure out Atmega328 control register
typedef struct CPUATMELState {
    target_ulong gpr[32]; //32 * 8-bit general purpose working registers
    /* last six register can be compose as three 16-bit indirect address register X-, Y-, Z-*/
    uint32_t AMR;
    uint32_t CSR;
    uint32_t GFPGFR;
    uint32_t ICR;
    uint32_t IER;
    uint32_t IFR;
    uint32_t IRP;
    uint32_t ISR;
    uint32_t ISTP;
    uint32_t NRP;
    uint32_t PC;   //Program Counter
    struct SREG {  //Status Register
        unsigned int C;    //Carry Flag
        unsigned int Z;    //Zero Flag
        unsigned int N;    //Negative Flag
        unsigned int V;    //Two's complement overflow indicator
        unsigned int S;    //N (+) V, For signed tests
        unsigned int H;    //Half Carry Flag
        unsigned int T;    //Transfer bit used by BLD and BST instruction
        unsigned int I;    //Global Interrupt Enable/Disable Flag
    } SREG;

    CPU_COMMON

} CPUATMELState;

#define ATMEL_CPUID_ATMEGA328   0x32800000
#define ATMEL_CPUID_ANY         0xffffffff

void atmel_cpu_list(FILE *f, int (*cpu_fprintf)(FILE *f, const char *fmt, ...));
CPUATMELState *cpu_atmel_init(const char *cpu_model);
int cpu_atmel_exec(CPUATMELState *s);
int cpu_atmel_handle_mmu_fault (CPUATMELState *env, target_ulong address, int rw, int mmu_idx, int is_softmmu);
#define TARGET_PAGE_BITS 10

#define cpu_init cpu_atmel_init
#define cpu_exec cpu_atmel_exec
#define cpu_gen_code cpu_atmel_gen_code
#define cpu_list atmel_cpu_list

/* MMU modes definitions */
#define MMU_MODE0_SUFFIX _nommu
#define MMU_MODE1_SUFFIX _kernel
#define MMU_MODE2_SUFFIX _user
static inline int cpu_mmu_index (CPUState *env)
{
    return 0;
}

#include "cpu-all.h"
#include "exec-all.h"

static inline void cpu_pc_from_tb(CPUState *env, TranslationBlock *tb)
{
    env->PC = tb->pc;
}

static inline void cpu_get_tb_cpu_state(CPUState *env, target_ulong *pc,
                                        target_ulong *cs_base, int *flags)
{
    *pc = env->PC;
    *cs_base = 0;
    *flags = env->CSR;
}

#endif
