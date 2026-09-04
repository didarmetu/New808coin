// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "utilitydialog.h"

#include "ui_helpmessagedialog.h"

#include "bitcoingui.h"
#include "clientmodel.h"
#include "guiconstants.h"
#include "intro.h"
#include "guiutil.h"

#include "clientversion.h"
#include "init.h"
#include "util.h"

#include <stdio.h>

#include <QCloseEvent>
#include <QLabel>
#include <QTextTable>
#include <QTextCursor>
#include <QVBoxLayout>

/** "Help message" or "About" dialog box */
HelpMessageDialog::HelpMessageDialog(QWidget* parent, bool about) : QDialog(parent),
                                                                    ui(new Ui::HelpMessageDialog)
{
    ui->setupUi(this);
    GUIUtil::restoreWindowGeometry("nHelpMessageDialogWindow", this->size(), this);

    QString version = tr("New808coin Core") + " " + tr("version") + " " + QString::fromStdString(FormatFullVersion());
/* On x86 add a bit specifier to the version so that users can distinguish between
     * 32 and 64 bit builds. On other architectures, 32/64 bit may be more ambigious.
     */
#if defined(__x86_64__)
    version += " " + tr("(%1-bit)").arg(64);
#elif defined(__i386__)
    version += " " + tr("(%1-bit)").arg(32);
#endif

    if (about) {
        setWindowTitle(tr("About New808coin Core"));

        const QString copyrightText =
            QChar(0xA9) + QString(" 2017-%1 ").arg(COPYRIGHT_YEAR) +
            tr("The New808coin Core Developers");

        const QString generalHeading =
            tr("General Information");

        const QString generalText =
            tr("New808coin is a decentralized digital currency network powered by "
               "staking and masternodes. New808coin Core provides the full-node wallet, "
               "blockchain validation and network services.");

        const QString releaseHeading =
            tr("What's new in v5.2.6.10");

        const QString releaseText =
            tr("&bull; New reward schedule activates at block 1,000,001<br>"
               "&bull; Maximum supply capped at 21,000,000 N808<br>"
               "&bull; Rewards: 85% masternodes / 15% PoS<br>"
               "&bull; Halving every 100,000 blocks with a 0.00000020 N808 floor<br>"
               "&bull; Protocol 70966 plus network, security and Qt improvements");

        const QString upstreamText =
            tr("Based on Bitcoin Core, Dash Core and PIVX Core.");

        const QString licenseText =
            tr("New808coin Core is open-source software released under the MIT License.");

        const QString noticesText =
            tr("See COPYING for full license and third-party notices.");

        text =
            version + "\n\n" +
            copyrightText + "\n\n" +
            generalHeading + "\n\n" +
            tr("New808coin is a decentralized digital currency network powered by "
               "staking and masternodes. New808coin Core provides the full-node wallet, "
               "blockchain validation and network services.") + "\n\n" +
            releaseHeading + "\n\n" +
            tr("- New reward schedule activates at block 1,000,001\n"
               "- Maximum supply capped at 21,000,000 N808\n"
               "- Rewards: 85% masternodes / 15% PoS\n"
               "- Halving every 100,000 blocks with a 0.00000020 N808 floor\n"
               "- Protocol 70966 plus network, security and Qt improvements") +
            "\n\n" +
            upstreamText + "\n\n" +
            licenseText + "\n\n" +
            noticesText;

        const QString aboutHtml =
            version.toHtmlEscaped() + "<br><br>" +
            copyrightText.toHtmlEscaped() + "<br><br>" +
            "<b>" + generalHeading.toHtmlEscaped() + "</b><br><br>" +
            generalText + "<br><br>" +
            "<b>" + releaseHeading.toHtmlEscaped() + "</b><br><br>" +
            releaseText + "<br><br>" +
            upstreamText.toHtmlEscaped() + "<br><br>" +
            licenseText.toHtmlEscaped() + "<br><br>" +
            noticesText.toHtmlEscaped();

        ui->aboutMessage->setTextFormat(Qt::RichText);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->aboutMessage->setText(aboutHtml);
        ui->aboutMessage->setWordWrap(true);
        ui->helpMessage->setVisible(false);
    } else {
        setWindowTitle(tr("Command-line options"));
        QString header = tr("Usage:") + "\n" +
                         "  new808coin-qt [" + tr("command-line options") + "]                     " + "\n";
        QTextCursor cursor(ui->helpMessage->document());
        cursor.insertText(version);
        cursor.insertBlock();
        cursor.insertText(header);
        cursor.insertBlock();

        std::string strUsage = HelpMessage(HMM_BITCOIN_QT);
        strUsage += HelpMessageGroup(tr("UI Options:").toStdString());
        strUsage += HelpMessageOpt("-choosedatadir", strprintf(tr("Choose data directory on startup (default: %u)").toStdString(), DEFAULT_CHOOSE_DATADIR));
        strUsage += HelpMessageOpt("-lang=<lang>", tr("Set language, for example \"de_DE\" (default: system locale)").toStdString());
        strUsage += HelpMessageOpt("-min", tr("Start minimized").toStdString());
        strUsage += HelpMessageOpt("-rootcertificates=<file>", tr("Set SSL root certificates for payment request (default: -system-)").toStdString());
        strUsage += HelpMessageOpt("-splash", strprintf(tr("Show splash screen on startup (default: %u)").toStdString(), DEFAULT_SPLASHSCREEN));
        QString coreOptions = QString::fromStdString(strUsage);
        text = version + "\n" + header + "\n" + coreOptions;

        QTextTableFormat tf;
        tf.setBorderStyle(QTextFrameFormat::BorderStyle_None);
        tf.setCellPadding(2);
        QVector<QTextLength> widths;
        widths << QTextLength(QTextLength::PercentageLength, 35);
        widths << QTextLength(QTextLength::PercentageLength, 65);
        tf.setColumnWidthConstraints(widths);

        QTextCharFormat bold;
        bold.setFontWeight(QFont::Bold);

        Q_FOREACH (const QString &line, coreOptions.split("\n")) {
            if (line.startsWith("  -"))
            {
                cursor.currentTable()->appendRows(1);
                cursor.movePosition(QTextCursor::PreviousCell);
                cursor.movePosition(QTextCursor::NextRow);
                cursor.insertText(line.trimmed());
                cursor.movePosition(QTextCursor::NextCell);
            } else if (line.startsWith("   ")) {
                cursor.insertText(line.trimmed()+' ');
            } else if (line.size() > 0) {
                //Title of a group
                if (cursor.currentTable())
                    cursor.currentTable()->appendRows(1);
                cursor.movePosition(QTextCursor::Down);
                cursor.insertText(line.trimmed(), bold);
                cursor.insertTable(1, 2, tf);
            }
        }

        ui->helpMessage->moveCursor(QTextCursor::Start);
        ui->scrollArea->setVisible(false);
    }
}

HelpMessageDialog::~HelpMessageDialog()
{
    GUIUtil::saveWindowGeometry("nHelpMessageDialogWindow", this);
    delete ui;
}

void HelpMessageDialog::printToConsole()
{
    // On other operating systems, the expected action is to print the message to the console.
    fprintf(stdout, "%s\n", qPrintable(text));
}

void HelpMessageDialog::showOrPrint()
{
#if defined(WIN32)
    // On Windows, show a message box, as there is no stderr/stdout in windowed applications
    exec();
#else
    // On other operating systems, print help text to console
    printToConsole();
#endif
}

void HelpMessageDialog::on_okButton_accepted()
{
    close();
}


/** "Shutdown" window */
ShutdownWindow::ShutdownWindow(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(new QLabel(
        tr("New808coin Core is shutting down...") + "<br /><br />" +
        tr("Do not shut down the computer until this window disappears.")));
    setLayout(layout);
}

void ShutdownWindow::showShutdownWindow(BitcoinGUI* window)
{
    if (!window)
        return;

    // Show a simple window indicating shutdown status
    QWidget* shutdownWindow = new ShutdownWindow();
    // We don't hold a direct pointer to the shutdown window after creation, so use
    // Qt::WA_DeleteOnClose to make sure that the window will be deleted eventually.
    shutdownWindow->setAttribute(Qt::WA_DeleteOnClose);
    shutdownWindow->setWindowTitle(window->windowTitle());

    // Center shutdown window at where main window was
    const QPoint global = window->mapToGlobal(window->rect().center());
    shutdownWindow->move(global.x() - shutdownWindow->width() / 2, global.y() - shutdownWindow->height() / 2);
    shutdownWindow->show();
}

void ShutdownWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
}
