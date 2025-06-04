# Gpush Tool

Essa ferramenta automatiza 4 comandos essenciais para um projeto em apenas 2 argumentos

> [!NOTE]
> Antes de tudo, se você não sabe o que é um commit, clique [aqui](./COMMIT.md)

### Instalação
```nginx
git clone https://github.com/Artemiz-TK/gpush-tool.git ~/
cd ~/gpush-tool
chmod +x installation
./installation
```

O que você vai ver:
```yaml
Preparando o ambiente...
Tudo pronto.
```

após isso, vá para algum repositório git e faça o teste

### Como usar

Se você não sabe como usar, basta digitar no git esse comando

```nginx
gpush
```

A saída vai ser algo como
```yaml
O commit nao pode estar vazio. Digite algum valor para o commit.
Exemplo:

gpush "primeiro commit"
```

ou apenas digite logo o commit ue você quer adicionar no repositório

```nginx
gpush "Atualizando a cena"
```

Depois e só apertar `Enter`