# PSE em Ação

## Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

Projeto acadêmico desenvolvido no curso de Bacharelado em Engenharia de Software da UniCesumar, em 2026. O projeto consiste em uma aplicação desenvolvida em linguagem C para auxiliar no planejamento, registro e acompanhamento de ações coletivas do Programa Saúde na Escola (PSE).

## Sobre o projeto

O PSE em Ação é uma aplicação executada em ambiente de terminal, desenvolvida em linguagem C. Seu objetivo é auxiliar profissionais das áreas de saúde e educação na organização e no acompanhamento de ações coletivas realizadas no ambiente escolar.

O sistema utiliza dados fictícios e informações coletivas, sem finalidade de registrar informações pessoais ou clínicas individuais dos estudantes.

## Funcionalidades

O sistema disponibiliza as seguintes funcionalidades:

- Cadastro de ações do Programa Saúde na Escola;
- Listagem das ações cadastradas;
- Pesquisa de ações por código, escola ou temática;
- Atualização da situação das ações;
- Registro da quantidade efetiva de participantes em ações realizadas;
- Geração de resumo geral das ações;
- Validação de entradas, códigos duplicados, campos obrigatórios, datas e quantidades.

As ações podem apresentar três situações: Planejada, Realizada ou Cancelada.

## Tecnologias utilizadas

- Linguagem C;
- Compilador GCC;
- Execução em ambiente de terminal;
- Estruturas de dados e arrays;
- Funções, estruturas condicionais e estruturas de repetição.

## Como executar

### 1. Obter o código-fonte

Clone o repositório:

```bash
git clone https://github.com/FelipeInacioMartins/PSE---em---Acao.git
```

Entre na pasta do projeto:

```bash
cd PSE---em---Acao
```

### 2. Compilar

Com o GCC instalado, execute:

```bash
gcc src/pse_em_acao.c -o pse_em_acao -Wall -Wextra -std=c11
```

### 3. Executar

No Windows (PowerShell):

```powershell
.\pse_em_acao.exe
```

No Linux:

```bash
./pse_em_acao
```

Após a execução, o menu principal será apresentado no terminal.

## Armazenamento e limitações

Os registros são armazenados temporariamente na memória do programa e são perdidos quando a aplicação é encerrada.

O sistema não possui interface gráfica, armazenamento permanente, edição ou exclusão de registros.

## Estrutura do projeto

```text
PSE---em---Acao/
├── .gitignore
├── README.md
├── src/
│   └── pse_em_acao.c
└── docs/
    ├── AEP - SEGUNDO SEMESTRE.pdf
    ├── README.md
    └── testes.md
```

## Documentação

Os materiais complementares do projeto estão disponíveis na pasta `docs`:

- [Documento acadêmico da AEP (PDF)](docs/AEP%20-%20SEGUNDO%20SEMESTRE.pdf)
- [Documentação complementar](docs/README.md)
- [Registro dos testes](docs/testes.md)

## Apresentação em vídeo

O vídeo demonstrativo apresenta o contexto do projeto, seus objetivos, os conceitos de Engenharia de Software utilizados e uma demonstração prática das funcionalidades implementadas.

[Assistir à apresentação do PSE em Ação no YouTube](https://youtu.be/BX5lWmM3Lj0)

## Integrantes

- Felipe Inácio Martins
- Alexia Maria da Silva Panaro
- Emanuel Lazarin Paião

## Instituição

**UniCesumar — Centro Universitário de Maringá**

Curso: Bacharelado em Engenharia de Software

Ano: 2026

## Status do projeto

Projeto acadêmico concluído.
