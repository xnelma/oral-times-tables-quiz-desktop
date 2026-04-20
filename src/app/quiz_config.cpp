#include "quiz_config.hpp"

QuizConfiguration::QuizConfiguration(const QObject *parent)
    : factorRange_(new FactorRange(this))
{
    connect(factorRange_,
            &FactorRange::fromChanged,
            this,
            &QuizConfiguration::factorRangeChanged);
    connect(factorRange_,
            &FactorRange::toChanged,
            this,
            &QuizConfiguration::factorRangeChanged);
}

QList<int> QuizConfiguration::timesTables()
{
    return timesTables_;
}

FactorRange *QuizConfiguration::factorRange()
{
    return factorRange_;
}

void QuizConfiguration::addTimesTable(const int number)
{
    if (timesTables_.contains(number))
        return;

    timesTables_.push_back(number);
    emit timesTablesChanged();
}

void QuizConfiguration::removeTimesTable(const int number)
{
    auto pos = timesTables_.indexOf(number);
    if (pos < 0)
        return;

    timesTables_.removeAt(pos);
    emit timesTablesChanged();
}

bool QuizConfiguration::containsTimesTable(const int number)
{
    return timesTables_.contains(number);
}

void QuizConfiguration::resetTimesTables()
{
    timesTables_.clear();
    emit timesTablesChanged();
}
