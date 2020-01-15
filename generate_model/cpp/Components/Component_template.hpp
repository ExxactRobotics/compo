#pragma once

{%if PARENT %}
#include "Components/{{PARENT.NAME}}/{{PARENT.NAME}}.hpp"
{%else%}
#include "Components/Component.hpp"
{%endif%}

// TYPE
#include "Data/{{FILE.replace('.yaml','')}}.hpp"

// STRUCT
{% for d in Function.model_get.get_struct_use_by(MAIN, FUNCTION, DATA).keys() %}
#include "Data/Struct_{{d}}.hpp"
{% endfor %}

// INTERFACES
// provide
{% for INTERFACE in PROVIDE %}
#include "Components/{{NAME}}/{{NAME}}_{{INTERFACE.INTERFACE.NAME}}_{{INTERFACE.NAME}}.hpp"
{% endfor %}

// require
{# TODO: replace include by anonyme #}
{% for INTERFACE in REQUIRE %}
#include "Interfaces/{{INTERFACE.INTERFACE.NAME}}/{{INTERFACE.INTERFACE.NAME}}.hpp"
{% endfor %}
{% for INTERFACE in REQUIRE_LIST %}
#include "Interfaces/{{INTERFACE.INTERFACE.NAME}}/{{INTERFACE.INTERFACE.NAME}}.hpp"
{% endfor %}

// SUB COMPONENT  ////////////////////////////////////////////////////////////
{% for sub_component in Function.model_get.get_sub_component_use_by(COMPONENT_INSTANCE).keys() %}
#include "Components/{{sub_component}}/{{sub_component}}.hpp"
{% endfor %}

// SUB CONNECTOR ////////////////////////////////////////////////////////////
{% for sc in CONNECTOR_INSTANCE %}
#include "connectors/{{sc.CONNECTOR.NAME}}.hpp"
{% endfor %}

#include <iostream>

namespace {{NAME}} {

  class {{NAME}} : public  {%if PARENT %}{{PARENT.NAME}}::{{PARENT.NAME}}{%else%}Component{%endif%} {

  public:
  // c++ 11 def
  //! construction
  {{NAME}}();

  //! Copy constructor
  {{NAME}}(const {{NAME}} &other) = delete;

  //! Move constructor
  {{NAME}}({{NAME}} &&other) = delete;

  //! Destructor
  virtual ~{{NAME}}() noexcept;

  //! Copy assignment operator
  {{NAME}}& operator=(const {{NAME}} &other) = delete;

  //! Move assignment operator
  {{NAME}}& operator=({{NAME}} &&other) noexcept = delete;


  // composant initialisation
  {%if PARENT%}
  void configuration() override;
  void connection() override;
  void start() override;
  void stop() override;
  void step() override;
  void status() override;
  {%else%}
  virtual void configuration();
  virtual void connection();
  virtual void start();
  virtual void stop();
  virtual void step();
  virtual void status();
  {%endif%}

  // GET/SET //////////////////////////////////////////////////////////////////
  {% for v in DATA -%}
  // {{v.NAME}}
  {{v.TYPE.NAME}} get_{{v.NAME}}() const;
  void set_{{v.NAME}}(const {{v.TYPE.NAME}}& {{v.NAME}});

  {% endfor %}

  // INTERFACE ////////////////////////////////////////////////////////////////
  // REQUIRES
  {% for req in REQUIRE %}
  void set_{{ req.NAME }}({{ req.INTERFACE.NAME }}*);
  {% endfor %}

  {% for req in REQUIRE %}
  Fake* fake_{{req.NAME}}();
  {% endfor %}

  // REQUIRES LISTS
  {% for req in REQUIRE_LIST %}
  void add_{{ req.NAME }}({{req.INTERFACE.NAME }}*);
  void remove_at_{{ req.NAME }}(int);
  void remove_{{ req.NAME }}({{req.INTERFACE.NAME }}* r);
  {% endfor %}

  // PROVIDES
  {% for pro in PROVIDE %}
  {{ pro.INTERFACE.NAME }}_{{pro.NAME}}& get_{{ pro.NAME }}();
  {% endfor %}

  // FUNCTIONS
  {% for f in FUNCTION %}
  virtual {{f.RETURN.NAME}} {{f.NAME}}(
    {%- for a in f.SIGNATURE -%}
    {{a.TYPE.NAME}} {{a.NAME}}
    {%- if not loop.last%},{% endif -%}
    {%- endfor-%}
    );
  {% endfor %}

  // SUB COMPONENTS
  {% for sc in COMPONENT_INSTANCE %}
  {{ sc.COMPONENT.NAME }}::{{ sc.COMPONENT.NAME }}& get_sc_{{ sc.NAME }}();
  {% endfor %}

  {% for sc in CONNECTOR_INSTANCE %}
  {{ sc.CONNECTOR.NAME }}& get_sc_{{ sc.NAME }}();
  {% endfor %}

  // PACK/UNPACK
  void save(std::ostream& os) const;
  void load(std::istream& is);

 private:

  // INTERFACE ////////////////////////////////////////////////////////////////
  // PROVIDE
  {% for pro in PROVIDE -%}
  {{ pro.INTERFACE.NAME }}_{{pro.NAME}} {{ pro.NAME }};
  {% endfor %}

  // REQUIRE
  {% for req in REQUIRE -%}
  {{ req.INTERFACE.NAME }}* {{ req.NAME }};
  {% endfor %}

  // REQUIRE_LIST
  {% for req in REQUIRE_LIST -%}
  std::vector<{{ req.INTERFACE.NAME }}*> {{ req.NAME }};
  {% endfor %}

  // DATA /////////////////////////////////////////////////////////////////////
  {% for v in DATA -%}
  {{v.TYPE.NAME}} {{v.NAME}};
  {% endfor %}

  // SUB COMPONENT ////////////////////////////////////////////////////////////
  {% for sc in COMPONENT_INSTANCE -%}
  {{ sc.COMPONENT.NAME }}::{{ sc.COMPONENT.NAME }} {{sc.NAME}};
  {% endfor %}

  // SUB CONNECTOR ////////////////////////////////////////////////////////////
  {% for sc in CONNECTOR_INSTANCE %}
  {{ sc.CONNECTOR.NAME }} {{sc.NAME}};
  {% endfor %}
};
}
