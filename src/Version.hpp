#ifndef VERSION_HPP
#define VERSION_HPP

// STL
#include <ctime>

// Qt
#include <QString>
#include <QWidget>
#include <QAction>
#include <QLabel>

class Version {
public:
    /**
     * Return a full version string
     */
    static QString getVersionString();

    /**
     * Replace placeholders with the values of the corresponding variables.
     *
     * A placeholder is the text "$VAR$" where VAR is one of the following:
     * - any variable defined in VersionDefs
     * - VERSION_STR (replaced by the result of getVersionString)
     *
     * @param str String to modify (in-place)
     */
    static QString replaceVars(QString& str);

    /**
     * @copydoc replaceVars(QString&)
     * @param win Widget - call replaceVars on specific properties of the widget
     */
    static void replaceVars(QWidget* win);

    /**
     * @copydoc replaceVars(QString&)
     * @param action Action Widget - call replaceVars on specific properties of the widget
     */
    static void replaceVars(QAction* action);

    /**
     * @copydoc replaceVars(QString&)
     * @param label Label Widget - call replaceVars on specific properties of the widget
     */
    static void replaceVars(QLabel* label);
};


#endif // VERSION_HPP
