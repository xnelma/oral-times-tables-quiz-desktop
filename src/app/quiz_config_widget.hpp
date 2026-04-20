#ifndef OTTQD_20260418_1202_INCLUDE
#define OTTQD_20260418_1202_INCLUDE

#include "quiz_config.hpp"
#include <QtWidgets>

class QuizConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuizConfigWidget(QWidget *parent);

private:
    QuizConfiguration *config_;
};

#endif // OTTQD_20260418_1202_INCLUDE
