#ifndef OP_H
#define OP_H

#include <QObject>

class op : public QObject
{
    Q_OBJECT
public:
    explicit op(QObject *parent = nullptr);

signals:

public slots:
};

#endif // OP_H
