#pragma once

// exe에서는 아래 주석을 해제해야 동작
#define EXE_EXPORT

#ifndef EXE_EXPORT
#define IMAGE_PATH(S) (L"..\\..\\..\\4_Resources\\"#S)
#else
#define IMAGE_PATH(S) (L"Resources\\"#S)
#endif

#ifndef EXE_EXPORT
#define SOUND_PATH(S) ("..\\..\\..\\4_Resources\\Sound\\"#S)
#else
#define SOUND_PATH(S) ("Resources\\Sound\\"#S)
#endif