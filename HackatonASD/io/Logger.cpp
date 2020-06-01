#include "Logger.h"

QPlainTextEdit* Logger::qpte = 0;

void Logger::log(const char* type, const char* message) {
    qpte->appendPlainText("[" + QString(type) + "] " + QString(message));
}

void Logger::info(const char* message) {
    log("info", message);
}

void Logger::warning(const char* message) {
    log("warning", message);
}

void Logger::error(const char* message) {
    log("error", message);
}
