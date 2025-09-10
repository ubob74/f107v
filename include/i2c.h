#ifndef _I2C_H_
#define _I2C_H_

int i2c_init(void);
void i2c_send_byte(unsigned char val, unsigned char addr);

#endif
