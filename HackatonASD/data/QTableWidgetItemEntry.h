#pragma once
#include <QTableWidgetItem>
template <typename T>
class QTableWidgetItemEntry : public QTableWidgetItem {
public:
    using QTableWidgetItem::QTableWidgetItem;
    T* e;
};