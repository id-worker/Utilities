# Notice of Modifications — Fork Patch Notes (RU + EN)

## English

This `Utilities/` directory is a **modified fork** of the official upstream project:

- **Upstream:** <https://github.com/gbl08ma/utilities>
- **Upstream author:** Gustavo Balieiro (gbl08ma)
- **Original license:** **GNU GPL v2** (or, at your option, any later version) — see the unmodified [`LICENSE`](LICENSE) file in this directory. The GPLv2 remains fully in effect for everything in this folder and **overrides the repository-root MIT license for this directory only**.

Compared to upstream `v2.1`, this copy contains the following local modifications, all distributed under the same GNU GPL v2 terms:

1. **Working PicoC console & native bindings** — added root-level `libs.c`, which exposes the calculator's native functions to the embedded PicoC interpreter (`src/picoc/`) so that standard C library calls work inside the Utilities *Text editor → PicoC* console; interpreter wiring/fixes accordingly.
2. **fx-CG50 build adjustments** — `Makefile` / `prizm.x` (linker script) and related build fixes so the add-in builds cleanly with the modern `sh3eb-elf-gcc` + `mkg3a` toolchain.
3. **Version tag** — the About screen reports `v2.1-cg50c` (upstream base `v2.1`).
4. **Packaging** — `Utilities/.gitignore` gained a `!Utilities.g3a` exception so the prebuilt binary is versioned in this repository.
5. **Packaging** — the upstream PicoC interpreter test-suite (`src/picoc/tests/`, 108 files) is not bundled here to keep hosting light; it is unchanged upstream content and remains available in the original repository.

All unmodified upstream sources remain intact in `src/`, and the **complete corresponding source code** of the distributed `Utilities.g3a` binary is included in this folder, satisfying GNU GPL v2 sections 2 and 3 (redistribution of the binary is permitted provided this license, the source code, and this notice accompany it).

The binary `Utilities.g3a` in this folder was verified on real Casio fx-CG50 hardware with OS `3.81` (`03.81.0202`).

## Русский

Папка `Utilities/` — это **модифицированная копия** официального проекта [gbl08ma/utilities](https://github.com/gbl08ma/utilities) (автор — Gustavo Balieiro, лицензия **GNU GPL v2**, см. файл `LICENSE` внутри папки; GPL действует на всю эту папку и **заменяет корневую MIT-лицензию репозитория только для этой папки**).

Что изменено относительно апстрима `v2.1` (всё под той же лицензией GPLv2):

1. Добавлен файл `libs.c` — нативные привязки, из-за которых консоль **PicoC** внутри аддина реально работает (стандартные C-функции доступны из редактора).
2. Правки сборки под fx-CG50 (`Makefile`, линковочный скрипт `prizm.x`, современный тулчейн `sh3eb-elf-gcc` + `mkg3a`).
3. Версия в *About* — `v2.1-cg50c`.
4. Упаковка: в `.gitignore` добавлено исключение `!Utilities.g3a`, чтобы бинарник попадал в репозиторий.
5. Упаковка: тесты интерпретатора PicoC (`src/picoc/tests/`, 108 файлов) не включены, чтобы облегчить загрузку — это неизменённый контент апстрима, доступный в оригинальном репозитории.

Исходники всех изменений лежат прямо здесь (`src/`, `libs.c`, `Makefile`), поэтому требование GPLv2 о предоставлении исходного кода к бинарному `Utilities.g3a` выполнено.
