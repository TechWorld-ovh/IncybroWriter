#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include <QFileDialog>
#include <QComboBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QLineEdit>
#include <QTextCharFormat>

#include <QDebug>

namespace Ui {
class NotepadWindow;
}

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotepadWindow(QWidget *parent = 0);
    void openfile(QString textfile);
    ~NotepadWindow();

private slots:
    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void onFontSizeChanged(QString selected);

    void on_actionBold_triggered(bool checked);

    void on_actionItalics_triggered(bool checked);

    void on_actionUnderline_triggered(bool checked);

    void on_actionLeft_triggered();

    void on_actionCenter_triggered();

    void on_actionRight_triggered();

    void on_actionJustify_triggered();

    void on_actionPrint_triggered();

    void on_currentCharFormatChanged(QTextCharFormat format);
    void on_cursorPositionChanged();


private:

    QString mFilename;
    Ui::NotepadWindow *ui;
    QComboBox* myComboBox;
};
#endif // NOTEPADWINDOW_H
