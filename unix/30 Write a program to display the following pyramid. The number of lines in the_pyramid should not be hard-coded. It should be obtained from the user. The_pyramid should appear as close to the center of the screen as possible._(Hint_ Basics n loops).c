#include <stdio.h>

void displayPyramid(int numLines) {
int spaces, stars;

for (int i = 1; i <= numLines; i++) {
spaces = numLines - i;

// Print spaces
for (int j = 1; j <= spaces; j++) {
printf(" ");
}

stars = 2 * i - 1;

// Print stars
for (int k = 1; k <= stars; k++) {
printf("*");
}

printf("\n");
}
}

int main() {
int numLines;

printf("Enter the number of lines in the pyramid: ");
scanf("%d", &numLines);

printf("\n");
displayPyramid(numLines);
printf("\n");

return 0;
}