#ifndef OTTQD_20260417_1022_INCLUDE
#define OTTQD_20260417_1022_INCLUDE

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(const MainWindow &) = delete;
    MainWindow(const MainWindow &&) = delete;
    MainWindow &operator=(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &&) = delete;

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};

#endif // OTTQD_20260417_1022_INCLUDE
