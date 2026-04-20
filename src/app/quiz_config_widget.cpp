#include "quiz_config_widget.hpp"

QuizConfigWidget::QuizConfigWidget(QWidget *parent)
    : config_(new QuizConfiguration(this))
{
    QGridLayout *layout = new QGridLayout();
    layout->setHorizontalSpacing(20);
    // The layout contains widgets that should expand to its size.
    // Per default the layout adjusts its size to the (default) sizes of
    // widgets, but for other constraints expect for the fixed size constraint,
    // a widget with expanding size policy also makes the layout expand,
    // instead of just expanding inside the cell. So set the size constraint to
    // fixed.
    layout->setSizeConstraint(QLayout::SetFixedSize);
    // This gives no room to center the widgets anymore. The fixed size fits
    // the widgets and is thus smaller than the window (and CentralWidget in
    // this case).
    // layout->setAlignment(Qt::AlignCenter);
    // (setAlignment does not align the the layout itself inside the widget
    // it is set to, but the widgets inside the layout)
    // Therefore add the layout to another layout + widget, and center it there.
    QBoxLayout *centeredLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    centeredLayout->setAlignment(Qt::AlignCenter);
    QWidget *layoutContainer = new QWidget();
    layoutContainer->setLayout(layout);
    centeredLayout->addWidget(layoutContainer);

    QFont boldFont;
    boldFont.setBold(true);

    // I decided to try out names without UI-component prefix, because it might
    // be a bit more readable and the type might be clear in IDEs.

    // And creating all the objects on the heap via raw pointers does not
    // cause memory getting leaked due to Qt managing object deletion:
    // adding them to e.g. layouts will put a widget inside an object tree, so
    // deleting a parent also frees the memory of the child objects.

    /*
     * Times tables section:
     */

    // Inside QObjects tr() is available, otherwise QApplication::translate()
    // would have to be used: it also takes the context the translation is
    // defined in.
    QLabel *timesTablesLabel = new QLabel(tr("Times Tables:"));
    layout->addWidget(timesTablesLabel, 0, 0, Qt::AlignCenter);

    auto toString = [](const QList<int> numbers) -> QString {
        QString str;
        for (const int n : numbers)
            str += QString::number(n) + ", ";

        if (str.length() < 2)
            return "";
        return str.first(str.length() - 2);
    };
    QLabel *timesTables = new QLabel(config_->timesTables().empty()
                                         ? tr("Add a number")
                                         : toString(config_->timesTables()));
    // TODO maybe use bindings?
    connect(config_,
            &QuizConfiguration::timesTablesChanged,
            this,
            [this, timesTables, toString]() {
                timesTables->setText(config_->timesTables().empty()
                                         ? tr("Add a number")
                                         : toString(config_->timesTables()));
            });

    // TODO set max width and elide
    timesTables->setFont(boldFont);
    layout->addWidget(timesTables, 1, 0, Qt::AlignCenter);

    /*
     * Subsection for controls:
     */

    QGridLayout *timesTablesLayout = new QGridLayout();
    timesTablesLayout->setHorizontalSpacing(10);
    timesTablesLayout->setVerticalSpacing(10);
    layout->addLayout(timesTablesLayout, 2, 0, Qt::AlignCenter);

    QSpinBox *tablesSingleStep = new QSpinBox();
    // TODO the step buttons should be reverted
    tablesSingleStep->setMinimum(1);
    tablesSingleStep->setMaximum(100);
    tablesSingleStep->setValue(10);
    tablesSingleStep->setAlignment(Qt::AlignCenter);
    tablesSingleStep->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // TODO set button to remove table if value already in list
    timesTablesLayout->addWidget(tablesSingleStep, 0, 0);

    QPushButton *addTimesTable = new QPushButton(tr("Add"));
    // Also set the size policy to expanding for the button, even if it is
    // normally wider than the spin box anyways: just in case. The column width
    // should be the maximum width of both widgets.
    addTimesTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(
        addTimesTable, &QPushButton::pressed, this, [this, tablesSingleStep]() {
            config_->addTimesTable(tablesSingleStep->value());
        });
    timesTablesLayout->addWidget(addTimesTable, 1, 0);

    QSlider *tablesDecimalStep = new QSlider(Qt::Vertical);
    tablesDecimalStep->setMinimum(10);
    tablesDecimalStep->setMaximum(90);
    tablesDecimalStep->setSingleStep(10);
    tablesDecimalStep->setPageStep(20);
    // TODO maybe restrict numbers to decimal steps. setSingleStep is for
    // keyboard controls, not the slider.
    tablesDecimalStep->setSliderPosition(10);
    tablesDecimalStep->setInvertedAppearance(true);
    // The slider should span the rows next to the spin box and button.
    tablesDecimalStep->setMinimumHeight(0);
    tablesDecimalStep->setSizePolicy(QSizePolicy::Fixed,
                                     QSizePolicy::Expanding);
    connect(
        tablesDecimalStep,
        &QSlider::valueChanged,
        this,
        [tablesSingleStep](const int &v) { tablesSingleStep->setValue(v); });
    timesTablesLayout->addWidget(tablesDecimalStep, 0, 1, 2, 1);

    /*
     * Separator between sections:
     */

    QFrame *verticalLine = new QFrame();
    verticalLine->setFrameShape(QFrame::VLine);
    verticalLine->setFrameShadow(QFrame::Raised);
    verticalLine->setLineWidth(2);
    verticalLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    layout->addWidget(verticalLine, 0, 1, 3, 1);

    /*
     * Factors section:
     */

    QLabel *factorsLabel = new QLabel(tr("Factors:"));
    layout->addWidget(factorsLabel, 0, 2, Qt::AlignCenter);

    auto factorStr = [](const FactorRange *fr) -> QString {
        return QString("[%1, %2]").arg(fr->from()).arg(fr->to());
    };
    QLabel *factors = new QLabel(factorStr(config_->factorRange()));
    connect(config_,
            &QuizConfiguration::factorRangeChanged,
            this,
            [this, factors, factorStr]() {
                factors->setText(factorStr(config_->factorRange()));
            });
    factors->setFont(boldFont);
    layout->addWidget(factors, 1, 2, Qt::AlignCenter);

    /*
     * Subsection for controls:
     */

    QGridLayout *factorsLayout = new QGridLayout();
    factorsLayout->setHorizontalSpacing(10);
    layout->addLayout(factorsLayout, 2, 2, Qt::AlignCenter);

    QToolButton *factorFromUp = new QToolButton();
    factorFromUp->setArrowType(Qt::UpArrow);
    factorsLayout->addWidget(factorFromUp, 0, 0, Qt::AlignTop);

    QToolButton *factorFromDown = new QToolButton();
    factorFromDown->setArrowType(Qt::DownArrow);
    factorsLayout->addWidget(factorFromDown, 1, 0, Qt::AlignBottom);

    QSlider *factorFromSlider = new QSlider(Qt::Vertical);
    factorFromSlider->setMinimum(1);
    factorFromSlider->setMaximum(100);
    // This is not a binding and would need a connection to the signal for
    // value changes if it can change somewhere else.
    factorFromSlider->setValue(config_->factorRange()->from());
    factorFromSlider->setInvertedAppearance(true);
    connect(factorFromUp, &QToolButton::pressed, this, [factorFromSlider]() {
        factorFromSlider->setValue(factorFromSlider->value()
                                   - factorFromSlider->singleStep());
    });
    connect(factorFromDown, &QToolButton::pressed, this, [factorFromSlider]() {
        factorFromSlider->setValue(factorFromSlider->value()
                                   + factorFromSlider->singleStep());
    });
    connect(factorFromSlider,
            &QSlider::valueChanged,
            this,
            [this](const int &v) { config_->factorRange()->setFrom(v); });
    factorsLayout->addWidget(factorFromSlider, 0, 1, 2, 1);

    QSlider *factorToSlider = new QSlider(Qt::Vertical);
    factorToSlider->setMinimum(1);
    factorToSlider->setMaximum(100);
    factorToSlider->setValue(config_->factorRange()->to());
    factorToSlider->setInvertedAppearance(true);
    connect(factorToSlider, &QSlider::valueChanged, this, [this](const int &v) {
        config_->factorRange()->setTo(v);
    });
    factorsLayout->addWidget(factorToSlider, 0, 2, 2, 1);

    QToolButton *factorToUp = new QToolButton();
    factorToUp->setArrowType(Qt::UpArrow);
    connect(factorToUp, &QToolButton::pressed, this, [factorToSlider]() {
        factorToSlider->setValue(factorToSlider->value()
                                 - factorToSlider->singleStep());
    });
    factorsLayout->addWidget(factorToUp, 0, 3, Qt::AlignTop);

    QToolButton *factorToDown = new QToolButton();
    factorToDown->setArrowType(Qt::DownArrow);
    connect(factorToDown, &QToolButton::pressed, this, [factorToSlider]() {
        factorToSlider->setValue(factorToSlider->value()
                                 + factorToSlider->singleStep());
    });
    factorsLayout->addWidget(factorToDown, 1, 3, Qt::AlignBottom);
}
