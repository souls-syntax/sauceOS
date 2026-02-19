
```C

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

```
```C
extern void term_write(const char *string, size_t length) {
    terminal_request.response->write(main_terminal, string, length);
}
```
Print like this when there is memory corruption issue cause maybe putpixel also got corrupted.

