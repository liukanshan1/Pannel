#include"classLib.h"
#include"libCommon.h"
#ifndef MAINLOOP_H
#define MAINLOOP_H
class mainLoop : public QThread
{
	Q_OBJECT

signals:
    //Sent Info
    void sentCpuUsage(int usage);
    void sentDiskIO(io diskIO, io read, io write);
    void sentDiskUsage(std::string name, std::string usage);
    void sentNetworkUD(io upload,io download);
    void sentRunningTime(runningTime t);
    void sentMemoryUsage(int usage,double freespace);
    //Allert
    void diskUsageWarning(char d, int usage);
    void memoryUsageWarning(int usage, bool status = false);
    void cpuUsageWarning(int usage, bool status = false);

public slots:
    void stopLoop();
public:
    mainLoop(QObject* parent,
        CPU* myCPU,
        disks* myDisks,
        memory* myMemory,
        network* myNetwork,
        operatingSystem* mySystem,
        update* myUpdate);
	~mainLoop();
    void run()override;
private:
    QMutex lock;
    bool running = true;
    CPU* myCPU = nullptr;
    disks* myDisks = nullptr;
    memory* myMemory = nullptr;
    network* myNetwork = nullptr;
    operatingSystem* mySystem = nullptr;
    update* myUpdate = nullptr;
};
#endif