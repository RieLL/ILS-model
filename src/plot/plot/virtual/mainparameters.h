#ifndef MAINPARAMETERS_H
#define MAINPARAMETERS_H

class MainParameters
{
public:
    MainParameters();
    virtual ~MainParameters();

    virtual void   setPitch(const int pitch);
    virtual void   setBank(const int bank);
    virtual void   setFreqKrm(const double frequency1);
    virtual void   setFreqGrm(const double frequency2);

    virtual int    getPitch() const;
    virtual int    getBank() const;
    virtual double getFreqKrm() const;
    virtual double getFreqGrm() const;

protected:
    int pitch;
    int bank;
    double frequency1;
    double frequency2;
};

#endif // MAINPARAMETERS_H
