/*Программа должна напечатать на стандартный поток вывода свой PID, после чего перейти в режим ожидания сигналов. Программа должна обрабатывать сигнал SIGHUP. На каждый приход сигнала программа должна напечатать номер поступления сигнала (0, 1, 2) — каждый раз на отдельной строке. На шестой приход сигнала программа не должна ничего выводить, а просто завершиться с кодом завершения 0.

Таким образом, программа всегда должна выводить:
СВОЙ-PID
0
1
2
3
4


Стандартный ввод и стандартный вывод программы будут перенаправлены. Не забывайте выводить разделитель и сбрасывать буфер вывода. С другой стороны каналов находится другой процесс, который начнет свою работу как только получит pid процесса.

Вывод на стандартный поток вывода разместите в обработчике сигнала.

Вариант семантики сигналов (SysV или BSD), используемый функцией signal, неизвестен.*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
volatile sig_atomic_t count = 0;

void handle(int sig)
{
    if(count == 5) {
        _exit(0);
    }
    printf("%d\n", count++);
    fflush(stdout);
}
int
main(void)
{
    sigaction(SIGHUP, &(struct sigaction) {.sa_handler = handle, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        pause();
    }
    return 0;
}
