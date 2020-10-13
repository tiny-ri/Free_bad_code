#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const QString &fileName)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/img/как.jpg"));

    ui->actionCut->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionCopy->setEnabled(false);

  connect(ui->textEdit->document(), &QTextDocument::contentsChanged,
             this, &MainWindow::documentModified);

    QSettings settings;
        QFont font = settings.value("font", QApplication::font()).value<QFont>();
        ui->textEdit->setFont(font);
        loadFile(fileName);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    ui->statusbar->showMessage("Create new file");
    MainWindow *newW= new MainWindow;
       newW->show();
}

void MainWindow::on_actionClose_triggered()
{
     ui->statusbar->showMessage("Close file");
     close();
}

void MainWindow::on_actionExit_triggered()
{
   qApp->closeAllWindows();
}

void MainWindow::on_actionSelectFont_triggered()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont( &ok, dynamic_cast<QWidget*>(this));
    if(ok == true) {
        this->ui->textEdit->setFont(newFont);
        QSettings settings;
        settings.setValue("font", newFont);
    }
}
void MainWindow::closeEvent(QCloseEvent *e)
{
    if (maybeSave()) {
           e->accept();
       } else {
           e->ignore();
       }
}


void MainWindow::documentModified()
{
   setWindowModified(true);

}

bool MainWindow::maybeSave(){
    if (!ui->textEdit->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Book"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        switch (ret) {
          case QMessageBox::Yes:
             actionSave_triggered();
            break;

          case QMessageBox::No:

         close(); // Don't Save was clicked
            break;

          case QMessageBox::Cancel:
            return false;  // Cancel was clicked


          default:
              // should never be reached
              break;
        }
        return true;
    }




void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();

}

void MainWindow::on_actionAboutQt_triggered()
{
     qApp->aboutQt();
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);

}


void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}

void MainWindow::on_textEdit_undoAvailable(bool b)
{
     ui->actionUndo->setEnabled(b);
}

void MainWindow::on_actionAbout_triggered()
{

    QMessageBox::about(this, tr("About Application"),
                       tr("Sofya Kozlova"
                          "B17-511"
                          ));

}



void MainWindow::on_actionOpen_triggered()
{
     QString file_Name = QFileDialog::getOpenFileName(this, "Open file");
     QFile file(file_Name) ;
     file_path =  file_Name;
     if(!file.open(QFile::ReadOnly | QFile::Text)){
         QMessageBox::warning(this,"..","file not open");
       return;
     }
     QTextStream in(&file);
     QString text =in.readAll();
     ui->textEdit->setText(text);
    file.close();
}

void MainWindow::setFileName(const QString &fileName)
 {
     current = fileName;
     setWindowTitle( QString("%1[*] - %2") .arg(current.isNull()?"NewFile.txt":QFileInfo(current).fileName()) .arg(QApplication::applicationName()) );
 }

void MainWindow::loadFile(const QString &fileName)
{
     if(fileName.isEmpty())
     {
         setFileName(QString());
         return;
     }
     QFile file(fileName);
     if( !file.open(QFile::ReadOnly | QIODevice::Text) )
     {
         QMessageBox::warning(this, tr("Error"), tr("File could't be opened"));
         return;
     }
     QTextStream text(&file);
     ui->textEdit->setText(text.readAll());
     setFileName(fileName);
     setWindowModified(false);
     file.close();
 }

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path) ;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_Name = QFileDialog::getSaveFileName(this, "Open file");
    QFile file(file_Name) ;
    file_path = file_Name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

bool MainWindow::actionSave_triggered()
{
    {
        if (current.isEmpty()) {
            on_actionSave_as_triggered();


        } else {
             on_actionSave_triggered();
        }
    }
}
