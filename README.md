AVR code used for driving a 3-phase AC induction motor using DMX512. 

The communication chain is as follows:

- PC with GNU/Linux and [QLC][qlc], a software lighting console;
- ENTTEC [DMX USB Pro][enttec] for USB-DMX conversion;
- Metalab's [Metaboard][metaboard] and two 75176 chips to do DMX-Modbus translation;
- a Delta Electronics [VFD-L][vfd] variable frequency driver, uses the Modbus protocol for communication;
- a 3-phase AC induction motor.

This was all done in one day, more or less as a proof-of-concept. Therefore, some values are hard-coded. Reuse value is limited.

If you're looking for a proper Modbus implementation for embedded devices, take a look at [FreeMODBUS][freemodbus].

License: GPL3

[qlc]: http://qlc.sourceforge.net/
[enttec]: http://www.enttec.com/index.php?main_menu=Products&prod=70304&show=description
[metaboard]: https://metalab.at/wiki/Metaboard
[freemodbus]: http://www.freemodbus.org/
[vfd]: http://www.delta.com.tw/product/em/drive/ac_motor/ac_motor_product.asp?pid=1&cid=1&itid=3
