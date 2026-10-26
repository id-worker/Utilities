#include "../picoc.h"
#include "../interpreter.h"

void* calloc(size_t num, size_t size) {
    void* p = malloc(num*size);
    if(!p) return NULL;
    memset(p, 0, num*size);
    return p;
}

/* deallocate any storage */
void PlatformCleanup()
{
}

/* get a line of interactive input */
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt)
{
    // XXX - unimplemented so far
    return NULL;
}

/* get a character of interactive input */
int PlatformGetCharacter()
{
    // XXX - unimplemented so far
    return 0;
}

static char picoc_outbuf[4096];
char* curoutptr = picoc_outbuf;
/* write a character to the console */
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream)
{
    if(curoutptr < picoc_outbuf + sizeof(picoc_outbuf) - 1) {
        *curoutptr = (char)OutCh;
        curoutptr++;
    }
}

/* mark where to end the program for platforms which require this */
jmp_buf PicocExitBuf;

/* exit the program */
void PlatformExit(int RetVal)
{
    PicocExitValue = RetVal;
    longjmp(PicocExitBuf, 1);
}

/* Utilities - PicoC output glue code */

char* PlatformGetOutputPointer() {
    return picoc_outbuf;
}

char* PlatformGetOutputCursor() {
    return curoutptr;
}

void PlatformClearOutput() {
    curoutptr = picoc_outbuf;
    picoc_outbuf[0] = '\0';
}
