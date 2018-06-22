#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QString>
#include "virtual/window.h"
#include "virtual/mainparameters.h"

class Signature : public Window, public MainParameters
{
public:
    explicit Signature();
    virtual ~Signature();

    void drawElement(QPainter* painter) override;
    void setText(const QString& str);

private:
    QString str;
};

#endif // SIGNATURE_H
