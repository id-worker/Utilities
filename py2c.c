/*
 * py2c.c -- Quick .py <-> .c Extension Switcher for Utilities PicoC
 * Uses < 3 KB of PicoC heap!
 * Controls: UP/DOWN = Select file, EXE = Toggle .py <-> .c, EXIT = Quit
 */
#include <fxcg/display.h>
#include <fxcg/file.h>
#include <fxcg/keyboard.h>
#include <utilities/graphicsProvider.h>

struct FsInfo {
    unsigned short id;
    unsigned short type;
    unsigned long fsize;
    unsigned long dsize;
    unsigned int property;
    unsigned long address;
};

int is_py(char *s) {
    int n = strlen(s);
    if (n < 3) return 0;
    if (s[n - 3] == '.') {
        if (s[n - 2] == 'p' || s[n - 2] == 'P') {
            if (s[n - 1] == 'y' || s[n - 1] == 'Y') return 1;
        }
    }
    return 0;
}

int is_c(char *s) {
    int n = strlen(s);
    if (n < 2) return 0;
    if (s[n - 2] == '.') {
        if (s[n - 1] == 'c' || s[n - 1] == 'C') return 1;
    }
    return 0;
}

int scan_py_c(char *names) {
    unsigned short u_mask[64];
    unsigned short u_found[128];
    char buf[128];
    struct FsInfo info;
    int fh = -1;
    int ret;
    int cnt = 0;

    Bfile_StrToName_ncpy(u_mask, "\\\\fls0\\*", 64);
    ret = Bfile_FindFirst_NON_SMEM((char *)u_mask, &fh, (char *)u_found, &info);
    while (ret == 0) {
        Bfile_NameToStr_ncpy(buf, u_found, 128);
        if (info.type != 0 || info.fsize > 0) {
            if (is_py(buf) || is_c(buf)) {
                if (cnt < 48) {
                    if (strlen(buf) < 47) {
                        strcpy(names + cnt * 48, buf);
                        cnt++;
                    }
                }
            }
        }
        ret = Bfile_FindNext_NON_SMEM(fh, (char *)u_found, (char *)&info);
    }
    if (fh >= 0) Bfile_FindClose(fh);
    return cnt;
}

int main() {
    char names[2304]; /* 48 * 48 bytes */
    int count;
    int sel = 0;
    int scroll = 0;
    int key = 0;
    int i;

    Bdisp_EnableColor(1);
    EnableStatusArea(3);
    count = scan_py_c(names);

    while (1) {
        drawRectangle(0, 0, 384, 20, 0x0000);
        multiPrintMini(8, -21, "py2c.c -- EXE: Toggle .py <-> .c    EXIT: Quit", 0xFFFF);
        drawRectangle(0, 20, 384, 196, 0xFFFF);

        if (count == 0) {
            multiPrintMini(16, 60, "No .py or .c files in \\\\fls0\\", 0x0000);
        } else {
            for (i = 0; i < 10; i++) {
                int pos = scroll + i;
                if (pos < count) {
                    char *nm = names + pos * 48;
                    int y = 24 + i * 18;
                    if (pos == sel) {
                        drawRectangle(6, y, 372, 17, 0x1084);
                        multiPrintMini(14, y - 23, nm, 0xFFFF);
                    } else {
                        multiPrintMini(14, y - 23, nm, 0x0000);
                    }
                }
            }
        }

        Bdisp_PutDisp_DD();
        GetKey(&key);

        if (key == 30002) { /* EXIT */
            break;
        } else if (key == 30018) { /* UP */
            if (sel > 0) sel--;
            if (sel < scroll) scroll = sel;
        } else if (key == 30023) { /* DOWN */
            if (sel + 1 < count) sel++;
            if (sel >= scroll + 10) scroll = sel - 9;
        } else if (key == 30004) { /* EXE */
            if (count > 0) {
                char *cur = names + sel * 48;
                char oldp[96];
                char newp[96];
                char newname[48];
                unsigned short u_old[96];
                unsigned short u_new[96];
                int n = strlen(cur);

                strcpy(newname, cur);
                if (is_py(newname)) {
                    newname[n - 2] = 'c';
                    newname[n - 1] = 0;
                } else {
                    newname[n - 1] = 'p';
                    newname[n] = 'y';
                    newname[n + 1] = 0;
                }

                sprintf(oldp, "\\\\fls0\\%s", cur);
                sprintf(newp, "\\\\fls0\\%s", newname);
                Bfile_StrToName_ncpy(u_old, oldp, 96);
                Bfile_StrToName_ncpy(u_new, newp, 96);
                Bfile_RenameEntry(u_old, u_new);

                count = scan_py_c(names);
                for (i = 0; i < count; i++) {
                    if (strcmp(names + i * 48, newname) == 0) sel = i;
                }
                if (sel >= count) sel = count > 0 ? count - 1 : 0;
            }
        }
    }

    EnableStatusArea(0);
    return 0;
}

main();
