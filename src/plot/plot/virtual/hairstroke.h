#ifndef HAIRSTROKE_H
#define HAIRSTROKE_H

class Hairstroke
{
public:
    Hairstroke();
    virtual ~Hairstroke();

    virtual void setCountLines(const int countHLines, const int countVLines);
    virtual void setCountHLines(const int countHLines);
    virtual void setCountVLines(const int countVLines);

    virtual int  getCountHLines() const;
    virtual int  getCountVLines() const;

protected:
    int countHLines;
    int countVLines;
};

#endif // HAIRSTROKE_H
