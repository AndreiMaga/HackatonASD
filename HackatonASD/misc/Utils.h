#pragma once
#include <string>
class Utils {
public:

    template <typename T>
    static std::string join(const T& vector, const std::string& delim = ",") {
        std::ostringstream s;
        for (const auto& i : vector) {
            if (&i != &vector[0]) {
                s << delim;
            }
            s << i;
        }

        return s.str();
    }
};

