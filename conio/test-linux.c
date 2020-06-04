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
