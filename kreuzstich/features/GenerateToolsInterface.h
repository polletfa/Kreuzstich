#ifndef GENERATETOOLSINTERFACE_H
#define GENERATETOOLSINTERFACE_H

namespace KreuzstichGUI {

    class GenerateToolsInterface {
    public:
        virtual void generateGrid() = 0;
        virtual void generateScriptAsText() = 0;
        virtual void generateScriptAsLaTeX() = 0;

    private:
    };


}

#endif // GENERATETOOLSINTERFACE_H
