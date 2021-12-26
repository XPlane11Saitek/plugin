// -*- lsst-c++ -*-
/** Ukraine:
 * Зручний формат для виведення логів.
 * - debug - Виведення виключно в режимі дебагу.
 *   Дані повідомлення не виводятися при роботі модуля.
 * 
 * - info  - Запис стрічки в лог файл та на екран
 *   Дані повідомлення мають інфрмаційний характер.
 * 
 * - warning - Запис зауваження.
 *   Дані повідомлення є дуже важливими.
 *   Вони мають критичний характре для роботи модуля
 *   Проте незаважає роботі та виконня уже поставлених
 *     задач.
 * 
 * - error - Немає і викликається через окремий клас помилок.
 * 
 * @file debug.h
 * @brief Main header files
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include "plugin.h"
#include <exception>

/**
 * @brief 
 * 
 */

void debug(const char *, ...);
void info(const char *, ...);
void warning(const char *, ...);

class Exception : public std::exception
{
protected:
    char message[STR_MESSAGE_SIZE];
    char line[STR_LINE_SIZE];

public:
    Exception(const char *, ...);
    const char *what() const noexcept;
};

#define PLUGIN_INFO "INFO"
#define PLUGIN_ERROR "CRITICAL ERROR"
#define PLUGIN_DEBUG "DEBUG"
#define PLUGIN_WARNING "WARNING"
