/*
 * esp32 / esp-idf gpio
 *
 * Copyright (C) 2019 - 2020 Andy Green <andy@warmcat.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <libwebsockets.h>
	
static void
lws_gpio_esp32_mode_write(_lws_plat_gpio_t gpio)
{
	gpio_reset_pin(gpio);
	gpio_set_pull_mode(gpio, GPIO_PULLUP_ONLY);
	gpio_set_direction(gpio, GPIO_MODE_INPUT_OUTPUT);
	gpio_set_level(gpio, 1);
}
static void
lws_gpio_esp32_mode_read(_lws_plat_gpio_t gpio)
{
	gpio_set_pull_mode(gpio, GPIO_PULLUP_ONLY);
	gpio_set_direction(gpio, GPIO_MODE_INPUT);
	gpio_set_level(gpio, 1);
}
static int
lws_gpio_esp32_read(_lws_plat_gpio_t gpio)
{
	return gpio_get_level(gpio);
}
static void
lws_gpio_esp32_set(_lws_plat_gpio_t gpio, int val)
{
	gpio_set_level(gpio, val);
}

const lws_gpio_ops_t lws_gpio_plat = {
	.mode_write		= lws_gpio_esp32_mode_write,
	.mode_read		= lws_gpio_esp32_mode_read,
	.read			= lws_gpio_esp32_read,
	.set			= lws_gpio_esp32_set,
};

