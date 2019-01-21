# i2c_multidev_emulate_f3k

The purpose of this code is to emulate multiple i2c slave devices
in order to emulate the PA board on Flex-3000 radio for testing
purposes.

The TCD2210 firmware via serial asserts that I'm missing the following
on the PA100 board -- which makes sense -- I have no PA board...

|chip	|part	|addr	|expected  |
|-------|-------|-------|----------|
|IC16	|PCA9555|	0x4E	|0xAB|
|IC13	|PCA9555|	0x4C	|0xAB|
|IC3	|AD5263	|0x5C	|0xAB|
|IC4	|AD5263	|0x5A	|0xAB|

So...either spend $16 at digikey, mess around with wiring the chips
up and see what else I'm missing or make an arduino answer synthetically.

This relies on the following project:

https://github.com/nox771/i2c_t3
