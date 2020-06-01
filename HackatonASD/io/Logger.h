#pragma once
#include <iostream>
#include <QString>
#include <QPlainTextEdit>
class Logger {
public:
    static QPlainTextEdit* qpte;
    static void log(const char* type, const char* message) {
        qpte->appendPlainText("[" + QString(type) + "] " + QString(message));
    }

    static void info(const char* message) {
        log("info", message);
    }

    static void warning(const char* message) {
        log("warning", message);
    }

    static void error(const char* message) {
        log("error", message);
    }
};
