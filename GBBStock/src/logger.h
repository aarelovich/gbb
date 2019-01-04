#ifndef LOGGER_H
#define LOGGER_H

#define LOG_FILE "logfile.log"

#include <QFile>
#include <QTextStream>

class Logger
{
public:
    Logger();
    void log();
};

#endif // LOGGER_H
