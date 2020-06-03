# Escreva seu próprio conio.h para GNU / Linux

##### Algumas seqüências de escape importantes são fornecidas na Tabela 1. Você pode usá-las dentro do printf da mesma forma que usa \n e \t.

|  Código de escape | Uso  |
| ------------ | ------------ |
| **\x1b[2J ** | Limpa o console  |
| **\x1bn;mH** ou **\x1bn;mf**  | Move o cursor para a linha n, coluna m. Os valores são baseados em 1 e o padrão é 1 (canto superior esquerdo) se omitido  |
| **\x1b?25l**  | Oculta o cursor (Nota: o último caractere está em minúsculas 'L')  |
| **\x1b?25h**  | Mostra o cursor.  |
| **\x1b[;km**  | Onde k é a cor (as cores do texto são de 30 a 37 e as cores de fundo são de 40 a 47). Para os códigos de cores, consulte a Tabela 2.  |
| **\x1b[5m**  | Pisca lentamente  |
| **\x1b[6m**  | Pisca rapidamente  |

**Tabela 1**: Alguns códigos de escape ANSI importantes

Como mostra a Tabela 1, você pode usar ***printf(\x1b[2J);*** para limpar o console, em vez de ***clrscr();***. Você pode usar ***printf(\x1b10;20H);*** em vez de ***gotoxy(20,10);*** ou ***printf(\x1b%d;%dH, a, b);*** em vez de ***gotoxy(a, b);***.

Porém, ao usar cores, com ***\x1b[;km***, é necessário substituir ***k*** por ***30+código_da_cor*** no caso da coloração em primeiro plano é ***40+código_da_cor*** no caso da coloração em segundo plano. Consulte a Tabela 2 para obter os códigos de cores.

| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  |
| :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: |
| Black  | Red  | Green  | Yellow  | Blue  | Magenta  | Cyan  | White  |

**Tabela 2**: Código de cores

Na Tabela 2, você pode usar ***printf(\x1b[31m);*** em vez de ***textcolor(RED);*** e ***printf(\x1b[41m);*** em vez de ***textbackground(RED);*** Você pode cancelar a coloração usando ***\x1b[0m***.

Para saber mais sobre os códigos de escape ANSI, visite: 

[Wikipedia (ANSI escape code)](http://www.en.wikipedia.org/wiki/ANSI_escape_code "Wikipedia (ANSI escape code)")

Esses códigos de escape também são usados em outros idiomas, como no Python, ao usar a função print(); por exemplo: print(“\x1b[32m”) para um primeiro plano verde.

Os programadores típicos do Turbo C iniciam seus programas com clrscr() para limpar a tela e terminam com getch() para aguardar o pressionamento de tecla antes que o programa termine. Ambos são sem sentido na maioria dos casos. Se você estiver familiarizado com a CLI, poderá ter notado a irritação enquanto o console limpa com todos os comandos que você fornece. Um programador Turbo C fornece o comando getch(). Caso contrário, o programa desaparecerá repentinamente e o resultado do programa não será visível. Em um console padrão, o resultado permanece lá por um longo tempo sem getch(). O pressionamento de tecla extra é uma irritação adicional.

No entanto, essas duas funções são úteis em alguns casos. Substituímos clrscr() por um código de escape, \x1b[2J. Mas não existe esse código para getch(), pois é uma função com o tipo de retorno char.

Na verdade, getch() pode ser substituído por getchar() em stdio.h. O problema, no entanto, é que getchar() aguarda o usuário pressionar a tecla 'Enter'. Também ecoa o que foi digitado. Gostaríamos de escrever nossa própria função que aguarda apenas um único pressionamento de tecla, que não ecoará o pressionamento de tecla. Aqui precisamos da ajuda de um programa CLI externo, stty, que é fornecido com quase todas as distribuições GNU/Linux.

O código fornecido abaixo mostra a combinação de códigos de escape e stty para criar um programa que limpa a tela, imprime ‘Olá, mundo! em branco com fundo azul, aguarda pressionamento de tecla e redefine o vídeo.
