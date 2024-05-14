#include "my_thread.h"

my_thread::my_thread(int seed)//конструктор потоков
{
    mtx= new QMutex;

    st = seed;

    mtx->lock();// захватили мьютекс

    stch = 0;
    com = 0;// команды/ответа нет

}

my_thread::~my_thread() //деструктор потоков
{
    mtx->unlock();
    delete mtx;
}

void my_thread::run(){      //переопределенная функция ран
    srand(unsigned(st));//rand()*time(nullptr));
    do
    {
        mtx->lock();//попытка захывата мьютекса
        int r;
        switch(com)
        {
        case 1://была команда работа( work)
            com = 3;
            r = rand()%10000;
            msleep(unsigned(r));
            stch = r;
            break;
        case 2 : //была командапора завершать существование
            com = 4;
            r = rand()%10000;
            msleep(unsigned(r));
            stch = r;
            break;
        case 5 :
            com = 4;
            break;
        default:
            com = 0;
            break;
        }
        emit status_upd(trans);
    }
    while(com!=4);//пока не пришло время умирать
}
