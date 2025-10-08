
#ifndef FORMATO_CSV_318_H
#define FORMATO_CSV_318_H

#include "Formato_318.h"

class FormatoCSV_318 : public Formato_318 {
public:
    std::vector<std::string> convertirACsv(const std::vector<std::string>& datos) override;
    std::string convertirDeCsv(const std::vector<std::string>& datos) override;
};

#endif
