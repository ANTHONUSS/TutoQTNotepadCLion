//
// Created by ANTHONUS on 11/06/2025.
//

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QFileDialog>
#include <QmessageBox>
#include <QFont>
#include <QFontDialog>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow {
Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad() override;

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void selectFont();
    void setItalic(bool italic);
    void setBold(bool bold);
    void setUnderline(bool underline);
    void showAbout();

private:
    Ui::Notepad *ui;
    QString currentFilePath;
};


#endif //NOTEPAD_H
