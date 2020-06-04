# Escreva seu próprio conio.h para GNU / Linux
[Fonte: OpenSourceforU.com](https://opensourceforu.com/2014/03/write-conio-h-gnulinux/ "Fonte de referência")
### Informações iniciais

##### Algumas seqüências de escape importantes são fornecidas na Tabela 1. Você pode usá-las dentro do printf da mesma forma que usa \n e \t.

|  Código de escape | Uso  |
| ------------ | ------------ |
| **\x1b[2J** | Limpa o console  |
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

Esses códigos de escape também são usados em outros idiomas, como no Python, ao usar a função ***print();*** por exemplo: ***print(“\x1b[32m”);*** para um primeiro plano verde.

Os programadores típicos do Turbo C iniciam seus programas com ***clrscr()*** para limpar a tela e terminam com ***getch()*** para aguardar o pressionamento de tecla antes que o programa termine. Para limpar o terminal podemos usar o código de escape, ***\x1b[2J***. Mas não existe um código de escape para ***getch()***, pois é uma função com o tipo de retorno ***char***.

Na verdade, ***getch()*** pode ser substituído por ***getchar()*** em ***stdio.h***. O problema, no entanto, é que ***getchar()*** aguarda o usuário pressionar a tecla ***'Enter'***. Também ecoa o que foi digitado. Gostaríamos de escrever nossa própria função que aguarda apenas um único pressionamento de tecla, que não ecoará o pressionamento de tecla. Aqui precisamos da ajuda de um programa CLI externo, ***stty***, que é fornecido com quase todas as distribuições ***GNU/Linux***.

O código fornecido abaixo mostra a combinação de códigos de ***escape*** e ***stty*** para criar um programa que limpa a tela, imprime ***"Olá, mundo!"*** em branco com fundo azul, aguarda pressionamento de tecla e redefine o vídeo.

```c
#include <stdio.h>
#include <stdlib.h>
void clrscr()
{
       printf("\x1b[2J");
}
 char getch()
{
      char c; // Esta função deve retornar o pressionamento de tecla

      system("stty raw"); // Entrada bruta - aguarde apenas um único pressionamento de tecla

      system("stty -echo"); // Eco desligado
      c = getchar();
      system("stty cooked"); // Redefinir - Cooked entrada
      system("stty echo"); // Redefinir - Eco ligado 
      return c;
}
int main()
{
    printf("\x1b[34m"); // Fundo azul
    clrscr(); // Limpar a tela com bg azul

    printf("\x1b[47m"); // Primeiro plano branco
    printf("Hello, World!\n");
    getch();
    printf("\x1b[0m"); // Redefinir o console
    return 0;
}
```

Agora, para melhorar acima, vamos escrever nosso próprio ***conio.h***.

Vamos combinar tudo o que foi descrito anteriormente em nossa própria biblioteca conio. Para simplificar, não vamos criar uma biblioteca ***.so*** compartilhada, mas escreva ***conio.c*** e ***conio.h*** separadamente e colocar na pasta ***libconio/***. Aqui estão os códigos, com algumas funções adicionais de nossa discussão anterior como ***nocursor()*** e ***showcursor()*** também:

#### conio.c:

```c
// conio.c for ANSI C and C++
// Extra functions are also provided.
// (C) 2013 Nandakumar <nandakumar96@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"

// General Utility Functions

void cagxy(unsigned int x, unsigned int y) { // Clear and Goto X,Y
	printf("%s\x1b[%d;%df", CLEAR, y, x);
}

void clrscr() { // Clear the Screen
	printf("%s",CLEAR);
}

char getch() {
	char c;
	system("stty raw -echo");
	c=getchar();
	system("stty cooked echo");

	return c;
}

void gotox(unsigned int x) {
	printf("\x1b[%dG", x);
}

void gotoxy(unsigned int x, unsigned int y) {
	printf("\x1b[%d;%df", y, x);
}

void nocursor() {
	printf("\x1b[?25l");
}

void reset_video() {
	printf("\x1b[0m");
}

void showcursor() {
	printf("\x1b[?25h");
}

void textcolor(char *color) {
	printf("%s",color);
}

void textbackground(char color[11]) {
	char col[11];
	strcpy(col,color);
	col[2]='4'; // The given color will be fg color. Replace '3' with '4'.
	printf("%s",col);
}
```

#### conio.h:

```c
// conio.h for ANSI C and C++
// Extra functions are also provided.
// (C) 2013 Nandakumar <nandakumar96@gmail.com>

#ifndef CONIO_H
#define CONIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// General Utility

#define CLEAR "\x1b[2J"
#define SET11 "\x1b[1;1f"  // Set the Cursor at 1,1

// Text Modification

#define BLINK_SLOW "\x1b[5m"
#define BLINK_RAPID "\x1b[6m"

// Colors

#define CC_CLEAR "\x1b[0m" // Console Color CLEAR

// FG Colours
#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

// FG Intense Colors
#define IBLACK "\x1b[30;1m"
#define IRED "\x1b[31;1m"
#define IGREEN "\x1b[32;1m"
#define IYELLOW "\x1b[33;1m"
#define IBLUE "\x1b[34;1m"
#define IMAGENTA "\x1b[35;1m"
#define ICYAN "\x1b[36;1m"
#define IWHITE "\x1b[37;1m"

// BG Colors
#define BGC_BLACK "\x1b[40m"
#define BGC_RED "\x1b[41m"
#define BGC_GREEN "\x1b[42m"
#define BGC_YELLOW "\x1b[43m"
#define BGC_BLUE "\x1b[44m"
#define BGC_MAGENTA "\x1b[45m"
#define BGC_CYAN "\x1b[46m"
#define BGC_WHITE "\x1b[47m"

// BG Intense Colors
#define BGC_IBLACK "\x1b[40;1m"
#define BGC_IRED "\x1b[41;1m"
#define BGC_IGREEN "\x1b[42;1m"
#define BGC_IYELLOW "\x1b[43;1m"
#define BGC_IBLUE "\x1b[44;1m"
#define BGC_IMAGENTA "\x1b[45;1m"
#define BGC_ICYAN "\x1b[46;1m"
#define BGC_IWHITE "\x1b[47;1m"

// General Utility Functions

void cagxy(unsigned int x, unsigned int y); // Clear and Goto X,Y

void clrscr(); // Clear the Screen

char getch();

void gotox(unsigned int x);

void gotoxy(unsigned int x, unsigned int y);

void nocursor();

void reset_video();

void showcursor();

void textcolor(char *color);

void textbackground(char color[11]);

#endif
```

#### Programa de exemplo

O código para o programa que ilustra o uso do nosso conio é dado abaixo:

#### test.c:

```c
#include <stdio.h>
#include "conio-linux/conio.c"

int main() {
	textbackground(BLUE);
	textcolor(WHITE);
	clrscr();
	printf("Hello, World!\n");
	getch();

	return 0;
}
```

Compile usando o seguinte comando:

***gcc -Wall test.c -o test***

Agora, você pode usar ***conio.c*** e ***conio.h*** para qualquer programa.