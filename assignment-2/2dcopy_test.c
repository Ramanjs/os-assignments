#include <sys/syscall.h>
#include <linux/kernel.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
	float arr[2][3] = {{1.1, 2.1, 3.1}, {4.4, 5.9, 9.6}};
	float dest[2][3];
	if (syscall(449, arr, dest, 2, 3) != EFAULT) {
		printf("System call successfully executed\n");
	} else {
		printf("Error");
		return 1;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[i][j] != dest[i][j]) {
				printf("Arrays not equal\n");
				return 0;
			}
		}
		printf("\n");
	}
	printf("Both arrays are equal\n");
	return 0;
}
