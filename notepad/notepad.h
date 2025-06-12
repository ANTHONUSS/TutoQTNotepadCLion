//
// Created by ANTHONUS on 11/06/2025.
//

#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QFileDialog>
#include <QmessageBox>
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

/* Les slots, c'est un peu comme des listeners. ça appelle une fonction quand une action s'est passée sur l'interface.
 * Dans le constructeur de Notepad, on a fait par exemple la ligne connect(ui->actionNouveau, &QAction::triggered, this, &Notepad::newDocument);
 * ça veut dire en gros que, quand on appuie (trigger) sur le bouton "actionNouveau" (qui a été définit dans l'application QT Designer) qui se trouve dans le Notepad.ui,
 * on appelle automatiquement la fonction "newDocument()" qui se trouve dans "this", dans ce cas là, la classe Notepad.
 */
private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void selectFont();
    void setItalic(bool italic); // Pour set un booléen dans un bouton, on coche la case "Checkable" dans QT Designer.
    void setBold(bool bold);
    void setUnderline(bool underline);
    void showAbout();

private:
    Ui::Notepad *ui; // ui représente le fichier Notepad.ui, donc quand on veut faire référence à un élément de QT Designer, on fait "ui->CODE"

    QString currentFilePath; // Chemin actuel du fichier chargé
};


#endif //NOTEPAD_H
