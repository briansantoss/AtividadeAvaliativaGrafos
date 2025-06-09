# Instruções
As instruções a seguir irão partir do pressuposto que tem a ferramenta `Make` instalada em seu sistema.

Para poder rodar as aplicações basta entrar no diretório do projeto e executar o seguinte comando:

```bash
make
```

ou

```bash
make all
```
---
> [!IMPORTANT]
> Ainda é possível executar as aplicações sem a ferramenta previamente citada, basta compilar manualmente cada uma delas usando do compilador de sua preferência.
---
Após isso ele vai rodar as duas aplicações `main` que se econram nos diretórios `projeto1` e `projeto2`, respectivamente.

## Extra
Há também a possibilidade de executar cada uma delas separadamente, isso é feito através dos alvos `run` junto do número do projeto.

Por exemplo, para o projeto 1 pode ser feito o seguinte:

```bash
make run1
```

O mesmo pode ser feito para o segundo projeto.
