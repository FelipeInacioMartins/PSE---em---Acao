# Registro de Testes — PSE em Ação

## 1. Objetivo

Este documento registra os testes realizados no sistema PSE em Ação, desenvolvido em linguagem C. O objetivo é verificar o funcionamento das funcionalidades, a validação das entradas e a consistência das informações apresentadas.

## 2. Ambiente de testes

- **Linguagem:** C
- **Compilador:** GCC
- **Padrão utilizado:** C11
- **Opções de compilação:** `-Wall -Wextra -std=c11`
- **Execução:** Terminal
- **Armazenamento:** Memória durante a execução do programa.

## 3. Casos de teste

| ID | Funcionalidade | Entrada ou procedimento | Resultado obtido |
|---|---|---|---|
| CT01 | Compilação | Compilar com GCC e opções de aviso habilitadas | Aprovado: sem erros ou avisos |
| CT02 | Menu principal | Informar opção 999 | Aprovado: opção inválida rejeitada |
| CT03 | Validação numérica | Informar números extremamente grandes | Aprovado: entrada inválida rejeitada |
| CT04 | Cadastro | Cadastrar ação com dados válidos | Aprovado: ação cadastrada |
| CT05 | Código duplicado | Cadastrar código já existente | Aprovado: duplicidade rejeitada |
| CT06 | Listagem | Consultar todas as ações cadastradas | Aprovado: informações exibidas corretamente |
| CT07 | Consulta | Pesquisar ação pelo código | Aprovado: registro localizado |
| CT08 | Consulta | Pesquisar código inexistente | Aprovado: mensagem de ausência de registro |
| CT09 | Atualização | Alterar situação para realizada | Aprovado: situação atualizada |
| CT10 | Atualização | Alterar situação para cancelada | Aprovado: situação atualizada e participantes efetivos zerados |
| CT11 | Relatório | Gerar relatório com ações em diferentes situações | Aprovado: quantidades e percentual calculados corretamente |
| CT12 | Data | Informar data inválida, como 24/20/2026 | Aprovado: data rejeitada |
| CT13 | Situação inicial | Cadastrar ação como planejada | Aprovado: participantes efetivos iniciados em zero |
| CT14 | Situação inicial | Cadastrar ação como realizada | Aprovado: solicitada a quantidade efetiva de participantes |
| CT15 | Situação inicial | Cadastrar ação como cancelada | Aprovado: participantes efetivos iniciados em zero |
| CT16 | Situação inicial | Informar opções 9, -1 e uma letra | Aprovado: entradas inválidas rejeitadas |
| CT17 | Quantidade prevista | Informar quantidade negativa | Aprovado: valor negativo rejeitado |
| CT18 | Quantidade efetiva | Informar quantidade maior que a prevista | Aprovado: valor aceito e registrado |

## 4. Exemplo de cálculo do relatório

Durante um dos testes, foi cadastrada uma ação com:

- Participantes previstos: 33
- Participantes efetivos: 22
- Situação: realizada

O sistema apresentou o percentual de participação de 66,67%, conforme o cálculo:

\[
\frac{22}{33}\times 100 = 66,67\%
\]

O resultado foi considerado correto.

## 5. Considerações sobre os testes

Os testes realizados demonstraram o funcionamento das principais funcionalidades do sistema, incluindo cadastro, listagem, consulta, atualização de situação e geração de relatório.

Também foram verificadas validações de entradas, como números inválidos, códigos duplicados, datas incorretas, opções inexistentes e quantidades negativas.

O sistema mantém os registros apenas durante a execução, não possuindo persistência em arquivos ou banco de dados.

## 6. Testes pendentes

- Verificar especificamente a rejeição de participantes efetivos negativos durante o cadastro inicial de uma ação realizada.
- Realizar uma última conferência geral das funcionalidades antes da entrega.
