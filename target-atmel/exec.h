#include "config.h"                                                                                                           
#include "dyngen-exec.h"

register struct CPUATMELState *env asm(AREG0);

#include "cpu.h"
#include "exec-all.h"

static inline void env_to_regs(void)
{
}

static inline void regs_to_env(void)
{
}

static inline int cpu_has_work(CPUState *env)
{
        return 0;
}

static inline int cpu_halted(CPUState *env)
{
        if (!env->halted)
                    return 0;
            return EXCP_HALTED;
}

#if !defined(CONFIG_USER_ONLY)
#include "softmmu_exec.h"
#endif

void raise_exception(int);

