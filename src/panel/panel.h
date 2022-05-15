// -*- lsst-c++ -*-
/** Ukraine:
 * Віртуальна панелі.
 *
 * @file panel.h
 * @brief Virtual panel
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#ifndef PANELFILE
#define PANELFILE

#include "spec.h"
#include "content.h"
#include "hidapi.h"
#include "form.h"

#ifdef XPLANE11PLUGIN
#include "XPLMDefs.h"
#endif

enum State
{
    init,
    loaded,
    run
};

/** Ukraine:
 * Віртуальна панель.
 * Віатальний клас для наслідування.
 * Всі панелі повинні наслідувати даний клас.
 * Драйвер почергово опрацює всі панелі.
 */
class Panel : public virtual PanelForm
{
protected:
    hid_device *panelUSBDevAddr;         // USB ADDRESS
    wchar_t panelSN[MAX_USB_HEADER_STR]; // Serial number
    int panelNumber;                     // UUID
    State state;                         // Panel status

protected:
    /** Ukraine:
     * Створення панелі відповідного типу. 
     * @brief Create object 
     * 
     * @return Panel* 
     */
    Panel *createPanelBIP(hid_device *, const wchar_t *, int);
    Panel *createPanelSW(hid_device *, const wchar_t *, int);
    Panel *createPanelRadio(hid_device *, const wchar_t *, int);
    Panel *createPanelMULTI(hid_device *, const wchar_t *, int);

    /** Ukraine:
     * Конструктор для глобального оєкту.
     * @brief Construct a new Panel object
     * 
     */
    Panel();

public:
    /** Ukraine:
     * Створення панелі. 
     * Конструктор класу.
     * 
     * @param 0 Адрес пристрою 
     * @param 1 серійний номер
     * @param 2 номер панелі
     * 
     * @brief Construct a new Panel object
     * 
     */
    Panel(hid_device *, const wchar_t *, int);

    /** Ukraine:
     * Віртуальний деструктор класу.
     * В цьому блоці повино вивільнити память
     * Вимкнути панель.
     * 
     * @brief Destroy the Panel object
     * 
     */
    virtual ~Panel(){};

    /** Ukraine:
     * Потрібно оновити статс 
     *   
     * @brief Refresh panel status
     * 
     */
    virtual void Reload(){};

    /** Ukraine:
     * Обнуляємо панель.
     * Виключаємо її.
     * 
     * @brief Reset configuration by panel
     * 
     */
    virtual void Clear(){};

    /** Ukraine:
     * Загружаємо новий стан панелі.
     * 
     * @brief Загружаємо поведіну панелі.
     * 
     */
    virtual void Load(FileContent *){};

    /**
     * @brief 
     * 
     */
    virtual int GetPanelID(char *);
};

/** Ukraine:
 * onFunction = Panel *(Panel::*)(hid_device *, const wchar_t *, int)
 * Чисто формально = тип функція. У нашому випадку метод класу.
 * В даному випадку задає універсальний формат
 * 
 * @brief function/method creation panels
 * 
 */
typedef Panel *(Panel::*onFunction)(hid_device *, const wchar_t *, int);

#endif
