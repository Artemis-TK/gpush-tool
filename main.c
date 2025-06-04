#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS_EXIT 0
#define FAIL_EXIT 1

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("O commit nao pode estar vazio. Digite algum valor para o commit.\nExemplo:\n\ngpush \"primeiro commit\"\n");
        return FAIL_EXIT;
    }

    char mensagem[512] = {0};
    for (int i = 1; i < argc; i++)
    {
        strcat(mensagem, argv[i]);
        if (i < argc - 1)
            strcat(mensagem, " ");
    }

    char comando[600];
    snprintf(comando, sizeof(comando), "git commit -m %s", mensagem);

    int git_pull_return = system("git pull origin main");

    if (git_pull_return != SUCCESS_EXIT)
    {
        printf("⚠️Possivelmente houve conflitos, resolva-os!⚠️\n");
        return EXIT_FAILURE;
    }
    system("git add .");
    system(comando);
    system("git push origin main");

    return SUCCESS_EXIT;
}
