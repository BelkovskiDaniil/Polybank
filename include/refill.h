#ifndef MIPT_BANK__REFIL_H_
#define MIPT_BANK__REFIL_H_

class refill : public imoney_operation{
 public:

  bool execute(big_int receiver_bill_id);

  bool cancel(big_int receiver_bill_id);
};

#endif
