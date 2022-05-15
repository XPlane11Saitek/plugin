// -*- lsst-c++ -*-
/** Ukraine:
 * Фай реалізаці обєкту який відповідає за 
 * логіку роботи із панелями як із групою.
 * Це глобальний обєкт який обєднує усі панелі.
 * 
 * @file panels.h
 * @brief Global object as panel list
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include "panel.h"
#include <list>
#include <string>

/** Ukraine:
 * Обєкт для групи панелей.
 * Задача обєднувати панелі в один обєкт.
 * Мати можливість працювати із панелями 
 * як із одним обєктом.
 * 
 * @brief group panel
 * 
 */
class Panels : public Panel
{
protected:
    /** Ukraine:
     * Сисок панелей.
     * Обєк типу list 
     * Який зберігає список обєктів.
     * @brief panel list
     * 
     */
    std::list<Panel *> device;

    /** Ukraine:
     * Функція пошуку usb пристроїв.
     * При знаходженні виклиається функція 
     * як задан параметром.
     * 
     * @brief Search usb devices
     * 
     */
    int findUSB(int, int, onFunction);

    /** Ukraine:
     * 
     * @brief 
     * 
     */
    int countBIP;
    int countSW;
    int countRadio;
    int countAP;

public:
    /** Ukraine:
     * Cтворення панелей. 
     * Пошук всіх USB пристроїв.
     * Також створення на базі кожної панелі 
     * індивідальни відповідний обєкт.
     * За допомогою цього методу досягаєтсья 
     * підтримка великої кількості панель.
     * 
     * @brief Construct a new Panels object
     * 
     */
    Panels();

    /** Ukraine:
     * Знищення панелей.
     * @brief Destrutor a exist Panels
     */
    ~Panels();

public:
    /** Ukraine:
     * Зкидання настройок панелі.
     * @brief Reset confugre for panel
     * 
     */
    void Clean();

    /** Ukraine:
     * Загузка нового файлу конфігураці.
     * @brief Configure panel and actions
     * 
     */
    void Load(FileContent *);

    /**
     * @brief Create a Virtual Device object
     * 
     * @return Panel* 
     */
    Panel *CreateVirtualDevice();

public:
    /** Ukraine:
     * Можливість видача списку панель
     * Також можливість пошуку панелі.
     * Можливості доступу до індивідальної 
     * панелі.
     * 
     * @brief Iterator by Panel 
     * 
     * @return std::list<Panel *>::iterator 
     */
    std::list<Panel *>::iterator begin();
    std::list<Panel *>::iterator end();
};

/** Ukraine:
 * Доступ до уже створеного екземпляру класу.
 * 
 * @brief Golobal object of Panel list
 * 
 */
#ifdef XPLANE11PLUGIN
extern Panels device;
#endif
