# DOJO - GDB / VALGRIND

## O que faremos?
Esse dojo funcionará em duas partes: <br>
1. Já ouviu falar de Capture the Flag? Temos 5 executáveis compactados em arquivos .zip protegidos com senha. Todos são programas diferentes que quando executados esperam por uma flag. Se a flag estiver errado o programa imprimirá `Fail`, se estiver correta imprimirá `Boua!`. Seu objetivo é encontrar no código a flag escondida usando gdb. Essa flag será a senha para o próximo desafio!

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
