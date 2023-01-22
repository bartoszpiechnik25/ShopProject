/**
 * @file sortwindow.h
 * @author bartoszpiechnik25@gmail.com
 * @brief File containing the SortWindow class definition.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <QDialog>
#include <QStyleFactory>
#include <QCommonStyle>
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SortWindow; }
QT_END_NAMESPACE

/**
 * @brief The SortWindow class
 * This class creates a dialog window for the user to select the sorting criteria and the sorting order.
 */
class SortWindow : public QDialog {
Q_OBJECT
private:
    Ui::SortWindow *ui;
public:
    /**
     * @brief Construct a new Sort Window object
     * @param parent Pointer to the parent widget
     */
    explicit SortWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Sort Window object
     */
    ~SortWindow() override;

    /**
     * @brief Sets the data for the combo box
     * @param data Vector of strings containing the data for the combo box
     */
    void setComboBoxData(const std::vector<std::string> &data);

    /**
     * @brief Overriden close event handler
     * This function is called when the user closes the window. It emits the cancelClicked() signal.
     * @param event Pointer to the close event
     */
    void closeEvent(QCloseEvent *event) override;

public slots:

    /**
     * @brief Slot for the ok button
     * This slot is called when the user clicks the ok button.
     */
    void okClicked();

    /**
     * @brief Slot for the cancel button
     * This slot is called when the user clicks the cancel button.
     */
    void cancelClicked();

signals:

    /**
     * @brief Signal emitted when the user clicks the ok button
     * @param sortDataBy String containing the sorting criteria
     * @param ascending Boolean indicating the sorting order
     */
    void sortDataBy(const std::string &, bool);
};