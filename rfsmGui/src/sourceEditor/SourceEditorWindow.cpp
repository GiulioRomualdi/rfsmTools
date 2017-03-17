#include <iostream>

#include "SourceEditorWindow.h"
#include "ui_SourceEditorWindow.h"
#include <QMessageBox>
#include <QShortcut>
#include <QCloseEvent>

SourceEditorWindow::SourceEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SourceEditorWindow)
{    
    ui->setupUi(this);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    //QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setFamily("Courier");
    font.setPointSize(10);
    ui->textEdit->setFont(font);
    QFontMetrics metrics(font);
    ui->textEdit->setTabStopWidth(4 * metrics.width(' '));

    highlighter = new Highlighter(ui->textEdit->document());    

    connect(ui->action_Save, SIGNAL(triggered()),this,SLOT(onSave()));
    connect(ui->action_Close, SIGNAL(triggered()),this,SLOT(onClose()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(onSave()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(onClose()));
}

SourceEditorWindow::~SourceEditorWindow()
{
    delete ui;
}

void SourceEditorWindow::setSourceCode(const QString& sourceCode){
    SourceEditorWindow::sourceCode = sourceCode;
    ui->textEdit->clear();
    ui->textEdit->setPlainText(sourceCode);
    showStatusBarMessage("");    
}

void SourceEditorWindow::closeEvent(QCloseEvent *event)
{
    onClose();
    QWidget::closeEvent(event);
}

void SourceEditorWindow::onClose() {

    if((sourceCode != ui->textEdit->toPlainText())) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Close", "The source code has been changed.\n Do you want to save it?",
                                      QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes) {
            onSave();
        }
    }
    SourceEditorWindow::close();
}


void SourceEditorWindow::onSave() {
    showStatusBarMessage("Saved!");
    sourceCode = ui->textEdit->toPlainText();
    // clear extra selections
    QList<QTextEdit::ExtraSelection> extraSelections;
    ui->textEdit->setExtraSelections(extraSelections);
    emit sourceCodeSaved();
}


QString& SourceEditorWindow::getSourceCode() {
    return sourceCode;
}

void SourceEditorWindow::showStatusBarMessage(const QString& message,
                          QColor color) {
    ui->statusbar->showMessage(message);
    QPalette palette;
    palette.setColor( QPalette::WindowText, color);
    statusBar()->setPalette(palette);
}

void SourceEditorWindow::setErrorMessage(const QString& message) {
    showStatusBarMessage(message, Qt::darkRed);
    QStringList strlist = message.split(":");
    if(strlist.size() > 1) {
        int lineNumer = strlist[1].toInt();
        QTextEdit::ExtraSelection highlight;
        highlight.cursor = ui->textEdit->textCursor();
        highlight.cursor.setPosition(0);
        highlight.cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumer-2);
        highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
        highlight.format.setBackground( QColor("#FA8072") );
        QList<QTextEdit::ExtraSelection> extras;
        extras << highlight;
        ui->textEdit->setExtraSelections( extras );        
    }
}

void SourceEditorWindow::setReadOnly(bool flag) {
    ui->textEdit->setReadOnly(flag);
    ui->action_Save->setEnabled(!flag);
}
