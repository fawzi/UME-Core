#include "sound/msm5205.h"

class pcktgal_state : public driver_device
{
public:
	pcktgal_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm") { }

	int m_msm5205next;
	int m_toggle;
	required_shared_ptr<UINT8> m_spriteram;
	DECLARE_WRITE8_MEMBER(pcktgal_bank_w);
	DECLARE_WRITE8_MEMBER(pcktgal_sound_bank_w);
	DECLARE_WRITE8_MEMBER(pcktgal_sound_w);
	DECLARE_WRITE8_MEMBER(pcktgal_adpcm_data_w);
	DECLARE_READ8_MEMBER(pcktgal_adpcm_reset_r);
	DECLARE_DRIVER_INIT(pcktgal);
	virtual void palette_init();
	virtual void machine_start();
	UINT32 screen_update_pcktgal(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_pcktgalb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(pcktgal_adpcm_int);
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<msm5205_device> m_msm;
};
