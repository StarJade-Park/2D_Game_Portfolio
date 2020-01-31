#include "GameColor.h"

GameColor GameColor::Magenta		= GameColor(__tag::max, __tag::zero, __tag::max);
GameColor GameColor::Red			= GameColor(__tag::max, __tag::zero, __tag::zero);
GameColor GameColor::Green			= GameColor(__tag::zero, __tag::max, __tag::zero);
GameColor GameColor::Lime			= GameColor(__tag::zero, __tag::max, __tag::zero);
GameColor GameColor::Blue			= GameColor(__tag::zero, __tag::zero, __tag::max);
GameColor GameColor::White			= GameColor(__tag::max, __tag::max, __tag::max);
GameColor GameColor::Black			= GameColor(__tag::zero, __tag::zero, __tag::zero);

GameColor GameColor::Top__		= GameColor(0, 255, 127);
GameColor GameColor::Bottom__	= GameColor(0, 0, 255); // blue
GameColor GameColor::Left__		= GameColor(255, 255, 0); // yello
GameColor GameColor::Right__	= GameColor(229, 0, 79);

const int GameColor::mBitmaskRed = 0x0000ff;  // 255
const int GameColor::mBitmaskGreen = 0x00ff00; // 65280
const int GameColor::mBitmaskBlue = 0xff0000;  // 16711680