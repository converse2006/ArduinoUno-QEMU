#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "exec-all.h"
#include "gdbstub.h"
#include "helpers.h"
#include "qemu-common.h"
#include "host-utils.h"

struct atmel_cpu_t {
    uint32_t id;
    const char *name;
};

static const struct atmel_cpu_t atmel_cpu_names[] = {
    { ATMEL_CPUID_ATMEGA328, "atmega328"},
    { 0, NULL}
};

void atmel_cpu_list(FILE *f, int (*cpu_fprintf)(FILE *f, const char *fmt, ...))
{
    int i;

    (*cpu_fprintf)(f, "Available CPUs:\n");
    for (i = 0; atmel_cpu_names[i].name;i++) {
        (*cpu_fprintf)(f, " %s\n", atmel_cpu_names[i].name);
    }
}

CPUATMELState *cpu_atmel_init(const char *cpu_model)
{
    CPUATMELState *env;

    env =qemu_mallocz(sizeof(CPUATMELState));
    cpu_exec_init(env);

    return env;
}

target_phys_addr_t cpu_get_phys_page_debug(CPUState *env, target_ulong addr)
{
    return addr;
}

//FIXME Make sure the TLB work flow is correct!!!
int cpu_atmel_handle_mmu_fault (CPUState *env, target_ulong address,
                              int access_type, int mmu_idx, int is_softmmu)
{
    uint32_t phys_addr;
    int prot;

    /* MMU/MPU disabled.  */
    phys_addr = address;
    prot = PAGE_READ | PAGE_WRITE;
    /* Map a signle [sub]page.  */
    phys_addr &= ~(uint32_t)0x3ff;
    address &= ~(uint32_t)0x3ff;
    tlb_set_page(env, address, phys_addr, prot, mmu_idx, is_softmmu);
    return 0;
}
