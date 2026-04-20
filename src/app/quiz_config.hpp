#ifndef OTTQ_20260420_1621_INCLUDE
#define OTTQ_20260420_1621_INCLUDE

#include "factor_range.hpp"
#include <QObject>
#include <QList>

struct QuizConfiguration : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QList<int> timesTables
               READ timesTables
               NOTIFY timesTablesChanged
               FINAL)
    Q_PROPERTY(FactorRange *factorRange
               READ factorRange
               NOTIFY factorRangeChanged
               FINAL)
    // clang-format on

public:
    QuizConfiguration(const QObject *parent = nullptr);

    QList<int> timesTables();
    FactorRange *factorRange();

    Q_INVOKABLE void addTimesTable(const int number);
    Q_INVOKABLE void removeTimesTable(const int number);
    Q_INVOKABLE bool containsTimesTable(const int number);
    Q_INVOKABLE void resetTimesTables();

signals:
    void timesTablesChanged();
    void factorRangeChanged();

private:
    QList<int> timesTables_;
    FactorRange *factorRange_;
};

#endif // OTTQ_20260420_1621_INCLUDE
