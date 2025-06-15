#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS_EXIT 0
#define FAIL_EXIT 1

int safe_mode(const char *mensagem, const char *remoto, const char *branch);
int normal_mode(const char *mensagem, const char *remoto, const char *branch);
void help_message();
int edit_commit(const char *mensagem, const char *remoto, const char *branch);

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("Uso:\n  gpush [-h|--help]\n");
        return FAIL_EXIT;
    }

    int modo_seguro = 0;
    int mensagem_index = 1;
    const char *mensagem = argv[mensagem_index];
    const char *remoto = (argc > mensagem_index + 1) ? argv[mensagem_index + 1] : "origin";
    const char *branch = (argc > mensagem_index + 2) ? argv[mensagem_index + 2] : "main";

    if (strncmp(argv[1], "--", 2) == 0)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            help_message();
            return SUCCESS_EXIT;
        }
        else if (strcmp(argv[1], "--safe") == 0)
        {
            modo_seguro = 1;
        }
        else if (strcmp(argv[1], "--no-safe") == 0)
        {
            modo_seguro = 0;
        }else if (strcmp(argv[1], "--edit") == 0)
        {
            mensagem_index = 3;
            int result_edit_commit = edit_commit(mensagem, remoto, branch);
            // return result_edit_commit;
        }
        else
        {
            printf("Flag desconhecida: %s\n", argv[1]);
            return FAIL_EXIT;
        }

        mensagem_index = 2;
    }
    else if (strncmp(argv[1], "-", 1) == 0)
    {
        if (strcmp(argv[1], "-h") == 0)
        {
            help_message();
            return SUCCESS_EXIT;
        }
    }

    if (argc <= mensagem_index)
    {
        printf("A mensagem do commit esta faltando.\n");
        return FAIL_EXIT;
    }


    printf("Modo: %s\n", modo_seguro ? "seguro" : "normal");
    printf("Mensagem: %s\n", mensagem);
    printf("Remoto: %s\n", remoto);
    printf("Branch: %s\n", branch);

    return modo_seguro ? safe_mode(mensagem, remoto, branch) : normal_mode(mensagem, remoto, branch);
}

int safe_mode(const char *mensagem, const char *remoto, const char *branch)
{
    char comando[600];

    char pull[256];
    snprintf(pull, sizeof(pull), "git pull %s %s", remoto, branch);
    int git_pull_return = system(pull);

    if (git_pull_return != SUCCESS_EXIT)
    {
        printf("⚠️ Conflitos detectados, resolva-os! ⚠️\n");
        return git_pull_return;
    }

    system("git add .");

    snprintf(comando, sizeof(comando), "git commit -m \"%s\"", mensagem);
    system(comando);

    char push[256];
    snprintf(push, sizeof(push), "git push %s %s", remoto, branch);
    system(push);

    return SUCCESS_EXIT;
}

int normal_mode(const char *mensagem, const char *remoto, const char *branch)
{
    char comando[600];

    system("git add .");

    snprintf(comando, sizeof(comando), "git commit -m \"%s\"", mensagem);
    system(comando);

    char push[256];
    snprintf(push, sizeof(push), "git push %s %s", remoto, branch);
    system(push);

    return SUCCESS_EXIT;
}

void help_message()
{
    printf("Uso:\n  gpush [opcoes(flags)] \"mensagem\" [comandos]\n");
    printf("\n  Opcoes:");
    printf("\n    --no-safe: nao atualiza o repositorio local (padrao)");
    printf("\n    --safe: atualiza o repositorio local");
    printf("\n    --edit: edita o ultimo commit e manda para o remoto");
}

int edit_commit(const char *mensagem, const char *remoto, const char *branch)
{
    char comando[300];

    snprintf(comando, sizeof(comando), "git commit -m \"%s\" --amend", mensagem);
    
    system(comando);

    char push_comando[50];

    snprintf(push_comando, sizeof(push_comando), "git push --force %s %s", remoto, branch);

    system(push_comando);

    return SUCCESS_EXIT;
}