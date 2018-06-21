#include "hairstroke.h"

Hairstroke::Hairstroke() :
    countHLines(0),
    countVLines(0)
{
    //
}

Hairstroke::~Hairstroke()
{
    //
}



// START SETS
void Hairstroke::setCountLines(const int countHLines, const int countVLines)
{
    this->countHLines = countHLines;
    this->countVLines = countVLines;
}

void Hairstroke::setCountHLines(const int countHLines)
{
    this->countHLines = countHLines;
}

void Hairstroke::setCountVLines(const int countVLines)
{
    this->countVLines = countVLines;
}
// END SETS



// START GETS
int Hairstroke::getCountHLines() const
{
    return this->countHLines;
}

int Hairstroke::getCountVLines() const
{
    return this->countVLines;
}
// END GETS
