#ifndef MY_THREAD_H
#define MY_THREAD_H

#include<QThread>
#include<QMutex>
#include<QTimer>

class my_thread : public QThread
{
    Q_OBJECT // Добавляем для работы с сигналами(после добавления надо удалить катало build.

public:
    my_thread(int seed);
    ~my_thread();

    void run();

    QMutex * mtx;
    int stch;
    int com;
    int trans;
    int st;

signals:
    void status_upd(int);

};

#endif // MY_THREAD_H
