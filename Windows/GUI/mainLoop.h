#include"classLib.h"
#include"libCommon.h"


#ifndef MAINLOOP_H
#define MAINLOOP_H

class mainLoop :public QThread
{
    Q_OBJECT;
signals:
    void sentCpuUsage(int usage);

    void sentDiskIO(io diskIO);
    void sentDiskRead(io read);
    void sentDiskWrite(io write);

    void sentNetworkDownload(io download);
    void sentNetworkUpload(io upload);

    void sentMemoryUsage(int usage);

public:


};



#endif


