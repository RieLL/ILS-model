#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QVector>

class DataImpl;

class Data
{
public:
    Data(QString fileName);
    virtual ~Data();

    QString readData(const int line, const int column) const;
    int line() const;
    int column() const;

private:
    DataImpl *dataImpl;
};

#endif // DATA_H
