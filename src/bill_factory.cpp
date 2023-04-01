#include "bill_factory.h"
#include "big_int.h"

int bill_factory::get_bill_kind() const {
  return bill_kind_;
}

big_int bill_factory::get_unique_id() const {
  return unique_id_;
}

big_int bill_factory::get_person_id() const {
  return person_id_;
}