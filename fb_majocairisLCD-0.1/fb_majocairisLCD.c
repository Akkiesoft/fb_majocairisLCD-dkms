// SPDX-License-Identifier: GPL-2.0+
/*
 * FB driver for the ILI9341 LCD display controller
 *
 * This display uses 9-bit SPI: Data/Command bit + 8 data bits
 * For platforms that doesn't support 9-bit, the driver is capable
 * of emulating this using 8-bit transfer.
 * This is done by transferring eight 9-bit words in 9 bytes.
 *
 * Copyright (C) 2013 Christian Vogelgsang
 * Based on adafruit22fb.c by Noralf Tronnes
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <video/mipi_display.h>

#include "fbtft.h"

#define DRVNAME		"fb_majocairisLCD"
#define WIDTH		640
#define HEIGHT		48
#define TXBUFLEN	(4 * PAGE_SIZE)
#define DEFAULT_GAMMA	"00 1C 21 02 11 07 3D 79 4B 07 0F 0C 1B 1F 0F\n" \
			"00 1C 20 04 0F 04 33 45 42 04 0C 0A 22 29 0F"


static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	//pr_info("majoca init_display\n");

	/* startup sequence for Maji Majo Pures LCD */

	write_reg(par, 0x01); /* software reset */
	mdelay(5);
	write_reg(par, 0x28); /* display off */

	/* --------------------------------------------------------- */
	///write_reg(par, 0x00);		//下記の化けのために試しに 0x00 送っても意味なかった
    // Set EXTC
	write_reg(par, 0xC8, 0xFF, 0x93, 0x42);		//0xC8 が DE に化けるので2回送ってる。。。
	write_reg(par, 0xC8, 0xFF, 0x93, 0x42);
    // Column Address Set
	write_reg(par, 0x2A, 0x00, 0x00, 0x01, 0x3F);
    // Page Address Set
	write_reg(par, 0x2B, 0x00, 0x00, 0x00, 0x5F);
    // Memory Access Control
	write_reg(par, 0x36, 0xC8);
	/* ------------power control-------------------------------- */
    // Power Control 1
	write_reg(par, 0xC0, 0x0E, 0x0E);
    // Power Control 2
	write_reg(par, 0xC1, 0x10);
	/* ------------VCOM --------- */
	write_reg(par, 0xC5, 0xFA);
    // Pixel Format Set
	/* ------------memory access control------------------------ */
	write_reg(par, 0x3A, 0x55); /* 16bit pixel */
	/* ------------frame rate----------------------------------- */
	write_reg(par, 0xB1, 0x00, 0x18);
	/* ------------Gamma---------------------------------------- */
	/* ------------display-------------------------------------- */

	write_reg(par, 0x11); /* sleep out */
	mdelay(130);
	write_reg(par, 0x29); /* display on */
	mdelay(10);


	return 0;
}

static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	xe = 319;
	ye = 95;
	//pr_info("majoca set_addr_win\n");

	write_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
		  (xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);

	write_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
		  (ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

	write_reg(par, MIPI_DCS_WRITE_MEMORY_START);
}

static struct fbtft_display display = {
	.buswidth = 8,
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbuflen = TXBUFLEN,
	.gamma_num = 2,
	.gamma_len = 15,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = {
		.write = fbtft_write_gpio8_wr,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
	},
};

FBTFT_REGISTER_DRIVER(DRVNAME, "ilitek,majocairisLCD", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:majocairisLCD");
MODULE_ALIAS("platform:majocairisLCD");

MODULE_DESCRIPTION("FB driver for the majocairis LCD display controller");
MODULE_AUTHOR("Christian Vogelgsang");
MODULE_LICENSE("GPL");
