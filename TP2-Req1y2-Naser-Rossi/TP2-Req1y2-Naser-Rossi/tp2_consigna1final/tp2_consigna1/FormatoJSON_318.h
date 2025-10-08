#ifndef FORMATO_JSON_318_H
#define FORMATO_JSON_318_H

#include "Formato_318.h"

class FormatoJSON_318 : public Formato_318 {
public:
    std::vector<std::string> convertirACsv(const std::vector<std::string>& datos) override;
    std::string convertirDeCsv(const std::vector<std::string>& datos) override;
};

#endif
