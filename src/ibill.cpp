#include "ibill.h"
#include "big_int.h"

int ibill::get_bill_kind() const {
  return bill_kind_;
}

big_int ibill::get_unique_id() const {
  return unique_id_;
}

big_int ibill::get_person_id() const {
  return person_id_;
}