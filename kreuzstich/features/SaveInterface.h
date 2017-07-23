#ifndef SAVEINTERFACE_H
#define SAVEINTERFACE_H

namespace KreuzstichGUI {

    class SaveInterface {
    public:
        virtual bool save() = 0;
        virtual bool saveAs() = 0;

        void setModified(bool);

    private:

    };


}

#endif // SAVEINTERFACE_H
