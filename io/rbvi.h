#ifndef RBVI_H
#define RBVI_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
/*
   RBVI stands for Raw Binary Vector Image
   This is intended to be an intermediary vector image format for rendering in OpenGL, DirectX, Vulkan, etc.
   It is intended that SVG images would be triangulated and converted to this before being rendered.
   To avoid unnecessary re-triangulating, these files should be saved and used as a cache of a sort.
   Or even supplies in videogames as a whole.
*/
typedef struct _RbviHeader
{
	char magicWord[5]; // Always supposed to be 'R', 'B', 'V', 'I', '\0'
	uint16_t layerCount;
	uint32_t canvasWidth; // In pixels
	uint32_t canvasHeight; // In pixels
	uint8_t vectorFormat; // 0x01 means float vertices, 0x10 means uint32_t vertices that need conversion to floats and division by canvas resolution
} RbviHeader;
/*
   The main difference between vector format 0x01 and 0x10 is that
   - 0x01 has floats with values between 0.0f and 1.0f representing the top/bottom and left/right edge of the canvas
   - 0x10 has uint32_t with values between 0 and either canvasWidth or canvasHeight.
   This means that for 0x10, before we want to render it in OpenGL, DirectX, Vulkan, whatever
   We will be forced to convert these uint32_t values to floats, and divide them with canvasWidth or canvasHeight
*/
typedef struct _RbviVertex0x01
{
	float x;
	float y;
} RbviVertex0x01;
typedef struct _RbviVertex0x10
{
	uint32_t x;
	uint32_t y;
} RbviVertex0x10;
typedef struct _RbviColour
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} RbviColour;
typedef struct _RbviLayerHeader
{
	uint32_t vertexCount; // Each vertex is either 2 * sizeof(float) or 2 * sizeof(uint32_t) big.
	uint32_t indexCount; // Each index is sizeof(int) big.
	RbviColour colourA; // RGBA
	RbviColour colourB; // RGBA
	uint8_t colourMode; // 0x01 means a gradient going from one edge to the other, 0x10 means a gradient where colour changes based off distance from center
} RbviLayerHeader;
/*
   Colours are given in RGBA. If we want to render in OpenGL, we will be forced to convert it to a vector of 4 floating point values
   by converting each of the four RGBA components to float and dividing by 255
*/
#ifdef __cplusplus
}
#endif
#endif // RBVI_H
