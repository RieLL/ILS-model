#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <QString>

class DataImpl;

struct SData
{
    uint32_t idPlot;
    uint32_t idFreq;
    uint32_t cLineH;
    uint32_t cLineV;
    uint32_t invelope;
    uint32_t idAxis;
    QString  namePlot;
};

class Data
{
public:
    explicit Data(QString& fileName);
    virtual ~Data();

    QList<SData>* getData() const;

private:
    DataImpl* m_pDataImpl;
};

#endif // DATA_H
