#include "MyTextEditor.h"



void MyTextEditor::readFile(const QString& path)
{
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly |
               QIODevice::Text))
        return ;


    setPlainText(QTextStream(&f).readAll());


    f.close();
}
void MyTextEditor::saveFile()
{
    QFile f(currentFile);
    if(!f.open(QIODevice::WriteOnly |
               QIODevice::Text))
        return ;

    QTextStream out(&f);
    out << toPlainText();
    f.close();

    textChange=false;
}

void MyTextEditor::dirty()
{
    textChange=true;
}
bool MyTextEditor::saveDirty()
{
    if(textChange)
    {
        QMessageBox m("Save?", "File has been changed",
                      QMessageBox::Question,
                      QMessageBox::Save,
                      QMessageBox::No,
                      QMessageBox::Cancel);

        m.setWindowIcon(QIcon(":/images/icon.png"));

        switch(m.exec())
        {
        case QMessageBox::Save:
            save();
            return true;
        case QMessageBox::Cancel:
            return false;

        }

    }
    return true;
}

void MyTextEditor::loadSettings()
{
    QFont f;
    QSettings s("Settings.ini", QSettings::IniFormat);
    setFont(qvariant_cast<QFont>(s.value("font", f)));
}
void MyTextEditor::saveSettings()
{
    QSettings s("Settings.ini", QSettings::IniFormat);
    s.setValue("font", this->font());
}

MyTextEditor::MyTextEditor(QWidget* parent)
    : QTextEdit(parent)
    , textChange(false)
{
    connect(this, &QTextEdit::textChanged,
            this, &MyTextEditor::dirty);

    loadSettings();

}


void MyTextEditor::open()
{
    if(!saveDirty())
        return;


    QFileDialog fd;
    currentFile=fd.getOpenFileName();
    if(!currentFile.isEmpty())
    {
        readFile(currentFile);
    }
}
void MyTextEditor::saveAs()
{
    if(!saveDirty())
        return;

    QFileDialog fd;
    QDir dir(currentFile);
    currentFile=fd.getSaveFileName(0, "Save", dir.path());
    saveFile();
}
void MyTextEditor::save()
{
    QFileDialog fd;
    QDir dir;
    if(currentFile.isEmpty())
        currentFile=fd.getSaveFileName(0, "Save", dir.homePath());
    saveFile();
}
void MyTextEditor::clear()
{
    saveDirty();

    currentFile.clear();
    setText("");
    textChange=false;
}
void MyTextEditor::changeFont()
{
    QFontDialog fontDialog;

    bool Ok;
    QFont f=fontDialog.getFont(&Ok, this->font());

    if(Ok) {
        this->setFont(f);
        saveSettings();
    }
}

