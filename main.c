#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS_EXIT 0
#define FAIL_EXIT 1
#define MAX_COMMAND_LEN 1024

bool execute_command(const char *command)
{
    printf("Executando: %s\n", command);
    int result = system(command);
    if (result != SUCCESS_EXIT)
    {
        fprintf(stderr, "Erro ao executar comando: %s\n", command);
    }
    return result == SUCCESS_EXIT;
}

int safe_mode(const char *mensagem, const char *remoto, const char *branch);
int normal_mode(const char *mensagem, const char *remoto, const char *branch);
void help_message();
int edit_commit(const char *mensagem, const char *remoto, const char *branch);

int main(int argc, const char *argv[])
{
    bool modo_seguro = false;
    bool modo_edit = false;
    bool show_help = false;
    const char *mensagem = NULL;
    const char *remoto = "origin";
    const char *branch = "main";

    int mensagem_index = -1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--safe") == 0) {
            modo_seguro = true;
        } 
        else if (strcmp(argv[i], "--no-safe") == 0) {
            modo_seguro = false;
        }
        else if (strcmp(argv[i], "--edit") == 0) {
            modo_edit = true;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            show_help = true;
        }
        else if (mensagem_index == -1 && argv[i][0] != '-') {
            mensagem_index = i;
        }
    }

    if (mensagem_index != -1) {
        mensagem = argv[mensagem_index];
        
        if (argc > mensagem_index + 1) {
            remoto = argv[mensagem_index + 1];
        }
        
        if (argc > mensagem_index + 2) {
            branch = argv[mensagem_index + 2];
        }
    }

    if (show_help)
    {
        help_message();
        return SUCCESS_EXIT;
    }

    if (mensagem == NULL && !modo_edit)
    {
        fprintf(stderr, "Erro: Mensagem do commit ausente\n");
        help_message();
        return FAIL_EXIT;
    }

    if (modo_edit)
    {
        return edit_commit(mensagem ? mensagem : "Commit atualizado", remoto, branch);
    }

    printf("Modo: %s\n", modo_seguro ? "seguro" : "normal");
    printf("Mensagem: %s\n", mensagem);
    printf("Remoto: %s\n", remoto);
    printf("Branch: %s\n", branch);

    return modo_seguro ? safe_mode(mensagem, remoto, branch) : normal_mode(mensagem, remoto, branch);
}

int safe_mode(const char *mensagem, const char *remoto, const char *branch)
{
    char command[MAX_COMMAND_LEN];

    snprintf(command, sizeof(command), "git pull %s %s", remoto, branch);
    if (!execute_command(command))
    {
        fprintf(stderr, "Conflitos detectados! Resolva antes de continuar.\n");
        return FAIL_EXIT;
    }

    if (!execute_command("git add ."))
        return FAIL_EXIT;

    snprintf(command, sizeof(command), "git commit -m \"%s\"", mensagem);
    if (!execute_command(command))
        return FAIL_EXIT;

    snprintf(command, sizeof(command), "git push %s %s", remoto, branch);
    if (!execute_command(command))
        return FAIL_EXIT;

    return SUCCESS_EXIT;
}

int normal_mode(const char *mensagem, const char *remoto, const char *branch)
{
    char command[MAX_COMMAND_LEN];

    if (!execute_command("git add ."))
        return FAIL_EXIT;

    snprintf(command, sizeof(command), "git commit -m \"%s\"", mensagem);
    if (!execute_command(command))
        return FAIL_EXIT;

    snprintf(command, sizeof(command), "git push %s %s", remoto, branch);
    if (!execute_command(command))
        return FAIL_EXIT;

    return SUCCESS_EXIT;
}

int edit_commit(const char *mensagem, const char *remoto, const char *branch)
{
    char command[MAX_COMMAND_LEN];

    snprintf(command, sizeof(command), "git commit --amend -m \"%s\"", mensagem);
    if (!execute_command(command))
        return FAIL_EXIT;

    snprintf(command, sizeof(command), "git push --force %s %s", remoto, branch);
    if (!execute_command(command))
        return FAIL_EXIT;

    return SUCCESS_EXIT;
}

void help_message()
{
    printf("Uso: gpush [opcoes] \"mensagem\" [argumentos]\n\n");
    printf("    Opções:\n");
    printf("        --safe      Atualiza o repositório local antes de enviar (recomendado)\n");
    printf("        --no-safe   Envia alterações sem atualizar local\n");
    printf("        --edit      Edita o último commit e força envio\n");
    printf("        -h, --help  Mostra esta ajuda\n\n");
    printf("    Argumentos:\n");
    printf("         Mensagem    Mensagem do commit (obrigatória)\n");
    printf("         Remoto      Nome do repositório remoto (padrão: origin)\n");
    printf("         Branch      Nome da branch (padrão: main)\n");
}