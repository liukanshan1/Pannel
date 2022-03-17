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
    void sentDiskIO(io diskIO);
    void sentDiskRead(io read);
    void sentDiskWrite(io write);
    void sentNetworkDownload(io download);
    void sentNetworkUpload(io upload);
    void sentRunningTime(runningTime t);
    void sentMemoryUsage(int usage,double freespace);
    void sentDiskUsage(int* usage,double* freeSpace);
    //Allert
    void diskUsageWarning(char d,int usage,bool status=false);
    void memoryUsageWarning(int usage, bool status = false);
    void cpuUsageWarning(int usage, bool status = false);
    void diskIOWarning(io diskIO, bool status = false);
    void diskReadWarning(io read, bool status = false);
    void diskWriteWarning(io write, bool status = false);
    void netIOWarning(io networkio, bool status = false);
    void netUploadWarning(io upload, bool status = false);
    void netDownloadWarning(io download, bool status = false);



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

    void create5minLog(int memoryUsageAver, int cpuUsageAver, io diskReadAver, io diskWriteAver, io diskIOAver, io netUploadAver, io netDownloadAver);
};
#endif