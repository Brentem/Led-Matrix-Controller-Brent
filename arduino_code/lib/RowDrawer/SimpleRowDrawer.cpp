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
    for(int i = 0; i < ROW_COUNT_PER_COLOR; i++)
    {
        redRows[i] = 0;
        greenRows[i] = 0;
        blueRows[i] = 0;
    }

    this->layout = layout;
    pinMode = function.pinModePtr;
    digitalWrite = function.digitalWritePtr;
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
        redRows[i] = redArray[i];
        greenRows[i] = greenArray[i];
        blueRows[i] = blueArray[i];
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
        drawPixel(layout.b1, blueRows[0]);
        // drawPixel(layout.r2, redRows[1]);
        // drawPixel(layout.g2, greenRows[1]);
        drawPixel(layout.b2, blueRows[1]);
        // drawPixels();

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

void SimpleRowDrawer::drawPixels()
{
    uint32_t mask = (dataMaskValue << ((rowLength - 1) - column));

    uint8_t r1 = (uint8_t)((redRows[0] & mask) >> ((rowLength - 1) - column));
    uint8_t g1 = (uint8_t)((greenRows[0] & mask) >> ((rowLength - 1) - column));
    uint8_t b1 = (uint8_t)((blueRows[0] & mask) >> ((rowLength - 1) - column));

    uint8_t r2 = (uint8_t)((redRows[1] & mask) >> ((rowLength - 1) - column));
    uint8_t g2 = (uint8_t)((greenRows[1] & mask) >> ((rowLength - 1) - column));
    uint8_t b2 = (uint8_t)((blueRows[1] & mask) >> ((rowLength - 1) - column));

    uint8_t rgb = r1;
    rgb |= g1 << 1;
    rgb |= b1 << 2;

    rgb |= r2 << 3;
    rgb |= g2 << 4;
    rgb |= b2 << 5;

    setColorPins(rgb);
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