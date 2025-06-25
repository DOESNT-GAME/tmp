#include "sha384.h"
#include <QCryptographicHash>

QString SHA384::hash(const QString& input)
{
    return QString(QCryptographicHash::hash(
                       input.toUtf8(), QCryptographicHash::Sha384).toHex());
}
