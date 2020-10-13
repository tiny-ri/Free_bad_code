#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLibraryInfo>
#include <QTranslator>
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFontDialog>
#include <QFileDialog>
#include <QSettings>
#include <QFile>
#include <QFont>
#include <QTextStream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

 explicit   MainWindow(QWidget *parent = 0, const QString &fileName=QString());
    ~MainWindow();



protected :
        void closeEvent(QCloseEvent *e);

private slots:
    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void on_actionSelectFont_triggered();


    void documentModified();
    bool maybeSave();


    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAboutQt_triggered();

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_redoAvailable(bool b);
    void on_textEdit_undoAvailable(bool b);


    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

   bool actionSave_triggered();


private:
    Ui::MainWindow *ui;
    QString file_path ;
    QString current;
    QString m_fileName;

    void loadFile(const QString &);
    void setFileName(const QString &fileName);
    QString getFileName(){return m_fileName;}


};
#endif // MAINWINDOW_H
