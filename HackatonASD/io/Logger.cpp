#include "Logger.h"

QPlainTextEdit* Logger::qpte = 0;

void Logger::log(const char* type, const char* message, QColor c) {
    int r = c.red();
    int g = c.green();
    int b = c.blue();
    qpte->appendHtml(QString("<font size=\"16\">[<font color=\"%1\">%2</font>] %3</font>").arg(c.name(),type,message));
}

void Logger::info(const char* message) {
    log("info", message, QColorConstants::White);
}

void Logger::warning(const char* message) {
    log("warning", message, QColorConstants::Yellow);
}

void Logger::error(const char* message) {
    log("error", message, QColorConstants::Red);
}
