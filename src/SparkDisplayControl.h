/*
 * SparkDisplayControl.h
 *
 *  Created on: 23.08.2021
 *      Author: stangreg
 */

#ifndef SPARKDISPLAYCONTROL_H_
#define SPARKDISPLAYCONTROL_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306
#include "Config_Definitions.h"

#include "SparkDataControl.h"
#include "SparkTypes.h"


// OLED Screen config
#define SCREEN_WIDTH 128 // Display width
#define SCREEN_HEIGHT 64 // Display height
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define DISPLAY_MIN_X_FACTOR -12 // for text size 2, scales linearly with text size

// Splash logo measurements
#define imageWidth 128
#define imageHeight 47

class SparkDataControl;

class SparkDisplayControl {
public:
	SparkDisplayControl();
	SparkDisplayControl(SparkDataControl* dc);
	virtual ~SparkDisplayControl();
	void init(int mode);
	void update(bool isInitBoot = false);
	void setDataControl(SparkDataControl *dc) {
			spark_dc = dc;
	}


private:
	static Adafruit_SSD1306 display;
	SparkDataControl* spark_dc;
	int activeBank = 1;
	int pendingBank = 1;
	const Preset* activePreset;
	const Preset* pendingPreset;
	const Preset* presetFromApp;
	int presetEditMode;
	int buttonMode = 1;
	int activePresetNum = 1;
	int selectedPresetNum = 1;
	int opMode = 1;
	int currentBTMode = 0;
	bool isBTConnected = false;
	KeyboardMapping mapping;

	std::string primaryLineText;
	const Preset* primaryLinePreset;
	std::string secondaryLineText;
	const Preset* secondaryLinePreset;
	std::string currentBTModeText;

	std::string lowerButtonsShort;
	std::string lowerButtonsLong;
	std::string upperButtonsShort;
	std::string upperButtonsLong;

	std::string lastKeyboardButtonPressed;
	unsigned long keyboardPressedTimestamp = 0;
	int showKeyboardPressedInterval = 500;
	bool showKeyboardPressedFlag = false;

	unsigned long previousMillis = 0;
	int showMessageInterval = 2000;
	bool showMsgFlag = false;

	//DISPLAY variables x1 for the first line, x2 for the second line
	int display_x1 = 0;
	int display_minX1 = DISPLAY_MIN_X_FACTOR * 10;
	int display_scroll_num1 = 1; // scroll speed, make bigger to speed up the scroll

	int display_x2 = 0;
	int display_minX2 = DISPLAY_MIN_X_FACTOR * 10;
	int display_scroll_num2 = 1; // scroll speed, make bigger to speed up the scroll

	int text_scroll_limit = 11;

	int text_row_1_timestamp = 0;
	int text_row_2_timestamp = 0;
	int text_scroll_delay = 3500;
	std::string text_filler = "   ";
	std::string previous_text1 = "";
	std::string previous_text2 = "";

	SparkDataControl* dataControl() {return spark_dc;}
	void showInitialMessage();
	void showConnection();
	void showBankAndPresetNum();
	void showPresetName();
	void showFX_SecondaryName();
	void updateTextPositions();

	void showPressedKey();
	void initKeyboardLayoutStrings();
	void showKeyboardLayout();

	void drawCentreString(const char *buf, int y, int offset = 0);
	void drawRightAlignedString(const char *buf, int y, int offset = 0);
	void drawInvertBitmapColor(int16_t x, int16_t y, const uint8_t *bitmap,
			int16_t w, int16_t h, uint16_t color);

	const unsigned char epd_bitmap_Ignitron_Logo[768] PROGMEM = {
			// 'Ignitron_logo_small, 128x47px
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xc3, 0xc0, 0x08, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00,
			0x7f, 0xff, 0xff, 0xff, 0xff, 0x82, 0x1f, 0x80, 0x1f, 0xdf, 0xfe,
			0x18, 0x60, 0x00, 0x00, 0x00, 0x3c, 0x47, 0xfe, 0xff, 0xbf, 0x81,
			0x8c, 0x00, 0x08, 0x01, 0x26, 0x06, 0x60, 0x00, 0x0f, 0xf8, 0x10,
			0x01, 0xe0, 0x04, 0x9f, 0xc7, 0xc8, 0x14, 0x00, 0x00, 0x02, 0x3f,
			0x0c, 0x34, 0x1f, 0xfe, 0x00, 0x78, 0x00, 0x00, 0x0f, 0xc7, 0xc0,
			0x7f, 0x80, 0xfc, 0x7c, 0x3f, 0x1f, 0xfe, 0x1f, 0xfe, 0x01, 0xfe,
			0x03, 0xf1, 0xe7, 0xc7, 0xc0, 0xff, 0xc0, 0xfc, 0xfc, 0x3f, 0x1f,
			0xfe, 0x0f, 0xff, 0x03, 0xff, 0x03, 0xf3, 0xf3, 0xc7, 0xc1, 0xff,
			0xc0, 0xfc, 0xfc, 0x3f, 0x1f, 0xfe, 0x0f, 0xbf, 0x07, 0xff, 0x83,
			0xf3, 0xf3, 0xc7, 0xc3, 0xff, 0xe0, 0xfe, 0xfc, 0x3f, 0x0f, 0xfc,
			0x1f, 0x9f, 0x07, 0xef, 0x83, 0xf3, 0xf3, 0xc7, 0xc3, 0xf3, 0xe0,
			0xfe, 0xfc, 0x3f, 0x01, 0xf0, 0x1f, 0x9f, 0x07, 0xcf, 0x83, 0xfb,
			0xf3, 0xc7, 0xc3, 0xf3, 0xe0, 0xfe, 0xfc, 0x3f, 0x01, 0xf0, 0x1f,
			0x9f, 0x0f, 0xcf, 0x83, 0xfb, 0xf3, 0xc7, 0xc3, 0xf3, 0xe0, 0xfe,
			0xfc, 0x3f, 0x01, 0xf0, 0x0f, 0xbf, 0x0f, 0xcf, 0x83, 0xf3, 0xf3,
			0xcf, 0xc3, 0xf0, 0x00, 0xfe, 0xfc, 0x3e, 0x01, 0xf0, 0x0f, 0xfe,
			0x07, 0xcf, 0x83, 0xfb, 0xf3, 0xc7, 0x83, 0xf0, 0x00, 0xff, 0x7c,
			0x3e, 0x01, 0xf0, 0x1f, 0xfc, 0x0f, 0xcf, 0x83, 0xff, 0xf3, 0xc7,
			0xc3, 0xef, 0xe0, 0xff, 0xfc, 0x3f, 0x01, 0xf0, 0x0f, 0xfe, 0x0f,
			0xcf, 0x83, 0xff, 0xf3, 0xc7, 0xc3, 0xef, 0xe0, 0xff, 0xfc, 0x3f,
			0x01, 0xf0, 0x1f, 0xff, 0x0f, 0xcf, 0x83, 0xff, 0xf3, 0xc7, 0xc3,
			0xff, 0xe0, 0xff, 0xfc, 0x3f, 0x01, 0xe0, 0x0f, 0x9f, 0x0f, 0xcf,
			0x83, 0xff, 0xf3, 0xc7, 0xc3, 0xef, 0xe0, 0xfb, 0xfc, 0x3f, 0x01,
			0xf0, 0x0f, 0x9f, 0x07, 0xcf, 0x83, 0xef, 0xf3, 0xc7, 0xc3, 0xf3,
			0xe0, 0xfb, 0xfc, 0x3f, 0x01, 0xf0, 0x1f, 0x9f, 0x0f, 0xcf, 0x83,
			0xef, 0xf1, 0xc7, 0xc3, 0xf3, 0xe0, 0xfb, 0xfc, 0x3f, 0x01, 0xf0,
			0x1f, 0x9f, 0x0f, 0xcf, 0x83, 0xef, 0xf1, 0xc7, 0xc1, 0xe3, 0xe0,
			0xfb, 0xfc, 0x3f, 0x03, 0xf1, 0x1f, 0x9f, 0x0f, 0xcf, 0x83, 0xef,
			0xf1, 0xc7, 0xc3, 0xf3, 0xe0, 0xf9, 0xfc, 0x3f, 0x01, 0xf1, 0x9f,
			0x9e, 0x07, 0xcf, 0x83, 0xe7, 0xf1, 0xc7, 0xc3, 0xff, 0xe0, 0xf9,
			0xfc, 0x3e, 0x01, 0xf1, 0x9f, 0x9e, 0x07, 0xff, 0x83, 0xe7, 0xf1,
			0x87, 0xc1, 0xff, 0xe0, 0xf9, 0xfc, 0x3f, 0x01, 0xf0, 0x9f, 0x9f,
			0x07, 0xff, 0x03, 0xe7, 0xf3, 0x87, 0xc1, 0xff, 0xe0, 0xf8, 0xfc,
			0x3e, 0x03, 0xf0, 0xcf, 0x9f, 0x03, 0xfe, 0x03, 0xe3, 0xf3, 0xc0,
			0x00, 0xfb, 0xe0, 0xf8, 0xfc, 0x00, 0x01, 0xf0, 0xc0, 0x00, 0x00,
			0xfc, 0x03, 0xe3, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0xc0, 0x00, 0x1e, 0x00, 0x30, 0x00, 0x03, 0xfc, 0x60,
			0x00, 0x03, 0x1f, 0xc3, 0xb1, 0xc0, 0x00, 0xe0, 0x00, 0xff, 0xec,
			0x3c, 0x7f, 0x4f, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 0xfb, 0xc0,
			0x3f, 0xe0, 0x3b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd6,
			0x03, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff };

	// 'bluetooth_logo', 15x17px
	const unsigned char epd_bitmap_bt_logo[36] PROGMEM = { 0x00, 0x00, 0x00,
			0x00, 0x01, 0x00, 0x01, 0x80, 0x01, 0xc0, 0x09, 0x20, 0x07, 0x40,
			0x03, 0xc0, 0x03, 0x80, 0x03, 0x80, 0x07, 0xc0, 0x0d, 0x20, 0x09,
			0x60, 0x01, 0xc0, 0x01, 0x80, 0x01, 0x00, 0x00, 0x00 };

	
};

#endif /* SPARKDISPLAYCONTROL_H_ */
