#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/delay.h>

#define OLED_NAME "etx_oled"
#define OLED_ADDR 0x3C   // địa chỉ phổ biến của SSD1306

// Gửi 1 byte command tới OLED
static void ssd1306_write_cmd(struct i2c_client *client, u8 cmd)
{
    u8 buf[2] = { 0x00, cmd };
    i2c_master_send(client, buf, 2);
}

// Gửi 1 byte data tới OLED
static void ssd1306_write_data(struct i2c_client *client, u8 data)
{
    u8 buf[2] = { 0x40, data };
    i2c_master_send(client, buf, 2);
}

// Khởi tạo OLED cơ bản
static void ssd1306_init(struct i2c_client *client)
{
    msleep(100);

    ssd1306_write_cmd(client, 0xAE); // Display OFF
    ssd1306_write_cmd(client, 0xD5);
    ssd1306_write_cmd(client, 0x80);
    ssd1306_write_cmd(client, 0xA8);
    ssd1306_write_cmd(client, 0x3F);
    ssd1306_write_cmd(client, 0xD3);
    ssd1306_write_cmd(client, 0x00);
    ssd1306_write_cmd(client, 0x40);
    ssd1306_write_cmd(client, 0x8D);
    ssd1306_write_cmd(client, 0x14);
    ssd1306_write_cmd(client, 0x20);
    ssd1306_write_cmd(client, 0x00);
    ssd1306_write_cmd(client, 0xA1);
    ssd1306_write_cmd(client, 0xC8);
    ssd1306_write_cmd(client, 0xDA);
    ssd1306_write_cmd(client, 0x12);
    ssd1306_write_cmd(client, 0x81);
    ssd1306_write_cmd(client, 0x7F);
    ssd1306_write_cmd(client, 0xA4);
    ssd1306_write_cmd(client, 0xA6);
    ssd1306_write_cmd(client, 0xAF); // Display ON
}

// Lấp đầy màn hình bằng 1 giá trị (0x00: tắt, 0xFF: sáng)
static void ssd1306_fill(struct i2c_client *client, u8 data)
{
    int i;
    for (i = 0; i < 128 * 8; i++) {
        ssd1306_write_data(client, data);
    }
}

static int etx_oled_probe(struct i2c_client *client)
{
    pr_info("OLED: Probed device at address 0x%x\n", client->addr);
    ssd1306_init(client);
    ssd1306_fill(client, 0xFF); // Fill trắng
    return 0;
}

static void etx_oled_remove(struct i2c_client *client)
{
    ssd1306_fill(client, 0x00); // Fill đen
    pr_info("OLED: Removed\n");
}

static struct i2c_driver etx_oled_driver = {
    .driver = {
        .name = OLED_NAME,
        .owner = THIS_MODULE,
    },
    .probe 	= etx_oled_probe,   
	.remove = etx_oled_remove,
};


module_i2c_driver(etx_oled_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Viet Tran");
MODULE_DESCRIPTION("Minimal SSD1306 OLED I2C driver for Raspberry Pi kernel 6.12.x");

