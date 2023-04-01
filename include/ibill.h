#ifndef MIPT_BANK__IBILL_H_
#define MIPT_BANK__IBILL_H_

#include "big_int"

class ibill {
 private:

  int bill_kind_;
  big_int unique_id_;
  big_int person_id_;

 public:

  int get_bill_kind() const;

  big_int get_unique_id() const;

  big_int get_person_id() const;

};

#endif
