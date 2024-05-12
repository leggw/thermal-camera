#include <Melopero_AMG8833.h>
#include "VirtualPanel.h"

Melopero_AMG8833 sensor;

bool panelInitialized = false; // Flag for panel initialization
bool powerOn = false; // Camera power state
bool infoPanelEnabled = false;
int statusCode = 0; // AGM8833 status 
float interpolatedPixels[10][10]; // Buffer for pixel interpolation
float highestTemperature = 0.0; // Highest temperature in frame
float lowestTemperature = 0.0; // Lowest temperature in frame
float centerTemperature = 0.0; // Temperature at center of frame
float scaleTop = 25.0; // Upper limit of color scale
float scaleBottom = 15.0; // Lower limit of color scale
float scaleStep = 0; // Step size of color scale
byte scaleOffset = 30;
byte horizontalOffset = ((255 - (16 * 8)) / 2) + 8 + 35; // Calculate horizontal image position
byte verticalOffset = ((220 - (16 * 8)) / 2) + 8; 
enum ImageMode { RAW, INTERPOLATED_29, INTERPOLATED_64 };
ImageMode selectedImageMode = RAW;
enum StillMode { OFF, CAPTURE, WRITE, DISPLAY};
StillMode stillMode = OFF;
byte interpolationPoints = 1;
byte pixelsPerRow = 16;
byte clickX = 0;
byte clickY = 0;
bool mirrorEnabled = false;

//----------------------------------------------------------------------------
void setup() 
{
  Panel.begin(); // Initialize port and protocol
  while(!panelInitialized) 
    Panel.receive(); // Wait for panel initialization
  Wire.begin(); // Start I2C  
  initializeAMG8833();  // Initialize AMG8833 sensor
}

//----------------------------------------------------------------------------
void loop() 
{
  Panel.receive(); // Read panel input

  if(powerOn) // If camera is powered on
  {
    readSensorData(); // Read sensor data
  } 
}
