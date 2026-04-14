#ifndef MOCKUP_ISTANDARDPATH_HPP
#define MOCKUP_ISTANDARDPATH_HPP

#include "../../MockupBase.hpp"

#include "creator/files/IStandardPaths.hpp"

class Mockup_IStandardPaths: public MockupBase, public IStandardPaths {
public:
    // MockupBase
    void SetUp() override;

    // IStandardPaths
    QStringList standardLocations(QStandardPaths::StandardLocation location) override;
    QString writableLocation(QStandardPaths::StandardLocation location) override;

private:
    QString m_root;
};

#endif // MOCKUP_ISTANDARDPATH_HPP
