#include "mainwindow.hpp"
#include "quiz_config_widget.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("OTTQ");

    QuizConfigWidget *quizConfig = new QuizConfigWidget(this);
    setCentralWidget(quizConfig);
}