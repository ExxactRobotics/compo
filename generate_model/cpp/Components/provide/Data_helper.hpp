// DATA for {{NAME}}
{%- for v in DATA %}
{{v["TYPE"]["NAME"]}} {{v["NAME"]}};
{%- endfor %}

{% with NAME=PARENT.NAME, DATA=PARENT.DATA, PARENT=PARENT.PARENT%}
{% include "Components/provide/Data_helper.hpp" with context %}
{% endwith %}
