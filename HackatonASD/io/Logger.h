#pragma once
#include <iostream>
#include <QString>
#include <QPlainTextEdit>
#include <QColor>
class Logger {
public:
    static QPlainTextEdit* qpte;
    static void log(const char* type, const char* message, QColor c);

    static void info(const char* message);

    static void warning(const char* message);

    static void error(const char* message);
};
