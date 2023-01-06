#include <stdio.h>
#include <locale.h>

// Test include/date.h
extern void group_Date(void);

// Test include/elements.h
extern void group_Elements(void);

// Test include/breakdowns.h
extern void group_Breakdowns(void);

// Test include/laptops.h
extern void group_Laptops(void);

// Test include/request.h
extern void group_Requests(void);


int main(void) {
	// setlocale(LC_ALL, "Portuguese");
	printf("olá mundoç");
	printf("Test include/date.h\n");
	group_Date();

	printf("\nTest include/elements.h\n");
	group_Elements();

	printf("\nTest include/breakdowns.h\n");
	group_Breakdowns();

	printf("\nTest include/laptops.h\n");
	group_Laptops();

	printf("\nTest include/requests.h\n");
	group_Requests();
}