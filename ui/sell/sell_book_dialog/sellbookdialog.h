/**
 * @file sellbookdialog.h
 * @author bartoszpiechnik25@gmail.com
 * @brief File containing the SellBookDialog class definition.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <QDialog>
#include "login.h"
#include "selldialog.h"
#include <algorithm>


QT_BEGIN_NAMESPACE
namespace Ui { class SellBookDialog; }
QT_END_NAMESPACE

/**
 * @brief The SellBookDialog class
 * This class creates a dialog window for the user to sell a book.
 */
class SellBookDialog : public QDialog {
Q_OBJECT
private:
    Ui::SellBookDialog *ui;
    std::vector<long> uniqueIDs;
public:
    /**
     * @brief Construct a new Sell Book Dialog object
     * @param parent Pointer to the parent widget
     */
    explicit SellBookDialog(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Sell Book Dialog object
     */
    ~SellBookDialog() override;

    /**
     * @brief Sets the data for the combo box
     * @param data Vector of strings containing the data for the combo box
     */
    void setID(std::vector<long> &id_) noexcept;

signals:

    /**
     * @brief Signal emitted when the user clicks the ok button
     * @param data Map containing the data entered by the user
     */
    void sendData(std::map<std::string, std::string> &data);

public slots:

    /**
     * @brief Slot for the clear button
     * This slot is called when the user clicks the clear button.
     */
    void clearText();

    /**
     * @brief Slot for the ok button
     * This slot is called when the user clicks the ok button.
     */
    void okClicked();

    /**
     * @brief Slot for the close button
     * This slot is called when the user clicks the close button.
     */
    void closeClicked();
};