# Gpush Tool

Essa ferramenta automatiza 4 comandos essenciais para um projeto em apenas 2 argumentos

> [!NOTE]
> Antes de tudo, se você não sabe o que é um commit, clique [aqui](./commit/)

### Instalação
```nginx
git clone https://github.com/Artemiz-TK/gpush-tool.git ~/gpush-tool
chmod +x ~/gpush-tool/install
~/gpush-tool/install
```

O que você vai ver:
```yaml
Preparando o ambiente...
Tudo pronto.
```

Após isso, vá para algum repositório git e faça o teste, mas primero, eu sugiro que adicione o diretório bin a variável PATH. Pra isso, segue abaixo o que cê tem que fazer

Vá para a sua home e abra o arquivo `.bashrc`, por exemplo
```bash
code ~/.bashrc # utilize o editor de sua escolha
```

Muito provavelmente esse arquivo vai tá vazio se você ainda nem criou. Copie tudo que estiver abaixo e cole no `.bashrc`
```bash
#!/bin/bash

export PATH="$PATH:$HOME/gpush-tool/bin"
```

Depois disso, atualize tudo

```bash
source ~/.bash_profile
```

### Como usar

Se você não sabe como usar, basta digitar no git esse comando

```nginx
gpush
```

A saída vai ser algo como
```yaml
Uso:
  gpush [-h|--help]
```

Então digite
```nginx
gpush -h # ou gpush --help
```

ou apenas digite logo o commit ue você quer adicionar no repositório

```nginx
gpush "Atualizando a cena"
```

Depois e só apertar `Enter`