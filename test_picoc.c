#include <fxcg/system.h>
#include <utilities/hardwareProvider.h>
#include <utilities/versionProvider.h>

int main() {
    printf("PicoC on fx-CG50 works!\n");
    printf("Utilities: %s\n", getVersion());
    printf("HW model: %d (3 = fx-CG50)\n", getHardwareModel());
    printf("SP: 0x%x\n", (unsigned int)GetStackPtr());

    int a = 0, b = 1, i;
    printf("Fib:");
    for (i = 0; i < 10; i++) {
        printf(" %d", a);
        int next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
    return 0;
}

main();
