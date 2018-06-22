#include "hairstroke.h"

Hairstroke::Hairstroke() 
    : countHLines { 0 }
    , countVLines { 0 }
{
    //
}

Hairstroke::~Hairstroke()
{
    //
}

void Hairstroke::setCountLines(const int countHLines, const int countVLines)
{
    this->countHLines = { countHLines };
    this->countVLines = { countVLines };
}

void Hairstroke::setCountHLines(const int countHLines)
{
    this->countHLines = { countHLines };
}

void Hairstroke::setCountVLines(const int countVLines)
{
    this->countVLines = { countVLines };
}

int Hairstroke::getCountHLines() const
{
    return { this->countHLines };
}

int Hairstroke::getCountVLines() const
{
    return { this->countVLines };
}
