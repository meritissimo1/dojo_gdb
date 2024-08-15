# DOJO - GDB / VALGRIND

## O que faremos?
Esse dojo funcionará em duas partes: <br>
1. Já ouviu falar de Capture the Flag? Temos 5 executáveis compactados em arquivos .zip protegidos com senha. Todos são programas diferentes que escondem uma flag que pode ser encontrada dentro ou no retorno da função `rand_string()`. Se a flag estiver errada o programa imprimirá `Fail`, se estiver correta imprimirá `Boua!`. Seu objetivo é encontrar no código a flag escondida usando o GDB. Essa flag será a senha para o próximo desafio!

	A senha para o primeiro desafio é `gdb`.

2. Alguns executáveis estão vazando memória! Usem o Valgrind para achar e consertar todos os leaks dos programas.

## Bônus
Temos um problema com o Ctrl-D. Consegue consertar?

## Comandos úteis:
- Abrir um arquivo zipado com senha:
	<br>```unzip -P "<senha>" <nome do arquivo>```

- GDB:
	<br>```gdb --tui ./<arquivo>```

- Valgrind:
	<br>```valgrind --leak-check=full --show-leak-kinds=all ./<arquivo>```

- Compilação com símbolos de debug (útil para o Valgrind): <br>
	`clang -g3 <arquivo>.c`

- Compilar um desafio: <br>
	`make -C libft` <br>
  	`clang -g3 <desafio>.c src/rand<numero do desafio>.c libft/libft.a`



# Bonus Content 

Neste conteúdo bônus, vou mostrar como usar o [GDB](https://www.sourceware.org/gdb/) e o [Valgrind](https://valgrind.org/) juntos, utilizando o [vgdb](https://valgrind.org/docs/manual/manual-core-adv.html#manual-core-adv.vgdb), um programa que serve como intermediário entre o Valgrind e o GDB, com o objetivo de encontrar erros no código com mais facilidade e acurácia.

Pra exemplificar, vamos usar um código em C que possui um erro de condicional jump na linha 13, causado pela desreferenciação de um ponteiro não inicializado :

```C
#include <stdio.h>
#include <stdlib.h>

int main( void )
{
    int *ptr;
    
    ptr = malloc(sizeof(int));

    // Descomentar a próxima linha resolve o erro de condicional jump
    // *ptr = 42;

    if (*ptr > 5)  // <= condicional jump
        printf("Valor maior que 5\n");
    else
        printf("Valor menor ou igual a 5\n");
    free(ptr);
    return (0);
}
```

Vamos compilar o nosso programa usando o gcc e a flag -g, que é necessária para ativar as informações de depuração (ty DWARF):

` gcc -g condicional_jump.c -o cj`

Ao rodar o valgrind ``valgrind ./cj`` , o seguinte erro aparece:

```
meritissimo1@fedora:~/m1/dojo_gdb$ valgrind ./cj
==18000== Memcheck, a memory error detector
==18000== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==18000== Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
==18000== Command: ./cj
==18000== 
==18000== Conditional jump or move depends on uninitialised value(s)
==18000==    at 0x401165: main (test.c:13)
==18000== 
Valor menor ou igual a 5
==18000== 
==18000== HEAP SUMMARY:
==18000==     in use at exit: 0 bytes in 0 blocks
==18000==   total heap usage: 2 allocs, 2 frees, 1,032 bytes allocated
==18000== 
==18000== All heap blocks were freed -- no leaks are possible
==18000== 
==18000== Use --track-origins=yes to see where uninitialised values come from
==18000== For lists of detected and suppressed errors, rerun with: -s
==18000== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0) 
```
Agora vamos ver como isso fica usando o GDB e o Valgrind juntos.

Primeiro, vamos abrir dois terminais: em um deles, executaremos o GDB, e no outro, o Valgrind. Isso é necessário porque ambos serão processos distintos, mas se comunicarão através de [UNIX SIGNALS](https://www.man7.org/linux/man-pages/man7/signal.7.html) 

No terminal onde o Valgrind será executado, vamos usar a opção `--vgdb-error=0`. Ao executar com `--vgdb-error=n`, o Valgrind espera que ocorram _n_ erros antes de pausar e aguardar uma conexão do GDB. Como estamos passando `n=0`, a opção `--vgdb-error=0` faz com que o Valgrind pause antes de executar qualquer instrução.

``` 
meritissimo1@fedora:~/m1/dojo_gdb$ valgrind --vgdb-error=0 ./cj
==18000== Memcheck, a memory error detector
==18000== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==18000== Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
==18000== Command: ./cj
==18000== 
==18000== (action at startup) vgdb me ... 
==18000== 
==18000== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==18000==   /path/to/gdb ./cj
==18000== and then give GDB the following command
==18000==   target remote | /usr/libexec/valgrind/../../bin/vgdb --pid=18000
==18000== --pid is optional if only one valgrind process is running

```
Note que o próprio Valgrind já nos dá uma instrução do que fazer. No outro terminal, execute o GDB como indicado, adicionando o `--tui` pra tudo ficar mais boninto :D.

`gdb --tui cj`

Após abrir o GDB, você verá a mensagem `--Type <RET> for more, q to quit, c to continue without paging--`. Basta digitar ***c*** e pressionar Enter.

Agora, dentro do GDB, execute o comando:

``target remote | vgdb --pid=18000 `` 

Perceba que o pid do processo do Valgrind altera sempre que executamos ele, e esse número sempre estará no início de cada linha de informação do Valgrind.

Após executar o comando acima, digite `continue` ou `c` no GDB para que ele execute o programa completamente. Nesta etapa, o GDB ficará "escutando" todas as informações do Valgrind. Como conectamos ambos via PID, assim que o Valgrind encontrar um erro, ele enviará um sinal SIGTRAP que será capturado pelo GDB, pausando a execução exatamente na linha onde o problema está.

[![Screenshot-from-2024-08-15-15-55-23.png](https://i.postimg.cc/wjCBY5rz/Screenshot-from-2024-08-15-15-55-23.png)](https://postimg.cc/9DB2G9Vg)

Se preferir, você pode rodar o GDB linha por linha, acompanhando no outro terminal quando o Valgrind identificar um erro. Para isso, basta definir um breakpoint na `main` com `b main` e usar o `continue`, permitindo que você percorra o código passo a passo.
