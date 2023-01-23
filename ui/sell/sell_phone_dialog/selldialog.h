/**
 * @file selldialog.h
 * @author bartoszpiechnik25@gmail.com
 * @brief File containing the SellDialog class definition.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <QDialog>
#include <algorithm>
#include <regex>
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SellDialog; }
QT_END_NAMESPACE

/**
 * @brief The SellDialog class
 * This class creates a dialog window for the user to sell a phone.
 */
class SellDialog : public QDialog {
Q_OBJECT
private:
    Ui::SellDialog *ui;
    std::vector<long> uniqueIDs;
public:
    /**
     * @brief Construct a new Sell Dialog object
     * @param parent Pointer to the parent widget
     */
    explicit SellDialog(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Sell Dialog object
     */
    ~SellDialog() override;

    /**
     * @brief Sets the data for the combo box
     * @param data Vector of IDs.
     */
    void setID(std::vector<long> &id_) noexcept;
    static bool isValidNumber(const std::string& text) noexcept;

signals:

    /**
     * @brief Signal emitted when the user clicks the ok button
     * @param data std::map containing the data entered by the user
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