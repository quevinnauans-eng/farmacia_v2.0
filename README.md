# Sistema de Controle de Farmácia

Sistema desenvolvido em linguagem C para gerenciamento de clientes, remédios e vendas em uma farmácia.

O projeto foi desenvolvido durante o início da disciplina de Estrutura de Dados no IFBA Campus Irecê, com foco em prática de modularização, manipulação de arquivos, alocação dinâmica de memória e relacionamento entre entidades.

---

## Funcionalidades

### Clientes
- Cadastrar clientes
- Listar clientes
- Buscar cliente por nome
- Buscar cliente por código
- Atualizar dados do cliente
- Remover cliente
- Salvar dados em arquivo
- Carregar dados do arquivo

### Remédios
- Cadastrar remédios
- Listar estoque
- Buscar remédios
- Atualizar dados
- Remover remédios
- Listar estoque abaixo
- Salvar dados em arquivo
- Carregar dados do arquivo

### Vendas
- Registrar vendas
- Relacionar clientes e remédios
- Registrar múltiplos itens em uma venda
- Atualizar estoque após venda
- Buscar vendas
- Listar vendas
- Salvar vendas em arquivo
- Carregar vendas do arquivo

---

## Conceitos utilizados

- Linguagem C
- Modularização
- Arquivos `.c` e `.h`
- Structs
- Ponteiros
- Alocação dinâmica de memória (`malloc` e `realloc`)
- Manipulação de arquivos `.txt`
- Relacionamento entre entidades
- Vetores dinâmicos

---

## Estrutura do Projeto

```text
Projeto/
│
├── src/        -> arquivos .c
├── include/    -> arquivos .h
├── data/       -> arquivos .txt
├── bin/        -> executável do sistema
└── README.md
```

---

## Como executar

### 1. Compile o projeto utilizando GCC

```bash
gcc src/*.c -Iinclude -o bin/sistema
```

### 2. Execute o programa

#### Linux/macOS
```bash
./bin/sistema
```

#### Windows
```bash
bin\sistema.exe
```

---

## Objetivo do Projeto

O objetivo do projeto foi praticar conceitos fundamentais da linguagem C e da disciplina de Estrutura de Dados, incluindo manipulação de memória, modularização e persistência de dados utilizando arquivos.

---

## Autor

Projeto desenvolvido por Quevin Nauan Silva.