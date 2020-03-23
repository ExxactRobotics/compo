class {{NAME}}_{{i.NAME}} :  public {{i.D_NAME}} {
 private:
  {{NAME}}* lo;

 public:
  {{NAME}}_{{i.NAME}}({{D_NAME}}* p_lo = NULL):{{i.D_NAME}}(),lo(p_lo){
  }
  // FUNCTION ///////////////////////////////////////////////////////////////
  {% include "Connectors/Logger_Interface_function.hpp" with context %}

  // GET/SET ////////////////////////////////////////////////////////////////
  {% include "Connectors/Logger_Interface_get_set.hpp" with context %}

  // INTERNAL
  {{i.D_NAME}}& get__c() const{return *this->lo->r;}
  std::ostream& get__os() const{ return *this->lo->os;}
};
