#include <xinu.h>

void sndA(sid32 s1, sid32 s2)
{
    wait(s1);
    kprintf("A\n");
    signal(s2);
}

void sndB(sid32 s1, sid32 s2)
{
    wait(s2);
    kprintf("B\n");
    signal(s1);
}

int saldo = 0;
int setor = 10;

void sndA_mutex(sid32 m1)
{
    wait(m1);
    saldo = saldo + setor;  
    kprintf("Saldo A: %d\n", saldo);
    signal(m1);
}

void sndB_mutex(sid32 m1)
{
    wait(m1);
    saldo = saldo + setor;  
    kprintf("Saldo B: %d\n", saldo);
    signal(m1);
}

void semaphore(void)
{
    sid32 s1, s2;
    sid32 m1;

    kprintf("\nOutput Signaling\n");

    s1 = semcreate(1); 
    s2 = semcreate(0); 

    resume(create(sndA, 1024, 20, "process A", 2, s1, s2));
    resume(create(sndB, 1024, 20, "process B", 2, s1, s2));

    sleep(2);

    kprintf("\nOutput Mutex\n");

    m1 = semcreate(1); 

    resume(create(sndA_mutex, 1024, 20, "process A", 1, m1));
    resume(create(sndB_mutex, 1024, 20, "process B", 1, m1));
}
