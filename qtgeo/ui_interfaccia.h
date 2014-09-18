/********************************************************************************
** Form generated from reading UI file 'interfaccia.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACCIA_H
#define UI_INTERFACCIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialogo
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *layout_stima;
    QToolButton *stima;
    QLabel *distanza_etichetta;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *carica;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *immagine;
    QGroupBox *file_groupbox;
    QFormLayout *formLayout;
    QGridLayout *layout_file;
    QLineEdit *bin_input;
    QLineEdit *center_input;
    QPushButton *center_tasto;
    QPushButton *out_tasto;
    QLabel *label_4;
    QLineEdit *cluster_input;
    QLabel *label_3;
    QPushButton *bin_tasto;
    QPushButton *cluster_tasto;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *out_input;
    QLineEdit *n_centroidi_input;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_4;
    QGraphicsView *mappa;
    QLabel *distanza_label;
    QLabel *label_10;

    void setupUi(QDialog *Dialogo)
    {
        if (Dialogo->objectName().isEmpty())
            Dialogo->setObjectName(QStringLiteral("Dialogo"));
        Dialogo->resize(561, 531);
        horizontalLayoutWidget_2 = new QWidget(Dialogo);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(271, 207, 122, 27));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalLayoutWidget_2->sizePolicy().hasHeightForWidth());
        horizontalLayoutWidget_2->setSizePolicy(sizePolicy);
        layout_stima = new QHBoxLayout(horizontalLayoutWidget_2);
        layout_stima->setObjectName(QStringLiteral("layout_stima"));
        layout_stima->setSizeConstraint(QLayout::SetMinimumSize);
        layout_stima->setContentsMargins(0, 0, 0, 0);
        stima = new QToolButton(horizontalLayoutWidget_2);
        stima->setObjectName(QStringLiteral("stima"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stima->sizePolicy().hasHeightForWidth());
        stima->setSizePolicy(sizePolicy1);

        layout_stima->addWidget(stima);

        distanza_etichetta = new QLabel(horizontalLayoutWidget_2);
        distanza_etichetta->setObjectName(QStringLiteral("distanza_etichetta"));
        sizePolicy.setHeightForWidth(distanza_etichetta->sizePolicy().hasHeightForWidth());
        distanza_etichetta->setSizePolicy(sizePolicy);

        layout_stima->addWidget(distanza_etichetta);

        horizontalLayoutWidget_3 = new QWidget(Dialogo);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(9, 205, 133, 29));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        carica = new QPushButton(horizontalLayoutWidget_3);
        carica->setObjectName(QStringLiteral("carica"));

        horizontalLayout_2->addWidget(carica);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        immagine = new QGraphicsView(Dialogo);
        immagine->setObjectName(QStringLiteral("immagine"));
        immagine->setGeometry(QRect(9, 9, 256, 192));
        file_groupbox = new QGroupBox(Dialogo);
        file_groupbox->setObjectName(QStringLiteral("file_groupbox"));
        file_groupbox->setEnabled(true);
        file_groupbox->setGeometry(QRect(9, 240, 354, 191));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(file_groupbox->sizePolicy().hasHeightForWidth());
        file_groupbox->setSizePolicy(sizePolicy2);
        file_groupbox->setContextMenuPolicy(Qt::DefaultContextMenu);
        file_groupbox->setAcceptDrops(false);
        file_groupbox->setLayoutDirection(Qt::LeftToRight);
        file_groupbox->setAutoFillBackground(false);
        file_groupbox->setInputMethodHints(Qt::ImhNone);
        file_groupbox->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);
        file_groupbox->setFlat(false);
        file_groupbox->setCheckable(false);
        formLayout = new QFormLayout(file_groupbox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        layout_file = new QGridLayout();
        layout_file->setObjectName(QStringLiteral("layout_file"));
        layout_file->setSizeConstraint(QLayout::SetNoConstraint);
        bin_input = new QLineEdit(file_groupbox);
        bin_input->setObjectName(QStringLiteral("bin_input"));

        layout_file->addWidget(bin_input, 2, 1, 1, 1);

        center_input = new QLineEdit(file_groupbox);
        center_input->setObjectName(QStringLiteral("center_input"));

        layout_file->addWidget(center_input, 4, 1, 1, 1);

        center_tasto = new QPushButton(file_groupbox);
        center_tasto->setObjectName(QStringLiteral("center_tasto"));

        layout_file->addWidget(center_tasto, 4, 2, 1, 1);

        out_tasto = new QPushButton(file_groupbox);
        out_tasto->setObjectName(QStringLiteral("out_tasto"));

        layout_file->addWidget(out_tasto, 1, 2, 1, 1);

        label_4 = new QLabel(file_groupbox);
        label_4->setObjectName(QStringLiteral("label_4"));

        layout_file->addWidget(label_4, 4, 0, 1, 1);

        cluster_input = new QLineEdit(file_groupbox);
        cluster_input->setObjectName(QStringLiteral("cluster_input"));

        layout_file->addWidget(cluster_input, 3, 1, 1, 1);

        label_3 = new QLabel(file_groupbox);
        label_3->setObjectName(QStringLiteral("label_3"));

        layout_file->addWidget(label_3, 3, 0, 1, 1);

        bin_tasto = new QPushButton(file_groupbox);
        bin_tasto->setObjectName(QStringLiteral("bin_tasto"));

        layout_file->addWidget(bin_tasto, 2, 2, 1, 1);

        cluster_tasto = new QPushButton(file_groupbox);
        cluster_tasto->setObjectName(QStringLiteral("cluster_tasto"));

        layout_file->addWidget(cluster_tasto, 3, 2, 1, 1);

        label_2 = new QLabel(file_groupbox);
        label_2->setObjectName(QStringLiteral("label_2"));

        layout_file->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(file_groupbox);
        label->setObjectName(QStringLiteral("label"));

        layout_file->addWidget(label, 1, 0, 1, 1);

        out_input = new QLineEdit(file_groupbox);
        out_input->setObjectName(QStringLiteral("out_input"));

        layout_file->addWidget(out_input, 1, 1, 1, 1);

        n_centroidi_input = new QLineEdit(file_groupbox);
        n_centroidi_input->setObjectName(QStringLiteral("n_centroidi_input"));

        layout_file->addWidget(n_centroidi_input, 5, 1, 1, 1);

        label_9 = new QLabel(file_groupbox);
        label_9->setObjectName(QStringLiteral("label_9"));

        layout_file->addWidget(label_9, 5, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, layout_file);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_4);

        horizontalLayoutWidget_3->raise();
        horizontalLayoutWidget_3->raise();
        mappa = new QGraphicsView(Dialogo);
        mappa->setObjectName(QStringLiteral("mappa"));
        mappa->setGeometry(QRect(271, 9, 256, 192));
        distanza_label = new QLabel(Dialogo);
        distanza_label->setObjectName(QStringLiteral("distanza_label"));
        distanza_label->setGeometry(QRect(400, 210, 67, 17));
        label_10 = new QLabel(Dialogo);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(350, 230, 67, 17));
        out_input->raise();
        horizontalLayoutWidget_2->raise();
        horizontalLayoutWidget_3->raise();
        immagine->raise();
        file_groupbox->raise();
        mappa->raise();
        distanza_label->raise();
        label_10->raise();

        retranslateUi(Dialogo);

        QMetaObject::connectSlotsByName(Dialogo);
    } // setupUi

    void retranslateUi(QDialog *Dialogo)
    {
        Dialogo->setWindowTitle(QApplication::translate("Dialogo", "Sattler For Dummies", 0));
#ifndef QT_NO_STATUSTIP
        stima->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_ACCESSIBILITY
        stima->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        stima->setText(QApplication::translate("Dialogo", "&Stima!", 0));
        distanza_etichetta->setText(QApplication::translate("Dialogo", "Distanza", 0));
        carica->setText(QApplication::translate("Dialogo", "Carica...", 0));
        file_groupbox->setTitle(QApplication::translate("Dialogo", "  Localizer", 0));
        center_tasto->setText(QApplication::translate("Dialogo", "Sfoglia", 0));
        out_tasto->setText(QApplication::translate("Dialogo", "Sfoglia", 0));
        label_4->setText(QApplication::translate("Dialogo", "center file", 0));
        label_3->setText(QApplication::translate("Dialogo", "Cluster file", 0));
        bin_tasto->setText(QApplication::translate("Dialogo", "Sfoglia", 0));
        cluster_tasto->setText(QApplication::translate("Dialogo", "Sfoglia", 0));
        label_2->setText(QApplication::translate("Dialogo", "Bin file", 0));
        label->setText(QApplication::translate("Dialogo", "Out file", 0));
        label_9->setText(QApplication::translate("Dialogo", "n. centroidi", 0));
        distanza_label->setText(QString());
        label_10->setText(QApplication::translate("Dialogo", "(in m)", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialogo: public Ui_Dialogo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACCIA_H
