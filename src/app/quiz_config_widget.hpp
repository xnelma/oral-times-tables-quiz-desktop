#ifndef OTTQD_20260418_1202_INCLUDE
#define OTTQD_20260418_1202_INCLUDE

#include <QtWidgets>
#include <QList>

class QuizConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuizConfigWidget(QWidget *parent);

private:
    QList<int> timesTables_;
    int factorFrom_;
    int factorTo_;
};

#endif // OTTQD_20260418_1202_INCLUDE