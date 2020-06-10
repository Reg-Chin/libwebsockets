list(APPEND SOURCES
        drivers/display/lws-display.c
        drivers/display/ssd1306-i2c.c
        drivers/i2c/lws-i2c.c
        drivers/i2c/bitbang/lws-bb-i2c.c
        plat/freertos/esp32/drivers/gpio-esp32.c
)

exports_to_parent_scope()

