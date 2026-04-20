#include "factor_range.hpp"

FactorRange::FactorRange(const QObject *parent) : from_(1), to_(20) { }

FactorRange::FactorRange() : from_(1), to_(20) { }

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
FactorRange::FactorRange(const int &from, const int &to) : from_(from), to_(to)
{
}

int FactorRange::from() const
{
    return from_;
}

int FactorRange::to() const
{
    return to_;
}

void FactorRange::setFrom(const int n)
{
    if (from_ == n)
        return;
    from_ = n;
    emit fromChanged();
}

void FactorRange::setTo(const int n)
{
    if (to_ == n)
        return;
    to_ = n;
    emit toChanged();
}

bool FactorRange::operator==(const FactorRange &factorRange)
{
    return from() == factorRange.from() && to() == factorRange.to();
}
