#ifndef JLEVELS_H
#define JLEVELS_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>

class JHeaderRow
{
public:
    //JHeaderRow();
    void setupUI(QGridLayout *gridLayout, int row, int col);

    QLabel      *groupName;

private:
    QFrame      *rowFrame;
    QHBoxLayout *rowLayout;
};


class JItemRow : public QObject
{
    Q_OBJECT

public:
    JItemRow();
    virtual ~JItemRow() {};

    void setupUI(QGridLayout *gridLayout, int row, int col);
    void showLevel();

    int          myLevel;
    unsigned int itemNo;
    QLabel      *itemName;
    QToolButton *leveling;

public slots:
    void on_leveling_pressed();

private:
    QFrame      *rowFrame;
    QHBoxLayout *rowLayout;

};

#endif // JLEVELS_H
