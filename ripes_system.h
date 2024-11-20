#ifndef RIPES_SYSTEM_H_
#define RIPES_SYSTEM_H_
// *****************************************************************************
// * SWITCHES_0
// *****************************************************************************
#define SWITCHES_0_BASE	(0xf0000000)
#define SWITCHES_0_SIZE	(0x4)
#define SWITCHES_0_N	(0x8)


// *****************************************************************************
// * D_PAD_0
// *****************************************************************************
#define D_PAD_0_BASE	(0xf0000004)
#define D_PAD_0_SIZE	(0x10)
#define D_PAD_0_UP_OFFSET	(0x0)
#define D_PAD_0_UP	(0xf0000004)
#define D_PAD_0_DOWN_OFFSET	(0x4)
#define D_PAD_0_DOWN	(0xf0000008)
#define D_PAD_0_LEFT_OFFSET	(0x8)
#define D_PAD_0_LEFT	(0xf000000c)
#define D_PAD_0_RIGHT_OFFSET	(0xc)
#define D_PAD_0_RIGHT	(0xf0000010)


// *****************************************************************************
// * LED_MATRIX_0
// *****************************************************************************
#define LED_MATRIX_0_BASE	(0xf0000014)
#define LED_MATRIX_0_SIZE	(0x2710)
#define LED_MATRIX_0_WIDTH	(0x32)
#define LED_MATRIX_0_HEIGHT	(0x32)


#endif // RIPES_IO_HEADER