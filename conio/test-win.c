#include <stdio.h>
#include "conio-windows/conio.c"

int main() {
	textbackground(BLUE);
	textcolor(WHITE);
	clrscr();
	printf("Hello, World!\n");
	getch();

	return 0;
}
