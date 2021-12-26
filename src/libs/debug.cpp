// -*- lsst-c++ -*-
/** Ukraine:
 * Програмна реалізацуія
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
 * @file debug.cpp
 * @brief function for output information
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include "debug.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <string>
#include <stdarg.h>

#ifdef XPLANE11PLUGIN
#include "XPLMUtilities.h"
#endif

/** Ukraine:
 * Зручний формат для виведення логів.
 * 
 * @brief Debug
 * 
 * @param format 
 * @param ... 
 */
void info(const char *format, ...)
{
   char msg[STR_MESSAGE_SIZE];
   char line[STR_LINE_SIZE];
   va_list args;
   va_start(args, format);
   vsnprintf(msg, STR_MESSAGE_SIZE, format, args);
   va_end(args);
   snprintf(line, STR_LINE_SIZE, "%s(%s) %s: %s\n", PLUGIN_NAME, XPVERSION, PLUGIN_INFO, msg);
   std::cout << line;
#ifdef XPLANE11PLUGIN
   XPLMDebugString(line);
#endif
}

/** Ukraine:
 * Зручний формат для виведення логів.
 * 
 * @brief Debug
 * 
 * @param format 
 * @param ... 
 */
void debug(const char *format, ...)
{
#ifdef DEBUG
   char msg[STR_MESSAGE_SIZE];
   char line[STR_LINE_SIZE];
   va_list args;
   va_start(args, format);
   vsnprintf(msg, STR_MESSAGE_SIZE, format, args);
   va_end(args);
   snprintf(line, STR_LINE_SIZE, "%s(%s) %s: %s\n", PLUGIN_NAME, XPVERSION, PLUGIN_DEBUG, msg);
   std::cout << line;
#ifdef XPLANE11PLUGIN
   XPLMDebugString(line);
#endif
#else
   (void)format;
#endif
}

void warning(const char *format, ...)
{
   char msg[STR_MESSAGE_SIZE];
   char line[STR_LINE_SIZE];
   va_list args;
   va_start(args, format);
   vsnprintf(msg, STR_MESSAGE_SIZE, format, args);
   va_end(args);
   snprintf(line, STR_LINE_SIZE, "%s(%s) %s: %s\n", PLUGIN_NAME, XPVERSION, PLUGIN_WARNING, msg);
   std::cout << line;
#ifdef XPLANE11PLUGIN
   XPLMDebugString(line);
#endif
}

/** Ukraine:
 * Кастомний формат помилок.
 * Даний формат використовую 
 * для стандартизації виводу
 * помилок.
 * 
 * @brief Exeption
 * 
 */
Exception::Exception(const char *format, ...)
{
   va_list args;
   va_start(args, format);
   vsnprintf(this->message, STR_MESSAGE_SIZE, format, args);
   va_end(args);
   snprintf(this->line, STR_LINE_SIZE, "%s(%s) %s: %s\n", PLUGIN_NAME, XPVERSION, PLUGIN_ERROR, this->message);
   std::cout << this->line;
#ifdef XPLANE11PLUGIN
   XPLMDebugString(this->line);
#endif
}

/** Ukraine:
 * Видача тексту помилки.
 * @brief Messages
 * 
 */
const char *Exception::what() const noexcept
{
   return message;
}
