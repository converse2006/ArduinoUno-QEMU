#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "cpu.h"
#include "exec-all.h"
#include "disas.h"
#include "tcg-op.h"
#include "qemu-common.h"

#include "helpers.h"

static TCGv_ptr cpu_env;
#include "gen-icount.h"

typedef struct DisasContext {
    target_ulong pc; /* pc = eip + cs_base */

} DisasContext;

static inline void gen_intermediate_code_internal(CPUState *env, 
                                                  struct TranslationBlock *tb,
                                                  int search_pc)
{
    DisasContext ctx;
}

void cpu_dump_state(CPUState *env, FILE *f,
                    int (*cpu_fprintf)(FILE *f, const char *fmt, ...),
                    int flags)
{
    cpu_fprintf(f, "PC=0x%08x\n", env->PC); //PCIE is control register
}

void gen_intermediate_code (CPUState *env, struct TranslationBlock *tb)
{
    gen_intermediate_code_internal(env, tb, 0);
}

void gen_intermediate_code_pc (CPUState *env, struct TranslationBlock *tb)
{
    gen_intermediate_code_internal(env, tb, 1);
}

void gen_pc_load(CPUState *env, TranslationBlock *tb,
                unsigned long searched_pc, int pc_pos, void *puc)
{
    //FIXME The "real" atmega328 PC register is need to find out!
    env->PC = gen_opc_pc[pc_pos];
}
