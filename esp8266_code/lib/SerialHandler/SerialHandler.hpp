#pragma once

#include <stdint.h>

#define MAX_BUFFER_SIZE 64
#define START_CHAR '#'
#define END_CHAR '%'

class SerialHandler
{
private:
    char retreivedMessage[MAX_BUFFER_SIZE];
    uint32_t baudRate;
    uint16_t readCount;
    bool messageRetreived;
    bool isReading;

public:
    SerialHandler(uint32_t baudRate);
    void Begin();
    void SendMessage(const char* message);
    void BuildMessage();
    bool MessageRetreived() const;
    char* GetRetreivedMessage();
    void Clear();
};