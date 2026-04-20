#ifndef OTTQ_20260420_1618_INCLUDE
#define OTTQ_20260420_1618_INCLUDE

#include <QObject>

struct FactorRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int from READ from WRITE setFrom NOTIFY fromChanged FINAL)
    Q_PROPERTY(int to READ to WRITE setTo NOTIFY toChanged FINAL)

public:
    FactorRange(const QObject *parent = nullptr);
    FactorRange();
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    FactorRange(const int &from, const int &to);

    int from() const;
    int to() const;

    void setFrom(const int from);
    void setTo(const int to);

    bool operator==(const FactorRange &fr);

signals:
    void fromChanged();
    void toChanged();

private:
    int from_;
    int to_;
};

#endif // OTTQ_20260420_1618_INCLUDE
