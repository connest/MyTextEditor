#ifndef MYTEXTEDITOR_H
#define MYTEXTEDITOR_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>

#include <QSettings>
#include <QIcon>

class MyTextEditor : public QTextEdit
{
    Q_OBJECT

    QString currentFile;
    void readFile(const QString& path);

    void saveFile();

    bool textChange;
    void dirty();
    bool saveDirty();

    void loadSettings();
    void saveSettings();
public:
    MyTextEditor(QWidget* parent);


public slots:
    void open();
    void saveAs();
    void save();
    void clear();
    void changeFont();
};

#endif // MYTEXTEDITOR_H
