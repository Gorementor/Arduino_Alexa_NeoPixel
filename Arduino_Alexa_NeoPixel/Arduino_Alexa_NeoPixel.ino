/*
 Name:		Arduino_Alexa_NeoPixel.ino
 Created:	12/18/2017 3:41:54 PM
 Author:	Sven
*/

#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

static int rgbColour[3] = { 255, 0, 0 }; // start with red
static int pixel = 0;
static int prevpixel = 23;

// the setup function runs once when you press reset or power the board
void setup() {
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
	strip.setBrightness(10);
}

// the loop function runs over and over again until power down or reset
void loop() {
	// reset
	if (pixel >= 24) pixel = 0;

	// set random r,g,b color values
	//r = random(256);
	//g = random(256 - r);
	//b = (255 - r - g);

	// Choose the colours to increment and decrement.
	for (int decColour = 0; decColour < 3; decColour += 1) {
		int incColour = decColour == 2 ? 0 : decColour + 1;

		// cross-fade the two colours.
		for (int i = 0; i < 255; i += 1) {
			rgbColour[decColour] -= 1;
			rgbColour[incColour] += 1;

			if (pixel >= 24) pixel = 0;

			//strip.setPixelColor(prevpixel, 0, 0, 0);
			strip.setPixelColor(pixel, rgbColour[0], rgbColour[1], rgbColour[2]);
			strip.show();

			delay(100);

			prevpixel = pixel;
			pixel++;

		}
	}

	// strip.setPixelColor(n, red, green, blue, white);
	//strip.setPixelColor(prevpixel, 0, 0, 0);
	//strip.setPixelColor(pixel, 70, 125, 180);
	//strip.setPixelColor(pixel, r, g, b);
	strip.show();

	delay(100);

	prevpixel = pixel;
	pixel++;
}
