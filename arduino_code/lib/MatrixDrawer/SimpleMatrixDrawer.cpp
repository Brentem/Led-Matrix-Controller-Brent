#include <SimpleMatrixDrawer.hpp>

const uint8_t outputMode = 1;

const uint8_t low = 0;
const uint8_t high = 1;

const uint32_t CLOCK_TIME_MICRO = 40;

const uint8_t AddrAMask = 0x01;
const uint8_t AddrBMask = 0x02;
const uint8_t AddrCMask = 0x04;

SimpleMatrixDrawer::SimpleMatrixDrawer(SimpleRowDrawer& rowDrawer, MatrixTimer& timer,
 MatrixPinLayout layout, IOFunction function)
: rowDrawer(rowDrawer), timer(timer)
{
    this->layout = layout;
    pinMode = function.pinModePtr;
    digitalWrite = function.digitalWritePtr;

    for(int i = 0; i < BUFFER_COUNT; i++)
    {
        redBuffer[i] = 0;
        greenBuffer[i] = 0;
        blueBuffer[i] = 0xFFFFFFFF;
    }

    drawEnable = false;
    signalEnable = false;
    signalCounter = 0;
    address = 0;
}

void SimpleMatrixDrawer::Setup()
{
    rowDrawer.Setup();
    
    pinMode(layout.addrA, outputMode);
    pinMode(layout.addrB, outputMode);
    pinMode(layout.addrC, outputMode);
    pinMode(layout.oe, outputMode);
    pinMode(layout.lat, outputMode);

    digitalWrite(layout.addrA, low);
    digitalWrite(layout.addrB, low);
    digitalWrite(layout.addrC, low);
    digitalWrite(layout.oe, low);
    digitalWrite(layout.lat, low);
}

void SimpleMatrixDrawer::TempFunction()
{
    uint32_t redArray[2] = {redBuffer[0], redBuffer[1]};
    uint32_t greenArray[2] = {greenBuffer[0], greenBuffer[1]};
    uint32_t blueArray[2] = {blueBuffer[0], blueBuffer[1]};

    rowDrawer.SetRows(redArray, greenArray, blueArray);

    drawEnable = true;
}

void SimpleMatrixDrawer::Draw()
{
    bool finishedDrawing = rowDrawer.Draw(drawEnable);

    if(finishedDrawing)
    {
        drawEnable = false;
        signalEnable = true;

        address++;
        if(address > 7)
        {
            address = 0;
        }
    }

    if(!signalEnable)
    {
       setAddress();
    }

    handleTimer();
    setOE_Latch();
}

void SimpleMatrixDrawer::setAddress()
{
    uint8_t addrA = address & AddrAMask;
    uint8_t addrB = address & AddrBMask;
    addrB = addrB >> 1;
    uint8_t addrC = address & AddrCMask;
    addrC = addrC >> 2;

    digitalWrite(layout.addrA, addrA);
    digitalWrite(layout.addrB, addrB);
    digitalWrite(layout.addrC, addrC);
}

void SimpleMatrixDrawer::handleTimer()
{
    if(signalEnable && !timer.IsStarted())
    {
        timer.Start(CLOCK_TIME_MICRO);
    }

    timer.Run();

    if(timer.IsFinished())
    {
        signalCounter++;
    }
}

void SimpleMatrixDrawer::setOE_Latch()
{
    if(signalCounter == LATCH)
    {
        digitalWrite(layout.lat, high);
        digitalWrite(layout.oe, low);
    }
    else if(signalCounter == OUTPUT_ENABLE)
    {
        digitalWrite(layout.lat, low);
        digitalWrite(layout.oe, high);
    }
    else if(signalCounter == STOP_SIGNALS)
    {
        signalCounter = 0;
        digitalWrite(layout.lat, low);
        digitalWrite(layout.oe, low);
        timer.Reset();
        signalEnable = false;
        drawEnable = true;
    }
}