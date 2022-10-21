#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
int
main(int argc, char *argv[])
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    int pid;
    const char p_name[] = "smain2";
    const char f_name[] = "smain2.c";
    const char path[] = "./smain2";
    FILE *file;
    file = fopen("smain2.c", "w");
    fprintf(file,"#include <stdio.h>\n#include <stdlib.h>\n int main(int x)\n { int reject = 1; ");
    fprintf(file,"int summon = 2; int disqualify = 3; int answ = -1;\nwhile((scanf(\"%%d\", &x)) > 0) {\n answ = ");
    for (int i = 1; i < argc; i++) {
        fprintf(file, "%s ", argv[i]);
    }
    fprintf(file, ";\n if(answ == 1) printf(\"reject\\n\");\nif(answ == 2) printf(\"summon\\n\");\n");
    fprintf(file,"if(answ == 3) printf(\"disqualify\\n\");\n}return 0;\n}");
    if(!(pid = fork())) {
        execlp("gcc","gcc",f_name, "-o", p_name, NULL);
    }
    wait(NULL);
    execl(path, p_name, NULL);
    fclose(file);
    return 0;
}
