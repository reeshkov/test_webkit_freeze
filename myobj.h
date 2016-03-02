#ifndef MYOBJ_H
#define MYOBJ_H

#include <QObject>
#include <QDebug>

#include <QThread>
#include <QTimer>

#define FREEZE_PERIOD_MS 500

class MyObj : public QObject {
    Q_OBJECT
public:
    MyObj() {
        qDebug()<< "Constructor MyObj";
        freezer = new QTimer(this);
        connect( freezer,SIGNAL(timeout()),this,SLOT(mySlot()) );
        freezer->setInterval(FREEZE_PERIOD_MS);
        freezer->start();
    }
    ~MyObj();
signals:
    void mySignal();
private:
    struct NOP : public QThread { using QThread::msleep;};
    QTimer *freezer;
private slots:
    void mySlot(){ qDebug("freeze");NOP::msleep(FREEZE_PERIOD_MS);qDebug("unfreeze"); }
};

#endif // MYOBJ_H
