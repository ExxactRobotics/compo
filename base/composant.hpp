#pragma once

#include "Types.hpp"

{% for Receptacle in Receptacles %}
class {{ Receptacle.type }};
{% endfor %}

{% for Facette in Facettes %}
class {{ Facette.type }};
{% endfor %}


class {{name}}
{
 public:
  // interface ////////////////////////////////////////////////////////////////

  // Receptacle
  {% for Receptacle in Receptacles %}
  {{ Receptacle.type }} {{ Receptacle.name }};
  {% endfor %}

  // Facette
  {% for Facette in Facettes %}
  {{ Facette.type }} {{ Facettes.name }};
  {% endfor %}

  // c++ 11 def
  //! construction
  {{name}}();

  //! Copy constructor
  {{name}}(const {{name}} &other);

  //! Move constructor
  {{name}}({{name}} &&other) noexcept;

  //! Destructor
  virtual ~{{name}}() noexcept;

  //! Copy assignment operator
  {{name}}& operator=(const {{name}} &other);

  //! Move assignment operator
  {{name}}& operator=({{name}} &&other) noexcept;


  // composant initialisation
  void configuration();

  void connection();

  void start();

  void stop();

  void status();

 private:

 protected:

};
