#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDebug>
//qt container
#include <QList>
#include <QVarLengthArray>
#include <QVector>

//stl container
#include <iostream>
#include <vector>
#include <windows.h>
#include <psapi.h>

QElapsedTimer timer;
const int MyCOLLECTIONSIZE = 1e7;
const int InserCount = 20;
qint64 time;
unsigned int compare(0);
int theMiddle=MyCOLLECTIONSIZE/2;
int theLast=theMiddle-1;
double insertValue=2.2;
void showMemoryInfo(unsigned int & compareValue )
{
    HANDLE handle=GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
    unsigned int size = pmc.WorkingSetSize/1000;

    if(compareValue!=0)
    {
        compareValue =size - compareValue;
    }
    qDebug()<<"内存使用:"<<size <<"K"<<"多使用了"<< compareValue;
    compareValue=size;
}

void QListTest()
{
    qDebug()<<"----------QList<double>----------------";
    QList<double> qListDouble;
    //qListDouble.reserve(SIZE);
    showMemoryInfo(compare);
    timer.start();
    for(int i = 0;i <MyCOLLECTIONSIZE; i++){
        qListDouble << i;
    }

    time = timer.elapsed();

    qDebug()<<"插入 "<<MyCOLLECTIONSIZE<<"数据 时间"<<time;
    showMemoryInfo(compare);

    timer.start();

    for(int i=0;i<InserCount;i++)
    {
        qListDouble.insert(0,insertValue);

        qListDouble.insert(theMiddle,insertValue);

        qListDouble.insert(theMiddle,insertValue);

    }
    time = timer.elapsed();

    qDebug()<<"修改操作时间 "<<time;
    showMemoryInfo(compare);
    qListDouble.clear();
    compare=0;
}

void QVectorTest()
{
    qDebug()<<"----------QVector<double>----------------";
    QVector<double> qQVector;
    //qQVector.reserve(SIZE);
    showMemoryInfo(compare);
    timer.start();
    for(int i = 0;i <MyCOLLECTIONSIZE; i++){
        qQVector << i;
    }

    time = timer.elapsed();
    qDebug()<<"插入 "<<MyCOLLECTIONSIZE<<"数据 时间"<<time;
    showMemoryInfo(compare);

    timer.start();
    for(int i=0;i<InserCount;i++)
    {
        qQVector.insert(0,insertValue);

        qQVector.insert(theMiddle,insertValue);

        qQVector.insert(theLast,insertValue);
    }
    time = timer.elapsed();
    qDebug()<<"修改操作时间 "<<time;
    showMemoryInfo(compare);
    qQVector.clear();
    compare=0;

}

void QVarLengthArrayTest()
{
    qDebug()<<"----------QVarLengthArray<double>----------------";
    QVarLengthArray<double> qVarlenArr;
    //qVarlenArr.reserve(SIZE);
    showMemoryInfo(compare);
    timer.start();
    for(int i = 0;i <MyCOLLECTIONSIZE; i++){
        qVarlenArr << i;
    }
    time = timer.elapsed();
    qDebug()<<"插入 "<<MyCOLLECTIONSIZE<<"数据 时间"<<time;
    showMemoryInfo(compare);

    timer.start();
    for(int i=0;i<InserCount;i++)
    {

        qVarlenArr.insert(0,insertValue);

        qVarlenArr.insert(theMiddle,insertValue);

        qVarlenArr.insert(theLast,insertValue);
    }
    time = timer.elapsed();
    qDebug()<<"修改操作时间 "<<time;
    showMemoryInfo(compare);
    qVarlenArr.clear();
    compare=0;
}

void stlVectorTest()
{
    //STL vector测试
    qDebug()<<"----------STL vector<double>----------------";
    std::vector<double> stlVector;
    showMemoryInfo(compare);
    timer.start();
    for(int i = 0;i <MyCOLLECTIONSIZE; i++){
        stlVector.push_back(i);
    }
    time = timer.elapsed();
    qDebug()<<"插入 "<<MyCOLLECTIONSIZE<<"数据 时间"<<time;
    showMemoryInfo(compare);

    timer.start();

    for(int i=0;i<InserCount;i++)
    {
        stlVector.insert(stlVector.begin(),insertValue);
        stlVector.insert(stlVector.begin()+theMiddle,insertValue);
        stlVector.insert(stlVector.end(),insertValue);
    }

    time = timer.elapsed();
    qDebug()<<"修改操作时间 "<<time;
    showMemoryInfo(compare);
    stlVector.clear();
    compare=0;
}

void stlListTest()
{
    //STL List测试
    qDebug()<<"----------STL List<double>----------------";
    std::list<double> stlList;
    showMemoryInfo(compare);
    timer.start();
    for(int i = 0;i <MyCOLLECTIONSIZE; i++){
        stlList.push_back(i);
    }
    time = timer.elapsed();
    qDebug()<<"插入 "<<MyCOLLECTIONSIZE<<"数据 时间"<<time;
    showMemoryInfo(compare);

    std::list<double>::iterator it = stlList.begin();
    std::advance(it, std::distance(stlList.begin(), stlList.end())/2);
    timer.start();

    for(int i=0;i<InserCount;i++)
    {
        stlList.insert(stlList.begin(),insertValue);
        stlList.insert(it,insertValue);
        stlList.insert(stlList.end(),insertValue);
    }
    time = timer.elapsed();
    qDebug()<<"修改操作时间 "<<time;
    showMemoryInfo(compare);
    stlList.clear();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QListTest();
    QVectorTest();
    QVarLengthArrayTest();
    stlVectorTest();
    stlListTest();

    return a.exec();
}
