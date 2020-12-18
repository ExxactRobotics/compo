#pragma once

#include "Structs/User.hpp"

#include <memory>

class User_builder {

public:
  User_builder();
  virtual ~User_builder();

  // setter

  User_builder &set_id(const i32 &p_id);

  User_builder &set_first_name(const CompoMe::String &p_first_name);

  User_builder &set_last_name(const CompoMe::String &p_last_name);

  User_builder &set_score(const double &p_score);

  User_builder &set_profile_img(const File &p_profile_img);

  // build
  User build();
  User *build_p();
  std::shared_ptr<User> build_sp();

protected:
  void asign(User &p_name);

private:
  i32 id;

  CompoMe::String first_name;

  CompoMe::String last_name;

  double score;

  File profile_img;
};