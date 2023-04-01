#ifndef MIPTBANK_BILL_FACTORY_H
#define MIPTBANK_BILL_FACTORY_H

#pragma once
#include "big_int"

class bill_factory {
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
