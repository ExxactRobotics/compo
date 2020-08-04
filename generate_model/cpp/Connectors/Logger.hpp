#pragma once

#include <iostream>

{% set i = MAIN.INTERFACES[INTERFACE] %}
#include "Interfaces/{{i.F_NAME}}/{{i.NAME}}.hpp"
#include "Components/Component.hpp"

{% include "helper/namespace_open.hpp" with context %}
class {{NAME}};

{% include "Connectors/Logger_Interface.hpp" with context %}

class {{NAME}} {
 public:

  {{NAME}}(std::ostream& p_os = std::cout):os(&p_os)
            {%for r in REQUIRE %},{{r.NAME}}(NULL){%endfor%}
            {%for p in PROVIDE %},{{p.NAME}}(this){%endfor%}
             {}

 std::ostream& get_os() {return *this->os;}

 private:
 std::ostream* os = NULL;
 {%include "provide_require.hpp" with context%}
};
{% include "helper/namespace_close.hpp" with context %}
