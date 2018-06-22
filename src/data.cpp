#include "data.h"

class DataImpl
{
public:
    DataImpl();
    ~DataImpl();
    void fOpen(QString fileName);

    QList<QString> fileArray;
    int line;
    int column;
};

DataImpl::DataImpl()
    : line {0}
    , column {0}
{
    //
}

DataImpl::~DataImpl()
{
    fileArray.clear();
}

void DataImpl::fOpen(QString fileName)
{
    QFile* file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);

    QByteArray fileRead;
    fileRead.append(file->readAll());

    file->close();
    delete file;

    line = fileRead.split('\n').length();
    column = (fileRead.split('@').length() / line) + 1;

    QList<QByteArray> arrayLine;
    arrayLine.append(fileRead.split('\n'));

    for (int i = 0; i < line; i++)
    {
        QList<QByteArray> arrayColumn;
        arrayColumn.append(arrayLine.value(i).split('@'));

        for (int j = 0; j < column; j++)
        {
            fileArray.append(arrayColumn.value(j));
        }
    }
}



Data::Data(QString fileName)
    : dataImpl {new DataImpl}
{
    dataImpl->fOpen(fileName);
}

Data::~Data()
{
    delete dataImpl;
}

QString Data::readData(const int line, const int column) const
{
    int element = (line * dataImpl->column) + column;
    return(dataImpl->fileArray.value(element));
}

int Data::line() const
{
    return dataImpl->line;
}

int Data::column() const
{
    return dataImpl->column;
}
