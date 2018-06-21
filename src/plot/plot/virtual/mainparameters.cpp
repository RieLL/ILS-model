#include "mainparameters.h"

MainParameters::MainParameters() :
    pitch(0),
    bank(0),
    frequency1(0.0),
    frequency2(0.0)
{
    //
}

MainParameters::~MainParameters()
{
    //
}



// START SETS
void MainParameters::setPitch(const int pitch)
{
    this->pitch = pitch;
}

void MainParameters::setBank(const int bank)
{
    this->bank = bank;
}

void MainParameters::setFreqKrm(const double frequency1)
{
    this->frequency1 = frequency1;
}

void MainParameters::setFreqGrm(const double frequency2)
{
    this->frequency2 = frequency2;
}
// END SETS



// START GETS
int MainParameters::getPitch() const
{
    return this->pitch;
}

int MainParameters::getBank() const
{
    return this->bank;
}

double MainParameters::getFreqKrm() const
{
    return this->frequency1;
}

double MainParameters::getFreqGrm() const
{
    return this->frequency2;
}
// END GETS
