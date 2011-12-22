#include "hw.h"
#include "pc.h"
#include "boards.h"
#include "sysemu.h"
#include "loader.h"
#include "elf.h"
#define UNO_FLASH_SIZE_MAX
#define UNO_SRAM_BASE
#define UNO SRAM_SIZE
#define UNO_RAM_SIZE
void pic_info(Monitor *mom)
{
}

void irq_info(Monitor *mom)
{
}

/*int ELFparser(int offset, int number, FILE *fp)
{
    int power = 1, result = 0, i;    
    fseek(fp, offset, SEEK_SET);
    for(i = 0; i < number; i++) 
    {
        unsigned char temp;
        fread(&temp, 1, 1, fp);
        result+=power * (int)temp;
        power *= (16 * 16);
    }
    return result;
}*/

static int  load_kernel(const char *filename, target_phys_addr_t addr)
{
    FILE *fp;
    int kernel_size, text_offset=0, ELFhead_offset=0;
    int text_size=0;
    int power=1;
    int i, ret;



/*    Elf32_Ehdr elfinfo;
    Elf32_Phdr text;
    Elf32_Phdr data;
    Elf32_Phdr bss;
    fp = fopen(filename, "rb");
    if(!fp) return -1; 

    
    elfinfo.e_ehsize = ELFparser(40, 2, fp);  // ELF header offset 
    printf("ELF header offset:0x%x (%d bytes)\n", elfinfo.e_ehsize, elfinfo.e_ehsize);
    elfinfo.e_machine = ELFparser(18, 2, fp); // The required architecture
    printf("ELF Machine type:0x%x (%d bytes)\n", elfinfo.e_machine, elfinfo.e_machine);
    elfinfo.e_phentsize = ELFparser(42, 2, fp);  // Program header size
    printf("Program header size:0x%x (%d bytes)\n", elfinfo.e_phentsize, elfinfo.e_phentsize);
    elfinfo.e_phnum = ELFparser(44, 2, fp);  // Number of program header
    printf("Number of program header:0x%x (Number of %d)\n", elfinfo.e_phnum, elfinfo.e_phnum);

    for(i = 0; i < elfinfo.e_phnum; i++)
    {
        int ProgramOffset = elfinfo.e_ehsize + i * elfinfo.e_phentsize;
        if(i == 0) //text section
        {
            text.p_offset  = ELFparser( ProgramOffset +  4, 4, fp);  // Segment file offset
            text.p_vaddr   = ELFparser( ProgramOffset +  8, 4, fp);  // Segment virtual address 
            text.p_paddr   = ELFparser( ProgramOffset + 12, 4, fp);  // Segment physical address
            text.p_filesz  = ELFparser( ProgramOffset + 16, 4, fp);  // Segment size in file
            text.p_memsz   = ELFparser( ProgramOffset + 20, 4, fp);  // Segment size in memory
        }
        else if(i == 1 && elfinfo.e_phnum > 2) //data section
        {
            data.p_offset  = ELFparser( ProgramOffset +  4, 4, fp);  // Segment file offset
            data.p_vaddr   = ELFparser( ProgramOffset +  8, 4, fp);  // Segment virtual address 
            data.p_paddr   = ELFparser( ProgramOffset + 12, 4, fp);  // Segment physical address
            data.p_filesz  = ELFparser( ProgramOffset + 16, 4, fp);  // Segment size in file
            data.p_memsz   = ELFparser( ProgramOffset + 20, 4, fp);  // Segment size in memory
        }
        else //.bss section
        {
            bss.p_offset  = ELFparser( ProgramOffset +  4, 4, fp);  // Segment file offset
            bss.p_vaddr   = ELFparser( ProgramOffset +  8, 4, fp);  // Segment virtual address 
            bss.p_paddr   = ELFparser( ProgramOffset + 12, 4, fp);  // Segment physical address
            bss.p_filesz  = ELFparser( ProgramOffset + 16, 4, fp);  // Segment size in file
            bss.p_memsz   = ELFparser( ProgramOffset + 20, 4, fp);  // Segment size in memory
        }
    

    }
    printf("Text:\n");
    printf("Segment file offset      :0x%7x (Number of %7d)\n", text.p_offset, text.p_offset);    
    printf("Segment virtual address  :0x%7x (Number of %7d)\n", text.p_vaddr, text.p_vaddr);    
    printf("Segment physical address :0x%7x (Number of %7d)\n", text.p_paddr, text.p_paddr);    
    printf("Segment size in file     :0x%7x (Number of %7d)\n", text.p_filesz, text.p_filesz);    
    printf("Segment size in memory   :0x%7x (Number of %7d)\n", text.p_memsz, text.p_memsz);    
    if(elfinfo.e_phnum > 2)
    {
        printf("Data:\n");
        printf("Segment file offset      :0x%7x (Number of %7d)\n", data.p_offset, data.p_offset);    
        printf("Segment virtual address  :0x%7x (Number of %7d)\n", data.p_vaddr, data.p_vaddr);    
        printf("Segment physical address :0x%7x (Number of %7d)\n", data.p_paddr, data.p_paddr);    
        printf("Segment size in file     :0x%7x (Number of %7d)\n", data.p_filesz, data.p_filesz);    
        printf("Segment size in memory   :0x%7x (Number of %7d)\n", data.p_memsz, data.p_memsz);    
    }
    printf("bss:\n");
    printf("Segment file offset      :0x%7x (Number of %7d)\n", bss.p_offset, bss.p_offset);    
    printf("Segment virtual address  :0x%7x (Number of %7d)\n", bss.p_vaddr, bss.p_vaddr);    
    printf("Segment physical address :0x%7x (Number of %7d)\n", bss.p_paddr, bss.p_paddr);    
    printf("Segment size in file     :0x%7x (Number of %7d)\n", bss.p_filesz, bss.p_filesz);    
    printf("Segment size in memory   :0x%7x (Number of %7d)\n", bss.p_memsz, bss.p_memsz);    */

    printf("Done \n");
    exit(1);
    return ret;
}

/* Arduino Uno hardware initialisation */
static void arduino_atmega328_init(ram_addr_t ram_size, const char *boot_device,
                                  const char *kernel_filename, const char *kernel_cmdline,
                                  const char *initrd_filename, const char *cpu_model)
{
    int kernel_size;
    int big_endian;
    uint64_t entry;
    uint64_t lowaddr;
    ram_addr_t ram_offset;
    CPUState *env;
    
    /* init CPUs */
    if(cpu_model == NULL) {
        cpu_model = "atmega328";
    }

    env = cpu_init(cpu_model);
    if(!env) {
        fprintf(stderr, "Unable to find CPU definition");
        exit(1);
    }

    //XXX reset/shutdown handler if need

    /* allocate RAM */
    if(ram_size > (256 << 20)) {
        fprintf(stderr,
                "qemu: Too much moemory for this machine: %d MB, maximum 256 MB\n",
                ((unsigned int)ram_size / (1 << 20)));
        exit(1);
    }
    ram_offset = qemu_ram_alloc(NULL, "integrator.ram", ram_size);
    
    cpu_register_physical_memory(0, ram_size, ram_offset | IO_MEM_RAM);

    /* load kernel*/
#ifdef TARGET_WORDS_BIGENDIAN
    big_endian = 1;
#else
    big_endian = 0;
#endif

    kernel_size = load_elf (kernel_filename, NULL, NULL, &entry,
                             NULL, NULL, big_endian, ELF_MACHINE, 1);
    if (kernel_size < 0) {
        fprintf(stderr, "qemu: could not load kernel '%s'\n",
                kernel_filename);
        exit(1);
    }   

    if (lowaddr == 0) {
    int x = ldl_phys(0);
    uint32_t pc = ldl_phys(4);
    printf("KUKU pc = %d\n",pc);                                                                                                         
    } else {
    printf("KAKA\n");
    int pc = entry;
    }

    //kernel_size = load_kernel(kernel_filename, 0x0);
    printf("kernel size is %d \n", kernel_size);
    printf("lowaddr = %x \n",&lowaddr);
    printf("entry = %d \n",entry);

    exit(0);

    if(kernel_size < 0) {
        fprintf(stderr, "qemu: could not load kernel '%s' \n", kernel_filename);
        exit(1);
    }
    else {
        env->PC = 0x0;
    }
}

static QEMUMachine arduino_machine = {
    .name = "arduino uno",
    .desc = "atmega328",
    .init = arduino_atmega328_init,
    .is_default = 1,
};

static void arduino_machine_init(void)
{
    qemu_register_machine(&arduino_machine);
}

machine_init(arduino_machine_init);
