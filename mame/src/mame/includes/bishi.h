/*************************************************************************

    Bishi Bashi Champ Mini Game Senshuken

*************************************************************************/
#include "sound/k007232.h"

#define CPU_CLOCK       (XTAL_24MHz / 2)        /* 68000 clock */
#define SOUND_CLOCK     XTAL_16_9344MHz     /* YMZ280 clock */

class bishi_state : public driver_device
{
public:
	bishi_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_k007232(*this, "k007232"),
		m_k056832(*this, "k056832"),
		m_k054338(*this, "k054338"),
		m_k055555(*this, "k055555") { }

	/* memory pointers */
	UINT8 *    m_ram;
//  UINT8 *    m_paletteram;    // currently this uses generic palette handling

	/* video-related */
	int        m_layer_colorbase[4];

	/* misc */
	UINT16     m_cur_control;
	UINT16     m_cur_control2;

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	optional_device<k007232_device> m_k007232;
	required_device<k056832_device> m_k056832;
	required_device<k054338_device> m_k054338;
	required_device<k055555_device> m_k055555;
	DECLARE_READ16_MEMBER(control_r);
	DECLARE_WRITE16_MEMBER(control_w);
	DECLARE_WRITE16_MEMBER(control2_w);
	DECLARE_READ16_MEMBER(bishi_mirror_r);
	DECLARE_READ16_MEMBER(bishi_K056832_rom_r);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_bishi(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	TIMER_DEVICE_CALLBACK_MEMBER(bishi_scanline);
	DECLARE_WRITE_LINE_MEMBER(sound_irq_gen);
};

/*----------- defined in video/bishi.c -----------*/
extern void bishi_tile_callback(running_machine &machine, int layer, int *code, int *color, int *flags);
