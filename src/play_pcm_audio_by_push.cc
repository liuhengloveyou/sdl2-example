#include <iostream>

extern "C"
{
#include "SDL.h"
}

int PlayPcmByPush()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    FILE *pFile = fopen("data/44100_16bit_2ch.pcm", "rb");
    if (!pFile)
    {
        std::cout << "file not exist!!!" << std::endl;
        return -1;
    }

    SDL_AudioSpec audioSpec;
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_S16SYS;
    audioSpec.channels = 2;
    audioSpec.silence = 0;
    audioSpec.samples = 1024;
    audioSpec.callback = nullptr;

    SDL_AudioDeviceID deviceId;
    if ((deviceId = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0)) < 2)
    {
        std::cout << "open audio device failed " << std::endl;
        return -1;
    }

    int bufferSize = 4096;
    char *buffer = (char *)malloc(bufferSize);

    SDL_Window *window = SDL_CreateWindow("SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_ALLOW_HIGHDPI);

    // 创建渲染器
    SDL_Renderer *pRenderer = SDL_CreateRenderer(window, -1, 0);
    // 指定渲染颜色
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    // 清空当前窗口的颜色
    SDL_RenderClear(pRenderer);
    // 执行渲染操作，更新窗口
    SDL_RenderPresent(pRenderer);

    SDL_PauseAudioDevice(deviceId, 0);

    while (true)
    {
        int num = fread(buffer, 1, bufferSize, pFile);
        std::cout << "read: " << num << std::endl;
        if (num)
        {
            SDL_QueueAudio(deviceId, buffer, bufferSize);
        } else {
            break;
        }

        SDL_Delay(20);
    }

    SDL_Delay(1000);

    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent))
    {
        switch (windowEvent.type)
        {
        case SDL_QUIT:
            break;
        default:
            break;
        }
    }

    free(buffer);
    SDL_DestroyWindow(window);
    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}