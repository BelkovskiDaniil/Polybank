#ifndef MIPT_BANK__IMPNEY_OPERATION_H_
#define MIPT_BANK__IMPNEY_OPERATION_H_

class imoney_operation {
 public:

  virtual bool execute(big_int receiver_bill_id) = 0;

  virtual bool cancel(big_int receiver_bill_id) = 0;

  virtual bool execute_transfer(big_int send_bill_id, big_int receiver_bill_id) = 0;

  virtual bool cancel_transfer(big_int send_bill_id, big_int receiver_bill_id) = 0;
};

#endif