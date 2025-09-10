#include <stdlib.h>
#include <hd44780.h>
#include <i2c.h>
#include <systick.h>

#define HD44780_ADDR	0x4E

enum hd44780_pins {
	RS,
	RW,
	E,
	BL,
	D4,
	D5,
	D6,
	D7,
};

struct hd44780 {
	int pos;
	unsigned char data;
};

static struct hd44780 hd44780;

static void hd44780_transfer(void)
{
	i2c_send_byte(hd44780.data, HD44780_ADDR);
}

static void hd44780_bl(int bl)
{
	if (bl)
		hd44780.data |= 1 << BL;
	else
		hd44780.data &= ~(1 << BL);

	hd44780_transfer();
}

static void hd44780_strobe(void)
{
	hd44780.data |= 1 << E;
	hd44780_transfer();

	hd44780.data &= ~(1 << E);
	hd44780_transfer();
}

static void hd44780_send(unsigned char val, int rs)
{
	int i;

	if (rs)
		hd44780.data |= 1 << RS;
	else
		hd44780.data &= ~(1 << RS);

	/* High nibble */
	hd44780.data &= ~(0xF << 4);
	for (i = 4; i < 8; i++)
		hd44780.data |= !!(val & (1 << i)) << i;

	hd44780_transfer();
	hd44780_strobe();

	/* Low nibble */
	hd44780.data &= ~(0xF << 4);
	for (i = 0; i < 4; i++)
		hd44780.data |= !!(val & (1 << i)) << (i + D4);

	hd44780_transfer();
	hd44780_strobe();
}

static void hd44780_cmd(unsigned char cmd)
{
	hd44780_send(cmd, 0);
}

static void hd44780_data(unsigned char data)
{
	hd44780_send(data, 1);
}

static void hd44780_clear(void)
{
	hd44780_cmd(0x01);
}

static void hd44780_home(void)
{
	hd44780_cmd(0x02);
}

static void hd44780_write(const char *data, int size)
{
	int i;

	hd44780_clear();
	hd44780_home();

	for (i = 0; i < size; i++) {
		if (data[i] == '\n')
			continue;
		hd44780_data(data[i]);
	}
}

void hd44780_init(void)
{
	int i;
	unsigned char cmd[] = {
		0x02, /* return home */
		0x20, /* 4-bit mode, 1 line */
		0x0C, /* display on, cursor off, blinking off */
		0x06, /* cursor increment */
		0x01, /* clear display */
	};

	hd44780_clear();
	hd44780_home();
	hd44780_bl(1);

	for (i = 0; i < 5; i++)
		hd44780_cmd(cmd[i]);
}

void hd44780_test(void)
{
	const char *str = "BREAKING BAD";

	hd44780_clear();
	hd44780_home();
	hd44780_write(str, 12);

	delay(1);
}

void hd44780_update(const char *data, int size)
{	
	hd44780_clear();
	hd44780_home();
	hd44780_write(data, size);
}

