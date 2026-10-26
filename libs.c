#include <utilities/versionProvider.h>

struct Func { void *fn; char *proto; };
struct Lib {
    char *name;
    void *setup;
    struct Func *funcs;
    char *src;
    struct Lib *next;
};

int count_funcs(struct Func *f) {
    int n = 0;
    if (f != NULL) {
        while (f->fn != NULL) {
            n++;
            f++;
        }
    }
    return n;
}

printf("PicoC (%s)\n", getVersion());

if (strcmp(getVersion(), "v2.1-cg50\xe7\x63") == 0) {
    int builtin_fn = count_funcs((struct Func *)0x00337ea4);
    struct Lib *p = *(struct Lib **)0x081002b4;
    int libs = 0, total_fn = builtin_fn;

    printf("[built-in C] (%d fn, no #include)\n", builtin_fn);
    while (p != NULL) {
        int n = count_funcs(p->funcs);
        printf("<%s> (%d fn)\n", p->name, n);
        libs++;
        total_fn += n;
        p = p->next;
    }
    printf("---\nTotal: %d headers + built-in C (%d fn)\n", libs, total_fn);
} else {
    printf("[built-in C]: printf sprintf gets getchar exit malloc calloc realloc free strcpy strncpy strcmp strncmp strcat index rindex strlen memset memcpy memcmp\n");
    printf("fxcg/*.h: app display file heap keyboard misc rtc serial system\n");
    printf("utilities/*.h: aboutGUI calendarGUI calendarProvider chronoGUI chronoProvider editorGUI fileGUI fileProvider firstRunGUI graphicsProvider hardwareProvider homeGUI imageGUI inputGUI keyboardProvider lightGUI lockGUI lockProvider memsysGUI menuGUI powerGUI selectorGUI settingsGUI settingsProvider stringsProvider structInit tasksGUI textEditGUI textGUI timeGUI timeProvider toolsGUI toolsProvider versionProvider\n");
}
