#include <SimpleRowDrawer.hpp>

const uint8_t outputMode = 1;

const uint8_t low = 0;
const uint8_t high = 1;

const uint32_t CLOCK_TIME_MICRO = 40;

const uint8_t rowLength = 32;
const uint32_t dataMaskValue = 0x00000001;

SimpleRowDrawer::SimpleRowDrawer(MatrixTimer& timer, RowPinLayout layout, IOFunction function)
: timer(timer)
{
    // Kan misschien vervangen worden met memset.
    // for(int i = 0; i < ROW_COUNT_PER_COLOR; i++)
    // {
    //     redRows[i] = 0;
    //     greenRows[i] = 0;
    //     blueRows[i] = 0;
    // }
    for(int i = 0; i < ROW_COUNT_PER_COLOR; i++)
    {
        colorRow[i] = 0;
    }

    this->layout = layout;
    pinMode = function.pinModePtr;
    digitalWrite = function.digitalWritePtr;
    setColorPins = function.setColorPins;
    clockActive = false;
    dataLoaded = false;
    column = 0;
}

void SimpleRowDrawer::Setup()
{
    pinMode(layout.clk, outputMode);
    pinMode(layout.r1, outputMode);
    pinMode(layout.g1, outputMode);
    pinMode(layout.b1, outputMode);
    pinMode(layout.r2, outputMode);
    pinMode(layout.g2, outputMode);
    pinMode(layout.b2, outputMode);

    digitalWrite(layout.clk, low);
    digitalWrite(layout.r1, low);
    digitalWrite(layout.g1, low);
    digitalWrite(layout.b1, low);
    digitalWrite(layout.r2, low);
    digitalWrite(layout.g2, low);
    digitalWrite(layout.b2, low);
}

void SimpleRowDrawer::SetRows(uint32_t* redArray, uint32_t* greenArray, uint32_t* blueArray)
{
    if((redArray == nullptr) || (greenArray == nullptr) || (blueArray == nullptr))
    {
        return; // Misschien veranderen naar een error code.
    }

    // Dit zal fout gaan als de size/count niet klopt van de ptr argumenten.
    for(int i = 0; i < ROW_COUNT_PER_COLOR; i++)
    {
        // redRows[i] = redArray[i];
        // greenRows[i] = greenArray[i];
        // blueRows[i] = blueArray[i];
    }
}

void SimpleRowDrawer::SetRows(uint8_t* colorBuffer)
{
    if(colorBuffer == nullptr)
    {
        return;
    }

    for(int i = 0; i < ROW_COUNT_PER_COLOR; i++)
    {
        colorRow[i] = colorBuffer[i];
    }
}

bool SimpleRowDrawer::Draw(bool drawEnable)
{
    bool drawingFinished = false;

    if(!drawEnable)
    {
        return drawingFinished;
    }

    if(timer.IsFinished())
    {
        toggleClock();
    }

    if(!timer.IsStarted())
    {
        timer.Start(CLOCK_TIME_MICRO);
    }

    timer.Run();
    loadData();

    if(column == rowLength)
    {
        column = 0;
        digitalWrite(layout.r1, low);
        digitalWrite(layout.g1, low);
        digitalWrite(layout.b1, low);
        digitalWrite(layout.r2, low);
        digitalWrite(layout.g2, low);
        digitalWrite(layout.b2, low);
        drawingFinished = true;
        dataLoaded = false;
        timer.SetTemp();
    }

    return drawingFinished;
}

void SimpleRowDrawer::loadData()
{
    if(!dataLoaded)
    {
        // drawPixel(layout.r1, redRows[0]);
        // drawPixel(layout.g1, greenRows[0]);
        // drawPixel(layout.b1, blueRows[0]);
        // drawPixel(layout.r2, redRows[1]);
        // drawPixel(layout.g2, greenRows[1]);
        // drawPixel(layout.b2, blueRows[1]);
        // drawPixels();

        setColorPins(colorRow[column]);

        column++;
        dataLoaded = true;
    }
}

void SimpleRowDrawer::drawPixel(uint8_t pin, uint32_t row)
{
    // uint32_t data = row;
    // uint32_t mask = (dataMaskValue << ((rowLength - 1) - column));
    // data &= mask;
    // data = data >> ((rowLength - 1) - column);
    // digitalWrite(pin, (uint8_t)data);
    digitalWrite(pin, high);
}

void SimpleRowDrawer::toggleClock()
{
    clockActive = !clockActive;

    if(clockActive)
    {
        digitalWrite(layout.clk, high);
    }
    else
    {
        digitalWrite(layout.clk, low);
        dataLoaded = false;
    }
}