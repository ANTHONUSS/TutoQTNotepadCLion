//
// Created by ANTHONUS on 11/06/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Notepad.h" resolved

#include "notepad.h"
#include "ui_Notepad.h"


Notepad::Notepad(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::Notepad)
{
    ui->setupUi(this);


    // Connecter le bouton "ui->BOUTON" quand il est trigerred à la classe "this", et ensuite à la méthode (qui est définie dans les slots du .h)
    connect(ui->actionNouveau, &QAction::triggered, this, &Notepad::newDocument);
    connect(ui->actionOuvrir, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionEnregistrer, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionEnregistrer_sous, &QAction::triggered, this, &Notepad::saveAs);

    connect(ui->actionQuitter, &QAction::triggered, this, &QWidget::close);

    connect(ui->actionPolice, &QAction::triggered, this, &Notepad::selectFont);
    connect(ui->actionItalique, &QAction::triggered, this, &Notepad::setItalic);
    connect(ui->actionGras, &QAction::triggered, this, &Notepad::setBold);
    connect(ui->actionSouligner, &QAction::triggered, this, &Notepad::setUnderline);

    connect(ui->actionAbout, &QAction::triggered, this, &Notepad::showAbout);
}

Notepad::~Notepad() {
    delete ui;
}

// On créé un nouveau document
void Notepad::newDocument() {
    currentFilePath.clear();
    ui->textArea->setText(QString());
    setWindowTitle("Notepad : Nouveau Document");
}

// On ouvre un document
void Notepad::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier");
    QFile file(fileName);
    currentFilePath = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Impossible d'ouvrir le fichier : " + file.errorString());
        return;
    }
    setWindowTitle("Notepad : " + fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textArea->setText(text);
    file.close();
}

// On sauvegarde un document
void Notepad::save() {
    QString filePath;
    if (currentFilePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(this, "Sauvegarder le fichier");
        currentFilePath = filePath;
    } else {
        filePath = currentFilePath;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Impossible d'enregistrer le fichier : " + file.errorString());
        return;
    }
    setWindowTitle("Notepad : " + filePath);
    QTextStream out(&file);
    out << ui->textArea->toPlainText();
    file.close();
}

// On enregistre-sous un document
void Notepad::saveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Sauvegarder sous");
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Impossible d'enregistrer le fichier : " + file.errorString());
        return;
    }
    currentFilePath = filePath;
    setWindowTitle("Notepad : " + filePath);
    QTextStream out(&file);
    out << ui->textArea->toPlainText();
    file.close();
}

// On selectionne la fond du Notepad (pas gardée dans le fichier quand on enregistre)
void Notepad::selectFont() {
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected) {
        ui->textArea->setFont(font);
    }
}

// On met le texte en italique (pas gardée dans le fichier quand on enregistre)
void Notepad::setItalic(bool italic) {
    ui->textArea->setFontItalic(italic);
}

// On met le texte en gras (pas gardée dans le fichier quand on enregistre)
void Notepad::setBold(bool bold) {
    ui->textArea->setFontWeight(bold ? QFont::Bold : QFont::Normal);
}

// On met le texte en souligné (pas gardée dans le fichier quand on enregistre)
void Notepad::setUnderline(bool underline) {
    ui->textArea->setFontUnderline(underline);
}

// On affiche une pop-up d'information
void Notepad::showAbout() {
    QMessageBox::about(this, "À propos", "Notepad - Application de traitement de texte simple\n"
                                         "Créé par ANTHONUS avec l'aide du tuto QT");
}
