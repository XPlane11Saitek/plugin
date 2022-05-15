// -*- lsst-c++ -*-
/** Ukraine:
 * Опис класу підтримки BIP
 *
 * @file bip.h
 * @brief BIP Header file
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include "cell.h"
#include "panel.h"
#include <cstring>
#include "spec.h"
#include "BIPForm.h"

/** Ukraine
 * Підтриммка пристою
 * @brief Support BIP
 * 
 */
class BIP : public Panel, public BIPForm
{
protected: // usb
    /** Ukraine:
     * індикація панелі.
     * @brief 
     */
    SingleLED *led[BIP_CELL_COUNT];
    /**
     * @brief USB Buffer
     */
    BIPSetFeature rawDisplay;
    /** 
     * @brief 
     */
    unsigned int step;

protected:
    /** Ukraine:
     * Виставлення панелі в певний режим
     * @brief step
     */
    void set(int);

    /** Ukraine:
     * Провірка коректності налаштувань панелі.
     * @brief check 
     */
    void check();

public:
    /** Ukraine:
     * Створення панелі.
     * @brief Construct a new BIP object
     */
    BIP(hid_device *, const wchar_t *, int);

    /** Ukraine:
     * Зупинка та виділення памяті.
     * @brief Destroy the BIP object
     */
    ~BIP();

    /** Ukraine:
     * Робоча процедура.
     * @brief steps
     */
    void Reload();

    /** Ukraine:
     * Очистака конфігурації
     * @brief Reset configure
     */
    void Clear();

    /** Ukraine:
     * Загрузка нової конфігурації.
     * @brief Load Configure
     */
    void Load(FileContent *);

    /**
     * @brief 
     * 
     */
    int GetPanelID(char *);
};
