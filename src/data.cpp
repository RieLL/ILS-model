#include "data.h"
#include <QFile>
#include <QList>

class DataImpl
{
public:
    explicit DataImpl();
    explicit DataImpl(QString& fileName);
    ~DataImpl();
    void fOpen(QString& fileName);

    QList<SData> m_SData;
};

DataImpl::DataImpl()
{
    //
}

DataImpl::DataImpl(QString& fileName)
    : DataImpl ()
{
    this->fOpen(fileName);
}

DataImpl::~DataImpl()
{
    //
}

void DataImpl::fOpen(QString& fileName)
{
    QFile* pFile = { new QFile(fileName) };
    pFile->open(QIODevice::ReadOnly);

    while ( !pFile->atEnd() )
    {
        SData tmpSData = {};
        QByteArray fileRead = { pFile->readLine() };
        QList<QByteArray> array( fileRead.split('@') );

        tmpSData.idPlot   = { array.value(0).toUInt() };
        tmpSData.idFreq   = { array.value(1).toUInt() };
        tmpSData.cLineH   = { array.value(2).toUInt() };
        tmpSData.cLineV   = { array.value(3).toUInt() };
        tmpSData.invelope = { array.value(4).toUInt() };
        tmpSData.idAxis   = { array.value(5).toUInt() };
        tmpSData.namePlot = { array.value(6) };

        m_SData.append(tmpSData);

        array.clear();
    }

    pFile->close();
    delete pFile;
}



Data::Data(QString& fileName)
    : m_pDataImpl { new DataImpl(fileName) }
{
    //
}

Data::~Data()
{
    delete m_pDataImpl;
}

QList<SData>* Data::getData() const
{
    return { &(m_pDataImpl->m_SData) };
}
