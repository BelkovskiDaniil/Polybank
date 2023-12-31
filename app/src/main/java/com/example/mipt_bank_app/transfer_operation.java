package com.example.mipt_bank_app;


import android.database.Cursor;

public class transfer_operation extends i_ne_easy_money_operation {
    public transfer_operation(bills_db trans, person_db pdb, operation_db odb) {
        trans_ = trans;
        pdb_ = pdb;
        odb_ = odb;
    }

    @Override
    public void executeTransferOperation(String sender_id, String receiver_bill_id, String money_size, String type) {

        Cursor cursor_bill1 = trans_.get_bill(sender_id, type);
        cursor_bill1.moveToFirst();
        String sender_bill_id = cursor_bill1.getString(1);
        String sender_money = cursor_bill1.getString(3);
        String sender_field_for_bill = cursor_bill1.getString(4);

        Cursor cursor_bill = trans_.get_bill(receiver_bill_id);
        cursor_bill.moveToFirst();
        String receiver_bill_kind = cursor_bill.getString(0);
        String receiver_person_id = cursor_bill.getString(2);
        String receiver_money = cursor_bill.getString(3);
        String receiver_field_for_bill = cursor_bill.getString(4);

        Cursor cursor_person = pdb_.get_person_by_id(sender_id);
        cursor_person.moveToFirst();
        String is_doubtful = cursor_person.getString(8);
        boolean flag = (is_doubtful.equals("1") ? true : false);

        big_int sender_balance_big = new big_int(sender_money);
        big_int receiver_balance_big = new big_int(receiver_money);
        big_int transfer_size = new big_int(money_size);
        big_int money_limit = new big_int(constants.money_limit);

        if (receiver_bill_id != sender_bill_id) {
            if (sender_balance_big.operator_more_or_equal(transfer_size) && (flag && transfer_size.operator_less_or_equal(money_limit) || !flag)) {

                sender_balance_big.operator_minus_equal(transfer_size);
                receiver_balance_big.operator_plus_equal(transfer_size);
                bill_factory bf = new bill_factory();
                i_bill receiver = null;
                i_bill sender = null;
                if (type == constants.BILL_KIND_CREDIT) {
                    big_int sender_field_for_bill_big = new big_int(sender_field_for_bill);
                    big_int receiver_field_for_bill_big = new big_int(receiver_field_for_bill);
                    sender_field_for_bill_big.operator_minus_equal(transfer_size);
                    sender = bf.build_credit(sender_bill_id, sender_id, sender_balance_big.toString(), sender_field_for_bill_big.toString());
                    if (receiver_bill_kind.equals("debit")) {
                        receiver = bf.build_debit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString());
                    } else if (receiver_bill_kind.equals("deposit")) {
                        receiver = bf.build_deposit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString());
                    } else if (receiver_bill_kind.equals("credit")) {
                        receiver_field_for_bill_big.operator_minus_equal(transfer_size);
                        receiver = bf.build_credit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString(), receiver_field_for_bill_big.toString());
                    }
                } else if (type == constants.BILL_KIND_DEBIT) {
                    sender = bf.build_debit(sender_bill_id, sender_id, sender_balance_big.toString());
                    if (receiver_bill_kind.equals("debit")) {
                        receiver = bf.build_debit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString());
                    } else if (receiver_bill_kind.equals("deposit")) {
                        receiver = bf.build_deposit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString());
                    } else if (receiver_bill_kind.equals("credit")) {
                        big_int receiver_field_for_bill_big = new big_int(receiver_field_for_bill);
                        receiver_field_for_bill_big.operator_minus_equal(transfer_size);
                        receiver = bf.build_credit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString(), receiver_field_for_bill_big.toString());
                    }
                } else if (type == constants.BILL_KIND_DEPOSIT) {
                    sender = bf.build_deposit(sender_bill_id, sender_id, sender_balance_big.toString());
                    if (receiver_bill_kind.equals("debit")) {
                        receiver = bf.build_debit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString());
                    } else if (receiver_bill_kind.equals("deposit")) {
                        receiver = bf.build_deposit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString());
                    } else if (receiver_bill_kind.equals("credit")) {
                        big_int receiver_field_for_bill_big = new big_int(receiver_field_for_bill);
                        receiver_field_for_bill_big.operator_minus_equal(transfer_size);
                        receiver = bf.build_credit(receiver_bill_id, receiver_person_id, receiver_balance_big.toString(), receiver_field_for_bill_big.toString());
                    }
                }
                odb_.insertUserData(receiver, transfer_size.toString(), receiver_person_id, constants.TRANSFER, sender_bill_id, receiver_bill_id);
                trans_.updateUserData(receiver);
                trans_.updateUserData(sender);
            }
        }
    }


    @Override
    public void cancelTransferOperation(String sender_bill_id,
                                        String receiver_bill_id,
                                        String money_size, String type) {

        Cursor cursor_sender = trans_.get_bill(sender_bill_id);
        cursor_sender.moveToFirst();
        String bill_kind_sender = cursor_sender.getString(0);
        String person_id_sender = cursor_sender.getString(2);
        String sum_sender = cursor_sender.getString(3);
        String spec_field_sender = cursor_sender.getString(4);

        Cursor cursor_receiver = trans_.get_bill(receiver_bill_id);
        cursor_receiver.moveToFirst();
        String bill_kind_receiver = cursor_receiver.getString(0);
        String person_id_reciver = cursor_receiver.getString(2);
        String sum_receiver = cursor_receiver.getString(3);
        String spec_field_receiver = cursor_receiver.getString(4);


        big_int money_transfer = new big_int(money_size);
        if (!receiver_bill_id.equals(sender_bill_id)) {
            big_int balance_sender = new big_int(sum_sender);
            big_int balance_receiver = new big_int(sum_receiver);
            balance_sender.operator_minus_equal(money_transfer);
            balance_receiver.operator_plus_equal(money_transfer);

            i_bill sender = null;
            i_bill receiver = null;

            bill_factory bf = new bill_factory();
            if (bill_kind_sender.equals(constants.BILL_KIND_DEBIT)) {
                sender = bf.build_debit(sender_bill_id, person_id_sender, balance_sender.toString());
            } else if (bill_kind_sender.equals(constants.BILL_KIND_DEPOSIT)) {
                sender = bf.build_deposit(sender_bill_id, person_id_sender, balance_sender.toString());
            } else if (bill_kind_sender.equals(constants.BILL_KIND_CREDIT)) {
                big_int special_field_big = new big_int(spec_field_sender);
                special_field_big.operator_minus_equal(money_transfer);
                sender = bf.build_credit(sender_bill_id, person_id_sender, balance_sender.toString(), special_field_big.toString());
            }

            if (bill_kind_receiver.equals(constants.BILL_KIND_DEBIT)) {
                receiver = bf.build_debit(receiver_bill_id, person_id_reciver, balance_receiver.toString());
            } else if (bill_kind_receiver.equals(constants.BILL_KIND_DEPOSIT)) {
                receiver = bf.build_deposit(receiver_bill_id, person_id_reciver, balance_receiver.toString());
            } else if (bill_kind_receiver.equals(constants.BILL_KIND_CREDIT)) {
                big_int special_field_big = new big_int(spec_field_receiver);
                special_field_big.operator_minus_equal(money_transfer);
                receiver = bf.build_credit(receiver_bill_id, person_id_reciver, balance_receiver.toString(), special_field_big.toString());
            }

            trans_.updateUserData(sender);
            trans_.updateUserData(receiver);
        }
    }

}
