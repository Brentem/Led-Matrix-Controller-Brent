#include "SerialHandler.hpp"

#include <Arduino.h>

SerialHandler::SerialHandler(uint32_t baudRate)
{
    Clear();
    this->baudRate = baudRate;
}

void SerialHandler::Begin()
{
    Serial.begin(baudRate);
}

void SerialHandler::SendMessage(const char* message)
{
    Serial.print(START_CHAR);
    Serial.print(message);
    Serial.print(END_CHAR);
}

void SerialHandler::BuildMessage()
{
    char readChar = 0;

    if(Serial.available())
    {
        readChar = Serial.read();

        if(readChar == END_CHAR)
        {
            isReading = false;
            messageRetreived = true;
        }

        if(isReading)
        {
            retreivedMessage[readCount] = readChar;
            readCount++;
        }
    }

    if(readChar == START_CHAR)
    {
        Clear();
        isReading = true;
    }
}

bool SerialHandler::MessageRetreived() const
{
    return messageRetreived;
}

char* SerialHandler::GetRetreivedMessage()
{
    if(!messageRetreived)
        return nullptr;
    
    return retreivedMessage;
}

void SerialHandler::Clear()
{
    isReading = false;
    messageRetreived = false;
    readCount = 0;
    
    for(uint16_t i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        retreivedMessage[i] = 0;
    }
}