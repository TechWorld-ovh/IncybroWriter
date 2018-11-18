#include "notepadwindow.h"
#include "ui_notepadwindow.h"


NotepadWindow::NotepadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotepadWindow)

{
    ui->setupUi(this);
    ui->actionBold->setCheckable(true);
    ui->actionItalics->setCheckable(true);
    ui->actionUnderline->setCheckable(true);
    ui->actionLeft->setCheckable(true);
    ui->actionRight->setCheckable(true);
    ui->actionCenter->setCheckable(true);
    ui->actionJustify->setCheckable(true);
    this->setCentralWidget(ui->textEdit); // Wyśrodkuj Pole tekstowe
    myComboBox = new QComboBox;
    ui->mainToolBar->addWidget(myComboBox);
    for (int i = 1; i < 102; i += 2) {
        myComboBox->addItem(QString::number(i));
    }
    myComboBox->setCurrentText("11");
    ui->textEdit->setFontPointSize(11);
    ui->actionLeft->setChecked(true);
    ui->actionRight->setChecked(false);
    ui->actionCenter->setChecked(false);
    ui->actionJustify->setChecked(false);

    QObject::connect(myComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onFontSizeChanged(QString)));

    QObject::connect(ui->textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(on_currentCharFormatChanged(QTextCharFormat)));
    QObject::connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(on_cursorPositionChanged()));
}


NotepadWindow::~NotepadWindow()
{
    delete ui;
}

void NotepadWindow::on_currentCharFormatChanged(QTextCharFormat format){
    qDebug() << format << endl;

    /**
      Check for Bold/Normal fontWeight
    **/
    qDebug() << "fontWeight : " << format.fontWeight() << endl;
    if(format.fontWeight() == QFont::Normal){
        ui->actionBold->setChecked(false);
    }else if(format.fontWeight() == QFont::Bold){
        ui->actionBold->setChecked(true);
    }

    /**
      Check for Italic
    **/
    qDebug() << "italic : " << format.fontItalic() << endl;
    if(format.fontItalic() == false){
        ui->actionItalics->setChecked(false);
    }else if(format.fontItalic() == true){
        ui->actionItalics->setChecked(true);
    }

    /**
      Check for Underlined
    **/
    qDebug() << "underlined : " << format.fontUnderline() << endl;
    if(format.fontUnderline() == false){
        ui->actionUnderline->setChecked(false);
    }else if(format.fontUnderline() == true){
        ui->actionUnderline->setChecked(true);
    }


    /**
      Get the actual fontPointSize (format.fontPointSitze) of text and change it to the comboBox (by searching the index)
    **/
    qDebug() << "fontPointSize : " << format.fontPointSize() << endl;
    qDebug() << "findText : " << myComboBox->findText(QString::number(format.fontPointSize())) << endl;
    myComboBox->setCurrentIndex(myComboBox->findText(QString::number(format.fontPointSize())));

}

void NotepadWindow::on_cursorPositionChanged(){
    qDebug() << "alignment: " << ui->textEdit->alignment() << endl;
    if(ui->textEdit->alignment() == Qt::AlignLeft){
        on_actionLeft_triggered();
    }else if(ui->textEdit->alignment() == Qt::AlignCenter){
        on_actionCenter_triggered();
    }else if(ui->textEdit->alignment() == Qt::AlignRight){
        on_actionRight_triggered();
    }else if(ui->textEdit->alignment() == Qt::AlignJustify){
        on_actionJustify_triggered();
    }
}

void NotepadWindow::onFontSizeChanged(QString selected)
{
    ui->textEdit->setFontPointSize(selected.toInt());
}

void NotepadWindow::openfile(QString textfile)
{
    QFile sFile(textfile);
    if(sFile.open(QFile::ReadOnly | QFile::Text)) // Jeśli plik jest otwarty
    {
        mFilename = textfile;
        QTextStream in(&sFile);
        in.setCodec("UTF-8"); // Ustaw kodowania znaków na UTF-8
        QString text = in.readAll();
        sFile.close();
        ui->textEdit->setHtml(text);
    }
}

void NotepadWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void NotepadWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void NotepadWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void NotepadWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void NotepadWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void NotepadWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

void NotepadWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "open"); // Otwórz okienko wyboru plików
    if(!file.isEmpty())        // Jeśli plik nie jest pusty
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text)) // Jeśli plik jest otwarty
        {
            mFilename = file;
            QTextStream in(&sFile);
            in.setCodec("UTF-8"); // Ustaw kodowania znaków na UTF-8
            QString text = in.readAll();
            sFile.close();
            ui->textEdit->setHtml(text);
        }
    }
}

void NotepadWindow::on_actionSave_triggered()
{
    QFile sFile(mFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text)) // Jeśli plik jest otwarty
    {
        QTextStream out(&sFile);
        out << ui->textEdit->toHtml();
        out.setCodec("UTF-8"); // Ustaw kodowania znaków na UTF-8
        sFile.flush();
        sFile.close();

    }
    else if(!sFile.open(QFile::WriteOnly | QFile::Text)) on_actionSave_as_triggered();
}

void NotepadWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,  tr("Incybro Writer files"), "", tr("Incybro Writer Document (*.idocu)"));
    if(!file.isEmpty())
    {
        mFilename = file;
        on_actionSave_triggered();
    }
}




void NotepadWindow::on_actionBold_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    if(!checked)
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }

}

void NotepadWindow::on_actionItalics_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontItalic(1);
    }
    if(!checked)
    {
        ui->textEdit->setFontItalic(0);
    }

}

void NotepadWindow::on_actionUnderline_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontUnderline(1);
    }
    if(!checked)
    {
        ui->textEdit->setFontUnderline(0);
    }

}

void NotepadWindow::on_actionLeft_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
    ui->actionLeft->setChecked(true);
    ui->actionRight->setChecked(false);
    ui->actionCenter->setChecked(false);
    ui->actionJustify->setChecked(false);
}

void NotepadWindow::on_actionCenter_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->actionLeft->setChecked(false);
    ui->actionRight->setChecked(false);
    ui->actionCenter->setChecked(true);
    ui->actionJustify->setChecked(false);
}

void NotepadWindow::on_actionRight_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
    ui->actionLeft->setChecked(false);
    ui->actionRight->setChecked(true);
    ui->actionCenter->setChecked(false);
    ui->actionJustify->setChecked(false);
}

void NotepadWindow::on_actionJustify_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignJustify);
    ui->actionLeft->setChecked(false);
    ui->actionRight->setChecked(false);
    ui->actionCenter->setChecked(false);
    ui->actionJustify->setChecked(true);
}

void NotepadWindow::on_actionPrint_triggered()
{

    QPrinter printer;
    printer.setPageSizeMM(QSize(210, 297));

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");

    QPainter painter;
    painter.begin(&printer);

    QTextDocument td;
    QSize size(793.7007874016, 1122.519685039);
    td.setPageSize(size);
    td.setHtml(ui->textEdit->toHtml());
    td.drawContents(&painter);
    //painter.drawText(printer.pageRect(), ui->textEdit->toPlainText());

    painter.end();
}
