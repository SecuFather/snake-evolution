#ifndef SNAKECONTROL_H
#define SNAKECONTROL_H

#include <QThread>

class SnakeControl : public QThread
{
    Q_OBJECT
public:
    explicit SnakeControl(QObject *parent = 0);
    
signals:

public slots:
    
};

#endif // SNAKECONTROL_H
