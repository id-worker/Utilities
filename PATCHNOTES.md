Copyright (c) 2026 Alex Work. Modifications described in this file, distributed under the repository's GNU GPL v2 license.

# Notice of Modifications — Fork Patch Notes (RU + EN)

## English

This repository is a **modified fork** of the official upstream project:

- **Upstream:** <https://github.com/gbl08ma/utilities>
- **Upstream author:** Gustavo Balieiro (gbl08ma)
- **Original license:** **GNU GPL v2** (or, at your option, any later version) — see the unmodified [`LICENSE`](LICENSE) file in this directory. The GPLv2 remains in effect for this standalone Utilities repository; it is not governed by the separate main repository's MIT license.

Compared to upstream `v2.1`, this copy contains the following local modifications, all distributed under the same GNU GPL v2 terms:

1. **Working PicoC console & native bindings** — added root-level `libs.c`, which exposes the calculator's native functions to the embedded PicoC interpreter (`src/picoc/`) so that standard C library calls work inside the Utilities *Text editor → PicoC* console; interpreter wiring/fixes accordingly.
2. **fx-CG50 build adjustments** — `Makefile` / `prizm.x` (linker script) and related build fixes so the add-in builds cleanly with the modern `sh3eb-elf-gcc` + `mkg3a` toolchain.
3. **Version labels** — the About screen reports `v2.1-cg50c` (upstream base `v2.1`); the GitHub Release tag is `v2.2`. These are different labels, not proof that the app itself displays `v2.2`.
4. **Packaging** — `.gitignore` gained a `!Utilities.g3a` exception so the prebuilt binary is versioned in this repository.
5. **Packaging** — the repository contains 108 files under `src/picoc/tests/` as of commit `f89d77a`; the older local `3_Utilities.zip` backup omitted them. Their presence does not imply that the tests were run.

This repository contains source and build files for Utilities. Preserve the GPL license, applicable upstream notices and corresponding source when redistributing; exact correspondence to a particular binary should be verified rather than assumed.

The binary `Utilities.g3a` in this folder was verified on real Casio fx-CG50 hardware with OS `3.81` (`03.81.0202`).

## Русский

Этот репозиторий — **модифицированная копия** официального проекта [gbl08ma/utilities](https://github.com/gbl08ma/utilities) (автор — Gustavo Balieiro, лицензия **GNU GPL v2**, см. файл `LICENSE` внутри папки; GPL действует в этом отдельном репозитории; MIT-лицензия другого основного репозитория её не заменяет).

Что изменено относительно апстрима `v2.1` (всё под той же лицензией GPLv2):

1. Добавлен файл `libs.c` — нативные привязки, из-за которых консоль **PicoC** внутри аддина реально работает (стандартные C-функции доступны из редактора).
2. Правки сборки под fx-CG50 (`Makefile`, линковочный скрипт `prizm.x`, современный тулчейн `sh3eb-elf-gcc` + `mkg3a`).
3. В *About* — `v2.1-cg50c` (база `v2.1`), а тег GitHub Release — `v2.2`. Это разные обозначения; тег не означает, что программа показывает `v2.2`.
4. Упаковка: в `.gitignore` добавлено исключение `!Utilities.g3a`, чтобы бинарник попадал в репозиторий.
5. Упаковка: в репозитории по состоянию на commit `f89d77a` находятся 108 файлов `src/picoc/tests/`; в старом локальном архиве `3_Utilities.zip` они отсутствовали. Само наличие тестов не означает, что они были запущены.

Исходники всех изменений лежат прямо здесь (`src/`, `libs.c`, `Makefile`), но при распространении следует сохранить GPL, notices и соответствующий исходный код и проверить его соответствие конкретному бинарнику.
